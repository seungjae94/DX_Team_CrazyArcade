#pragma once
#include <EngineCore/GameMode.h>
#include <EngineBase/EngineThread.h>
#include <EngineBase/EngineNetHeader.h>
#include <EngineCore/EngineNetWindow.h>
#include <EngineBase/EngineDispatcher.h>
#include "MainPlayLevel.h"

// Ό³Έν :
class UEngineNetWindow;
class ServerTestPlayer;
class AServerGameMode : public AMainPlayLevel
{
	GENERATED_BODY(AMainPlayLevel)

	

public:
	// constrcuter destructer
	AServerGameMode();
	~AServerGameMode();

	// delete Function
	AServerGameMode(const AServerGameMode& _Other) = delete;
	AServerGameMode(AServerGameMode&& _Other) noexcept = delete;
	AServerGameMode& operator=(const AServerGameMode& _Other) = delete;
	AServerGameMode& operator=(AServerGameMode&& _Other) noexcept = delete;


	void HandlerInit() override;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;

	void CheckGame(float _DeltaTime);

	float BombDestoryTime = 1.0f;
	float CurBombDestoryTime = 0.0f;

	float WinTime = 5.0f;
	float CurWinTime = 0.0f;


};

