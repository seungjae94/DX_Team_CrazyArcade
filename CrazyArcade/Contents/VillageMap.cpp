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

	PushPlayerStartPoint({  0, 12 });
	PushPlayerStartPoint({  1,  1 });
	PushPlayerStartPoint({  6,  0 });
	PushPlayerStartPoint({  7, 12 });
	PushPlayerStartPoint({ 13, 11 });
	PushPlayerStartPoint({ 14,  0 });
}

void AVillageMap::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	if (true == IsDestroy())
	{
		return;
	}

	CreateHouses();
	CreateTrees();
	CreateVillageBoxs();
	CreateVillageMoveBoxs();
	CreateVillageBush();
}

void AVillageMap::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}

void AVillageMap::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AVillageMap::CreateHouses()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			CreateWall({ 2 * i, 2 * j }, MapImgRes::block_vil_house_1);
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			CreateWall({ 10 + 2 * i, 8 + 2 * j }, MapImgRes::block_vil_house_2);
		}
	}

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			CreateWall({ 1 + 2 * i, 7 + 2 * j }, MapImgRes::block_vil_house_0);
		}
	}

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			CreateWall({ 11 + 2 * i, 1 + 2 * j }, MapImgRes::block_vil_house_0);
		}
	}
}

void AVillageMap::CreateTrees()
{
	CreateWall({  0,  6 }, MapImgRes::block_vil_tree_0);
	CreateWall({  2,  6 }, MapImgRes::block_vil_tree_0);
	CreateWall({  4,  6 }, MapImgRes::block_vil_tree_0);
	CreateWall({  5,  1 }, MapImgRes::block_vil_tree_0);
	CreateWall({  5,  3 }, MapImgRes::block_vil_tree_0);
	CreateWall({  5,  7 }, MapImgRes::block_vil_tree_0);
	CreateWall({  5,  9 }, MapImgRes::block_vil_tree_0);
	CreateWall({  5, 11 }, MapImgRes::block_vil_tree_0);
	CreateWall({  9,  1 }, MapImgRes::block_vil_tree_0);
	CreateWall({  9,  3 }, MapImgRes::block_vil_tree_0);
	CreateWall({  9,  5 }, MapImgRes::block_vil_tree_0);
	CreateWall({  9,  9 }, MapImgRes::block_vil_tree_0);
	CreateWall({  9, 11 }, MapImgRes::block_vil_tree_0);
	CreateWall({ 10,  6 }, MapImgRes::block_vil_tree_0);
	CreateWall({ 12,  6 }, MapImgRes::block_vil_tree_0);
	CreateWall({ 14,  6 }, MapImgRes::block_vil_tree_0);
}

void AVillageMap::CreateVillageBoxs()
{
	CreateBox({  0,  3 }, MapImgRes::block_vil_box2, EItemType::Bubble);
	CreateBox({  0,  7 }, MapImgRes::block_vil_box2, EItemType::Fluid);
	CreateBox({  1,  5 }, MapImgRes::block_vil_box2);
	CreateBox({  1,  8 }, MapImgRes::block_vil_box2, EItemType::Bubble);
	CreateBox({  1, 12 }, MapImgRes::block_vil_box2, EItemType::Bubble);
	CreateBox({  2,  3 }, MapImgRes::block_vil_box2);
	CreateBox({  2,  7 }, MapImgRes::block_vil_box2, EItemType::Roller);
	CreateBox({  2, 10 }, MapImgRes::block_vil_box2, EItemType::Roller);
	CreateBox({  3,  1 }, MapImgRes::block_vil_box2, EItemType::Fluid);
	CreateBox({  3,  5 }, MapImgRes::block_vil_box2);
	CreateBox({  3,  8 }, MapImgRes::block_vil_box2);
	CreateBox({  3, 12 }, MapImgRes::block_vil_box2, EItemType::Fluid);
	CreateBox({  4,  3 }, MapImgRes::block_vil_box2, EItemType::Bubble);
	CreateBox({  4,  7 }, MapImgRes::block_vil_box2, EItemType::RedDevil);
	CreateBox({  4, 10 }, MapImgRes::block_vil_box2);
	CreateBox({ 10,  0 }, MapImgRes::block_vil_box2, EItemType::Ultra);
	CreateBox({ 10,  4 }, MapImgRes::block_vil_box2, EItemType::Fluid);
	CreateBox({ 10,  9 }, MapImgRes::block_vil_box2, EItemType::Bubble);
	CreateBox({ 11,  2 }, MapImgRes::block_vil_box2);
	CreateBox({ 11,  7 }, MapImgRes::block_vil_box2, EItemType::Roller);
	CreateBox({ 11, 11 }, MapImgRes::block_vil_box2, EItemType::Roller);
	CreateBox({ 12,  0 }, MapImgRes::block_vil_box2);
	CreateBox({ 12,  4 }, MapImgRes::block_vil_box2, EItemType::Fluid);
	CreateBox({ 12,  9 }, MapImgRes::block_vil_box2, EItemType::Bubble);
	CreateBox({ 13,  2 }, MapImgRes::block_vil_box2, EItemType::Bubble);
	CreateBox({ 13,  7 }, MapImgRes::block_vil_box2);
	CreateBox({ 14,  4 }, MapImgRes::block_vil_box2, EItemType::Bubble);
	CreateBox({ 14,  9 }, MapImgRes::block_vil_box2);

	CreateBox({  0,  5 }, MapImgRes::block_vil_box1, EItemType::Roller);
	CreateBox({  0,  8 }, MapImgRes::block_vil_box1);
	CreateBox({  1,  3 }, MapImgRes::block_vil_box1);
	CreateBox({  2,  1 }, MapImgRes::block_vil_box1, EItemType::Roller);
	CreateBox({  2,  5 }, MapImgRes::block_vil_box1, EItemType::Roller);
	CreateBox({  2,  8 }, MapImgRes::block_vil_box1, EItemType::Ultra);
	CreateBox({  2, 12 }, MapImgRes::block_vil_box1, EItemType::Bubble);
	CreateBox({  3,  0 }, MapImgRes::block_vil_box1, EItemType::RedDevil);
	CreateBox({  3,  3 }, MapImgRes::block_vil_box1);
	CreateBox({  3, 10 }, MapImgRes::block_vil_box1, EItemType::Fluid);
	CreateBox({  4,  1 }, MapImgRes::block_vil_box1, EItemType::Bubble);
	CreateBox({  4,  5 }, MapImgRes::block_vil_box1, EItemType::Roller);
	CreateBox({  4,  8 }, MapImgRes::block_vil_box1);
	CreateBox({  4, 12 }, MapImgRes::block_vil_box1);
	CreateBox({ 10,  2 }, MapImgRes::block_vil_box1, EItemType::Bubble);
	CreateBox({ 10,  5 }, MapImgRes::block_vil_box1);
	CreateBox({ 10,  7 }, MapImgRes::block_vil_box1, EItemType::Fluid);
	CreateBox({ 10, 11 }, MapImgRes::block_vil_box1);
	CreateBox({ 11,  0 }, MapImgRes::block_vil_box1, EItemType::Bubble);
	CreateBox({ 11,  4 }, MapImgRes::block_vil_box1);
	CreateBox({ 11,  9 }, MapImgRes::block_vil_box1);
	CreateBox({ 11, 12 }, MapImgRes::block_vil_box1, EItemType::Bubble);
	CreateBox({ 12,  2 }, MapImgRes::block_vil_box1, EItemType::Fluid);
	CreateBox({ 12,  5 }, MapImgRes::block_vil_box1);
	CreateBox({ 12,  7 }, MapImgRes::block_vil_box1, EItemType::Fluid);
	CreateBox({ 13,  4 }, MapImgRes::block_vil_box1, EItemType::Roller);
	CreateBox({ 13,  9 }, MapImgRes::block_vil_box1, EItemType::Roller);
	CreateBox({ 14,  5 }, MapImgRes::block_vil_box1);
	CreateBox({ 14,  7 }, MapImgRes::block_vil_box1, EItemType::Bubble);
}

void AVillageMap::CreateVillageMoveBoxs()
{
	CreateMoveBox({  0,  9 }, MapImgRes::block_vil_box0, EItemType::Bubble);
	CreateMoveBox({  1,  4 }, MapImgRes::block_vil_box0, EItemType::Bubble);
	CreateMoveBox({  2,  9 }, MapImgRes::block_vil_box0);
	CreateMoveBox({  2, 11 }, MapImgRes::block_vil_box0, EItemType::Roller);
	CreateMoveBox({  3,  2 }, MapImgRes::block_vil_box0);
	CreateMoveBox({  3,  4 }, MapImgRes::block_vil_box0, EItemType::Fluid);
	CreateMoveBox({  4,  9 }, MapImgRes::block_vil_box0);
	CreateMoveBox({  4, 11 }, MapImgRes::block_vil_box0, EItemType::Bubble);
	CreateMoveBox({  6,  1 }, MapImgRes::block_vil_box0, EItemType::Roller);
	CreateMoveBox({  6,  3 }, MapImgRes::block_vil_box0);
	CreateMoveBox({  6,  5 }, MapImgRes::block_vil_box0, EItemType::Superman);
	CreateMoveBox({  6,  7 }, MapImgRes::block_vil_box0),
	CreateMoveBox({  6,  9 }, MapImgRes::block_vil_box0),
	CreateMoveBox({  6, 11 }, MapImgRes::block_vil_box0, EItemType::Bubble),
	CreateMoveBox({  7,  1 }, MapImgRes::block_vil_box0, EItemType::Ultra);
	CreateMoveBox({  7,  4 }, MapImgRes::block_vil_box0, EItemType::Bubble);
	CreateMoveBox({  7,  7 }, MapImgRes::block_vil_box0, EItemType::Roller);
	CreateMoveBox({  8,  7 }, MapImgRes::block_vil_box0);
	CreateMoveBox({  7, 10 }, MapImgRes::block_vil_box0, EItemType::Fluid);
	CreateMoveBox({  8,  0 }, MapImgRes::block_vil_box0);
	CreateMoveBox({  8,  2 }, MapImgRes::block_vil_box0, EItemType::RedDevil);
	CreateMoveBox({  8,  4 }, MapImgRes::block_vil_box0, EItemType::Devil);
	CreateMoveBox({  8,  6 }, MapImgRes::block_vil_box0, EItemType::Devil);
	CreateMoveBox({  8,  8 }, MapImgRes::block_vil_box0, EItemType::Bubble);
	CreateMoveBox({  8, 10 }, MapImgRes::block_vil_box0);
	CreateMoveBox({  8, 12 }, MapImgRes::block_vil_box0);
	CreateMoveBox({ 10,  1 }, MapImgRes::block_vil_box0, EItemType::Fluid);
	CreateMoveBox({ 10,  3 }, MapImgRes::block_vil_box0);
	CreateMoveBox({ 11,  8 }, MapImgRes::block_vil_box0);
	CreateMoveBox({ 11, 10 }, MapImgRes::block_vil_box0, EItemType::Fluid);
	CreateMoveBox({ 12,  1 }, MapImgRes::block_vil_box0, EItemType::Roller);
	CreateMoveBox({ 12,  3 }, MapImgRes::block_vil_box0);
	CreateMoveBox({ 13,  8 }, MapImgRes::block_vil_box0, EItemType::Bubble);
	CreateMoveBox({ 13, 10 }, MapImgRes::block_vil_box0);
	CreateMoveBox({ 14,  3 }, MapImgRes::block_vil_box0, EItemType::Roller);
}

void AVillageMap::CreateVillageBush()
{
	CreateBush({  1,  6 }, MapImgRes::block_vil_bush);
	CreateBush({  3,  6 }, MapImgRes::block_vil_bush);
	CreateBush({  5,  0 }, MapImgRes::block_vil_bush);
	CreateBush({  5,  2 }, MapImgRes::block_vil_bush);
	CreateBush({  5,  4 }, MapImgRes::block_vil_bush);
	CreateBush({  5,  6 }, MapImgRes::block_vil_bush);
	CreateBush({  5,  8 }, MapImgRes::block_vil_bush);
	CreateBush({  5, 10 }, MapImgRes::block_vil_bush);
	CreateBush({  5, 12 }, MapImgRes::block_vil_bush);
	CreateBush({  9,  0 }, MapImgRes::block_vil_bush);
	CreateBush({  9,  2 }, MapImgRes::block_vil_bush);
	CreateBush({  9,  4 }, MapImgRes::block_vil_bush);
	CreateBush({  9,  6 }, MapImgRes::block_vil_bush);
	CreateBush({  9,  8 }, MapImgRes::block_vil_bush);
	CreateBush({  9, 10 }, MapImgRes::block_vil_bush);
	CreateBush({  9, 12 }, MapImgRes::block_vil_bush);
	CreateBush({ 11,  6 }, MapImgRes::block_vil_bush);
	CreateBush({ 13,  6 }, MapImgRes::block_vil_bush);
}