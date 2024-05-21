#include "PreCompile.h"
#include "MoveBox.h"

#include "MainPlayLevel.h"
#include "MapConstant.h"
#include "ItemBase.h"
#include "MapBase.h"

#include "Packets.h"

AMoveBox::AMoveBox()
{
}

AMoveBox::~AMoveBox()
{
}

void AMoveBox::BeginPlay()
{
	Super::BeginPlay();

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
			MoveOneBlockCheck();

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

			PlayLevel->GetMap()->GetTileInfo(NextPoint).Block = this;
		}
	);

	State.SetStartFunction(BlockState::destroy, [=] 
		{
			CheckNearDestroy(AMapBase::ConvertLocationToPoint(GetActorLocation()));
			GetBody()->ChangeAnimation(MapAnim::block_destroy);
		}
	);

	// State Update
	State.SetUpdateFunction(BlockState::move, [=](float _DeltaTime)
		{
			MoveUpdate(_DeltaTime);

			//ProtocolTick([=](std::shared_ptr<UEngineProtocol> _Packet) 
			//	{
			//		std::shared_ptr<USpawnUpdatePacket> UpdatePacket = std::dynamic_pointer_cast<USpawnUpdatePacket>(_Packet);
			//		SetActorLocation(UpdatePacket->Pos);
			//	}
			//);

			FPoint CurPoint = AMapBase::ConvertLocationToPoint(GetActorLocation());
			if (nullptr == PlayLevel->GetMap()->GetTileInfo(CurPoint).Bush)
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

			if (nullptr != PlayLevel->GetMap()->GetTileInfo(CurPoint).Bush)
			{
				GetBody()->SetActive(false);
			}

			if (nullptr != PlayLevel->GetMap()->GetTileInfo(CurPoint).Item)
			{
				PlayLevel->GetMap()->GetTileInfo(CurPoint).Item->Destroy();
			}

			PlayLevel->GetMap()->GetTileInfo(PrevPoint).Block = nullptr;

			DelayCallBack(0.25f, [=] { CanMoveValue = true; });
		}
	);

}

void AMoveBox::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AMoveBox::SetMoveState(const FVector& _Dir)
{
	if (false == CanMoveValue)
	{
		return;
	}

	MoveDir = _Dir;
	State.ChangeState(BlockState::move);
}

void AMoveBox::MoveOneBlockCheck()
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

void AMoveBox::CheckNearDestroy(FPoint _CurPoint)
{
	FPoint UpPoint = { _CurPoint.X, _CurPoint.Y + 1 };
	if (true == AMapBase::MapRangeCheckByPoint(UpPoint)
	&&	this == PlayLevel->GetMap()->GetTileInfo(UpPoint).Block)
	{
		PlayLevel->GetMap()->GetTileInfo(UpPoint).Block = nullptr;
	}

	FPoint DownPoint = { _CurPoint.X, _CurPoint.Y - 1 };
	if (true == AMapBase::MapRangeCheckByPoint(DownPoint)
	&&	this == PlayLevel->GetMap()->GetTileInfo(DownPoint).Block)
	{
		PlayLevel->GetMap()->GetTileInfo(DownPoint).Block = nullptr;
	}

	FPoint LeftPoint = { _CurPoint.X - 1, _CurPoint.Y };
	if (true == AMapBase::MapRangeCheckByPoint(LeftPoint)
	&&	this == PlayLevel->GetMap()->GetTileInfo(LeftPoint).Block)
	{
		PlayLevel->GetMap()->GetTileInfo(LeftPoint).Block = nullptr;
	}

	FPoint RightPoint = { _CurPoint.X + 1, _CurPoint.Y };
	if (true == AMapBase::MapRangeCheckByPoint(RightPoint)
	&&	this == PlayLevel->GetMap()->GetTileInfo(RightPoint).Block)
	{
		PlayLevel->GetMap()->GetTileInfo(RightPoint).Block = nullptr;
	}
}
