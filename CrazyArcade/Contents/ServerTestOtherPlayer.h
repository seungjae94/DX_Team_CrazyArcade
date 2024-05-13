#pragma once
#include <EngineCore/Actor.h>
#include <EngineCore/StateManager.h>
#include <EngineCore/SpriteRenderer.h>
#include "ServerTestPlayer.h"


class ServerTestOtherPlayer : public ServerTestPlayer
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	ServerTestOtherPlayer();
	~ServerTestOtherPlayer();

	// delete Function
	ServerTestOtherPlayer(const ServerTestOtherPlayer& _Other) = delete;
	ServerTestOtherPlayer(ServerTestOtherPlayer&& _Other) noexcept = delete;
	ServerTestOtherPlayer& operator=(const ServerTestOtherPlayer& _Other) = delete;
	ServerTestOtherPlayer& operator=(ServerTestOtherPlayer&& _Other) noexcept = delete;


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

};