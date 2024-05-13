#include "PreCompile.h"
#include "VillageMap.h"
#include "MapConstant.h"

AVillageMap::AVillageMap()
{
}

AVillageMap::~AVillageMap()
{
}

void AVillageMap::BeginPlay()
{
	Super::BeginPlay();

	SetBackGround(MapImgRes::village_background);
	SetMapInfoSize(15, 13);

	CreateWall(0, 0, MapImgRes::block_house_1);
}

void AVillageMap::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
