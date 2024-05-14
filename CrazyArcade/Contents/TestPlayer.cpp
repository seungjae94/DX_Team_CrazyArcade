#include "PreCompile.h"
#include "TestPlayer.h"

#include "MainPlayLevel.h"
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

	AMainPlayLevel* PlayLevel = dynamic_cast<AMainPlayLevel*>(GetWorld()->GetGameMode().get());
	GetRenderer()->SetOrder(PlayLevel->GetMap()->GetRenderOrder(GetActorLocation()));

	{
		std::string Msg = std::format("PlayerPos : {}\n", GetActorLocation().ToString());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}
}

void ATestPlayer::KeyMove(float _DeltaTime, FVector _Dir, float _Speed)
{

}
