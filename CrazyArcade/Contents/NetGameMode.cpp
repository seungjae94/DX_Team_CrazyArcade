#include "PreCompile.h"
#include "NetGameMode.h"
#include "ServerManager.h"
#include "CrazyArcadeCore.h"

ANetGameMode::ANetGameMode()
{
}

ANetGameMode::~ANetGameMode()
{
}

void ANetGameMode::BeginPlay()
{
    Super::BeginPlay();

    UCrazyArcadeCore::NetWindow.ReserveHandler([=]() {
        if (false == IsHandlerInit)
        {
            HandlerInit();
            IsHandlerInit = true;
        }
        });
}

void ANetGameMode::Tick(float _DeltaTime)
{
    Super::Tick(_DeltaTime);
}
