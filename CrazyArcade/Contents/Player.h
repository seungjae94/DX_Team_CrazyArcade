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

struct FPlayerInfo
{
	// 키: 세션 토큰
	static std::map<int, bool> IsDeads; // IsDeads[3]: 3번 플레이어가 죽었는지
	static std::map<int, std::string> Names; // Names[3]: 3번 플레이어의 이름
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

	inline void IncreaseBombCount()
	{
		++BombCount;
	}

	void SetSupermanOff();

	void SetPlayerDead();
	void PlayerInfoUpdate();

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

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	UStateManager State;

	UDefaultSceneComponent* DefaultComponent;
	USpriteRenderer* Renderer;
	USpriteRenderer* ShadowRenderer;
	USpriteRenderer* DebugRenderer;
	
	std::shared_ptr<APlayer> Player = nullptr;
	ECharacterType CharacterType;
	void SetCharacterType(ECharacterType _Character);
	void SetPlayerColor(ECharacterColor _Color);

	std::map<ECharacterType, FCharacterTypeData> MCharacterTypeData;
	FVector PlayerPos;
	std::string Name = "Player";
	EPlayerDir PlayerDir = EPlayerDir::Down;
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

	std::map<EItemType, int> MPlayerItem;
	std::map<EItemType, int>::iterator MPlayerItemIter;

	float BlockSize = 0.0f;
	AMainPlayLevel* PlayLevel = nullptr;

	void PickUpItem();
	void AddItemCount(EItemType _ItemType);

	float DevilRenderChangeTime = 0.0f;
	float DevilTime = 15.0f;
	void Devil(float _DeltaTime);
	float SupermanRenderChangeTime = 0.0f;
	float SupermanTime = 10.0f;
	void Superman(float _DeltaTime);

	void SpawnBombCheckSend();
	void CheckBombCount();
	FPoint SpawnBombPoint = { -1, -1 };
	bool IsBombOn = false;

	std::string Type = "luxMarid";
	ECharacterColor PlayerColor = ECharacterColor::Red;
	std::string PlayerColorText = "_R";

	void PlayerCreateCuttingBazzi(std::string _Color);
	void PlayerCreateCutting(std::string _CharacterType_Color);

	void PlayerCreateBazziAnimation(std::string _Color);
	void PlayerCreateAnimation(std::string _CharacterType_Color);

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
	void Traped(float _DeltaTime);
	void TrapEnd(float _DeltaTime);
	void Die(float _DeltaTime);
	void Revival(float _DeltaTime);

	void KeyMove(float _DeltaTime, FVector _Dir, float _Speed);

	float JumpTime = 0.0f;
	bool IsDead = false;

	float TrapStartTime = 0.28f;
	float TrapedTime = 4.0f;
	float TrapEndTime = 1.6f;
};