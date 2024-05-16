#pragma once
#include <EngineCore/TextWidget.h>

class ALobbyTitleGameMode :public AGameMode
{
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

	inline void SetUserName(std::string_view _UserName)
	{
		Name_Player = _UserName;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void UserInfoUpdate(int _Index);

	void SpaceOn(int _Index);
	void SpaceOff(int _Index);

	void PanelOn();
	void PanelOff();

	void FadeIn(float _DeltaTime);
	void FadeOut(float _DeltaTime);

private:
	// PlayerInfo
	int SpaceIndex_Player = 2;
	std::string Name_Player = "";
	ECharacterType CharacterType_Player = ECharacterType::Random;
	//charactercolor, ability, rank, ...etc.

	// TitleLevel Info
	std::string UserName_Input = "";

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
	std::vector<UTextWidget*> Usernames_Space;

	// CharacterSelect
	UImage* UpperPanel_CharacterSelect = nullptr;
	UImage* Panel_CharacterSelect = nullptr;
	std::map<int, std::vector<UImage*>> Traits_CharacterSelect;
	std::vector<UImage*> Btns_CharacterSelect;
	std::vector<bool> CharacterSelect_Pick;
	UImage* Outline_CharacterSelect = nullptr;
	UImage* Checker_CharacterSelect = nullptr;
	int BombMin_Panel = 0;
	int BombMax_Panel = 0;
	int BombWaterMin_Panel = 0;
	int BombWaterMax_Panel = 0;
	int SpeedMin_Panel = 0;
	int SpeedMax_Panel = 0;

	void SettingPanel(ECharacterType _CharacterType);
	void ChangeCharacter(ECharacterType _CharacterType);
};