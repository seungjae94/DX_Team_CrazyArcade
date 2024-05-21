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


	ResultBackGround = CreateWidget<UImage>(GetWorld(), "ResultBackGroundUI");
	ResultBackGround->SetSprite("ResultWindow.png");
	ResultBackGround->SetMulColor({ 1.0f,1.0f,1.0f,0.7f });
	ResultBackGround->AddWidgetLocation(FVector{-80.0,-30.0f });
	ResultBackGround->AddToViewPort(3);
	ResultBackGround->SetScale({ 550,400 });


	ResultSummary = CreateWidget<UImage>(GetWorld(), "ResultBackGroundUI");
	ResultSummary->SetSprite("Result_Summary.png");
	
	ResultSummary->AddWidgetLocation(FVector{ -90.0f,140.0f });
	ResultSummary->SetScale({ 350,20 });
	ResultSummary->AddToViewPort(4);



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


	ResultBackGround->SetActive(false);
	ResultSummary->SetActive(false);

}
void AInGameUI::Tick(float _DeltaTIme)
{

	Super::Tick(_DeltaTIme);

}



