#include "PreCompile.h"
#include "BlockBase.h"

ABlockBase::ABlockBase()
{
}

ABlockBase::~ABlockBase()
{
}

void ABlockBase::BeginPlay()
{
	Super::BeginPlay();
}

void ABlockBase::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
