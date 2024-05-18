#include "PreCompile.h"
#include "ServerManager.h"
#include <Contents/ConnectionInfo.h>
#include <Contents/CrazyArcadeCore.h>
#include <Contents/Packets.h>
#include <EngineBase/EngineServer.h>

ServerManager::ServerManager()
{
}

ServerManager::~ServerManager()
{
	int a = 0;
}


void ServerManager::ServerOpen()
{
	UEngineNetWindow::ServerOpen();
	UEngineDispatcher& Dis = UCrazyArcadeCore::Net->Dispatcher;

	Dis.AddHandler<UConnectPacket>([=](std::shared_ptr<UConnectPacket> _Packet)
		{
			GEngine->GetCurLevel()->PushFunction([=]()
				{
					//ConnectionInfo::GetInst().SetSessionCount(_Packet->ConnectNum);
					//ConnectionInfo::GetInst().SetOrder(_Packet->ConnectNum);
					//std::string Name = ConnectionInfo::GetInst().GetMyName();
					ConnectionInfo::GetInst().SetUserInfos(_Packet->Infos);
				});
		});

	UEngineDispatcher& Diss = UCrazyArcadeCore::Net->Dispatcher;
	Diss.AddHandler<UConnectInitPacket>([=](std::shared_ptr<UConnectInitPacket> _Packet)
		{
			GEngine->GetCurLevel()->PushFunction([=]()
				{
					std::lock_guard<std::mutex> Lock(SessinInitMutex);
					ConnectionInfo::GetInst().PushUserInfos(_Packet->GetSessionToken(), _Packet->Name);
					SessionInitVec[_Packet->Session] = true;

					std::shared_ptr<UConnectPacket> ConnectNumPacket = std::make_shared<UConnectPacket>();
					ConnectNumPacket->Infos = ConnectionInfo::GetInst().GetUserInfos();

					Send(ConnectNumPacket);

				});
		});
}

void ServerManager::ClientOpen(std::string_view _Ip, int _Port)
{
	UEngineNetWindow::ClientOpen(_Ip, _Port);
	UEngineDispatcher& Dis = UCrazyArcadeCore::Net->Dispatcher;
	Dis.AddHandler<UConnectPacket>([=](std::shared_ptr<UConnectPacket> _Packet)
		{
			GEngine->GetCurLevel()->PushFunction([=]()
				{
					ConnectionInfo::GetInst().SetUserInfos(_Packet->Infos);
				});
		});

	UEngineDispatcher& Diss = UCrazyArcadeCore::Net->Dispatcher;
	Diss.AddHandler<UConnectInitPacket>([=](std::shared_ptr<UConnectInitPacket> _Packet)
		{
			GEngine->GetCurLevel()->PushFunction([=]()
				{
					ConnectionInfo::GetInst().PushUserInfos(_Packet->GetSessionToken(), _Packet->Name);
					SessionInitVec[_Packet->Session] = true;
				});
		});
}

void ServerManager::Update(float _DeltaTime)
{
	std::map<int, std::string> UserInfo = ConnectionInfo::GetInst().GetUserInfos();
	int a = 0;

	if (ManagerType == ENetType::Server) {
		ServerUpdate(_DeltaTime);
	}
	else if (ManagerType == ENetType::Client) {
		ClientUpdate(_DeltaTime);
	}

}

void ServerManager::ServerUpdate(float _DeltaTime)
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

void ServerManager::ClientUpdate(float _DeltaTime)
{

}


void ServerManager::ServerInit()
{
	if (true == ServerBool) return;

	if (-1 != UCrazyArcadeCore::Net->GetSessionToken()) {
		ConnectionInfo::GetInst().SetOrder(UCrazyArcadeCore::Net->GetSessionToken());
		ServerBool = true;
	}
}

void ServerManager::ClientInit()
{
	if (true == ClientBool) return;

	if (-1 != UCrazyArcadeCore::Net->GetSessionToken()) {
		std::shared_ptr<UConnectInitPacket> InitPacket = std::make_shared<UConnectInitPacket>();
		InitPacket->Session = UCrazyArcadeCore::Net->GetSessionToken();
		InitPacket->Name = ConnectionInfo::GetInst().GetMyName();
		Send(InitPacket);
		ClientBool = true;
	}
}

void ServerManager::SManagerInit()
{
	if (false == UCrazyArcadeCore::NetWindow->IsNetInit())
	{
		// 네트워크 통신준비가 아직 안된 오브젝트다.
		if (nullptr != UCrazyArcadeCore::NetWindow)
		{
			UCrazyArcadeCore::NetWindow->InitNet(UCrazyArcadeCore::Net);
			ManagerType = ENetType::Server;
		}
	}
}

void ServerManager::CManagerInit()
{
	if (false == UCrazyArcadeCore::NetWindow->IsNetInit())
	{
		// 네트워크 통신준비가 아직 안된 오브젝트다.
		if (nullptr != UCrazyArcadeCore::NetWindow)
		{
			UCrazyArcadeCore::NetWindow->InitNet(UCrazyArcadeCore::Net);
			ManagerType = ENetType::Client;
		}
	}
}