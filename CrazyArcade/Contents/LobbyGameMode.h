#pragma once
#include <EngineCore/TextWidget.h>
#include "NetGameMode.h"
#include "MouseUI.h"

class ALobbyGameMode :public ANetGameMode
{
	GENERATED_BODY(ANetGameMode)
public:
	// constructor destructor
	ALobbyGameMode();
	~ALobbyGameMode();

	// delete Function
	ALobbyGameMode(const ALobbyGameMode& _Other) = delete;
	ALobbyGameMode(ALobbyGameMode&& _Other) noexcept = delete;
	ALobbyGameMode& operator=(const ALobbyGameMode& _Other) = delete;
	ALobbyGameMode& operator=(ALobbyGameMode&& _Other) = delete;

private:
	// UserInfos
	struct UserInfo
	{
		int SpaceIndex;
		std::string Name;
		ECharacterType CharacterType;
		ECharacterColor CharacterColor;
		bool IsReady;
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
	void ReadyUpdate();
	void MapImageUpdate();

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
	bool IsGameStartable = false;

	// MapSelect
	UImage* Btn_MapSelect = nullptr;
	UImage* Btn_MapSelect_InActive = nullptr;
	UImage* Image_MapSelect = nullptr;
	bool IsMapSelectOn = false;
	UImage* BackGround_MapSelect = nullptr;
	UImage* Fade_MapSelect = nullptr;
	UImage* Btn_MapSelectAccept = nullptr;
	UImage* Btn_MapSelectCancel = nullptr;
	UImage* Instruction_MapSelect = nullptr;
	std::vector<UImage*> Btns_MapType;
	std::vector<bool> MapSelect_Pick;
	EMapType MapType = EMapType::Village;
	EMapType MapType_Picked = EMapType::None;

	// Space
	std::vector<bool> Space_IsAvailable;
	std::vector<bool> Space_IsUserIn;
	std::vector<UImage*> Btns_Space;
	std::vector<UImage*> Characters_Space;
	std::vector<UImage*> Flags_Space;
	std::vector<UImage*> Shadows_Space;
	std::vector<UImage*> Readys_Space;
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
	UImage* Line_UnderBar = nullptr;

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


	std::shared_ptr<AMouse> MouseUI = nullptr;

	void SettingPanel(ECharacterType _CharacterType);
	void SettingCharacterSelect(ECharacterType _CharacterType);
	void SettingColorSelect(ECharacterColor _CharacterColor);
	void SettingName(int _SpaceIndex);
	void SettingReady(int _SpaceIndex);
	void SettingCharacterImage(int _SpaceIndex);
	void SettingMapSelect(EMapType _MapType);
	void SettingMapImage(EMapType _MapType);
	void ChangeCharacter(ECharacterType _CharacterType);
	void ChangeColor(ECharacterColor _CharacterColor);
	void ChangeReady(bool _IsReady);
	void ChangeMap(EMapType _MapType);
	void ChangeFadeOut(bool _IsFadeOut);

	// »ç¿îµå
	UEngineSoundPlayer BgmPlayer;
};