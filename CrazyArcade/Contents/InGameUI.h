#pragma once
#include"ConnectionInfo.h"

class APlayer;
class AMainPlayLevel;
class AInGameUI : public AActor
{
	GENERATED_BODY(AActor)
private:
	struct PlayerState
	{
		int Order;
		std::string PlayerName;
		ECharacterColor PlayerColor;
		ECharacterType PlayerType;
		bool IsDead;
		bool IsChange = false; //Tick을 계속돌면서 changeAni를 막기위한것
		int Needle;

		//지윤이랑 인터페이스 동일하게 진행 
	};

public:
	// constructor destructor
	AInGameUI();
	~AInGameUI();

	// delete Function
	AInGameUI(const AInGameUI& _Other) = delete;
	AInGameUI(AInGameUI&& _Other) noexcept = delete;
	AInGameUI& operator=(const AInGameUI& _Other) = delete;
	AInGameUI& operator=(AInGameUI&& _Other) = delete;


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTIme) override;

	void LevelEnd(ULevel* _NextLevel);
	void LevelStart(ULevel* _PrevLevel);

	void GameEnd();

private:
	std::string MinText;
	std::string SecText;

	int Min = 0;


	UImage* CancelBtn = nullptr;
	UImage* CancelBtn_InActive = nullptr;
	UImage* ResultBackGround = nullptr;
	

	UImage* PlayerStateRender = nullptr;
	UImage* NeedleRender = nullptr; // 원래는 아이템 벡터로 받을려고 했는데 시간상 그냥 아이템 하나 
	UImage* NeedleRender2 = nullptr;

	UImage* NeedleNum = nullptr;
	UImage* NeedleNum2 = nullptr;
	UImage* NeedleX = nullptr;


	int ServerToken = 0;

	std::vector<UImage*> PlayerUI; //플레이어
	std::vector<UTextWidget*> PlayerNameUI;
	std::vector<PlayerState> PlayerInfo;


	void InitPlayerInfo();

	void PlayerUpdate();

	void DeadCheck();

	void NeedleCheck();

	void DataToRender();

	void PlayerStateCheck();

	void ResultCheck();




	//아이템 및 바늘
	int Needles = 0;
	AMainPlayLevel* PlayerLevelPtr = nullptr;
	APlayer* PlayerPtr = nullptr;
	bool PlayerDeadAct;


	static std::string StateToAnimName(ECharacterType _Type, ECharacterColor _Color, bool _IsDead);
	static std::string TypeToName(ECharacterType _Type);
	static std::string ColorToName(ECharacterColor _Color);

	UEngineSoundPlayer WinSound;
	UEngineSoundPlayer Losesound;

	// Fade
	UImage* Fade = nullptr;
	bool IsFadeIn = true;
	bool IsFadeOut = false;
	float FadeAlpha = 1.0f;
	void FadeIn(float _DeltaTime);
	void FadeOut(float _DeltaTime);
	void ChangeFadeOut(bool _IsFadeOut);
};