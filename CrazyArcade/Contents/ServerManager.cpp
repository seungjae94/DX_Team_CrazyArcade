#include "PreCompile.h"
#include "ServerManager.h"
#include <Contents/ConnectionInfo.h>
#include <Contents/CrazyArcadeCore.h>
#include <Contents/Packets.h>
#include <EngineBase/EngineServer.h>
#include "MapHelper.h"
#include "MapBase.h"
#include "ServerHelper.h"
#include "BombBase.h"
#include "ServerTestOtherPlayer.h"
#include <EngineBase/EngineClient.h>

int UServerManager::CommonObjectValue = 10000;

UServerManager::UServerManager()
{
}

UServerManager::~UServerManager()
{
}


void UServerManager::ServerOpen()
{
	if (nullptr == UCrazyArcadeCore::Net)
	{
		UCrazyArcadeCore::Net = std::make_shared<UEngineServer>();
		UCrazyArcadeCore::NetManager.SManagerInit();
		UCrazyArcadeCore::Net->ServerOpen(30000, 512);
	}

	UEngineDispatcher& Dis = UCrazyArcadeCore::Net->Dispatcher;

	Dis.AddHandler<UConnectPacket>([=](std::shared_ptr<UConnectPacket> _Packet)
		{
			PushUpdate([=]()
				{
					{
						ConnectionInfo::GetInst().SetUserInfos(_Packet->Infos);
					}

					{
						std::shared_ptr<UConnectPacket> Packet = std::make_shared<UConnectPacket>();
						std::map<int, ConnectUserInfo>& Infos = ConnectionInfo::GetInst().GetUserInfos();

						Packet->Infos = Infos;
						Send(Packet);
					}
				});
		});

	Dis.AddHandler<UConnectInitPacket>([=](std::shared_ptr<UConnectInitPacket> _Packet)
		{
			PushUpdate([=]()
				{
					std::lock_guard<std::mutex> Lock(SessinInitMutex);
					if (_Packet->GetSessionToken() >= GetServerSize()) {
						std::shared_ptr<UServerRejectPacket> ServerRejectPacket = std::make_shared<UServerRejectPacket>();
						ServerRejectPacket->WhichSession = _Packet->GetSessionToken();
						Send(ServerRejectPacket);
						return;
					}
					ConnectionInfo::GetInst().PushUserInfos(_Packet->GetSessionToken(), _Packet->Name);
					//SessionInitVec[_Packet->Session] = true;

					{
						std::shared_ptr<UConnectPacket> Packet = std::make_shared<UConnectPacket>();
						std::map<int, ConnectUserInfo>& Infos = ConnectionInfo::GetInst().GetUserInfos();

						Packet->Infos = Infos;
						Send(Packet);
					}

					{
						std::shared_ptr<UStageUpdatePacket> Packet = std::make_shared<UStageUpdatePacket>();
						Packet->MapType = ConnectionInfo::GetInst().GetCurMapType();
						Send(Packet);
					}

				});
		});

	Dis.AddHandler<UChangeLevelPacket>([=](std::shared_ptr<UChangeLevelPacket> _Packet)
		{
			PushUpdate([=]()
				{
					if (GEngine->GetCurLevel()->GetName()._Equal(_Packet->LevelName)) {
						return;
					}
					GEngine->ChangeLevel(_Packet->LevelName);
				});
		});

	Dis.AddHandler<UDeadUpdatePacket>([=](std::shared_ptr<UDeadUpdatePacket> _Packet)
		{
			PushUpdate([=]()
				{
					ConnectionInfo::GetInst().GetUserInfos()[_Packet->Order].SetIsDead(_Packet->DeadValue);

					{
						std::shared_ptr<UDeadUpdatePacket> Packet = std::make_shared<UDeadUpdatePacket>();
						Packet->Order = _Packet->Order;
						Packet->DeadValue = _Packet->DeadValue;
						Send(Packet);
					}

					ConnectionInfo::GetInst().TeamCount();
					ECharacterColor Win = ConnectionInfo::GetInst().WinCheck();
					ConnectionInfo::GetInst().SetWins(Win);
				});
		});

	Dis.AddHandler<UReadyUpdatePacket>([=](std::shared_ptr<UReadyUpdatePacket> _Packet)
		{
			PushUpdate([=]()
				{
					ConnectionInfo::GetInst().GetUserInfos()[_Packet->Order].SetIsReady(_Packet->ReadyValue);
					{
						std::shared_ptr<UReadyUpdatePacket> Packet = std::make_shared<UReadyUpdatePacket>();
						Packet->Order = _Packet->Order;
						Packet->ReadyValue = _Packet->ReadyValue;
						Send(Packet);
					}
				});
		});

	Dis.AddHandler<UEndSession>([=](std::shared_ptr<UEndSession> _Packet)
		{
			PushUpdate([=]()
				{
					if (_Packet->GetSessionToken() >= GetServerSize()) {
						return;
					}

					UCrazyArcadeCore::Net->Send(_Packet);
					if (true == IsNetObject(_Packet->GetSessionToken() * 1000)) {
						APlayer* OtherPlayer = dynamic_cast<APlayer*>(AllNetObject[_Packet->GetSessionToken() * 1000]);
						if (OtherPlayer != nullptr) {
							{
								AMainPlayLevel* PlayLevel = dynamic_cast<AMainPlayLevel*>(OtherPlayer->GetWorld()->GetGameMode().get());
								if (nullptr != PlayLevel->GetMap())
								{
									PlayLevel->GetMap()->PlayerDelete(OtherPlayer);
								}
							}
							OtherPlayer->Destroy();
						}
					}
					ConnectionInfo::GetInst().SetEmpty(_Packet->GetSessionToken());
				});
		});
}

void UServerManager::ClientOpen(std::string_view _Ip, int _Port)
{
	if (nullptr == UCrazyArcadeCore::Net)
	{
		UCrazyArcadeCore::Net = std::make_shared<UEngineClient>();
		UCrazyArcadeCore::Net->Connect(std::string(_Ip), _Port);
		if (UCrazyArcadeCore::Net->IsNetConnetion() == false) {
			MsgBoxAssert("정상적인 연결이 되지 않았습니다");
			UCrazyArcadeCore::Net->End();
			return;
		}
		UCrazyArcadeCore::NetManager.CManagerInit();
	}

	UEngineDispatcher& Dis = UCrazyArcadeCore::Net->Dispatcher;
	Dis.AddHandler<UServerRejectPacket>([=](std::shared_ptr<UServerRejectPacket> _Packet)
		{
			PushUpdate([=]()
				{
					if (_Packet->WhichSession == UCrazyArcadeCore::Net->GetSessionToken()) {
						
						std::shared_ptr<UEndSession> EndSessionPacket = std::make_shared<UEndSession>();
						Send(EndSessionPacket);
						UCrazyArcadeCore::Net->End();
						UCrazyArcadeCore::Net = nullptr;
						UCrazyArcadeCore::NetManager.CFailInit();
						GEngine->ChangeLevel("MainTitleLevel");
						MsgBoxLogT("서버 알림", "서버에 남은 자리가 없습니다");
					}
				});
		});


	Dis.AddHandler<UConnectPacket>([=](std::shared_ptr<UConnectPacket> _Packet)
		{
			PushUpdate([=]()
				{
					ConnectionInfo::GetInst().SetUserInfos(_Packet->Infos);
				});
		});

	Dis.AddHandler<UChangeLevelPacket>([=](std::shared_ptr<UChangeLevelPacket> _Packet)
		{
			PushUpdate([=]()
				{
					GEngine->ChangeLevel(_Packet->LevelName);
				});
		});

	Dis.AddHandler<UDeadUpdatePacket>([=](std::shared_ptr<UDeadUpdatePacket> _Packet)
		{
			PushUpdate([=]()
				{
					ConnectionInfo::GetInst().GetUserInfos()[_Packet->Order].SetIsDead(_Packet->DeadValue);
					ConnectionInfo::GetInst().TeamCount();
					ECharacterColor Win = ConnectionInfo::GetInst().WinCheck();
					ConnectionInfo::GetInst().SetWins(Win);
				});
		});

	Dis.AddHandler<UReadyUpdatePacket>([=](std::shared_ptr<UReadyUpdatePacket> _Packet)
		{
			PushUpdate([=]()
				{
					ConnectionInfo::GetInst().GetUserInfos()[_Packet->Order].SetIsReady(_Packet->ReadyValue);
				});
		});

	Dis.AddHandler<UEndSession>([=](std::shared_ptr<UEndSession> _Packet)
		{
			PushUpdate([=]()
				{
					if (_Packet->GetSessionToken() == 0) {
						MsgBoxLogT("서버 알림", "서버가 종료되었습니다");
						GEngine->EngineWindow.Off();
					}
					if (true == IsNetObject(_Packet->GetSessionToken() * 1000)) {
						APlayer* OtherPlayer = dynamic_cast<APlayer*>(AllNetObject[_Packet->GetSessionToken() * 1000]);
						if (OtherPlayer != nullptr) {
							{
								AMainPlayLevel* PlayLevel = dynamic_cast<AMainPlayLevel*>(OtherPlayer->GetWorld()->GetGameMode().get());
								if (nullptr != PlayLevel->GetMap())
								{
									PlayLevel->GetMap()->PlayerDelete(OtherPlayer);
								}
							}
							OtherPlayer->Destroy();
						}
					}
					ConnectionInfo::GetInst().SetEmpty(_Packet->GetSessionToken());
				});
		});

	Dis.AddHandler<UStageUpdatePacket>([=](std::shared_ptr<UStageUpdatePacket> _Packet)
		{
			PushUpdate([=]()
				{
					ConnectionInfo::GetInst().SetMapType(_Packet->MapType);
				});
		});

	Dis.AddHandler<UFadeOutUpdatePacket>([=](std::shared_ptr<UFadeOutUpdatePacket> _Packet)
		{
			PushUpdate([=]()
				{
					ConnectionInfo::GetInst().SetIsFadeOut(_Packet->IsFadeOut);
				});

		});
}

void UServerManager::AddHandlerFunction()
{
	for (std::function<void()>& Handler : ReservedHandlers)
	{
		Handler();
	}
}

void UServerManager::Update(float _DeltaTime)
{
	{
		std::lock_guard<std::mutex> Lock(UpdateLock);
		for (std::function<void()> Function : UpdateTick)
		{
			Function();
		}
		UpdateTick.clear();
	}

	if (ManagerType == ENetType::Server) {
		ServerUpdate(_DeltaTime);
	}
	else if (ManagerType == ENetType::Client) {
		ClientUpdate(_DeltaTime);
	}
}

void UServerManager::ServerUpdate(float _DeltaTime)
{
	ServerInit();

	if (nullptr != UCrazyArcadeCore::Net)
	{
		// ??
	}
}

void UServerManager::ClientUpdate(float _DeltaTime)
{
	ClientInit();
}

void UServerManager::BoxTokenInit()
{
	UServerManager::CommonObjectValue = 10000;
}


void UServerManager::ServerInit()  //한 번만 실행되는 함수
{
	if (true == ServerBool) return;

	if (-1 != UCrazyArcadeCore::Net->GetSessionToken()) {
		ConnectionInfo::GetInst().SetOrder(UCrazyArcadeCore::Net->GetSessionToken());
		ServerBool = true;
		AddHandlerFunction();
	}
}

void UServerManager::ClientInit()  //한 번만 실행되는 함수
{
	if (true == ClientBool) return;

	if (-1 != UCrazyArcadeCore::Net->GetSessionToken()) {
		ConnectionInfo::GetInst().SetOrder(UCrazyArcadeCore::Net->GetSessionToken());
		std::shared_ptr<UConnectInitPacket> InitPacket = std::make_shared<UConnectInitPacket>();
		InitPacket->Session = UCrazyArcadeCore::Net->GetSessionToken();
		InitPacket->Name = ConnectionInfo::GetInst().GetTempName();
		AddHandlerFunction();
		Send(InitPacket);
		ClientBool = true;
	}
}

void UServerManager::SManagerInit()
{
	if (false == UCrazyArcadeCore::NetManager.IsNetInit())
	{
		// 네트워크 통신준비가 아직 안된 오브젝트다.
		UCrazyArcadeCore::NetManager.InitNet(UCrazyArcadeCore::Net);
		ManagerType = ENetType::Server;
		SetObjectToken(-1);
	}
}

void UServerManager::CManagerInit()
{
	if (false == UCrazyArcadeCore::NetManager.IsNetInit())
	{
		// 네트워크 통신준비가 아직 안된 오브젝트다.
		UCrazyArcadeCore::NetManager.InitNet(UCrazyArcadeCore::Net);
		ManagerType = ENetType::Client;
		SetObjectToken(-1);
	}
}

void UServerManager::CFailInit()
{
	if (true == UCrazyArcadeCore::NetManager.IsNetInit())
	{
		// 네트워크 통신준비가 아직 안된 오브젝트다.
		UCrazyArcadeCore::NetManager.InitNet(nullptr);
		ManagerType = ENetType::None;
		SetObjectToken(-1);
		ClientBool = false;
	}
	else {
		MsgBoxAssert("이상함");
	}
}

void UServerManager::ReserveHandler(std::function<void()> _Handler)
{
	ReservedHandlers.push_back(_Handler);
}
