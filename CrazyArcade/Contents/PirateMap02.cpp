#include "PreCompile.h"
#include "PirateMap02.h"
#include "MapConstant.h"

#include "Box.h"

APirateMap02::APirateMap02()
{
}

APirateMap02::~APirateMap02()
{
}

void APirateMap02::BeginPlay()
{
	Super::BeginPlay();

	SetBackGround(MapImgRes::Pirate_background02);
	SetMapInfoSize(15, 13);
	Createlabps();
	CreatePirateBoxs();
	CreatePirateMoveBoxs();
	CreateWalls();
}

void APirateMap02::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

}

void APirateMap02::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}

void APirateMap02::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void APirateMap02::Createlabps()
{
	CreateAnimationWall({ 4, 4 }, MapImgRes::block_Pirate_labp);
	CreateAnimationWall({ 4, 8 }, MapImgRes::block_Pirate_labp);
	CreateAnimationWall({ 10, 4 }, MapImgRes::block_Pirate_labp);
	CreateAnimationWall({ 10, 8 }, MapImgRes::block_Pirate_labp);
}

void APirateMap02::CreateWalls()
{
	CreateWall({ 1,11 }, MapImgRes::block_Pirate_wall);
	CreateWall({ 1,1 }, MapImgRes::block_Pirate_wall);
	CreateWall({ 13,11 }, MapImgRes::block_Pirate_wall);
	CreateWall({ 13,1 }, MapImgRes::block_Pirate_wall);
}


void APirateMap02::CreatePirateBoxs()
{
	//box01
	CreateBox({ 0, 0 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 2, 0 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 4, 0 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 7, 0 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 10, 0 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 12, 0 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 14, 0 }, MapImgRes::block_Pirate_box1);

	CreateBox({ 6, 2 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 8, 2 }, MapImgRes::block_Pirate_box1);

	CreateBox({ 0, 3 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 7, 3 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 14, 3 }, MapImgRes::block_Pirate_box1);

	CreateBox({ 1, 4 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 13, 4 }, MapImgRes::block_Pirate_box1);


	CreateBox({ 0, 5 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 6, 5 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 7, 5 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 14, 5 }, MapImgRes::block_Pirate_box1);

	CreateBox({ 6, 6 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 7, 6 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 8, 6 }, MapImgRes::block_Pirate_box1);

	CreateBox({ 0, 7 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 7, 7 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 8, 7 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 14, 7 }, MapImgRes::block_Pirate_box1);

	CreateBox({ 1, 8 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 13, 8 }, MapImgRes::block_Pirate_box1);

	CreateBox({ 0, 9 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 7, 9 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 14, 9 }, MapImgRes::block_Pirate_box1);

	CreateBox({ 6, 10 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 8, 10 }, MapImgRes::block_Pirate_box1);

	CreateBox({ 0, 12 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 2, 12 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 4, 12 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 7, 12 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 10, 12 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 12, 12 }, MapImgRes::block_Pirate_box1);
	CreateBox({ 14, 12 }, MapImgRes::block_Pirate_box1);

	//box02
	CreateBox({ 1, 0 }, MapImgRes::block_Pirate_box2);
	CreateBox({ 3, 0 }, MapImgRes::block_Pirate_box2);
	CreateBox({ 5, 0 }, MapImgRes::block_Pirate_box2);
	CreateBox({ 6, 0 }, MapImgRes::block_Pirate_box2);
	CreateBox({ 8, 0 }, MapImgRes::block_Pirate_box2);
	CreateBox({ 9, 0 }, MapImgRes::block_Pirate_box2);
	CreateBox({ 11, 0 }, MapImgRes::block_Pirate_box2);
	CreateBox({ 13, 0 }, MapImgRes::block_Pirate_box2);


	CreateBox({ 0, 1 }, MapImgRes::block_Pirate_box2);
	CreateBox({ 14, 1 }, MapImgRes::block_Pirate_box2);

	CreateBox({ 0, 2 }, MapImgRes::block_Pirate_box2);
	CreateBox({ 4, 2 }, MapImgRes::block_Pirate_box2);
	CreateBox({ 10, 2 }, MapImgRes::block_Pirate_box2);
	CreateBox({ 11, 2 }, MapImgRes::block_Pirate_box2);
	CreateBox({ 14, 2 }, MapImgRes::block_Pirate_box2);

	CreateBox({ 6, 3 }, MapImgRes::block_Pirate_box2);
	CreateBox({ 8, 3 }, MapImgRes::block_Pirate_box2);

	CreateBox({ 0, 4 }, MapImgRes::block_Pirate_box2);
	CreateBox({ 14, 4 }, MapImgRes::block_Pirate_box2);

	CreateBox({ 0, 6 }, MapImgRes::block_Pirate_box2);
	CreateBox({ 14, 6 }, MapImgRes::block_Pirate_box2);

	CreateBox({ 0, 8 }, MapImgRes::block_Pirate_box2);
	CreateBox({ 14, 8 }, MapImgRes::block_Pirate_box2);

	CreateBox({ 6, 9 }, MapImgRes::block_Pirate_box2);
	CreateBox({ 8, 9 }, MapImgRes::block_Pirate_box2);

	CreateBox({ 0, 10 }, MapImgRes::block_Pirate_box2);
	CreateBox({ 4, 10 }, MapImgRes::block_Pirate_box2);
	CreateBox({ 10, 10 }, MapImgRes::block_Pirate_box2);
	CreateBox({ 14, 10 }, MapImgRes::block_Pirate_box2);

	CreateBox({ 0, 11 }, MapImgRes::block_Pirate_box2);
	CreateBox({ 14, 11 }, MapImgRes::block_Pirate_box2);

	CreateBox({ 1, 12 }, MapImgRes::block_Pirate_box2);
	CreateBox({ 3, 12 }, MapImgRes::block_Pirate_box2);
	CreateBox({ 5, 12 }, MapImgRes::block_Pirate_box2);
	CreateBox({ 6, 12 }, MapImgRes::block_Pirate_box2);
	CreateBox({ 8, 12 }, MapImgRes::block_Pirate_box2);
	CreateBox({ 9, 12 }, MapImgRes::block_Pirate_box2);
	CreateBox({ 11, 12 }, MapImgRes::block_Pirate_box2);
	CreateBox({ 13, 12 }, MapImgRes::block_Pirate_box2);

}


void APirateMap02::CreatePirateMoveBoxs()
{
	CreateMoveBox({ 2, 1 }, MapImgRes::block_Pirate_box0);
	CreateMoveBox({ 3, 1 }, MapImgRes::block_Pirate_box0);
	CreateMoveBox({ 5, 1 }, MapImgRes::block_Pirate_box0);
	CreateMoveBox({ 9, 1 }, MapImgRes::block_Pirate_box0);
	CreateMoveBox({ 11, 1 }, MapImgRes::block_Pirate_box0);
	CreateMoveBox({ 12, 1 }, MapImgRes::block_Pirate_box0);

	CreateMoveBox({ 3, 2 }, MapImgRes::block_Pirate_box0);
	CreateMoveBox({ 5, 2 }, MapImgRes::block_Pirate_box0);
	CreateMoveBox({ 7, 2 }, MapImgRes::block_Pirate_box0);
	CreateMoveBox({ 9, 2 }, MapImgRes::block_Pirate_box0);

	CreateMoveBox({ 2, 3 }, MapImgRes::block_Pirate_box0);
	CreateMoveBox({ 5, 3 }, MapImgRes::block_Pirate_box0);
	CreateMoveBox({ 9, 3 }, MapImgRes::block_Pirate_box0);
	CreateMoveBox({ 12, 3 }, MapImgRes::block_Pirate_box0);

	CreateMoveBox({ 3, 4 }, MapImgRes::block_Pirate_box0);
	CreateMoveBox({ 5, 4 }, MapImgRes::block_Pirate_box0);
	CreateMoveBox({ 7, 4 }, MapImgRes::block_Pirate_box0);
	CreateMoveBox({ 9, 4 }, MapImgRes::block_Pirate_box0);
	CreateMoveBox({ 11, 4 }, MapImgRes::block_Pirate_box0);

	CreateMoveBox({ 2, 5 }, MapImgRes::block_Pirate_box0);
	CreateMoveBox({ 5, 5 }, MapImgRes::block_Pirate_box0);
	CreateMoveBox({ 9, 5 }, MapImgRes::block_Pirate_box0);
	CreateMoveBox({ 12, 5 }, MapImgRes::block_Pirate_box0);

	CreateMoveBox({ 3, 6 }, MapImgRes::block_Pirate_box0);
	CreateMoveBox({ 4, 6 }, MapImgRes::block_Pirate_box0);
	CreateMoveBox({ 5, 6 }, MapImgRes::block_Pirate_box0);
	CreateMoveBox({ 9, 6 }, MapImgRes::block_Pirate_box0);
	CreateMoveBox({ 10, 6 }, MapImgRes::block_Pirate_box0);
	CreateMoveBox({ 11, 6 }, MapImgRes::block_Pirate_box0);

	CreateMoveBox({ 2, 7 }, MapImgRes::block_Pirate_box0);
	CreateMoveBox({ 5, 7 }, MapImgRes::block_Pirate_box0);
	CreateMoveBox({ 9, 7 }, MapImgRes::block_Pirate_box0);
	CreateMoveBox({ 12, 7 }, MapImgRes::block_Pirate_box0);

	CreateMoveBox({ 3, 8 }, MapImgRes::block_Pirate_box0);
	CreateMoveBox({ 5, 8 }, MapImgRes::block_Pirate_box0);
	CreateMoveBox({ 7, 8 }, MapImgRes::block_Pirate_box0);
	CreateMoveBox({ 9, 8 }, MapImgRes::block_Pirate_box0);
	CreateMoveBox({ 11, 8 }, MapImgRes::block_Pirate_box0);

	CreateMoveBox({ 2, 9 }, MapImgRes::block_Pirate_box0);
	CreateMoveBox({ 5, 9 }, MapImgRes::block_Pirate_box0);
	CreateMoveBox({ 9, 9 }, MapImgRes::block_Pirate_box0);
	CreateMoveBox({ 12, 9 }, MapImgRes::block_Pirate_box0);

	CreateMoveBox({ 3, 10 }, MapImgRes::block_Pirate_box0);
	CreateMoveBox({ 5, 10 }, MapImgRes::block_Pirate_box0);
	CreateMoveBox({ 7, 10 }, MapImgRes::block_Pirate_box0);
	CreateMoveBox({ 9, 10 }, MapImgRes::block_Pirate_box0);
	CreateMoveBox({ 11, 10 }, MapImgRes::block_Pirate_box0);

	CreateMoveBox({ 2, 11 }, MapImgRes::block_Pirate_box0);
	CreateMoveBox({ 3, 11 }, MapImgRes::block_Pirate_box0);
	CreateMoveBox({ 5, 11 }, MapImgRes::block_Pirate_box0);
	CreateMoveBox({ 9, 11 }, MapImgRes::block_Pirate_box0);
	CreateMoveBox({ 11, 11 }, MapImgRes::block_Pirate_box0);
	CreateMoveBox({ 12, 11 }, MapImgRes::block_Pirate_box0);

}

void APirateMap02::CreateItems()
{

}
