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

private:
	ECharacterType CharacterType = ECharacterType::Random;

	UImage* LobbyBackGround = nullptr;
	UImage* Btn_GameStart = nullptr;
	UImage* Btn_MapSelect = nullptr;
	UImage* Outline_CharacterSelect = nullptr;

	std::vector<UImage*> Btns_Space;
	std::vector<UImage*> Btns_CharacterSelect;
	std::vector<bool> Space_Available;
	std::vector<bool> CharacterSelect_Pick;
};