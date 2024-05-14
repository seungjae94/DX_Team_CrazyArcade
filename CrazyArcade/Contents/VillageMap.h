#pragma once
#include "MapBase.h"

// Ό³Έν : VilageMap 
class AVillageMap : public AMapBase
{
	GENERATED_BODY(AMapBase)
public:
	// constrcuter destructer
	AVillageMap();
	~AVillageMap();

	// delete Function
	AVillageMap(const AVillageMap& _Other) = delete;
	AVillageMap(AVillageMap&& _Other) noexcept = delete;
	AVillageMap& operator=(const AVillageMap& _Other) = delete;
	AVillageMap& operator=(AVillageMap&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void CreateHouse();
	void CreateTree();
	void CreateVillageBox();
	void CreateVillageMoveBox();

};

