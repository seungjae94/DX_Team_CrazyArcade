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

	if (nullptr == UCrazyArcadeCore::Net)
	{
		MsgBoxAssert("네트워크 연결이 안된상태에서 아더플레어를 만들었습니다.");
	}

	std::shared_ptr<UEngineProtocol> Protocol = nullptr;

	do
	{
		Protocol = PopProtocol();
		if (nullptr == Protocol)
		{
			break;
		}

		EContentPacket PacketType = Protocol->GetPacketType<EContentPacket>();

		switch (PacketType)
		{
		case EContentPacket::ActorUpdatePacket:
		{
			std::shared_ptr<UActorUpdatePacket> ActorUpdatePacket = std::dynamic_pointer_cast<UActorUpdatePacket>(Protocol);

			SetActorLocation(ActorUpdatePacket->Pos);
			Renderer->ChangeAnimation(ActorUpdatePacket->SpriteName);

			int a = 0;
			break;
		}
		case EContentPacket::SpawnUpdatePacket:
		{
			std::shared_ptr<USpawnUpdatePacket> SpawnUpdatePacket = std::dynamic_pointer_cast<USpawnUpdatePacket>(Protocol);
			SetActorLocation(SpawnUpdatePacket->Pos);
			break;
		}
		default:
			break;
		}

	} while (nullptr != Protocol);
}