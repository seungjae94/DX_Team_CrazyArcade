#include "PreCompile.h"
#include "ServerTestOtherPlayer.h"
#include "Packets.h"
#include "CrazyArcadeCore.h"


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