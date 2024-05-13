#include "PreCompile.h"
#include "CrazyArcadeCore.h"
#include "InitTestGameMode.h"

UCrazyArcadeCore::UCrazyArcadeCore()
{
}

UCrazyArcadeCore::~UCrazyArcadeCore()
{
}

void UCrazyArcadeCore::Initialize()
{
	GEngine->CreateLevel<AInitTestGameMode>("InitTestLevel");
	GEngine->ChangeLevel("InitTestLevel");
}
