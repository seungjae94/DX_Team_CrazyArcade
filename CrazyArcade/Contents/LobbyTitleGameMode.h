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

	void PanelOn()
	{
		UpperPanel_CharacterSelect->SetActive(true);
		Panel_CharacterSelect->SetActive(true);
	}

	void PanelOff()
	{
		UpperPanel_CharacterSelect->SetActive(false);
		Panel_CharacterSelect->SetActive(false);
	}

private:
	ECharacterType CharacterType = ECharacterType::Random;

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

	void SettingPanel(ECharacterType _CharacterType);
	void ChangeCharacter(ECharacterType _CharacterType);
};