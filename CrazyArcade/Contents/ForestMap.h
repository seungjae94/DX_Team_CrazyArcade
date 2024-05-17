#pragma once
#include "MapBase.h"

// Ό³Έν : VilageMap 
class AForestMap : public AMapBase
{
	GENERATED_BODY(AMapBase)
public:
	// constrcuter destructer
	AForestMap();
	~AForestMap();

	// delete Function
	AForestMap(const AForestMap& _Other) = delete;
	AForestMap(AForestMap&& _Other) noexcept = delete;
	AForestMap& operator=(const AForestMap& _Other) = delete;
	AForestMap& operator=(AForestMap&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;

private:
	void CreateHouses();
	void CreateTrees();
	void CreateVillageBoxs();
	void CreateVillageMoveBoxs();
	void CreateItems();

};

