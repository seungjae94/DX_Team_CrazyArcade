#include"PreCompile.h"
#include "InGameUI.h"

AInGameUI::AInGameUI()
{

}

AInGameUI::~AInGameUI()
{
}


void AInGameUI::BeginPlay()
{
	UEngineSprite::CreateCutting("Play_ExitButtonHover.png", 1, 2);

	Super::BeginPlay();
	CancelBtn = CreateWidget<UImage>(GetWorld(), "CancelButton");
	CancelBtn->CreateAnimation("CancelButtonUnHoverAni", "Play_ExitButtonUnHover.png", 0.1f, false, 0, 0);
	CancelBtn->CreateAnimation("CancelButtonHoverAni", "Play_ExitButtonHover.png", 0.1f, false, 0, 1);
	CancelBtn->CreateAnimation("CancelButtonIsDownAni", "Play_ExitButtonIsDown.png", 0.1f, false, 0, 0);

	CancelBtn->SetAutoSize(1.0f, true);
	CancelBtn->ChangeAnimation("CancelButtonUnHoverAni");
	CancelBtn->SetWidgetLocation({ 316.0f, -276.0f });
	CancelBtn->AddToViewPort(3);


	CancelBtn->SetUnHover([=] {



		CancelBtn->ChangeAnimation("CancelButtonUnHoverAni");

		});
	CancelBtn->SetHover([=] {

		CancelBtn->ChangeAnimation("CancelButtonHoverAni");


		});
	CancelBtn->SetDown([=] {



		CancelBtn->ChangeAnimation("CancelButtonUnHoverAni");
		CancelBtn->SetUp([=] {

			GEngine->ChangeLevel("LobbyTitleTestLevel");
			});

		});




}
void AInGameUI::Tick(float _DeltaTIme)
{

	Super::Tick(_DeltaTIme);

}



