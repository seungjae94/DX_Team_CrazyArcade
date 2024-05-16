#pragma once
#include"MainTitleGameMode.h"
class MainTitleGameMode;

class ALobbyTitleGameMode :public AGameMode
{
	struct LobbyUserInfo
	{
		std::string UserName;
	};

	GENERATED_BODY(AGameMode)
public:
	// constructor destructor
	ALobbyTitleGameMode();
	~ALobbyTitleGameMode();

	// delete Function
	ALobbyTitleGameMode(const ALobbyTitleGameMode& _Other) = delete;
	ALobbyTitleGameMode(ALobbyTitleGameMode&& _Other) noexcept = delete;
	ALobbyTitleGameMode& operator=(const ALobbyTitleGameMode& _Other) = delete;
	ALobbyTitleGameMode& operator=(ALobbyTitleGameMode&& _Other) = delete;

	inline void SetPlayerName(std::string_view _UserName)
	{
		PlayerName = _UserName;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void SpaceOn(int _Index);
	void SpaceOff(int _Index);

	void PanelOn();
	void PanelOff();

	void FadeIn(float _DeltaTime);
	void FadeOut(float _DeltaTime);

private:
	// BackGround
	UImage* LobbyBackGround = nullptr;

	// Fade
	UImage* Fade = nullptr;
	bool IsFadeIn = true;
	bool IsFadeOut = false;
	float FadeAlpha = 1.0f;

	// GameStart, MapSelect
	UImage* Btn_GameStart = nullptr;
	UImage* Btn_MapSelect = nullptr;

	// Space
	std::vector<bool> Space_Available;
	std::vector<UImage*> Btns_Space;
	std::vector<UImage*> Characters_Space;
	std::vector<UImage*> Flags_Space;
	std::vector<UImage*> Shadows_Space;

	// CharacterSelect
	ECharacterType CharacterType = ECharacterType::Random;
	int BombMin = 0;
	int BombMax = 0;
	int BombWaterMin = 0;
	int BombWaterMax = 0;
	int SpeedMin = 0;
	int SpeedMax = 0;

	//UserName
	std::string PlayerName = "";
	UTextWidget* TextWidget = nullptr;


	UImage* UpperPanel_CharacterSelect = nullptr;
	UImage* Panel_CharacterSelect = nullptr;
	std::map<int, std::vector<UImage*>> Traits_CharacterSelect;
	std::vector<UImage*> Btns_CharacterSelect;
	std::vector<bool> CharacterSelect_Pick;
	UImage* Outline_CharacterSelect = nullptr;
	UImage* Checker_CharacterSelect = nullptr;
	


	void SettingPanel(ECharacterType _CharacterType);
	void ChangeCharacter(ECharacterType _CharacterType);
};