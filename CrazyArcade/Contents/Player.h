#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/StateManager.h>
#include <EngineCore/SpriteRenderer.h>
#include "MapBase.h"

enum class EPlayerDir
{
	Left,
	Right,
	Up,
	Down,
};

class APlayer : public AActor
{
	GENERATED_BODY(AActor)

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

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	UStateManager State;

	USpriteRenderer* Renderer;
	USpriteRenderer* ShadowRenderer;
	USpriteRenderer* DebugRenderer;
	
	FVector PlayerPos;
	std::string Name = "Player";
	EPlayerDir PlayerDir = EPlayerDir::Down;
	int BombCount = 1;
	int BombPower = 1;
	float BaseSpeed = 200.0f;
	float Speed = 1.0f;
	float CalSpeed = BaseSpeed * Speed;

	bool Push = false;
	bool Throw = false;

	std::map<EPlayerItem, int> MPlayerItem;
	std::map<EPlayerItem, int>::iterator MPlayerItemIter;

	float BlockSize = AMapBase::GetBlockSize();

	//State
	void StateInit();

	void Idle(float _DeltaTime);
	void Run(float _DeltaTime);
	void Lock(float _DeltaTime);
	void Escape(float _DeltaTime);
	void Die(float _DeltaTime);

	virtual void KeyMove(float _DeltaTime, FVector _Dir, float _Speed);
};