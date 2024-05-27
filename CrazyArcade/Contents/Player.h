#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/StateManager.h>
#include <EngineCore/SpriteRenderer.h>
#include "MapHelper.h"

enum class EPlayerDir
{
	Left,
	Right,
	Up,
	Down,
};

enum class ERiding
{
	None,
	Owl,
	Turtle,
	UFO,
};

struct FCharacterTypeData
{
	std::string Type;

	int DataBaseBombCount;
	int DataMaxBombCount;

	int DataBaseBombPower;
	int DataMaxBombPower;

	float DataBaseSpeed;
	float DataMaxSpeed;
};

class AMainPlayLevel;
class ABombBase;

class APlayer : public ANetActor
{
	GENERATED_BODY(ANetActor)

public:
	// constrcuter destructer
	APlayer();
	~APlayer();

	// delete Function
	APlayer(const APlayer& _Other) = delete;
	APlayer(APlayer&& _Other) noexcept = delete;
	APlayer& operator=(const APlayer& _Other) = delete;
	APlayer& operator=(APlayer&& _Other) noexcept = delete;

	USpriteRenderer* GetRenderer()
	{
		return Renderer;
	}

	inline int GetBombPower()
	{
		return BombPower;
	}

	inline int GetNeedleCount()
	{
		return NeedleCount;
	}

	inline bool GetIsTrapped()
	{
		return IsTrapped;
	}

	inline bool GetIsDead()
	{
		return IsDead;
	}

	inline FVector GetPlayerDirVector()
	{
		return PlayerDirVector;
	}
	
	inline void IncreaseBombCount()
	{
		++BombCount;
	}

	void SetSupermanOff();

	void SetPlayerDead();
	void PlayerInfoUpdate();
	void CheckWinLose();

	void SetTrapState();
	
	// 플레이어 캐릭터, 색상 설정 후 생성
	void SettingPlayer(int _ObjectToken);
	inline ECharacterType GetCharacterType()
	{
		return CharacterType;
	}
	inline ECharacterColor GetPlayerColor()
	{
		return PlayerColor;
	}

	virtual void NeedleUpdate() {}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void CheckDead();

	UStateManager State;

	UDefaultSceneComponent* DefaultComponent;
	USpriteRenderer* Renderer;
	USpriteRenderer* ShadowRenderer;
	
	ECharacterType CharacterType = ECharacterType::None;
	void SetCharacterType(ECharacterType _Character);
	void SetPlayerColor(ECharacterColor _Color);

	std::map<ECharacterType, FCharacterTypeData> MCharacterTypeData;
	FVector PlayerPos;
	std::string Name = "Player";
	EPlayerDir PlayerDir = EPlayerDir::Down;
	FVector PlayerDirVector = FVector::Zero;
	ABombBase* Bomb = nullptr;
	ERiding Riding = ERiding::None;

	int BaseBombCount = 1;
	int BombCount = 2;
	int MaxBombCount = 6;

	int BaseBombPower = 0;
	int BombPower = 0;
	int MaxBombPower = 6;

	float BaseSpeed = 40.0f * 5.0f;
	float Speed = 0.0f;
	float MaxSpeed = 40.0f * 9.0f;
	float CurSpeed = BaseSpeed + Speed;

	bool Push = false;
	bool Throw = false;

	bool NoHit = false;

	bool IsDevil = false;
	bool MoveDevil = false;

	bool IsSuperman = false;

	int NeedleCount = 1;
	bool IsNeedleUse = false;

	std::map<EItemType, int> MPlayerItem;
	std::map<EItemType, int>::iterator MPlayerItemIter;

	float BlockSize = 0.0f;
	AMainPlayLevel* PlayLevel = nullptr;

	void PickUpItem();
	void AddItemCount(EItemType _ItemType);

	float DevilRenderChangeTime = 0.0f;
	float DevilTime = 10.0f;
	void Devil(float _DeltaTime);
	float SupermanRenderChangeTime = 0.0f;
	float SupermanTime = 10.0f;
	void Superman(float _DeltaTime);

	void SpawnBombCheckSend();
	void CheckBombCount();
	FPoint SpawnBombPoint = { -1, -1 };
	bool IsBombOn = false;

	std::string Type = "Bazzi";
	ECharacterColor PlayerColor = ECharacterColor::Red;
	std::string PlayerColorText = "_R";

	void PlayerCreateCuttingBazzi(std::string _Color);
	void PlayerCreateCutting(std::string _CharacterType_Color);

	void PlayerCreateBazziAnimation(std::string _Color);
	void PlayerCreateAnimation(std::string _CharacterType_Color);

	bool IsBlink = false;
	float BlinkTerm = 0.0f;
	float BlinkTime = 0.0f;
	void StartBlink(float _BlinkTime);
	void BlinkRenderer(float _DeltaTime);

	void CharacterTypeDataInit();

	//State
	void StateInit();

	void Ready(float _DeltaTime);
	void Idle(float _DeltaTime);
	void Run(float _DeltaTime);
	void RidingIdle(float _DeltaTime);
	void RidingRun(float _DeltaTime);
	void RidingDown(float _DeltaTime);
	void TrapStart(float _DeltaTime);
	void Trapped(float _DeltaTime);
	void TrapEnd(float _DeltaTime);
	void Die(float _DeltaTime);
	void Revival(float _DeltaTime);
	void Win(float _DeltaTime);
	void Lose(float _DeltaTime);

	void KeyMove(float _DeltaTime, FVector _Dir, float _Speed);
	void HideInBush();
	bool IsInBush = false;

	float JumpTime = 0.0f;
	bool IsDead = false;
	bool IsTrapped = false;

	float TrapStartTime = 0.28f;
	float TrappedTime = 4.0f;
	float TrapEndTime = 1.6f;
};