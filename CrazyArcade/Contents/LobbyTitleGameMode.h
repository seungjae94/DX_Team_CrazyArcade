#pragma once
#include <EngineCore/TextWidget.h>
#include "NetGameMode.h"

class ALobbyTitleGameMode :public ANetGameMode
{
	GENERATED_BODY(ANetGameMode)
public:
	// constructor destructor
	ALobbyTitleGameMode();
	~ALobbyTitleGameMode();

	// delete Function
	ALobbyTitleGameMode(const ALobbyTitleGameMode& _Other) = delete;
	ALobbyTitleGameMode(ALobbyTitleGameMode&& _Other) noexcept = delete;
	ALobbyTitleGameMode& operator=(const ALobbyTitleGameMode& _Other) = delete;
	ALobbyTitleGameMode& operator=(ALobbyTitleGameMode&& _Other) = delete;

private:
	// UserInfos
	struct UserInfo
	{
		int SpaceIndex;
		std::string Name;
		ECharacterType CharacterType;
		ECharacterColor CharacterColor;
	};
	std::vector<UserInfo> UserInfos;
	UserInfo Player;

public:
	inline UserInfo GetPlayerInfo()
	{
		return Player;
	}

	inline ECharacterType GetPlayerCharacterType()
	{
		return Player.CharacterType;
	}

	inline ECharacterColor GetPlayerCharacterColor()
	{
		return Player.CharacterColor;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;

	void UserInfosUpdate();
	void ChatUpdate();

	void SpaceOn(int _Index);
	void SpaceOff(int _Index);

	void PanelOn();
	void PanelOff();

	void MapSelectOn();
	void MapSelectOff();

	void FadeIn(float _DeltaTime);
	void FadeOut(float _DeltaTime);

	void GameStart();

	void HandlerInit() override;

private:
	// BackGround
	UImage* LobbyBackGround = nullptr;

	// Fade
	UImage* Fade = nullptr;
	bool IsFadeIn = true;
	bool IsFadeOut = false;
	float FadeAlpha = 1.0f;

	// GameStart
	UImage* Btn_GameStart = nullptr;
	UImage* Btn_GameStart_InActive = nullptr;

	// MapSelect
	UImage* Btn_MapSelect = nullptr;
	UImage* Btn_MapSelect_InActive = nullptr;
	UImage* BackGround_MapSelect = nullptr;
	UImage* Btn_MapSelectAccept = nullptr;
	UImage* Btn_MapSelectCancel = nullptr;

	// Space
	std::vector<bool> Space_IsAvailable;
	std::vector<bool> Space_IsUserIn;
	std::vector<UImage*> Btns_Space;
	std::vector<UImage*> Characters_Space;
	std::vector<UImage*> Flags_Space;
	std::vector<UImage*> Shadows_Space;
	std::vector<UTextWidget*> Usernames_Space;

	// CharacterSelect
	UImage* UpperPanel_CharacterSelect = nullptr;
	UImage* Panel_CharacterSelect = nullptr;
	std::map<int, std::vector<UImage*>> Traits_CharacterSelect;

	struct CharacterAbilityInfo
	{
		int BombMin = 0;
		int BombMax = 0;
		int BombWaterMin = 0;
		int BombWaterMax = 0;
		int SpeedMin = 0;
		int SpeedMax = 0;
	};
	std::vector<CharacterAbilityInfo> CharacterAbilityInfos;
	CharacterAbilityInfo PanelInfo;

	std::vector<UImage*> Btns_CharacterSelect;
	std::vector<UImage*> Btns_CharacterSelect_InActive;
	std::vector<bool> CharacterSelect_Pick;
	UImage* Outline_CharacterSelect = nullptr;
	UImage* Checker_CharacterSelect = nullptr;

	// ColorSelect
	std::vector<UImage*> Btns_ColorSelect;
	std::vector<UImage*> Btns_ColorSelect_InActive;
	std::vector<bool> ColorSelect_Pick;
	UImage* Checker_ColorSelect = nullptr;

	// UnderBar
	UImage* Btn_Back = nullptr;
	UImage* Btn_Exit = nullptr;
	UImage* Image_Line = nullptr;

	// Chat
	UImage* VoidBox = nullptr;
	UImage* ChatBox = nullptr;
	UTextWidget* ChatInputText = nullptr;
	std::vector<UTextWidget*> ChatTexts;
	bool Chat_IsActive = false;
	int Chat_Size = 0;
	std::string ChatInput = "";
	std::string Chat = "";
	std::string Chat_Prev = "";

	void SettingPanel(ECharacterType _CharacterType);
	void SettingCharacterSelect(ECharacterType _CharacterType);
	void SettingColorSelect(ECharacterColor _CharacterColor);
	void SettingName(int _SpaceIndex);
	void SettingCharacterImage(int _SpaceIndex);
	void ChangeCharacter(ECharacterType _CharacterType);
	void ChangeColor(ECharacterColor _CharacterColor);
};