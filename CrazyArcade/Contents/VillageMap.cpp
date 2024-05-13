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
	
	// Wall »ý¼º
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			CreateWall(2 * i, 2 * j, MapImgRes::block_house_1);
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			CreateWall(10 + 2 * i, 8 + 2 * j, MapImgRes::block_house_2);
		}
	}

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			CreateWall(1 + 2 * i, 7 + 2 * j, MapImgRes::block_house_0);
		}
	}

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			CreateWall(11 + 2 * i, 1 + 2 * j, MapImgRes::block_house_0);
		}
	}





}

void AVillageMap::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
