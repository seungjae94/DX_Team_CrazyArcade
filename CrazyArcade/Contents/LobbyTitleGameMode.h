#pragma once
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

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void PanelOn();
	void PanelOff();

private:
	ECharacterType CharacterType = ECharacterType::Random;
	int BombMin = 0;
	int BombMax = 0;
	int BombWaterMin = 0;
	int BombWaterMax = 0;
	int SpeedMin = 0;
	int SpeedMax = 0;

	UImage* LobbyBackGround = nullptr;
	UImage* Btn_GameStart = nullptr;
	UImage* Btn_MapSelect = nullptr;

	std::vector<UImage*> Btns_Space;
	std::vector<bool> Space_Available;

	std::vector<UImage*> Btns_CharacterSelect;
	std::vector<bool> CharacterSelect_Pick;
	UImage* Outline_CharacterSelect = nullptr;
	UImage* Checker_CharacterSelect = nullptr;
	UImage* UpperPanel_CharacterSelect = nullptr;
	UImage* Panel_CharacterSelect = nullptr;
	std::map<int, std::vector<UImage*>> Traits_CharacterSelect;

	void SettingPanel(ECharacterType _CharacterType);
	void ChangeCharacter(ECharacterType _CharacterType);
};