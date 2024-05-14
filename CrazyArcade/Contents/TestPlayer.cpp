#include "PreCompile.h"
#include "TestPlayer.h"

#include "MapTestLevel.h"
#include "MapBase.h"

ATestPlayer::ATestPlayer()
{
}

ATestPlayer::~ATestPlayer()
{
}

void ATestPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void ATestPlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	{
		std::string Msg = std::format("PlayerPos : {}\n", GetActorLocation().ToString());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}
}

void ATestPlayer::KeyMove(float _DeltaTime, FVector _Dir, float _Speed)
{
	AMapTestLevel* PlayLevel = dynamic_cast<AMapTestLevel*>(GetWorld()->GetGameMode().get());
	AMapBase* Map = PlayLevel->GetMap().get();
	FVector NextPos = GetActorLocation() + FVector(_DeltaTime * _Speed * _Dir.X, _DeltaTime * _Speed * _Dir.Y, 0.0f);
	bool CanMove = Map->CanMovePos(NextPos, _Dir);

	if (true == CanMove)
	{
		APlayer::KeyMove(_DeltaTime, _Dir, _Speed);
	}
}
