#include "PreCompile.h"
#include "OtherPlayer.h"
#include <EngineCore/Collision.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include "CrazyArcadeCore.h"
#include "Packets.h"

AOtherPlayer::AOtherPlayer() 
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");

	USpriteRenderer* Ptr = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Ptr->SetupAttachment(Root);

	SetRoot(Root);

	SetActorScale3D({ 150.0f, 150.0f ,150.0f });
}

AOtherPlayer::~AOtherPlayer() 
{
}

void AOtherPlayer::BeginPlay()
{
	AActor::BeginPlay();
}

void AOtherPlayer::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
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
		case ActorUpdatePacket:
		{
			std::shared_ptr<UActorUpdatePacket> ActorUpdatePacket = std::dynamic_pointer_cast<UActorUpdatePacket>(Protocol);

			SetActorLocation(ActorUpdatePacket->Pos);

			int a = 0;
			break;
		}
		default:
			break;
		}

	} while (nullptr != Protocol);


	// 나한테 패킷이 온게 있다면 하나 꺼내줘.
	// PopPacket();

}
