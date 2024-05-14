#include "PreCompile.h"
#include "VillageMap.h"
#include "MapConstant.h"

#include "Box.h"

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
	
	CreateHouse();
	CreateTree();
	CreateVillageBox();


}

void AVillageMap::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AVillageMap::CreateHouse()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			CreateWall(2 * i, 2 * j, MapImgRes::block_vil_house_1);
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			CreateWall(10 + 2 * i, 8 + 2 * j, MapImgRes::block_vil_house_2);
		}
	}

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			CreateWall(1 + 2 * i, 7 + 2 * j, MapImgRes::block_vil_house_0);
		}
	}

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			CreateWall(11 + 2 * i, 1 + 2 * j, MapImgRes::block_vil_house_0);
		}
	}
}

void AVillageMap::CreateTree()
{
	CreateWall(0, 6, MapImgRes::block_vil_tree_0);
	CreateWall(2, 6, MapImgRes::block_vil_tree_0);
	CreateWall(4, 6, MapImgRes::block_vil_tree_0);
	CreateWall(5, 1, MapImgRes::block_vil_tree_0);
	CreateWall(5, 3, MapImgRes::block_vil_tree_0);
	CreateWall(5, 7, MapImgRes::block_vil_tree_0);
	CreateWall(5, 9, MapImgRes::block_vil_tree_0);
	CreateWall(5, 11, MapImgRes::block_vil_tree_0);
	CreateWall(9, 1, MapImgRes::block_vil_tree_0);
	CreateWall(9, 3, MapImgRes::block_vil_tree_0);
	CreateWall(9, 5, MapImgRes::block_vil_tree_0);
	CreateWall(9, 9, MapImgRes::block_vil_tree_0);
	CreateWall(9, 11, MapImgRes::block_vil_tree_0);
	CreateWall(10, 6, MapImgRes::block_vil_tree_0);
	CreateWall(12, 6, MapImgRes::block_vil_tree_0);
	CreateWall(14, 6, MapImgRes::block_vil_tree_0);
}

void AVillageMap::CreateVillageBox()
{
	CreateBox(0, 3, MapImgRes::block_vil_box2);
	CreateBox(0, 7, MapImgRes::block_vil_box2);
	CreateBox(1, 5, MapImgRes::block_vil_box2);
	CreateBox(1, 8, MapImgRes::block_vil_box2);
	CreateBox(1, 12, MapImgRes::block_vil_box2);
	CreateBox(2, 3, MapImgRes::block_vil_box2);
	CreateBox(2, 7, MapImgRes::block_vil_box2);
	CreateBox(2, 10, MapImgRes::block_vil_box2);
	CreateBox(3, 1, MapImgRes::block_vil_box2);
	CreateBox(3, 5, MapImgRes::block_vil_box2);
	CreateBox(3, 8, MapImgRes::block_vil_box2);
	CreateBox(3, 12, MapImgRes::block_vil_box2);
	CreateBox(4, 3, MapImgRes::block_vil_box2);
	CreateBox(4, 7, MapImgRes::block_vil_box2);
	CreateBox(4, 10, MapImgRes::block_vil_box2);
	CreateBox(10, 0, MapImgRes::block_vil_box2);
	CreateBox(10, 4, MapImgRes::block_vil_box2);



	CreateBox(0, 5, MapImgRes::block_vil_box1);
	CreateBox(0, 8, MapImgRes::block_vil_box1);
	CreateBox(1, 3, MapImgRes::block_vil_box1);




	

}