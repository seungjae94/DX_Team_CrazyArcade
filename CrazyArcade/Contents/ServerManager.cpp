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

UServerManager::UServerManager()
{
}

UServerManager::~UServerManager()
{
	int a = 0;
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
					ConnectionInfo::GetInst().SetUserInfos(_Packet->Infos);
				});
		});

	UEngineDispatcher& Diss = UCrazyArcadeCore::Net->Dispatcher;
	Diss.AddHandler<UConnectInitPacket>([=](std::shared_ptr<UConnectInitPacket> _Packet)
		{
			PushUpdate([=]()
				{
					std::lock_guard<std::mutex> Lock(SessinInitMutex);
					ConnectionInfo::GetInst().PushUserInfos(_Packet->GetSessionToken(), _Packet->Name);
					SessionInitVec[_Packet->Session] = true;

					std::shared_ptr<UConnectPacket> ConnectNumPacket = std::make_shared<UConnectPacket>();
					ConnectNumPacket->Infos = ConnectionInfo::GetInst().GetUserInfos();

					Send(ConnectNumPacket);

				});
		});

	UEngineDispatcher& Diss = UCrazyArcadeCore::Net->Dispatcher;
	Diss.AddHandler<UChangeLevelPacket>([=](std::shared_ptr<UChangeLevelPacket> _Packet)
		{
			PushUpdate([=]()
				{
					GEngine->ChangeLevel(_Packet->LevelName);
				});
		});
}

void UServerManager::ClientOpen(std::string_view _Ip, int _Port)
{
	if (nullptr == UCrazyArcadeCore::Net)
	{
		UCrazyArcadeCore::Net = std::make_shared<UEngineClient>();
		UCrazyArcadeCore::NetManager.CManagerInit();
		UCrazyArcadeCore::Net->Connect(std::string(_Ip), _Port);
	}

	UEngineDispatcher& Dis = UCrazyArcadeCore::Net->Dispatcher;
	Dis.AddHandler<UConnectPacket>([=](std::shared_ptr<UConnectPacket> _Packet)
		{
			PushUpdate([=]()
				{
					ConnectionInfo::GetInst().SetUserInfos(_Packet->Infos);
				});
		});

	UEngineDispatcher& Diss = UCrazyArcadeCore::Net->Dispatcher;
	Diss.AddHandler<UConnectInitPacket>([=](std::shared_ptr<UConnectInitPacket> _Packet)
		{
			PushUpdate([=]()
				{
					ConnectionInfo::GetInst().PushUserInfos(_Packet->GetSessionToken(), _Packet->Name);
					SessionInitVec[_Packet->Session] = true;
				});
		});

	UEngineDispatcher& Diss = UCrazyArcadeCore::Net->Dispatcher;
	Diss.AddHandler<UChangeLevelPacket>([=](std::shared_ptr<UChangeLevelPacket> _Packet)
		{
			PushUpdate([=]()
				{
					GEngine->ChangeLevel(_Packet->LevelName);
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
		//int ServerSessionCount = ConnectionInfo::GetInst().GetInfoSize();
		//bool Isinit = true;
		//for (int i = 0; i <= ServerSessionCount; ++i) {
		//	Isinit = Isinit || SessionInitVec[i];
		//}
		//if (Isinit == false) {
		//	return;
		//}
		//int CurSessionToken = Server->GetCurSessionToken();
		//if (ServerSessionCount != CurSessionToken)
		//{
		//	std::shared_ptr<UConnectPacket> ConnectNumPacket = std::make_shared<UConnectPacket>();
		//	ConnectNumPacket->Infos = ConnectionInfo::GetInst().GetUserInfos();

		//	Send(ConnectNumPacket);
		//}
	}
}

void UServerManager::ClientUpdate(float _DeltaTime)
{
	ClientInit();
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
		std::shared_ptr<UConnectInitPacket> InitPacket = std::make_shared<UConnectInitPacket>();
		InitPacket->Session = UCrazyArcadeCore::Net->GetSessionToken();
		InitPacket->Name = ConnectionInfo::GetInst().GetMyName();
		Send(InitPacket);
		ClientBool = true;
		AddHandlerFunction();
	}
}

void UServerManager::SManagerInit()
{
	if (false == UCrazyArcadeCore::NetManager.IsNetInit())
	{
		// 네트워크 통신준비가 아직 안된 오브젝트다.
		UCrazyArcadeCore::NetManager.InitNet(UCrazyArcadeCore::Net);
		ManagerType = ENetType::Server;
	}
}

void UServerManager::CManagerInit()
{
	if (false == UCrazyArcadeCore::NetManager.IsNetInit())
	{
		// 네트워크 통신준비가 아직 안된 오브젝트다.
		UCrazyArcadeCore::NetManager.InitNet(UCrazyArcadeCore::Net);
		ManagerType = ENetType::Client;
	}
}

void UServerManager::ReserveHandler(std::function<void()> _Handler)
{
	ReservedHandlers.push_back(_Handler);
}
