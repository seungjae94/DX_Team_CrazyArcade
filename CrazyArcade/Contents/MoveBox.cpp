#include "PreCompile.h"
#include "MoveBox.h"

AMoveBox::AMoveBox()
{
}

AMoveBox::~AMoveBox()
{
}

void AMoveBox::BeginPlay()
{
	Super::BeginPlay();

	SetBlockType(EBlockType::MoveBox);
}

void AMoveBox::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
