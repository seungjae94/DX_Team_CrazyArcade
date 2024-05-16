#include "PreCompile.h"
#include "MoveBox.h"

#include "MainPlayLevel.h"
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

	StateInit();
	SetBlockType(EBlockType::MoveBox);
	State.ChangeState("Idle");
}

void AMoveBox::StateInit()
{
	// State Create
	State.CreateState("Idle");
	State.CreateState("Move");

	// State Start
	State.SetStartFunction("Idle", [=] {});
	State.SetStartFunction("Move", [=] 
		{
			MoveOneBlockCheck();
		}
	);

	// State Update
	State.SetUpdateFunction("Idle", [=](float _DeltaTime) {});
	State.SetUpdateFunction("Move", [=](float _DeltaTime)
		{
			MoveUpdate(_DeltaTime);
		}
	);

	// State End
	State.SetEndFunction("Move", [=]
		{
			FPoint CurPoint = PlayLevel->GetMap()->CovertLocationToPoint(GetActorLocation());
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

	State.Update(_DeltaTime);
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

		GetBody()->SetOrder(PlayLevel->GetMap()->GetRenderOrder(GetActorLocation()));

		if (1.0f < MoveTime)
		{
			MoveTime = 0.0f;
			IsMoveValue = false;
			State.ChangeState("Idle");
			return;
		}
	}
}

