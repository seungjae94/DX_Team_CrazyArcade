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
	SetTileInfoSize(15, 13);
}

void AVillageMap::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
