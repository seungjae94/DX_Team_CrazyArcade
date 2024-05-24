#pragma once
#include "MapBase.h"

// Ό³Έν : VilageMap 
class APirateMap02 : public AMapBase
{
	GENERATED_BODY(AMapBase)
public:
	// constrcuter destructer
	APirateMap02();
	~APirateMap02();

	// delete Function
	APirateMap02(const APirateMap02& _Other) = delete;
	APirateMap02(APirateMap02&& _Other) noexcept = delete;
	APirateMap02& operator=(const APirateMap02& _Other) = delete;
	APirateMap02& operator=(APirateMap02&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;

private:
	void Createlabps();
	void CreateWalls();
	void CreatePirateBoxs();
	void CreatePirateMoveBoxs();

};

