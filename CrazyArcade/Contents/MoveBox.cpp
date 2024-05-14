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

	SetBlockType(EBlockType::MoveBox);
}

void AMoveBox::StateInit()
{
}

void AMoveBox::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	
	MoveUpdate(_DeltaTime);
}

void AMoveBox::MoveOneBlockCheck(const FVector& _Dir)
{
	if (true == IsMoveValue)
	{
		return;
	}

	StartPos = GetActorLocation();
	TargetPos = GetActorLocation();

	if (0.0f < _Dir.X)
	{
		TargetPos.X += AMapBase::GetBlockSize();
	}
	else if (0.0f > _Dir.X)
	{
		TargetPos.X -= AMapBase::GetBlockSize();
	}
	else if (0.0f < _Dir.Y)
	{
		TargetPos.Y += AMapBase::GetBlockSize();
	}
	else if (0.0f > _Dir.Y)
	{
		TargetPos.Y -= AMapBase::GetBlockSize();
	}

	//AMainPlayLevel* PlayLevel = dynamic_cast<AMainPlayLevel*>(GetWorld()->GetGameMode().get());
	//PlayLevel->GetMap()->CanMovePos()

	IsMoveValue = true;
}

void AMoveBox::MoveUpdate(float _DeltaTime)
{
	if (true == IsMoveValue)
	{
		MoveTime += 3.5f * _DeltaTime;
		FVector NextPos = FVector::LerpClamp(StartPos, TargetPos, MoveTime);
		SetActorLocation(NextPos);

		AMainPlayLevel* PlayLevel = dynamic_cast<AMainPlayLevel*>(GetWorld()->GetGameMode().get());
		GetBody()->SetOrder(PlayLevel->GetMap()->GetRenderOrder(GetActorLocation()));

		if (1.0f < MoveTime)
		{
			MoveTime = 0.0f;
			IsMoveValue = false;
		}
	}
}

