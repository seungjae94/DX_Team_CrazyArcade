#include "PreCompile.h"
#include "ServerGameMode.h"
#include "Player.h"
#include <EngineCore/Image.h>
#include <EngineCore/Camera.h>
#include <EngineBase/EngineSerializer.h>
#include <EngineCore/BlurEffect.h>
#include <EngineCore/EngineEditorGUI.h>
#include "PlayGameMode.h"
#include "CrazyArcadeCore.h"
#include "Packets.h"
#include "ServerTestPlayer.h"
#include "ServerTestOtherPlayer.h"
#include <EngineBase/NetObject.h>
#include "ServerHelper.h"
#include "CrazyArcadeEnum.h"
#include "BombBase.h"
#include "MapBase.h"
#include "ServerManager.h"

AServerGameMode::AServerGameMode()
	:AMainPlayLevel()
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
}

void AServerGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	UNetObject::AllNetObject;
	int a = 0;
}

void AServerGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);
	Player->SetObjectToken(UNetObject::GetNewObjectToken());
}


void AServerGameMode::ServerPacketInit(UEngineDispatcher& Dis)
{
	Dis.AddHandler<UActorUpdatePacket>([=](std::shared_ptr<UActorUpdatePacket> _Packet)
		{
			//if (nullptr == UCrazyArcadeCore::Net)
			//{
			//	return;
			//}

			//// 다른 사람들한테 이 오브젝트에 대해서 알리고
			//UCrazyArcadeCore::Net->Send(_Packet);

			//GetWorld()->PushFunction([=]()
			//	{
			//		// 여긴 주쓰레드니까.
			//		ServerTestOtherPlayer* OtherPlayer = UNetObject::GetNetObject<ServerTestOtherPlayer>(_Packet->GetObjectToken());
			//		if (nullptr == OtherPlayer)
			//		{
			//			OtherPlayer = this->GetWorld()->SpawnActor<ServerTestOtherPlayer>("OtherPlayer", 0).get();
			//			OtherPlayer->SetObjectToken(_Packet->GetObjectToken());
			//		}
			//		OtherPlayer->PushProtocol(_Packet);
			//		//OtherPlayer
			//	});


		});

	Dis.AddHandler<USpawnUpdatePacket>([=](std::shared_ptr<USpawnUpdatePacket> _Packet)  //엑터 스폰 테스트용
		{
			//GetWorld()->PushFunction([=]()
			//	{
			//		ABombBase* MyBomb;
			//		MyBomb = ServerHelper::EnumSpawn(GetWorld(), _Packet->SpawnSelect).get();
			//		MyBomb->SetObjectToken(_Packet->GetObjectToken());
			//		MyBomb->PushProtocol(_Packet);  
			//		MyBomb->SetActorLocation(_Packet->Pos);

			//		FPoint Point = AMapBase::ConvertLocationToPoint(_Packet->Pos);
			//		MyBomb->SetCurPoint(Point);
			//		GetMap()->SetMapBomb(Point, MyBomb);

			//		FEngineTimeStamp Stamp = UEngineTime::GetCurTime();
			//		float FloatResult = Stamp.TimeToFloat();
			//		MyBomb->ReduceCurExplosionTime(FloatResult - _Packet->SpawnTime);
			//	});
		});
}

void AServerGameMode::ClientPacketInit(UEngineDispatcher& Dis)
{
	Dis.AddHandler<UActorUpdatePacket>([=](std::shared_ptr<UActorUpdatePacket> _Packet)
		{
			//GetWorld()->PushFunction([=]()
			//	{
			//		ServerTestOtherPlayer* OtherPlayer = UNetObject::GetNetObject<ServerTestOtherPlayer>(_Packet->GetObjectToken());
			//		if (nullptr == OtherPlayer)
			//		{
			//			OtherPlayer = this->GetWorld()->SpawnActor<ServerTestOtherPlayer>("OtherPlayer", 0).get();
			//			OtherPlayer->SetObjectToken(_Packet->GetObjectToken());
			//		}
			//		OtherPlayer->PushProtocol(_Packet);
			//	});
		});

	Dis.AddHandler<USpawnUpdatePacket>([=](std::shared_ptr<USpawnUpdatePacket> _Packet)  //엑터 스폰 테스트용
		{
			//GetWorld()->PushFunction([=]()
			//	{
			//		ABombBase* MyBomb;
			//		MyBomb = ServerHelper::EnumSpawn<ABombBase>(GetWorld(), _Packet->SpawnSelect).get();
			//		MyBomb->SetObjectToken(_Packet->GetObjectToken());
			//		MyBomb->PushProtocol(_Packet);
			//		MyBomb->SetActorLocation(_Packet->Pos);

			//		FPoint Point = AMapBase::ConvertLocationToPoint(_Packet->Pos);
			//		MyBomb->SetCurPoint(Point);
			//		GetMap()->SetMapBomb(Point, MyBomb);

			//		FEngineTimeStamp Stamp = UEngineTime::GetCurTime();
			//		float FloatResult = Stamp.TimeToFloat();
			//		MyBomb->ReduceCurExplosionTime(FloatResult - _Packet->SpawnTime);
			//	});
		});
}

void AServerGameMode::HandlerInit()
{
	if (false == IsHandlerInit)
	{
		IsHandlerInit = true;
		UCrazyArcadeCore::NetWindow->SetServerPlayHandler([&]()
			{
				UEngineDispatcher& Dis = UCrazyArcadeCore::Net->Dispatcher;
				Dis.AddHandler<UActorUpdatePacket>([=](std::shared_ptr<UActorUpdatePacket> _Packet)
					{
						if (nullptr == UCrazyArcadeCore::Net)
						{
							MsgBoxAssert("이거왜들어옴?");
						}
						UCrazyArcadeCore::Net->Send(_Packet);

						GetWorld()->PushFunction([=]()
							{
								// 여긴 주쓰레드니까.
								ANetActor* OtherPlayer = UNetObject::GetNetObject<ANetActor>(_Packet->GetObjectToken());
								if (nullptr == OtherPlayer)
								{
									ServerHelper::EnumSpawn(GetWorld(), _Packet->SpawnSelect, _Packet->GetObjectToken());
									OtherPlayer = UNetObject::GetNetObject<ANetActor>(_Packet->GetObjectToken());
								}

								OtherPlayer->PushProtocol(_Packet);
							});


					});
			});

		UCrazyArcadeCore::NetWindow->SetClientPlayHandler([&]()
			{
				UEngineDispatcher& Dis = UCrazyArcadeCore::Net->Dispatcher;
				Dis.AddHandler<UActorUpdatePacket>([=](std::shared_ptr<UActorUpdatePacket> _Packet)
					{
						if (nullptr == UCrazyArcadeCore::Net)
						{
							MsgBoxAssert("이거왜들어옴?");
						}
						GetWorld()->PushFunction([&]()
							{
								// 여긴 주쓰레드니까.
								ANetActor* OtherPlayer = UNetObject::GetNetObject<ANetActor>(_Packet->GetObjectToken());
								if (nullptr == OtherPlayer)
								{
									ServerHelper::EnumSpawn(GetWorld(), _Packet->SpawnSelect, _Packet->GetObjectToken());
									OtherPlayer = UNetObject::GetNetObject<ANetActor>(_Packet->GetObjectToken());
								}

								OtherPlayer->PushProtocol(_Packet);
							});


					});
			});

	}
	else {
		return;
	}
}

void AServerGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);


	UCrazyArcadeCore::NetWindow->Off();
}