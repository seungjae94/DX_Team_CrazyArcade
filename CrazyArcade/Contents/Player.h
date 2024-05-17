#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/StateManager.h>
#include <EngineCore/SpriteRenderer.h>

enum class EPlayerDir
{
	Left,
	Right,
	Up,
	Down,
};

struct FPlayerInfo
{
	// 키: 세션 토큰
	static std::vector<bool> IsDeads; // IsDeads[3]: 3번 플레이어가 죽었는지
	static std::vector<std::string> Names; // Names[3]: 3번 플레이어의 이름
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

	inline void IncreaseBombCount()
	{
		++BombCount;
	}

	void SetPlayerDead();
	void SetCharacterType(ECharacterType _Character);
	void SetPlayerColor(ECharacterColor _Color);
	void PlayerInfoUpdate();

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	UStateManager State;

	UDefaultSceneComponent* DefaultComponent;
	USpriteRenderer* Renderer;
	USpriteRenderer* ShadowRenderer;
	USpriteRenderer* DebugRenderer;
	
	FVector PlayerPos;
	std::string Name = "Player";
	EPlayerDir PlayerDir = EPlayerDir::Down;
	ABombBase* Bomb = nullptr;
	int BombCount = 10;
	int MaxBombPower = 5;
	int BombPower = 0;
	float BaseSpeed = 200.0f;
	float Speed = 0.0f;
	float MaxSpeed = 400.0f;
	float CurSpeed = BaseSpeed + Speed;

	bool Push = false;
	bool Throw = false;

	std::map<EItemType, int> MPlayerItem;
	std::map<EItemType, int>::iterator MPlayerItemIter;

	float BlockSize = 0.0f;
	AMainPlayLevel* PlayLevel = nullptr;

	void PickUpItem();
	void AddItemCount(EItemType _ItemType);

	ECharacterColor PlayerColor = ECharacterColor::Green;
	std::string PlayerColorText = "_G";

	void CreateAnimation();

	//State
	void StateInit();

	void Idle(float _DeltaTime);
	void Run(float _DeltaTime);
	void TrapStart(float _DeltaTime);
	void Traped(float _DeltaTime);
	void TrapEnd(float _DeltaTime);
	void Die(float _DeltaTime);
	void Revival(float _DeltaTime);

	void KeyMove(float _DeltaTime, FVector _Dir, float _Speed);

};