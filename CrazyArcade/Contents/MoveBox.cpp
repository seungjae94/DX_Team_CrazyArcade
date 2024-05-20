#include "PreCompile.h"
#include "MoveBox.h"

#include "MainPlayLevel.h"
#include "MapConstant.h"
#include "MapBase.h"

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
		}
	);

	State.SetStartFunction(BlockState::destroy, [=] 
		{
			GetBody()->ChangeAnimation(MapAnim::block_destroy);
		}
	);

	// State Update
	State.SetUpdateFunction(BlockState::move, [=](float _DeltaTime)
		{
			MoveUpdate(_DeltaTime);
		}
	);

	State.SetUpdateFunction(BlockState::destroy, [=](float _DeltaTime)
		{
			if (true == GetBody()->IsCurAnimationEnd() || false == GetBody()->IsActive())
			{
				FPoint CurPoint = AMapBase::ConvertLocationToPoint(GetActorLocation());
				if (nullptr == PlayLevel->GetMap()->GetTileInfo(CurPoint).Item)
				{
					PlayLevel->GetMap()->CreateItem(CurPoint, GetSpawnItemType());
				}

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

			PlayLevel->GetMap()->GetTileInfo(CurPoint).Block = this;
			PlayLevel->GetMap()->GetTileInfo(PrevPoint).Block = nullptr;
			
			if (nullptr != PlayLevel->GetMap()->GetTileInfo(CurPoint).Bush)
			{
				GetBody()->SetActive(false);
			}
			else
			{
				GetBody()->SetActive(true);
			}
		}
	);
}

void AMoveBox::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
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

	IsMoveValue = true;
}

void AMoveBox::MoveUpdate(float _DeltaTime)
{
	if (true == IsMoveValue)
	{
		MoveTime += 3.5f * _DeltaTime;
		FVector NextPos = FVector::LerpClamp(StartPos, TargetPos, MoveTime);
		SetActorLocation(NextPos);

		GetBody()->SetOrder(AMapBase::GetRenderOrder(GetActorLocation()));

		if (1.0f < MoveTime)
		{
			MoveTime = 0.0f;
			IsMoveValue = false;
			State.ChangeState(BlockState::idle);
			return;
		}
	}
}

