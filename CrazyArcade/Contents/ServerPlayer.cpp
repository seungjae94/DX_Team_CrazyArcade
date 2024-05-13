#include "PreCompile.h"
#include "ServerPlayer.h"
#include <EngineCore/Collision.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include "CrazyArcadeCore.h"
#include "Packets.h"

AServerPlayer::AServerPlayer() 
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");

	USpriteRenderer* Ptr = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Ptr->SetupAttachment(Root);

	SetRoot(Root);

	SetActorScale3D({ 150.0f, 150.0f ,150.0f });

	
}

AServerPlayer::~AServerPlayer() 
{
}

void AServerPlayer::BeginPlay()
{
	AActor::BeginPlay();
	// 이플레이어가 내가 조작하는 플레이어인지
	// 다른 유저의 플레이어인지 
	if (true)
	{
		InputOn();
	}
}

void AServerPlayer::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	// 플레이어를 컨트롤도 하면서
	// 내가 플레이하는 플레이어 => 키 누르면 움직이고
	
	// 서버로 접속한 프렐이

	// 이플레이어가 내가 조작하는 플레이어인지
	// 다른 유저의 플레이어인지 


	float Speed = 500.0f;

	if (true == IsPress('A'))
	{
		AddActorLocation(FVector::Left * _DeltaTime * Speed);
	}

	if (true == IsPress('D'))
	{
		AddActorLocation(FVector::Right * _DeltaTime * Speed);
	}

	if (true == IsPress('W'))
	{
		AddActorLocation(FVector::Up * _DeltaTime * Speed);
	}

	if (true == IsPress('S'))
	{
		AddActorLocation(FVector::Down * _DeltaTime * Speed);
	}

	if (false == IsNetInit())
	{
		// 네트워크 통신준비가 아직 안된 오브젝트다.
		if (nullptr != UCrazyArcadeCore::Net)
		{
			InitNet(UCrazyArcadeCore::Net);
		}
	}

	static float FrameTime = 1.0f / 60.0f;
	static float CurTime = FrameTime;

	CurTime -= _DeltaTime;

	if (0.0f >= CurTime && true == IsNetInit())
	{
		std::shared_ptr<UActorUpdatePacket> Packet = std::make_shared<UActorUpdatePacket>();

		Packet->Pos = GetActorLocation();
		Send(Packet);
		CurTime += FrameTime;
	}

	// 움직였어
}
