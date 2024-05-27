#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/NetObject.h>
#include <EngineCore/StateManager.h>
#include <EngineCore/SpriteRenderer.h>
#include "Player.h"

enum class ServerDir
{
	Left,
	Right,
	Up,
	Down,
};

class ServerTestPlayer : public APlayer
{
	GENERATED_BODY(APlayer)

public:
	// constrcuter destructer
	ServerTestPlayer();
	~ServerTestPlayer();

	// delete Function
	ServerTestPlayer(const ServerTestPlayer& _Other) = delete;
	ServerTestPlayer(ServerTestPlayer&& _Other) noexcept = delete;
	ServerTestPlayer& operator=(const ServerTestPlayer& _Other) = delete;
	ServerTestPlayer& operator=(ServerTestPlayer&& _Other) noexcept = delete;

	USpriteRenderer* GetRenderer() {
		return Renderer;
	}

	void NeedleUpdate() override;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	bool IsSpawn = false;
	void SpawnBomb();

	bool IsDeadPacketSend = false;

	USpriteRenderer* ArrowRenderer;
};