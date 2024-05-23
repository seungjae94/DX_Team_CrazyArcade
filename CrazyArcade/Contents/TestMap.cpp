#include "PreCompile.h"
#include "TestMap.h"

#include "MapConstant.h"

TestMap::TestMap()
{
}

TestMap::~TestMap()
{
}

void TestMap::BeginPlay()
{
	Super::BeginPlay();

	SetBackGround(MapImgRes::village_background);
	SetMapInfoSize(15, 13);

	PushPlayerStartPoint({ 2,  6 });
}

void TestMap::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void TestMap::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	if (true == IsDestroy())
	{
		return;
	}

	CreateTestMoveBox();
}

void TestMap::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}

void TestMap::CreateTestMoveBox()
{
	CreateMoveBox({ 0,  9 }, MapImgRes::block_vil_box0, EItemType::Roller);
	CreateMoveBox({ 1,  4 }, MapImgRes::block_vil_box0, EItemType::Roller);
	CreateMoveBox({ 2,  9 }, MapImgRes::block_vil_box0, EItemType::Superman);
	CreateMoveBox({ 2, 11 }, MapImgRes::block_vil_box0, EItemType::Superman);
	CreateMoveBox({ 3,  2 }, MapImgRes::block_vil_box0, EItemType::Superman);
	CreateMoveBox({ 3,  4 }, MapImgRes::block_vil_box0, EItemType::Owl);
	CreateMoveBox({ 4,  9 }, MapImgRes::block_vil_box0, EItemType::Owl);
	CreateMoveBox({ 4, 11 }, MapImgRes::block_vil_box0, EItemType::Owl);
	CreateMoveBox({  6,  1 }, MapImgRes::block_vil_box0, EItemType::Roller);
	CreateMoveBox({  6,  3 }, MapImgRes::block_vil_box0, EItemType::RedDevil);
	CreateMoveBox({  6,  5 }, MapImgRes::block_vil_box0, EItemType::RedDevil);
	CreateMoveBox({  6,  7 }, MapImgRes::block_vil_box0, EItemType::Bubble);
	CreateMoveBox({  6,  9 }, MapImgRes::block_vil_box0, EItemType::Bubble);
	CreateMoveBox({  6, 11 }, MapImgRes::block_vil_box0, EItemType::Bubble);
	CreateMoveBox({ 7,  1 }, MapImgRes::block_vil_box0, EItemType::RedDevil);
	CreateMoveBox({ 7,  4 }, MapImgRes::block_vil_box0, EItemType::Bubble);
	CreateMoveBox({ 7,  7 }, MapImgRes::block_vil_box0, EItemType::Fluid);
	CreateMoveBox({ 8,  7 }, MapImgRes::block_vil_box0, EItemType::Fluid);
	CreateMoveBox({  7, 10 }, MapImgRes::block_vil_box0, EItemType::Owl);
	CreateMoveBox({  8,  0 }, MapImgRes::block_vil_box0, EItemType::Superman);
	CreateMoveBox({  8,  2 }, MapImgRes::block_vil_box0, EItemType::RedDevil);
	CreateMoveBox({  8,  4 }, MapImgRes::block_vil_box0, EItemType::Superman);
	CreateMoveBox({  8,  6 }, MapImgRes::block_vil_box0, EItemType::Roller);
	CreateMoveBox({  8,  8 }, MapImgRes::block_vil_box0, EItemType::Owl);
	CreateMoveBox({  8, 10 }, MapImgRes::block_vil_box0, EItemType::Roller);
	CreateMoveBox({  8, 12 }, MapImgRes::block_vil_box0, EItemType::Superman);
	CreateMoveBox({ 10,  1 }, MapImgRes::block_vil_box0, EItemType::RedDevil);
	CreateMoveBox({ 10,  3 }, MapImgRes::block_vil_box0, EItemType::Superman);
	CreateMoveBox({ 11,  8 }, MapImgRes::block_vil_box0, EItemType::Roller);
	CreateMoveBox({ 11, 10 }, MapImgRes::block_vil_box0, EItemType::Roller);
	CreateMoveBox({ 12,  1 }, MapImgRes::block_vil_box0, EItemType::Owl);
	CreateMoveBox({ 12,  3 }, MapImgRes::block_vil_box0, EItemType::Owl);
	CreateMoveBox({ 13,  8 }, MapImgRes::block_vil_box0, EItemType::RedDevil);
	CreateMoveBox({ 13, 10 }, MapImgRes::block_vil_box0, EItemType::Roller);
	CreateMoveBox({ 14,  3 }, MapImgRes::block_vil_box0, EItemType::Roller);
}