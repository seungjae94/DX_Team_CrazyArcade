#include "PreCompile.h"
#include "MoveBox.h"

#include "MainPlayLevel.h"
#include "MapConstant.h"
#include "ItemBase.h"
#include "MapBase.h"
#include "Player.h"

#include "Packets.h"
#include "CrazyArcadeCore.h"
#include "ServerManager.h"

AMoveBox::AMoveBox()
{
}

AMoveBox::~AMoveBox()
{
}

void AMoveBox::BeginPlay()
{
	Super::BeginPlay();

	if (false == IsNetInit())
	{
		if (nullptr != UCrazyArcadeCore::Net)
		{
			InitNet(UCrazyArcadeCore::Net);
		}
	}

	UCrazyArcadeCore::NetManager.SetCommonToken(this);

	USpawnItemBlock::SetBlock(this);
	SetBlockType(EBlockType::MoveBox);
}

void AMoveBox::StateInit()
{
	Super::StateInit();
	 
	// State Create
	State.CreateState(BlockState::move);
	State.CreateState(BlockState::destroy);

	// State Start
	State.SetStartFunction(BlockState::move, [=]
		{
			FPoint CurPoint = AMapBase::ConvertLocationToPoint(GetActorLocation());
			FPoint NextPoint = CurPoint;

			if (0.0f < MoveDir.X)
			{
				NextPoint.X += 1;
			}
			else if (0.0f > MoveDir.X)
			{
				NextPoint.X -= 1;
			}
			else if (0.0f < MoveDir.Y)
			{
				NextPoint.Y += 1;
			}
			else if (0.0f > MoveDir.Y)
			{
				NextPoint.Y -= 1;
			}

			if (true == AMapBase::MapRangeCheckByPoint(NextPoint))
			{
				PlayLevel->GetMap()->GetTileInfo(NextPoint).Block = this;
			}
		}
	);

	State.SetStartFunction(BlockState::destroy, [=] 
		{
			FPoint CurPoint = AMapBase::ConvertLocationToPoint(GetActorLocation());
			for (size_t Y = 0; Y < PlayLevel->GetMap()->TileInfo.size(); Y++)
			{
				for (size_t X = 0; X < PlayLevel->GetMap()->TileInfo[Y].size(); X++)
				{
					FPoint Point = { static_cast<int>(X), static_cast<int>(Y) };
					if (Point != CurPoint && PlayLevel->GetMap()->TileInfo[Y][X].Block == this)
					{
						PlayLevel->GetMap()->TileInfo[Y][X].Block = nullptr;
					}
				}
			}

			GetBody()->ChangeAnimation(MapAnim::block_destroy);
		}
	);

	// State Update
	State.SetUpdateFunction(BlockState::move, [=](float _DeltaTime)
		{
			MoveUpdate(_DeltaTime);

			FPoint CurPoint = AMapBase::ConvertLocationToPoint(GetActorLocation());
			if (true == AMapBase::MapRangeCheckByPoint(CurPoint) && nullptr == PlayLevel->GetMap()->GetTileInfo(CurPoint).Bush)
			{
				GetBody()->SetActive(true);
			}
		}
	);

	State.SetUpdateFunction(BlockState::destroy, [=](float _DeltaTime)
		{
			if (true == GetBody()->IsCurAnimationEnd() || false == GetBody()->IsActive())
			{
				FPoint CurPoint = AMapBase::ConvertLocationToPoint(GetActorLocation());
				PlayLevel->GetMap()->CreateItem(CurPoint, GetSpawnItemType());

				PlayLevel->GetMap()->GetTileInfo(CurPoint).Block = nullptr;

				Destroy();
			}
		}
	);

	// State End
	State.SetEndFunction(BlockState::move, [=]
		{
			FPoint CurPoint = AMapBase::ConvertLocationToPoint(GetActorLocation());
			FPoint PrevPoint = CurPoint;

			if (0.0f < MoveDir.X)
			{
				PrevPoint.X -= 1;
			}
			else if (0.0f > MoveDir.X)
			{
				PrevPoint.X += 1;
			}
			else if (0.0f < MoveDir.Y)
			{
				PrevPoint.Y -= 1;
			}
			else if (0.0f > MoveDir.Y)
			{
				PrevPoint.Y += 1;
			}

			if (true == AMapBase::MapRangeCheckByPoint(CurPoint))
			{
				if (nullptr != PlayLevel->GetMap()->GetTileInfo(CurPoint).Bush)
				{
					GetBody()->SetActive(false);
				}

				if (nullptr != PlayLevel->GetMap()->GetTileInfo(CurPoint).Item)
				{
					PlayLevel->GetMap()->GetTileInfo(CurPoint).Item->Destroy();
					PlayLevel->GetMap()->GetTileInfo(CurPoint).Item = nullptr;
				}

				PlayLevel->GetMap()->GetTileInfo(PrevPoint).Block = nullptr;
			}

			DelayCallBack(0.25f, [=] { CanMoveValue = true; });
		}
	);

}

void AMoveBox::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	ProtocolTick([=](std::shared_ptr<UEngineProtocol> _Packet)
		{
			std::shared_ptr<UBlockUpdatePacket> UpdatePacket = std::dynamic_pointer_cast<UBlockUpdatePacket>(_Packet);
			bool IsMove = UpdatePacket->IsMoveValue;
			if (true == IsMove)
			{
				RecvMoveCheck(UpdatePacket->Pos, UpdatePacket->MoveDir);
			}

			bool IsDestroy = UpdatePacket->IsDestroy;
			if (true == IsDestroy && BlockState::destroy != State.GetCurStateName())
			{
				State.ChangeState(BlockState::destroy);
				return;
			}
		}
	);
}

void AMoveBox::SetMoveState(const FVector& _Dir)
{
	if (false == CanMoveValue)
	{
		return;
	}

	FVector CurPos = GetActorLocation();
	FPoint NextPoint = AMapBase::ConvertLocationToPoint(CurPos);

	if (0.0f < _Dir.X)
	{
		NextPoint.X += 1;
	}
	else if (0.0f > _Dir.X)
	{
		NextPoint.X -= 1;
	}
	else if (0.0f < _Dir.Y)
	{
		NextPoint.Y += 1;
	}
	else if (0.0f > _Dir.Y)
	{
		NextPoint.Y -= 1;
	}

	for (size_t i = 0; i < PlayLevel->GetMap()->AllPlayer.size(); i++)
	{
		APlayer* Player = PlayLevel->GetMap()->AllPlayer[i];

		if (nullptr == Player || (true == Player->GetIsDead() && false == Player->GetRenderer()->IsActive()))
		{
			continue;
		}

		FVector PlayerPos = Player->GetActorLocation();
		FPoint PlayerPoint = AMapBase::ConvertLocationToPoint(PlayerPos);

		if (NextPoint == PlayerPoint)
		{
			return;
		}
	}

	MoveDir = _Dir;
	MoveOneBlockCheckSend();
	State.ChangeState(BlockState::move);
}

void AMoveBox::MoveOneBlockCheckSend()
{
	StartPos = GetActorLocation();
	TargetPos = GetActorLocation();

	if (0.0f < MoveDir.X)
	{
		TargetPos.X += AMapBase::GetBlockSize();
	}
	else if (0.0f > MoveDir.X)
	{
		TargetPos.X -= AMapBase::GetBlockSize();
	}
	else if (0.0f < MoveDir.Y)
	{
		TargetPos.Y += AMapBase::GetBlockSize();
	}
	else if (0.0f > MoveDir.Y)
	{
		TargetPos.Y -= AMapBase::GetBlockSize();
	}

	CanMoveValue = false;
	IsMoveValue = true;

	std::shared_ptr<UBlockUpdatePacket> Packet = std::make_shared<UBlockUpdatePacket>();
	Packet->MoveDir = MoveDir;
	Packet->IsMoveValue = IsMoveValue;
	Packet->Pos = GetActorLocation();
	Send(Packet);
}

void AMoveBox::MoveOneBlockCheckRecv()
{
	FPoint CurPoint = AMapBase::ConvertLocationToPoint(GetActorLocation());
	FVector CurPos = AMapBase::ConvertPointToLocation(CurPoint);

	CurPos.X -= AMapBase::BlockSize * 0.5f;
	CurPos.Y -= AMapBase::BlockSize * 0.5f;

	StartPos = CurPos;
	TargetPos = CurPos;

	if (0.0f < MoveDir.X)
	{
		TargetPos.X += AMapBase::GetBlockSize();
	}
	else if (0.0f > MoveDir.X)
	{
		TargetPos.X -= AMapBase::GetBlockSize();
	}
	else if (0.0f < MoveDir.Y)
	{
		TargetPos.Y += AMapBase::GetBlockSize();
	}
	else if (0.0f > MoveDir.Y)
	{
		TargetPos.Y -= AMapBase::GetBlockSize();
	}

	CanMoveValue = false;
	IsMoveValue = true;
	State.ChangeState(BlockState::move);
}

void AMoveBox::MoveUpdate(float _DeltaTime)
{
	if (true == IsMoveValue)
	{
		MoveTimeCount += 3.5f * _DeltaTime;
		FVector NextPos = FVector::LerpClamp(StartPos, TargetPos, MoveTimeCount);
		SetActorLocation(NextPos);

		if (0.0f < MoveDir.Y)
		{
			NextPos.Y += AMapBase::GetBlockSize() * 0.5f;
		}

		GetBody()->SetOrder(AMapBase::GetRenderOrder(NextPos));

		if (1.0f < MoveTimeCount)
		{
			MoveTimeCount = 0.0f;
			IsMoveValue = false;
			State.ChangeState(BlockState::idle);
			return;
		}
	}
}

// 패킷 관련
void AMoveBox::RecvMoveCheck(const FVector& _Pos, const FVector& _MoveDir)
{
	SetActorLocation(_Pos);

	if (BlockState::move == State.GetCurStateName())
	{
		for (size_t Y = 0; Y < PlayLevel->GetMap()->TileInfo.size(); Y++)
		{
			for (size_t X = 0; X < PlayLevel->GetMap()->TileInfo[Y].size(); X++)
			{
				if (PlayLevel->GetMap()->TileInfo[Y][X].Block == this)
				{
					PlayLevel->GetMap()->TileInfo[Y][X].Block = nullptr;
				}
			}
		}
	}

	MoveDir = _MoveDir;
	MoveOneBlockCheckRecv();
}
