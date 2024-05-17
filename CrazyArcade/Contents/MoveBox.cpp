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

	PlayLevel = dynamic_cast<AMainPlayLevel*>(GetWorld()->GetGameMode().get());

	SetBlockType(EBlockType::MoveBox);
}

void AMoveBox::StateInit()
{
	Super::StateInit();
	 
	// State Create
	State.CreateState(MoveBoxState::move);

	// State Start
	State.SetStartFunction(MoveBoxState::move, [=]
		{
			MoveOneBlockCheck();
		}
	);

	// State Update
	State.SetUpdateFunction(MoveBoxState::move, [=](float _DeltaTime)
		{
			MoveUpdate(_DeltaTime);
		}
	);

	// State End
	State.SetEndFunction(MoveBoxState::move, [=]
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

			PlayLevel->GetMap()->SetMapBlock({ CurPoint.X, CurPoint.Y }, PlayLevel->GetMap()->GetMapBlock({ PrevPoint.X, PrevPoint.Y }));
			PlayLevel->GetMap()->SetMapBlock({ PrevPoint.X, PrevPoint.Y }, nullptr);
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
			State.ChangeState(BlockBaseState::idle);
			return;
		}
	}
}

