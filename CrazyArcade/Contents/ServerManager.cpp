#include "PreCompile.h"
#include "ServerManager.h"
#include <Contents/ServerNumber.h>
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

	Dis.AddHandler<UConnectNumberPacket>([=](std::shared_ptr<UConnectNumberPacket> _Packet)
		{
			GEngine->GetCurLevel()->PushFunction([=]()
				{
					ServerNumber::GetInst().SetSessionCount(_Packet->ConnectNum);

					ServerNumber::GetInst().SetOrder(_Packet->ConnectNum);
					ServerNumber::GetInst().SetMyName(_Packet->UserName);

					ServerNumber::GetInst().SetUserInfos(_Packet->Infos);
				});
		});

	UEngineDispatcher& Diss = UCrazyArcadeCore::Net->Dispatcher;
	Dis.AddHandler<UConnectInitPacket>([=](std::shared_ptr<UConnectInitPacket> _Packet)
		{
			GEngine->GetCurLevel()->PushFunction([=]()
				{
					SessionInitVec[_Packet->Session] = true;
				});
		});
}

void ServerManager::ClientOpen(std::string_view _Ip, int _Port)
{
	UEngineNetWindow::ClientOpen(_Ip, _Port);
	UEngineDispatcher& Dis = UCrazyArcadeCore::Net->Dispatcher;
	Dis.AddHandler<UConnectNumberPacket>([=](std::shared_ptr<UConnectNumberPacket> _Packet)
		{
			GEngine->GetCurLevel()->PushFunction([=]()
				{
					ServerNumber::GetInst().SetSessionCount(_Packet->ConnectNum);

					ServerNumber::GetInst().SetOrder(_Packet->ConnectNum);
					ServerNumber::GetInst().SetMyName(_Packet->UserName);

					ServerNumber::GetInst().SetUserInfos(_Packet->Infos);
				});
		});

	UEngineDispatcher& Diss = UCrazyArcadeCore::Net->Dispatcher;
	Dis.AddHandler<UConnectInitPacket>([=](std::shared_ptr<UConnectInitPacket> _Packet)
		{
			GEngine->GetCurLevel()->PushFunction([=]()
				{
					SessionInitVec[_Packet->Session] = true;
				});
		});
}

void ServerManager::Update(float _DeltaTime)
{
	if (nullptr != UCrazyArcadeCore::Net)
	{
		std::shared_ptr<UEngineServer> Server = dynamic_pointer_cast<UEngineServer>(UCrazyArcadeCore::Net);
		if (nullptr == Server)
		{
			return;
		}
		int ServerSessionCount = ServerNumber::GetInst().GetCurSessionCount();
		bool Isinit = true;
		for (int i = 0; i <= ServerSessionCount; ++i) {
			Isinit = Isinit || SessionInitVec[i];
		}
		if (Isinit == false) {
			return;
		}
		int CurSessionToken = Server->GetCurSessionToken();
		if (ServerSessionCount != CurSessionToken)
		{
			ServerNumber::GetInst().SetSessionCount(Server->GetCurSessionToken());
			std::shared_ptr<UConnectNumberPacket> ConnectNumPacket = std::make_shared<UConnectNumberPacket>();

			int Count = ServerNumber::GetInst().GetCurSessionCount();
			std::string Name = ServerNumber::GetInst().GetMyName();

			ServerNumber::GetInst().PushUserInfos(Count, Name);

			ConnectNumPacket->ConnectNum = Count;
			ConnectNumPacket->UserName = Name;

			ConnectNumPacket->Infos = ServerNumber::GetInst().GetUserInfos();
			UCrazyArcadeCore::Net->Send(ConnectNumPacket);
		}
	}
}
