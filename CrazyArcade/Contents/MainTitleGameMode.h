#pragma once
#include <EngineCore/Widget.h>
#include <EngineCore/TextWidget.h>
#include<vector>
class AMainTitleGameMode : public AGameMode
{
	GENERATED_BODY(AGameMode)
public:
	// constructor destructor
	AMainTitleGameMode();
	~AMainTitleGameMode();

	// delete Function
	AMainTitleGameMode(const AMainTitleGameMode& _Other) = delete;
	AMainTitleGameMode(AMainTitleGameMode&& _Other) noexcept = delete;
	AMainTitleGameMode& operator=(const AMainTitleGameMode& _Other) = delete;
	AMainTitleGameMode& operator=(AMainTitleGameMode&& _Other) = delete;

	std::string GetPlayerName();



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
	
	// UI
	UImage* TitleBackGround = nullptr;
	UImage* LoginUI = nullptr;
	UImage* StartButton = nullptr;
	UImage* PlayerNameBox = nullptr;
	UImage* VoidBox = nullptr;
	UTextWidget* TextWidget = nullptr;
	UImage* Button_1P = nullptr;
	UImage* Button_2P = nullptr;

	std::string PlayerName;

	bool IsNameBoxAct = false;
};

