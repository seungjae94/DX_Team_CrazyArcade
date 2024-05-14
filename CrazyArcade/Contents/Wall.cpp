#include "PreCompile.h"
#include "Wall.h"

AWall::AWall()
{
}

AWall::~AWall()
{
}

void AWall::BeginPlay()
{
	Super::BeginPlay();

	SetBlockType(EBlockType::Wall);
}

void AWall::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}
