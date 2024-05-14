#include "PreCompile.h"
#include "LobbyTitleGameMode.h"

ALobbyTitleGameMode::ALobbyTitleGameMode()
{
}

ALobbyTitleGameMode::~ALobbyTitleGameMode()
{
}

void ALobbyTitleGameMode::BeginPlay()
{
	Super::BeginPlay();

	{
		LobbyBackGround = CreateWidget<UImage>(GetWorld(), "LobbyBackGround");
		LobbyBackGround->SetSprite("Lobby.png");
		LobbyBackGround->AddToViewPort(1);
		LobbyBackGround->SetAutoSize(1.0f, true);
		LobbyBackGround->SetWidgetLocation({0.0f, 0.0f, 0.0f, 0.0f});

		Button_GameStart = CreateWidget<UImage>(GetWorld(), "Button_GameStart");
		Button_GameStart->SetSprite("Button_GameStart_Unhover.png");
		Button_GameStart->AddToViewPort(1);
		Button_GameStart->SetAutoSize(1.0f, true);
		Button_GameStart->SetWidgetLocation({ 231.0f, -222.0f, 0.0f, 0.0f });
		//Button_GameStart->set
	}
}


void ALobbyTitleGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}