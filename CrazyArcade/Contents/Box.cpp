#include "PreCompile.h"
#include "Box.h"

ABox::ABox()
{
}

ABox::~ABox()
{
}

void ABox::BeginPlay()
{
	Super::BeginPlay();

	SetBlockType(EBlockType::Box);
}

void ABox::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
