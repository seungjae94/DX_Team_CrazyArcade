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
					{
						std::map<int, ConnectUserInfo> Infos;
						for (std::pair<const int, std::string> NamePair : _Packet->NameInfos)
						{
							int Key = NamePair.first;
							Infos[Key].MyName = NamePair.second;
							Infos[Key].SetMyCharacterType(_Packet->GetMyCharacterType(Key));
							Infos[Key].SetMyColorType(_Packet->GetMyColorType(Key));
						}

						ConnectionInfo::GetInst().SetUserInfos(Infos);
					}

					{
						std::shared_ptr<UConnectPacket> ConnectNumPacket = std::make_shared<UConnectPacket>();
						std::map<int, ConnectUserInfo>& Infos = ConnectionInfo::GetInst().GetUserInfos();
						
						std::map<int, std::string> NameInfos;
						std::map<int, int> CharacterTypeInfos;
						std::map<int, int> ColorInfos;

						for (std::pair<const int, ConnectUserInfo> Pair : Infos)
						{
							int Key = Pair.first;
							NameInfos[Key] = Pair.second.MyName;
							CharacterTypeInfos[Key] = static_cast<int>(Pair.second.GetMyCharacterType());
							ColorInfos[Key] = static_cast<int>(Pair.second.GetMyColorType());
						}

						ConnectNumPacket->NameInfos = NameInfos;
						ConnectNumPacket->CharacterTypeInfos = CharacterTypeInfos;
						ConnectNumPacket->ColorInfos = ColorInfos;
						Send(ConnectNumPacket);
					}
				});
		});

	Dis.AddHandler<UConnectInitPacket>([=](std::shared_ptr<UConnectInitPacket> _Packet)
		{
			PushUpdate([=]()
				{
					std::lock_guard<std::mutex> Lock(SessinInitMutex);
					ConnectionInfo::GetInst().PushUserInfos(_Packet->GetSessionToken(), _Packet->Name);
					SessionInitVec[_Packet->Session] = true;

					{
						std::shared_ptr<UConnectPacket> ConnectNumPacket = std::make_shared<UConnectPacket>();
						std::map<int, ConnectUserInfo>& Infos = ConnectionInfo::GetInst().GetUserInfos();

						std::map<int, std::string> NameInfos;
						std::map<int, int> CharacterTypeInfos;
						std::map<int, int> ColorInfos;

						for (std::pair<const int, ConnectUserInfo> Pair : Infos)
						{
							int Key = Pair.first;
							NameInfos[Key] = Pair.second.MyName;
							CharacterTypeInfos[Key] = static_cast<int>(Pair.second.GetMyCharacterType());
							ColorInfos[Key] = static_cast<int>(Pair.second.GetMyColorType());
						}

						ConnectNumPacket->NameInfos = NameInfos;
						ConnectNumPacket->CharacterTypeInfos = CharacterTypeInfos;
						ConnectNumPacket->ColorInfos = ColorInfos;
						Send(ConnectNumPacket);
					}

				});
		});

	Dis.AddHandler<UChangeLevelPacket>([=](std::shared_ptr<UChangeLevelPacket> _Packet)
		{
			PushUpdate([=]()
				{
					GEngine->ChangeLevel(_Packet->LevelName);
				});
		});

	/*Dis.AddHandler<UCharacterTypePacket>([=](std::shared_ptr<UCharacterTypePacket> _Packet)
		{
			PushUpdate([=]()
				{
					ConnectionInfo::GetInst().SetCharacterType(_Packet->Infos);

					std::shared_ptr<UCharacterTypePacket> CharacterTypePacket = std::make_shared<UCharacterTypePacket>();
					CharacterTypePacket->Infos = ConnectionInfo::GetInst().GetCharacterTypeInfos();
					Send(CharacterTypePacket);
				});
		});

	Dis.AddHandler<UColorTypePacket>([=](std::shared_ptr<UColorTypePacket> _Packet)
		{
			PushUpdate([=]()
				{
					ConnectionInfo::GetInst().SetCharacterColor(_Packet->Infos);

					std::shared_ptr<UColorTypePacket> ColorTypePacket = std::make_shared<UColorTypePacket>();
					ColorTypePacket->Infos = ConnectionInfo::GetInst().GetCharacterColorInfos();
					Send(ColorTypePacket);
				});
		});*/
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
					std::map<int, ConnectUserInfo> Infos;
					for (std::pair<const int, std::string> NamePair : _Packet->NameInfos)
					{
						int Key = NamePair.first;
						Infos[Key].MyName = NamePair.second;
						Infos[Key].SetMyCharacterType(_Packet->GetMyCharacterType(Key));
						Infos[Key].SetMyColorType(_Packet->GetMyColorType(Key));
					}

					ConnectionInfo::GetInst().SetUserInfos(Infos);
				});
		});

	Dis.AddHandler<UConnectInitPacket>([=](std::shared_ptr<UConnectInitPacket> _Packet)
		{
			PushUpdate([=]()
				{
					ConnectionInfo::GetInst().PushUserInfos(_Packet->GetSessionToken(), _Packet->Name);
					SessionInitVec[_Packet->Session] = true;
				});
		});

	Dis.AddHandler<UChangeLevelPacket>([=](std::shared_ptr<UChangeLevelPacket> _Packet)
		{
			PushUpdate([=]()
				{
					GEngine->ChangeLevel(_Packet->LevelName);
				});
		});

	/*Dis.AddHandler<UCharacterTypePacket>([=](std::shared_ptr<UCharacterTypePacket> _Packet)
		{
			PushUpdate([=]()
				{
					ConnectionInfo::GetInst().SetCharacterType(_Packet->Infos);
				});
		});

	Dis.AddHandler<UColorTypePacket>([=](std::shared_ptr<UColorTypePacket> _Packet)
		{
			PushUpdate([=]()
				{
					ConnectionInfo::GetInst().SetCharacterColor(_Packet->Infos);
				});
		});*/

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
		ConnectionInfo::GetInst().SetOrder(UCrazyArcadeCore::Net->GetSessionToken());
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
