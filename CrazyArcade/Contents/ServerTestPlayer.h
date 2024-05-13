#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/NetObject.h>
#include <EngineCore/StateManager.h>
#include <EngineCore/SpriteRenderer.h>

enum class ServerDir
{
	Left,
	Right,
	Up,
	Down,
};

class ServerTestPlayer : public AActor, public UNetObject
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	ServerTestPlayer();
	~ServerTestPlayer();

	// delete Function
	ServerTestPlayer(const ServerTestPlayer& _Other) = delete;
	ServerTestPlayer(ServerTestPlayer&& _Other) noexcept = delete;
	ServerTestPlayer& operator=(const ServerTestPlayer& _Other) = delete;
	ServerTestPlayer& operator=(ServerTestPlayer&& _Other) noexcept = delete;


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	UStateManager State;

	USpriteRenderer* Renderer;
	USpriteRenderer* ShadowRenderer;

	FVector PlayerPos;
	std::string Name = "Player";
	ServerDir PlayerDir = ServerDir::Down;
	float BaseSpeed = 200.0f;
	float Speed = 1.0f;
	float CalSpeed = BaseSpeed * Speed;

	//State
	void StateInit();

	void Idle(float _DeltaTime);
	void Run(float _DeltaTime);
	void Die(float _DeltaTime);

	void KeyMove(float _DeltaTime, FVector _Dir, float _Speed);
};