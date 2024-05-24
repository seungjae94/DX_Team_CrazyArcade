#include "PreCompile.h"
#include "PirateMap.h"
#include "MapConstant.h"

#include "Box.h"

APirateMap::APirateMap()
{
}

APirateMap::~APirateMap()
{
}

void APirateMap::BeginPlay()
{
	Super::BeginPlay();

	SetBackGround(MapImgRes::Pirate_background01);
	SetMapInfoSize(15, 13);

	PushPlayerStartPoint({  1,  7 });
	PushPlayerStartPoint({  2,  0 });
	PushPlayerStartPoint({  4,  5 });
	PushPlayerStartPoint({  5, 12 });
	PushPlayerStartPoint({  9, 12 });
	PushPlayerStartPoint({ 10,  5 });
	PushPlayerStartPoint({ 12,  0 });
	PushPlayerStartPoint({ 13,  7 });
}

void APirateMap::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	if (true == IsDestroy())
	{
		return;
	}

	CreateFlag(6, 6);
	CreatePirateBoxs();
	CreatePirateMoveBoxs();
	CreateWalls();
}

void APirateMap::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}

void APirateMap::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void APirateMap::CreateFlag(int _x, int _y)
{
	CreateAnimationWall({ _x, _y }, MapImgRes::block_Pirate_flag);
	CreateHollowWall({ _x + 1, _y });
	CreateHollowWall({ _x + 2, _y });
}

void APirateMap::CreateWalls()
{
	CreateWall({ 1,11 },MapImgRes::block_Pirate_wall);
	CreateWall({ 1,1 }, MapImgRes::block_Pirate_wall);
	CreateWall({ 13,11 }, MapImgRes::block_Pirate_wall);
	CreateWall({ 13,1 }, MapImgRes::block_Pirate_wall);
}


void APirateMap::CreatePirateBoxs()
{
	//box01
	CreateBox({ 0, 0 }, MapImgRes::block_Pirate_box1, EItemType::Bubble);
	CreateBox({ 0, 1 }, MapImgRes::block_Pirate_box1, EItemType::Fluid);
	CreateBox({ 0, 2 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 0, 3 }, MapImgRes::block_Pirate_box1, EItemType::Roller);
	CreateBox({ 0, 4 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 0, 5 }, MapImgRes::block_Pirate_box1, EItemType::Bubble);
	CreateBox({ 0, 7 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 0, 8 }, MapImgRes::block_Pirate_box1, EItemType::Bubble);
	CreateBox({ 0, 9 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 0, 10 }, MapImgRes::block_Pirate_box1, EItemType::Roller);
	CreateBox({ 0, 11 }, MapImgRes::block_Pirate_box1, EItemType::Fluid);
	CreateBox({ 0, 12 }, MapImgRes::block_Pirate_box1, EItemType::Owl);

	CreateBox({ 1, 2 }, MapImgRes::block_Pirate_box1, EItemType::Bubble);
	CreateBox({ 1, 3 }, MapImgRes::block_Pirate_box1, EItemType::Fluid);
	CreateBox({ 1, 10 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 1, 12 }, MapImgRes::block_Pirate_box1, EItemType::Bubble);

	CreateBox({ 2, 3 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 2, 4 }, MapImgRes::block_Pirate_box1, EItemType::Fluid);
	CreateBox({ 2, 11 }, MapImgRes::block_Pirate_box1, EItemType::Bubble);
	CreateBox({ 2, 12 }, MapImgRes::block_Pirate_box1, EItemType::Bubble);

	CreateBox({ 3, 0 }, MapImgRes::block_Pirate_box1, EItemType::Bubble);
	CreateBox({ 3, 1 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 3, 12 }, MapImgRes::block_Pirate_box1, EItemType::Fluid);

	CreateBox({ 4, 0 }, MapImgRes::block_Pirate_box1, EItemType::Fluid);
	CreateBox({ 4, 1 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 4, 2 }, MapImgRes::block_Pirate_box1, EItemType::Roller);
	CreateBox({ 4, 6 }, MapImgRes::block_Pirate_box1, EItemType::Roller);
	CreateBox({ 4, 7 }, MapImgRes::block_Pirate_box1, EItemType::Needle);
	CreateBox({ 4, 8 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 4, 9 }, MapImgRes::block_Pirate_box1);

	CreateBox({ 5, 0 }, MapImgRes::block_Pirate_box1, EItemType::Bubble);
	CreateBox({ 5, 1 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 5, 4 }, MapImgRes::block_Pirate_box1, EItemType::Bubble);
	CreateBox({ 5, 5 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 5, 6 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 5, 7 }, MapImgRes::block_Pirate_box1, EItemType::RedDevil);
	CreateBox({ 5, 8 }, MapImgRes::block_Pirate_box1);

	CreateBox({ 6, 0 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 6, 4 }, MapImgRes::block_Pirate_box1, EItemType::Bubble);
	CreateBox({ 6, 5 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 6, 7 }, MapImgRes::block_Pirate_box1, EItemType::Fluid);
	CreateBox({ 6, 8 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 6, 9 }, MapImgRes::block_Pirate_box1, EItemType::Owl);

	CreateBox({ 7, 0 }, MapImgRes::block_Pirate_box1, EItemType::Bubble);
	CreateBox({ 7, 3 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 7, 4 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 7, 5 }, MapImgRes::block_Pirate_box1, EItemType::Bubble);
	CreateBox({ 7, 7 }, MapImgRes::block_Pirate_box1, EItemType::Roller);
	CreateBox({ 7, 8 }, MapImgRes::block_Pirate_box1, EItemType::Fluid);
	CreateBox({ 7, 9 }, MapImgRes::block_Pirate_box1, EItemType::Bubble);

	CreateBox({ 8, 0 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 8, 4 }, MapImgRes::block_Pirate_box1, EItemType::Roller);
	CreateBox({ 8, 5 }, MapImgRes::block_Pirate_box1, EItemType::Roller);
	CreateBox({ 8, 7 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 8, 8 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 8, 9 }, MapImgRes::block_Pirate_box1, EItemType::Bubble);

	CreateBox({ 9, 0 }, MapImgRes::block_Pirate_box1, EItemType::Fluid);
	CreateBox({ 9, 1 }, MapImgRes::block_Pirate_box1, EItemType::Bubble);
	CreateBox({ 9, 4 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 9, 5 }, MapImgRes::block_Pirate_box1, EItemType::Bubble);
	CreateBox({ 9, 6 }, MapImgRes::block_Pirate_box1, EItemType::RedDevil);
	CreateBox({ 9, 7 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 9, 8 }, MapImgRes::block_Pirate_box1, EItemType::Fluid);
	CreateBox({ 9, 9 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 9, 10 }, MapImgRes::block_Pirate_box1);

	CreateBox({ 10, 0 }, MapImgRes::block_Pirate_box1, EItemType::Roller);
	CreateBox({ 10, 2 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 10, 7 }, MapImgRes::block_Pirate_box1, EItemType::Devil);
	CreateBox({ 10, 8 }, MapImgRes::block_Pirate_box1);

	CreateBox({ 11, 0 }, MapImgRes::block_Pirate_box1, EItemType::Bubble);
	CreateBox({ 11, 1 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 11, 2 }, MapImgRes::block_Pirate_box1, EItemType::Fluid);
	CreateBox({ 11, 3 }, MapImgRes::block_Pirate_box1, EItemType::Bubble);
	CreateBox({ 11, 6 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 11, 12 }, MapImgRes::block_Pirate_box1, EItemType::Roller);

	CreateBox({ 12, 3 }, MapImgRes::block_Pirate_box1, EItemType::Bubble);
	CreateBox({ 12, 11 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 12, 12 }, MapImgRes::block_Pirate_box1, EItemType::Fluid);

	CreateBox({ 13, 2 }, MapImgRes::block_Pirate_box1, EItemType::Fluid);
	CreateBox({ 13, 3 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 13, 4 }, MapImgRes::block_Pirate_box1, EItemType::Superman);
	CreateBox({ 13, 5 }, MapImgRes::block_Pirate_box1, EItemType::Turtle);
	CreateBox({ 13, 10 }, MapImgRes::block_Pirate_box1, EItemType::Bubble);
	CreateBox({ 13, 12 }, MapImgRes::block_Pirate_box1, EItemType::Ultra);

	CreateBox({ 14, 0 }, MapImgRes::block_Pirate_box1, EItemType::Roller);
	CreateBox({ 14, 1 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 14, 2 }, MapImgRes::block_Pirate_box1, EItemType::Bubble);
	CreateBox({ 14, 3 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 14, 4 }, MapImgRes::block_Pirate_box1, EItemType::Ultra);
	CreateBox({ 14, 5 }, MapImgRes::block_Pirate_box1, EItemType::Bubble);
	CreateBox({ 14, 6 }, MapImgRes::block_Pirate_box1, EItemType::Bubble);
	CreateBox({ 14, 7 }, MapImgRes::block_Pirate_box1, EItemType::Roller);
	CreateBox({ 14, 8 }, MapImgRes::block_Pirate_box1, EItemType::Roller);
	CreateBox({ 14, 9 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 14, 10 }, MapImgRes::block_Pirate_box1, EItemType::Fluid);
	CreateBox({ 14, 11 }, MapImgRes::block_Pirate_box1, EItemType::Bubble);
	CreateBox({ 14, 12 }, MapImgRes::block_Pirate_box1, EItemType::Fluid);

	//box02
	CreateBox({ 0, 6 }, MapImgRes::block_Pirate_box2, EItemType::Bubble);
	CreateBox({ 1, 5 }, MapImgRes::block_Pirate_box2, EItemType::RedDevil);
	CreateBox({ 1, 4 }, MapImgRes::block_Pirate_box2);
	CreateBox({ 3, 3 }, MapImgRes::block_Pirate_box2, EItemType::Roller);
	CreateBox({ 3, 2 }, MapImgRes::block_Pirate_box2, EItemType::Bubble);
	CreateBox({ 5, 10 }, MapImgRes::block_Pirate_box2);
	CreateBox({ 5, 9 }, MapImgRes::block_Pirate_box2, EItemType::Needle);
	CreateBox({ 7, 12 }, MapImgRes::block_Pirate_box2, EItemType::Bubble);
	CreateBox({ 10, 1 }, MapImgRes::block_Pirate_box2);
	CreateBox({ 10, 6 }, MapImgRes::block_Pirate_box2, EItemType::Devil);
	CreateBox({ 10, 9 }, MapImgRes::block_Pirate_box2);
	CreateBox({ 11, 8 }, MapImgRes::block_Pirate_box2, EItemType::Fluid);
	CreateBox({ 12, 4 }, MapImgRes::block_Pirate_box2, EItemType::Bubble);


}


void APirateMap::CreatePirateMoveBoxs()
{
	CreateMoveBox({ 3 , 5 }, MapImgRes::block_Pirate_box0, EItemType::Bubble);
	CreateMoveBox({ 2 , 6 }, MapImgRes::block_Pirate_box0);
	CreateMoveBox({ 2 , 7 }, MapImgRes::block_Pirate_box0, EItemType::Fluid);
	CreateMoveBox({ 2 , 8 }, MapImgRes::block_Pirate_box0);
	CreateMoveBox({ 2 , 9 }, MapImgRes::block_Pirate_box0, EItemType::Roller);
	CreateMoveBox({ 3 , 10 }, MapImgRes::block_Pirate_box0, EItemType::Bubble);

	CreateMoveBox({ 4 , 11 }, MapImgRes::block_Pirate_box0, EItemType::Fluid);
	CreateMoveBox({ 5 , 11 }, MapImgRes::block_Pirate_box0, EItemType::Roller);
	CreateMoveBox({ 6 , 11 }, MapImgRes::block_Pirate_box0, EItemType::Bubble);

	CreateMoveBox({ 7 , 10 }, MapImgRes::block_Pirate_box0, EItemType::Bubble);

	CreateMoveBox({ 8 , 11 }, MapImgRes::block_Pirate_box0);
	CreateMoveBox({ 9 , 11 }, MapImgRes::block_Pirate_box0, EItemType::Bubble);
	CreateMoveBox({ 10 , 11 }, MapImgRes::block_Pirate_box0, EItemType::Turtle);

	CreateMoveBox({ 6 , 2 }, MapImgRes::block_Pirate_box0, EItemType::Bubble);
	CreateMoveBox({ 7 , 2 }, MapImgRes::block_Pirate_box0);
	CreateMoveBox({ 8 , 2 }, MapImgRes::block_Pirate_box0, EItemType::Roller);

	CreateMoveBox({ 11 , 5 }, MapImgRes::block_Pirate_box0, EItemType::Owl);
	CreateMoveBox({ 12 , 6 }, MapImgRes::block_Pirate_box0);
	CreateMoveBox({ 12 , 7 }, MapImgRes::block_Pirate_box0);
	CreateMoveBox({ 12 , 8 }, MapImgRes::block_Pirate_box0, EItemType::Fluid);
	CreateMoveBox({ 12 , 9 }, MapImgRes::block_Pirate_box0);
	CreateMoveBox({ 11 , 10 }, MapImgRes::block_Pirate_box0, EItemType::Roller);

	CreateMoveBox({ 4 , 4 }, MapImgRes::block_Pirate_box0);
	CreateMoveBox({ 5 , 3 }, MapImgRes::block_Pirate_box0, EItemType::Ultra);
	CreateMoveBox({ 9 , 3 }, MapImgRes::block_Pirate_box0, EItemType::Roller);
	CreateMoveBox({ 10 , 4 }, MapImgRes::block_Pirate_box0, EItemType::Bubble);
}