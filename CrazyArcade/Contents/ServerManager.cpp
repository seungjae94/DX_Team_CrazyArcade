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
					ConnectionInfo::GetInst().PushUserInfos(_Packet->GetSessionToken(), _Packet->Name);
					SessionInitVec[_Packet->Session] = true;
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
		int ServerSessionCount = ConnectionInfo::GetInst().InfoSize();
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
			std::shared_ptr<UConnectPacket> ConnectNumPacket = std::make_shared<UConnectPacket>();
			ConnectNumPacket->Infos = ConnectionInfo::GetInst().GetUserInfos();
			
			UCrazyArcadeCore::Net->Send(ConnectNumPacket);
		}
	}
}
