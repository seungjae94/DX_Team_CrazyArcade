#include "PreCompile.h"
#include "ServerGameMode.h"
#include "Player.h"
#include <EngineCore/Image.h>
#include <EngineCore/Camera.h>
#include <EngineBase/EngineSerializer.h>
#include <EngineCore/BlurEffect.h>
#include <EngineCore/EngineEditorGUI.h>
#include "ServerPlayer.h"
#include "PlayGameMode.h"
#include "CrazyArcadeCore.h"
#include "Packets.h"
#include "OtherPlayer.h"
#include "ServerTestPlayer.h"
#include "ServerTestOtherPlayer.h"


AServerGameMode::AServerGameMode()
{
}

AServerGameMode::~AServerGameMode()
{
	if (nullptr != UCrazyArcadeCore::Net)
	{
		UCrazyArcadeCore::Net->End();
		UCrazyArcadeCore::Net = nullptr;
	}
}

void AServerGameMode::BeginPlay()
{
	Super::BeginPlay();
	// TestThread.Start();
	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, -100.0f));

	MainPlayer = GetWorld()->SpawnActor<ServerTestPlayer>("Player");

}

void AServerGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}

void AServerGameMode::LevelStart(ULevel* _DeltaTime)
{
	if (nullptr == NetWindow)
	{
		NetWindow = UEngineEditorGUI::CreateEditorWindow<UEngineNetWindow>("NetWindow");

		NetWindow->SetServerOpenFunction([&]()
			{
				UCrazyArcadeCore::Net = std::make_shared<UEngineServer>();
				UCrazyArcadeCore::Net->ServerOpen(30000, 512);

				// 여기에서 메인 플레이어한테 번호를 하나 줄겁니다.

				MainPlayer->SetObjectToken(UNetObject::GetNewObjectToken());

				ServerPacketInit(UCrazyArcadeCore::Net->Dispatcher);
			});

		NetWindow->SetClientConnectFunction([&](std::string IP, short PORT)
			{
				UCrazyArcadeCore::Net = std::make_shared<UEngineClient>();
				UCrazyArcadeCore::Net->Connect(IP, PORT);

				UCrazyArcadeCore::Net->SetTokenPacketFunction([=](USessionTokenPacket* _Token)
					{
						MainPlayer->SetObjectToken(_Token->GetObjectToken());

					});

				// 어떤 패키싱 왔을때 어떻게 처리할건지를 정하는 걸 해야한다.
				ClientPacketInit(UCrazyArcadeCore::Net->Dispatcher);
			});
	}
	NetWindow->On();
}

void AServerGameMode::ServerPacketInit(UEngineDispatcher& Dis)
{
	Dis.AddHandler<UActorUpdatePacket>([=](std::shared_ptr<UActorUpdatePacket> _Packet)
		{
			if (nullptr == UCrazyArcadeCore::Net)
			{
				return;
			}

			// 다른 사람들한테 이 오브젝트에 대해서 알리고
			UCrazyArcadeCore::Net->Send(_Packet);

			GetWorld()->PushFunction([=]()
				{
					// 여긴 주쓰레드니까.
					ServerTestOtherPlayer* OtherPlayer = UNetObject::GetNetObject<ServerTestOtherPlayer>(_Packet->GetObjectToken());
					if (nullptr == OtherPlayer)
					{
						OtherPlayer = this->GetWorld()->SpawnActor<ServerTestOtherPlayer>("OtherPlayer", 0).get();
						OtherPlayer->SetObjectToken(_Packet->GetObjectToken());
					}
					OtherPlayer->PushProtocol(_Packet);
				});


		});

	Dis.AddHandler<USpawnUpdatePacket>([=](std::shared_ptr<USpawnUpdatePacket> _Packet)  //엑터 스폰 테스트용
		{
			GetWorld()->PushFunction([=]()
				{
					ServerTestOtherPlayer* OtherPlayer;
					OtherPlayer = this->GetWorld()->SpawnActor<ServerTestOtherPlayer>("OtherPlayer", 0).get();
					OtherPlayer->SetObjectToken(10);
					OtherPlayer->SetActorLocation(_Packet->Pos);
				});
		});
}

void AServerGameMode::ClientPacketInit(UEngineDispatcher& Dis)
{
	Dis.AddHandler<UActorUpdatePacket>([=](std::shared_ptr<UActorUpdatePacket> _Packet)
		{
			GetWorld()->PushFunction([=]()
				{
					ServerTestOtherPlayer* OtherPlayer = UNetObject::GetNetObject<ServerTestOtherPlayer>(_Packet->GetObjectToken());
					if (nullptr == OtherPlayer)
					{
						OtherPlayer = this->GetWorld()->SpawnActor<ServerTestOtherPlayer>("OtherPlayer", 0).get();
						OtherPlayer->SetObjectToken(_Packet->GetObjectToken());
					}
					OtherPlayer->SetActorLocation(_Packet->Pos);
					OtherPlayer->GetRenderer()->ChangeAnimation(_Packet->SpriteName);
				});
		});

	Dis.AddHandler<USpawnUpdatePacket>([=](std::shared_ptr<USpawnUpdatePacket> _Packet)  //엑터 스폰 테스트용
		{
			GetWorld()->PushFunction([=]()
				{
					ServerTestOtherPlayer* OtherPlayer;
					OtherPlayer = this->GetWorld()->SpawnActor<ServerTestOtherPlayer>("OtherPlayer", 0).get();
					OtherPlayer->SetObjectToken(10);
					OtherPlayer->SetActorLocation(_Packet->Pos);
				});
		});
}

void AServerGameMode::LevelEnd(ULevel* _DeltaTime)
{
	NetWindow->Off();
}