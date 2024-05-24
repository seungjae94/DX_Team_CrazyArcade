#include "PreCompile.h"
#include "ForestMap.h"
#include "MapConstant.h"

#include "Box.h"

AForestMap::AForestMap()
{
}

AForestMap::~AForestMap()
{
}

void AForestMap::BeginPlay()
{
	Super::BeginPlay();

	SetBackGround(MapImgRes::Forest_background);
	SetMapInfoSize(15, 13);

	PushPlayerStartPoint({  5,  9 });
	PushPlayerStartPoint({  7,  3 });
	PushPlayerStartPoint({  8, 12 });
	PushPlayerStartPoint({ 14,  3 });
}

void AForestMap::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	if (true == IsDestroy())
	{
		return;
	}

	CreatePools();
	Createrocks();
	CreateForestLeafsAndBushs();
	CreateForestMoveBoxs();
}

void AForestMap::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}

void AForestMap::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AForestMap::CreatePool(int _x,int _y)
{
	CreateWall({ _x,_y }, MapImgRes::block_forest_pool);
	CreateHollowWall({ _x + 1,_y });
	CreateHollowWall({ _x + 2,_y });
	CreateHollowWall({ _x ,_y + 1 });
	CreateHollowWall({ _x + 1,_y + 1 });
	CreateHollowWall({ _x+ 2,_y + 1 });
}

void AForestMap::CreatePools()
{
	CreatePool(4, 1);
	CreatePool(8, 1);
	CreatePool(12, 1);
	CreatePool(3, 4);
	CreatePool(7, 4);
	CreatePool(11, 4);
	CreatePool(2, 7);
	CreatePool(6, 7);
	CreatePool(10, 7);
	CreatePool(1, 10);
	CreatePool(5, 10);
	CreatePool(9, 10);

}

void AForestMap::Createrocks()
{
	CreateWall({ 0, 0 }, MapImgRes::block_forest_rock);
	CreateWall({ 0, 2 }, MapImgRes::block_forest_rock);
	CreateWall({ 0, 8 }, MapImgRes::block_forest_rock);
	CreateWall({ 1, 4 }, MapImgRes::block_forest_rock);
	CreateWall({ 1, 6 }, MapImgRes::block_forest_rock);
	CreateWall({ 2, 1 }, MapImgRes::block_forest_rock);
	CreateWall({ 2, 3 }, MapImgRes::block_forest_rock);
	CreateWall({ 13, 9 }, MapImgRes::block_forest_rock);
	CreateWall({ 13, 11 }, MapImgRes::block_forest_rock);
	CreateWall({ 14, 6 }, MapImgRes::block_forest_rock);
	CreateWall({ 14, 8 }, MapImgRes::block_forest_rock);
}

void AForestMap::CreateForestLeafsAndBushs()
{
	//leaf1
	CreateBox({ 0,  1 }, MapImgRes::block_forest_leef1, EItemType::Bubble);
	CreateBox({ 0,  3 }, MapImgRes::block_forest_leef1, EItemType::Fluid);
	CreateBox({ 0,  5 }, MapImgRes::block_forest_leef1, EItemType::Roller);
	CreateBox({ 0,  7 }, MapImgRes::block_forest_leef1);
	CreateBox({ 0, 11 }, MapImgRes::block_forest_leef1, EItemType::Owl);
	CreateBox({ 1,  0 }, MapImgRes::block_forest_leef1, EItemType::Roller);
	CreateBox({ 1,  2 }, MapImgRes::block_forest_leef1, EItemType::Needle);
	CreateBox({ 1,  8 }, MapImgRes::block_forest_leef1);
	CreateBox({ 1, 12 }, MapImgRes::block_forest_leef1, EItemType::Bubble);
	CreateBox({ 2,  5 }, MapImgRes::block_forest_leef1);
	CreateBox({ 2,  9 }, MapImgRes::block_forest_leef1, EItemType::Turtle);
	CreateBox({ 3,  0 }, MapImgRes::block_forest_leef1);
	CreateBox({ 3,  2 }, MapImgRes::block_forest_leef1, EItemType::Roller);
	CreateBox({ 3,  6 }, MapImgRes::block_forest_leef1, EItemType::Bubble);
	CreateBox({ 3, 12 }, MapImgRes::block_forest_leef1, EItemType::Devil);
	CreateBox({ 4,  3 }, MapImgRes::block_forest_leef1);
	CreateBox({ 4, 11 }, MapImgRes::block_forest_leef1, EItemType::Needle);
	CreateBox({ 5,  0 }, MapImgRes::block_forest_leef1);
	CreateBox({ 5, 12 }, MapImgRes::block_forest_leef1, EItemType::Roller);
	CreateBox({ 7,  0 }, MapImgRes::block_forest_leef1, EItemType::Bubble);
	CreateBox({ 9,  6 }, MapImgRes::block_forest_leef1);
	CreateBox({ 9,  8 }, MapImgRes::block_forest_leef1, EItemType::Fluid);
	CreateBox({ 10,  5 }, MapImgRes::block_forest_leef1, EItemType::Ultra);
	CreateBox({ 10,  9 }, MapImgRes::block_forest_leef1);
	CreateBox({ 11,  0 }, MapImgRes::block_forest_leef1, EItemType::Bubble);
	CreateBox({ 11,  6 }, MapImgRes::block_forest_leef1, EItemType::Fluid);
	CreateBox({ 12,  9 }, MapImgRes::block_forest_leef1, EItemType::Needle);
	CreateBox({ 12,  11 }, MapImgRes::block_forest_leef1);
	CreateBox({ 13,  0 }, MapImgRes::block_forest_leef1, EItemType::RedDevil);
	CreateBox({ 13,  6 }, MapImgRes::block_forest_leef1);
	CreateBox({ 13,  12 }, MapImgRes::block_forest_leef1);
	CreateBox({ 14,   5 }, MapImgRes::block_forest_leef1, EItemType::Owl);
	CreateBox({ 14,   7 }, MapImgRes::block_forest_leef1);
	CreateBox({ 14,  11 }, MapImgRes::block_forest_leef1, EItemType::Roller);
	//leaf2

	CreateBox({ 0,   4 }, MapImgRes::block_forest_leef2, EItemType::Bubble);
	CreateBox({ 0,  10 }, MapImgRes::block_forest_leef2, EItemType::Fluid);
	CreateBox({ 1,  1 }, MapImgRes::block_forest_leef2, EItemType::Fluid);
	CreateBox({ 1,  7 }, MapImgRes::block_forest_leef2, EItemType::Roller);
	CreateBox({ 1,  9 }, MapImgRes::block_forest_leef2);
	CreateBox({ 2,  2 }, MapImgRes::block_forest_leef2, EItemType::Bubble);
	CreateBox({ 2,  4 }, MapImgRes::block_forest_leef2);
	CreateBox({ 2,  6 }, MapImgRes::block_forest_leef2, EItemType::Roller);
	CreateBox({ 2,  12 }, MapImgRes::block_forest_leef2, EItemType::Bubble);
	CreateBox({ 3,  3 }, MapImgRes::block_forest_leef2, EItemType::Fluid);
	CreateBox({ 3,  9 }, MapImgRes::block_forest_leef2, EItemType::Bubble);
	CreateBox({ 4,  0 }, MapImgRes::block_forest_leef2);
	CreateBox({ 4,  10 }, MapImgRes::block_forest_leef2, EItemType::Roller);
	CreateBox({ 4,  12 }, MapImgRes::block_forest_leef2, EItemType::Bubble);
	CreateBox({ 6,  0 }, MapImgRes::block_forest_leef2);
	CreateBox({ 6,  12 }, MapImgRes::block_forest_leef2, EItemType::Fluid);
	CreateBox({ 7,  1 }, MapImgRes::block_forest_leef2);
	CreateBox({ 8,  0 }, MapImgRes::block_forest_leef2, EItemType::Fluid);
	CreateBox({ 8,  6 }, MapImgRes::block_forest_leef2, EItemType::Bubble);
	CreateBox({ 9,  7 }, MapImgRes::block_forest_leef2);
	CreateBox({ 10,  0 }, MapImgRes::block_forest_leef2, EItemType::Superman);
	CreateBox({ 10,  6 }, MapImgRes::block_forest_leef2, EItemType::Roller);
	CreateBox({ 10,  12 }, MapImgRes::block_forest_leef2, EItemType::RedDevil);
	CreateBox({ 11,  1 }, MapImgRes::block_forest_leef2);
	CreateBox({ 11,  9 }, MapImgRes::block_forest_leef2, EItemType::Bubble);
	CreateBox({ 12,  0 }, MapImgRes::block_forest_leef2, EItemType::Ultra);
	CreateBox({ 12,  6 }, MapImgRes::block_forest_leef2);
	CreateBox({ 12,  10 }, MapImgRes::block_forest_leef2);
	CreateBox({ 12,  12 }, MapImgRes::block_forest_leef2, EItemType::Roller);
	CreateBox({ 13,  7 }, MapImgRes::block_forest_leef2, EItemType::Fluid);
	CreateBox({ 14,  0 }, MapImgRes::block_forest_leef2, EItemType::Fluid);
	CreateBox({ 14,  10 }, MapImgRes::block_forest_leef2, EItemType::Bubble);

	//bush1
	CreateBox({ 0 , 12 }, MapImgRes::block_forest_bush1, EItemType::Bubble);
	CreateBox({ 4 ,  6 }, MapImgRes::block_forest_bush1);
	CreateBox({ 4 ,  9 }, MapImgRes::block_forest_bush1, EItemType::Owl);
	CreateBox({ 5 ,  3 }, MapImgRes::block_forest_bush1);
	CreateBox({ 7 ,  2 }, MapImgRes::block_forest_bush1, EItemType::Bubble);
	CreateBox({ 7 ,  12 }, MapImgRes::block_forest_bush1, EItemType::Owl);
	CreateBox({ 11 ,  2 }, MapImgRes::block_forest_bush1);

	//bush2
	CreateBox({ 0 ,  9 }, MapImgRes::block_forest_bush2, EItemType::Fluid);
	CreateBox({ 1 ,  5 }, MapImgRes::block_forest_bush2, EItemType::Owl);
	CreateBox({ 3 ,  1 }, MapImgRes::block_forest_bush2);
	CreateBox({ 9 ,  9 }, MapImgRes::block_forest_bush2, EItemType::Roller);
	CreateBox({ 9 ,  12 }, MapImgRes::block_forest_bush2);
	CreateBox({ 10 ,  4 }, MapImgRes::block_forest_bush2, EItemType::Turtle);
	CreateBox({ 13 ,  8 }, MapImgRes::block_forest_bush2, EItemType::Owl);
	CreateBox({ 14 ,  4 }, MapImgRes::block_forest_bush2);
	CreateBox({ 14 ,  12 }, MapImgRes::block_forest_bush2, EItemType::Bubble);

	//bush3
	CreateBox({ 9 ,  0 }, MapImgRes::block_forest_bush3);

}

void AForestMap::CreateForestMoveBoxs()
{
	CreateMoveBox({ 0 , 6 }, MapImgRes::block_forest_basket, EItemType::Bubble);
	CreateMoveBox({ 1 , 3 }, MapImgRes::block_forest_basket);
	CreateMoveBox({ 2 , 0 }, MapImgRes::block_forest_basket, EItemType::Fluid);
	CreateMoveBox({ 11 , 12 }, MapImgRes::block_forest_basket);
	CreateMoveBox({ 13 , 10 }, MapImgRes::block_forest_basket, EItemType::Bubble);
	CreateMoveBox({ 14 ,  9 }, MapImgRes::block_forest_basket, EItemType::Roller);
}
