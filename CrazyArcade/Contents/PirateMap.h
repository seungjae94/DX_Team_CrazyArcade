#pragma once
#include "MapBase.h"

// Ό³Έν : VilageMap 
class APirateMap : public AMapBase
{
	GENERATED_BODY(AMapBase)
public:
	// constrcuter destructer
	APirateMap();
	~APirateMap();

	// delete Function
	APirateMap(const APirateMap& _Other) = delete;
	APirateMap(APirateMap&& _Other) noexcept = delete;
	APirateMap& operator=(const APirateMap& _Other) = delete;
	APirateMap& operator=(APirateMap&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;

private:
	void CreateFlag(int _x, int _y);
	void CreateWalls();
	void CreatePirateBoxs();
	void CreatePirateMoveBoxs();

};

