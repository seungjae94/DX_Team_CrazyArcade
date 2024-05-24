#include "PreCompile.h"
#include "MainTitleGameMode.h"
#include <vector>

#include "LobbyGameMode.h"
#include"ConnectionInfo.h"
#include "ServerGameMode.h"

#include <EngineCore/EngineEditorGUI.h>
#include "CrazyArcadeCore.h"
#include "ServerManager.h"

#include "Packets.h"
#include "ServerHelper.h"

#include"MouseUI.h"

AMainTitleGameMode* AMainTitleGameMode::Title = nullptr;

AMainTitleGameMode::AMainTitleGameMode()
{
	
	AMainTitleGameMode::Title = this;
}

AMainTitleGameMode::~AMainTitleGameMode()
{
}

void AMainTitleGameMode::BeginPlay()
{

	

	Super::BeginPlay();
	//MouseUI = CreateWidget<UImage>(GetWorld(), "MouseRenderUI");
	MouseUI = GetWorld()->SpawnActor<AMouse>("MouseUIActor");


	TitleBackGround = CreateWidget<UImage>(GetWorld(), "TitleBackGround");
	TitleBackGround->SetSprite("Login.png");
	TitleBackGround->AddToViewPort(1); //UITest;
	TitleBackGround->SetScale({ 800,600 });
	TitleBackGround->SetPosition({ 0.0f,0.0f });

	StartButton = CreateWidget<UImage>(GetWorld(), "TitleBackGround");
	StartButton->AddToViewPort(2); //UITest;
	StartButton->SetAutoSize(1.0f, true);
	StartButton->CreateAnimation("NoneStartButtonAni", "StartButton", 0.1f, false, 0, 0);
	StartButton->CreateAnimation("HoverStartButtonAni", "StartButton", 0.5f, false, 1, 1);
	StartButton->ChangeAnimation("NoneStartButtonAni");
	StartButton->SetPosition({ 0.0f,-218.0f });

	VoidBox = CreateWidget<UImage>(GetWorld(), "VoidBoxUI");
	VoidBox->SetSprite("Login.png");
	VoidBox->AddToViewPort(1); //UITest;
	VoidBox->SetScale({ 800,600 });
	VoidBox->SetPosition({ 0.0f,0.0f });

	PlayerNameBox = CreateWidget<UImage>(GetWorld(), "PlayerBoxUI");
	PlayerNameBox->AddToViewPort(3);
	PlayerNameBox->CreateAnimation("NotActiveAni", "NameBoxNotActive.png", 0.1f, false, 0, 0);
	PlayerNameBox->CreateAnimation("ActiveAni", "NameBox.png", 0.1f, false, 0, 0);
	PlayerNameBox->ChangeAnimation("NotActiveAni");
	PlayerNameBox->SetScale({ 210.0f, 22.5f });
	PlayerNameBox->SetWidgetLocation({ -10.5f,-155.5f });

	TextWidget = CreateWidget<UTextWidget>(GetWorld(), "TextWidget");
	TextWidget->SetFont("굴림");
	TextWidget->SetScale(16.0f);
	TextWidget->SetColor(Color8Bit::Black);
	TextWidget->SetPosition({ -110.0f ,-145.0f });
	TextWidget->SetFlag(FW1_LEFT); //좌로 정렬
	TextWidget->AddToViewPort(4);
	TextWidget->SetText(PlayerName);


	StartButton->SetUnHover([=] {
			StartButton->ChangeAnimation("NoneStartButtonAni");
		});
	StartButton->SetHover([=]{
			StartButton->ChangeAnimation("HoverStartButtonAni");
		});
	StartButton->SetDown([=] {
		// 1P, 2P 버튼이 있으므로 비활성화
		//GEngine->ChangeLevel("LobbyLevel");
		});

	VoidBox->SetDown([=] {
		//키 입력 제한
		if (IsNameBoxAct == true)
		{
			PlayerNameBox->ChangeAnimation("NotActiveAni");
			IsNameBoxAct = false;
		}
		if (IsIPNumBoxActive == true)
		{
			IPNumBox->ChangeAnimation("InActive");
			IsIPNumBoxActive = false;
		}
		if (IsPortNumBoxActive == true)
		{
			PortNumBox->ChangeAnimation("InActive");
			IsPortNumBoxActive = false;
		}

		UEngineInputRecorder::GetText();
		UEngineInputRecorder::RecordEnd();
		});

	PlayerNameBox->SetDown([=] {
		//키 입력
		PlayerNameBox->ChangeAnimation("ActiveAni");
		IsNameBoxAct = true;
		IPNumBox->ChangeAnimation("InActive");
		IsIPNumBoxActive = false;
		PortNumBox->ChangeAnimation("InActive");
		IsPortNumBoxActive = false;

		UEngineInputRecorder::RecordStart(TextWidget->GetText(), PlayerNameMaxLength);
		});

	// 1P Button
	{
		Button_1P = CreateWidget<UImage>(GetWorld(), "Button_1P");
		Button_1P->AddToViewPort(1);
		Button_1P->SetAutoSize(1.0f, true);
		Button_1P->SetWidgetLocation({ -210.0f, -172.0f });

		Button_1P->CreateAnimation("UnHover", "Button_1P_UnHover.png", 0.1f, false, 0, 0);
		Button_1P->CreateAnimation("Hover", "Button_1P_Hover.png", 0.1f, false, 0, 0);
		Button_1P->CreateAnimation("Down", "Button_1P_Down.png", 0.1f, false, 0, 0);
		Button_1P->ChangeAnimation("UnHover");

		Button_1P->SetUnHover([=] {
			Button_1P->ChangeAnimation("UnHover");
			});

		Button_1P->SetHover([=] {
			if (Button_1P->IsCurAnimationEnd() == true)
			{
				Button_1P->ChangeAnimation("Hover");
			}
			});

		Button_1P->SetDown([=] {
			Button_1P->ChangeAnimation("Down");
			});

		Button_1P->SetPress([=] {

			});

		Button_1P->SetUp([=] {
			if (TextWidget->GetText().size() <= 0)
			{
				// 이름을 입력해주세요 UI 추가 
				//return;
			}
			Button_1P->ChangeAnimation("UnHover");
			IsServer = true;
			IsFadeOut = true;
			//ServerStart();
			});
	}

	// 2P Button
	{
		Button_2P = CreateWidget<UImage>(GetWorld(), "Button_2P");
		Button_2P->AddToViewPort(1);
		Button_2P->SetAutoSize(1.0f, true);
		Button_2P->SetWidgetLocation({ 210.0f, -172.0f });

		Button_2P->CreateAnimation("UnHover", "Button_2P_UnHover.png", 0.1f, false, 0, 0);
		Button_2P->CreateAnimation("Hover", "Button_2P_Hover.png", 0.1f, false, 0, 0);
		Button_2P->CreateAnimation("Down", "Button_2P_Down.png", 0.1f, false, 0, 0);
		Button_2P->ChangeAnimation("UnHover");

		Button_2P->SetUnHover([=] {
			Button_2P->ChangeAnimation("UnHover");
			});

		Button_2P->SetHover([=] {
			if (Button_2P->IsCurAnimationEnd() == true)
			{
				Button_2P->ChangeAnimation("Hover");
			}
			});

		Button_2P->SetDown([=] {
			Button_2P->ChangeAnimation("Down");
			});

		Button_2P->SetPress([=] {

			});

		Button_2P->SetUp([=] {
			if (TextWidget->GetText().size() <= 0)
			{
				// 이름을 입력해주세요 UI 추가 
				//return;
			}
			Button_2P->ChangeAnimation("UnHover");
			IsServer = false;
			IsFadeOut = true;
			//ClientStart();
			});
	}

	// IP Number Box
	{
		IPNumBox = CreateWidget<UImage>(GetWorld(), "IPNumBox");
		IPNumBox->AddToViewPort(3);
		IPNumBox->SetScale({ 210.0f, 22.5f });
		IPNumBox->SetWidgetLocation({ 275.0f, -40.0f });

		IPNumBox->CreateAnimation("InActive", "NameBoxNotActive.png", 0.1f, false, 0, 0);
		IPNumBox->CreateAnimation("Active", "NameBox.png", 0.1f, false, 0, 0);
		IPNumBox->ChangeAnimation("InActive");

		IPNumBox->SetDown([=] {
			PlayerNameBox->ChangeAnimation("NotActiveAni");
			IsNameBoxAct = false;
			IPNumBox->ChangeAnimation("Active");
			IsIPNumBoxActive = true;
			PortNumBox->ChangeAnimation("InActive");
			IsPortNumBoxActive = false;

			UEngineInputRecorder::RecordStart(IPNumText->GetText(), IPNumMaxLength);
			});

		IPNumText = CreateWidget<UTextWidget>(GetWorld(), "IPNumText");
		IPNumText->AddToViewPort(4);
		IPNumText->SetScale(20.0f);
		IPNumText->SetWidgetLocation({ 173.0f, -28.0f });
		IPNumText->SetFont("굴림");
		IPNumText->SetColor(Color8Bit::Black);
		IPNumText->SetFlag(FW1_LEFT);
		IPNumText->SetText(IPNum);

		IPNumTitle = CreateWidget<UTextWidget>(GetWorld(), "IPNumTitle");
		IPNumTitle->AddToViewPort(4);
		IPNumTitle->SetScale(20.0f);
		IPNumTitle->SetWidgetLocation({ 130.0f, -28.0f });
		IPNumTitle->SetFont("굴림");
		IPNumTitle->SetColor(Color8Bit::Black);
		IPNumTitle->SetFlag(FW1_LEFT);
		IPNumTitle->SetText("IP : ");
	}

	// Port Number Box
	{
		PortNumBox = CreateWidget<UImage>(GetWorld(), "PortNumBox");
		PortNumBox->AddToViewPort(3);
		PortNumBox->SetScale({ 100.0f, 22.5f });
		PortNumBox->SetWidgetLocation({ 220.0f, -70.0f });

		PortNumBox->CreateAnimation("InActive", "NameBoxNotActive.png", 0.1f, false, 0, 0);
		PortNumBox->CreateAnimation("Active", "NameBox.png", 0.1f, false, 0, 0);
		PortNumBox->ChangeAnimation("InActive");

		PortNumBox->SetDown([=] {
			PlayerNameBox->ChangeAnimation("NotActiveAni");
			IsNameBoxAct = false;
			IPNumBox->ChangeAnimation("InActive");
			IsIPNumBoxActive = false;
			PortNumBox->ChangeAnimation("Active");
			IsPortNumBoxActive = true;

			UEngineInputRecorder::RecordStart(PortNumText->GetText(), PortNumMaxLength);
			});

		PortNumText = CreateWidget<UTextWidget>(GetWorld(), "PortNumText");
		PortNumText->AddToViewPort(4);
		PortNumText->SetScale(20.0f);
		PortNumText->SetWidgetLocation({ 173.0f, -58.0f });
		PortNumText->SetFont("굴림");
		PortNumText->SetColor(Color8Bit::Black);
		PortNumText->SetFlag(FW1_LEFT);
		PortNumText->SetText(PortNum);

		PortNumTitle = CreateWidget<UTextWidget>(GetWorld(), "PortNumText");
		PortNumTitle->AddToViewPort(4);
		PortNumTitle->SetScale(20.0f);
		PortNumTitle->SetWidgetLocation({ 110.0f, -58.0f });
		PortNumTitle->SetFont("굴림");
		PortNumTitle->SetColor(Color8Bit::Black);
		PortNumTitle->SetFlag(FW1_LEFT);
		PortNumTitle->SetText("Port : ");
	}

	// Fade
	{
		Fade = CreateWidget<UImage>(GetWorld(), "Fade");
		Fade->SetSprite("FadeBlack.png");
		Fade->AddToViewPort(10);
		Fade->SetAutoSize(1.0f, true);
		Fade->SetWidgetLocation({ 0.0f, 0.0f });
		Fade->SetMulColor(float4(1.0f, 1.0f, 1.0f, 0.0f));
	}
}

void AMainTitleGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	// PlayerName, IPNum, PortNum on screen
	StringToText();

	// Fade & ChangeLevel
	{
		if (IsFadeOut == true)
		{
			FadeOut(_DeltaTime);
		}
	}

	// Debug
	{
		FVector CameraPos = GetWorld()->GetMainCamera()->GetActorLocation();
		FVector MousePos = GEngine->EngineWindow.GetScreenMousePos();
		FVector WindowScale = GEngine->EngineWindow.GetWindowScale();
		FVector TargetPos = FVector(CameraPos.X, CameraPos.Y, 0.0f) + FVector(MousePos.X - WindowScale.hX(), -(MousePos.Y - WindowScale.hY()), 0.0f);

		{
			std::string Msg = std::format("MousePos : {}\n", TargetPos.ToString());
			UEngineDebugMsgWindow::PushMsg(Msg);
		}
	}
}

void AMainTitleGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	BgmPlayer = UEngineSound::SoundPlay("TitleBgm.mp3");
	BgmPlayer.Loop(-1);

	// Fade
	FadeAlpha = 0.0f;
}

void AMainTitleGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);

	BgmPlayer.Off();

	ALobbyGameMode* Lobby = dynamic_cast<ALobbyGameMode*>(_NextLevel->GetGameMode().get());
	if (nullptr == Lobby)
	{
		return;
	}
}

void AMainTitleGameMode::ServerStart()
{
	if (UCrazyArcadeCore::Net == nullptr)
	{
		UCrazyArcadeCore::NetManager.ServerOpen();
		GEngine->ChangeLevel("LobbyLevel");

		if (true == PlayerName._Equal(""))
		{
			PlayerName = "Anonymous";
		}
		ConnectionInfo::GetInst().SetTempName(PlayerName);
		ConnectionInfo::GetInst().PushUserInfos(0, ConnectionInfo::GetInst().GetTempName());
	}
}

void AMainTitleGameMode::ClientStart()
{
	if (UCrazyArcadeCore::Net == nullptr)
	{
		UCrazyArcadeCore::NetManager.ClientOpen(IPNum, 30000);
		if (true == PlayerName._Equal(""))
		{
			PlayerName = "Anonymous";
		}
		ConnectionInfo::GetInst().SetTempName(PlayerName);
		GEngine->ChangeLevel("LobbyLevel");
	}
}

void AMainTitleGameMode::HandlerInit()
{
	UEngineDispatcher& Dis = UCrazyArcadeCore::Net->Dispatcher;
}

void AMainTitleGameMode::StringToText()
{
	if (IsNameBoxAct == true)
	{
		PlayerName = UEngineInputRecorder::GetText();
	}
	else if (IsIPNumBoxActive == true)
	{
		IPNum = UEngineInputRecorder::GetText();
	}
	else if (IsPortNumBoxActive == true)
	{
		PortNum = UEngineInputRecorder::GetText();
	}

	TextWidget->SetText(PlayerName);
	IPNumText->SetText(IPNum);
	PortNumText->SetText(PortNum);
}

void AMainTitleGameMode::FadeOut(float _DeltaTime)
{
	if (FadeAlpha >= 1.0f)
	{
		IsFadeOut = false;
		FadeAlpha = 0.0f;
		if (IsServer == true)
		{
			ServerStart();
		}
		else
		{
			ClientStart();
		}
		return;
	}

	FadeAlpha += _DeltaTime * 3.0f;
	Fade->SetMulColor(float4(1.0f, 1.0f, 1.0f, FadeAlpha));
}