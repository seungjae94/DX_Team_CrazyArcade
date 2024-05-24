#pragma once
#include <EngineCore/Widget.h>
#include <EngineCore/TextWidget.h>
#include<vector>
#include "NetGameMode.h"
#include "CrazyArcadeDebugWindow.h"

class AMouse;
class AMainTitleGameMode : public ANetGameMode
{
	GENERATED_BODY(ANetGameMode)
public:
	// constructor destructor
	AMainTitleGameMode();
	~AMainTitleGameMode();

	// delete Function
	AMainTitleGameMode(const AMainTitleGameMode& _Other) = delete;
	AMainTitleGameMode(AMainTitleGameMode&& _Other) noexcept = delete;
	AMainTitleGameMode& operator=(const AMainTitleGameMode& _Other) = delete;
	AMainTitleGameMode& operator=(AMainTitleGameMode&& _Other) = delete;

	static AMainTitleGameMode* Title;

	void MyChangeIP() {
		IPNum = "127.0.0.1";
	}

	void SungMinChangeIP() {
		IPNum = "192.168.0.198";
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;

	void ServerStart();
	void ClientStart();

	void HandlerInit() override;

private:
	void StringToText();
	
	std::shared_ptr<AMouse> MouseUI = nullptr;

	// UI
	UImage* TitleBackGround = nullptr;
	UImage* LoginUI = nullptr;

	UImage* StartButton = nullptr;
	UImage* Button_1P = nullptr;
	UImage* Button_2P = nullptr;
	bool IsServer = false;

	UImage* VoidBox = nullptr;
	UImage* PlayerNameBox = nullptr;
	UTextWidget* TextWidget = nullptr;
	UImage* IPNumBox = nullptr;
	UTextWidget* IPNumText = nullptr;
	UTextWidget* IPNumTitle = nullptr;
	UImage* PortNumBox = nullptr;
	UTextWidget* PortNumText = nullptr;
	UTextWidget* PortNumTitle = nullptr;

	std::string PlayerName;
	std::string IPNum = "192.168.0.198";
	std::string PortNum = "30000";

	bool IsNameBoxAct = false;
	bool IsIPNumBoxActive = false;
	bool IsPortNumBoxActive = false;

	const int PlayerNameMaxLength = 6;
	const int IPNumMaxLength = 15;
	const int PortNumMaxLength = 5;

	// Fade
	UImage* Fade = nullptr;
	bool IsFadeOut = false;
	float FadeAlpha = 0.0f;
	void FadeOut(float _DeltaTime);

	// »ç¿îµå
	UEngineSoundPlayer BgmPlayer;
};