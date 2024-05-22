#include "PreCompile.h"
#include "ServerTestOtherPlayer.h"
#include "Packets.h"
#include "CrazyArcadeCore.h"
#include "MainPlayLevel.h"
#include "MapBase.h"

ServerTestOtherPlayer::ServerTestOtherPlayer()
	:APlayer()
{
}

ServerTestOtherPlayer::~ServerTestOtherPlayer()
{
}

void ServerTestOtherPlayer::BeginPlay()
{
	Super::BeginPlay();
	InputOff();

	PlayLevel->GetMap()->PushOtherPlayer(this);
}

void ServerTestOtherPlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	ProtocolTick([=](std::shared_ptr<UEngineProtocol> _Packet) {
		std::shared_ptr<UActorUpdatePacket> UpdatePacket = std::dynamic_pointer_cast<UActorUpdatePacket>(_Packet);
		SetActorLocation(UpdatePacket->Pos);
		Renderer->ChangeAnimation(UpdatePacket->SpriteName);
		});
}