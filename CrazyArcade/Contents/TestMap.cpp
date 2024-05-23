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
}

void TestMap::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}
