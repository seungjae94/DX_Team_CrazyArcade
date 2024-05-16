#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/StateManager.h>
#include <EngineCore/SpriteRenderer.h>
#include "ServerTestPlayer.h"


class ServerTestOtherPlayer : public APlayer
{
	GENERATED_BODY(APlayer)

public:
	// constrcuter destructer
	ServerTestOtherPlayer();
	~ServerTestOtherPlayer();

	// delete Function
	ServerTestOtherPlayer(const ServerTestOtherPlayer& _Other) = delete;
	ServerTestOtherPlayer(ServerTestOtherPlayer&& _Other) noexcept = delete;
	ServerTestOtherPlayer& operator=(const ServerTestOtherPlayer& _Other) = delete;
	ServerTestOtherPlayer& operator=(ServerTestOtherPlayer&& _Other) noexcept = delete;

	USpriteRenderer* GetRenderer() {
		return Renderer;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

};