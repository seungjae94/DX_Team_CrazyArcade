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
						std::map<int, ConnectUserInfo> Infos;
						for (std::pair<const int, std::string> NamePair : _Packet->NameInfos)
						{
							int Key = NamePair.first;
							Infos[Key].MyName = NamePair.second;
							Infos[Key].SetMyCharacterType(_Packet->GetMyCharacterType(Key));
							Infos[Key].SetMyColorType(_Packet->GetMyColorType(Key));
							Infos[Key].SetIsExist(_Packet->GetExist(Key));
						}

						ConnectionInfo::GetInst().SetUserInfos(Infos);
					}

					{
						std::shared_ptr<UConnectPacket> Packet = std::make_shared<UConnectPacket>();
						std::map<int, ConnectUserInfo>& Infos = ConnectionInfo::GetInst().GetUserInfos();

						std::map<int, std::string> NameInfos;
						std::map<int, int> CharacterTypeInfos;
						std::map<int, int> ColorInfos;
						std::map<int, bool> ExistInfos;

						for (std::pair<const int, ConnectUserInfo> Pair : Infos)
						{
							int Key = Pair.first;
							NameInfos[Key] = Pair.second.MyName;
							CharacterTypeInfos[Key] = static_cast<int>(Pair.second.GetMyCharacterType());
							ColorInfos[Key] = static_cast<int>(Pair.second.GetMyColorType());
							ExistInfos[Key] = Pair.second.GetIsExist();
						}

						Packet->NameInfos = NameInfos;
						Packet->CharacterTypeInfos = CharacterTypeInfos;
						Packet->ColorInfos = ColorInfos;
						Packet->ExistInfos = ExistInfos;
						Send(Packet);
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
						std::shared_ptr<UConnectPacket> Packet = std::make_shared<UConnectPacket>();
						std::map<int, ConnectUserInfo>& Infos = ConnectionInfo::GetInst().GetUserInfos();

						std::map<int, std::string> NameInfos;
						std::map<int, int> CharacterTypeInfos;
						std::map<int, int> ColorInfos;
						std::map<int, bool> ExistInfos;

						for (std::pair<const int, ConnectUserInfo> Pair : Infos)
						{
							int Key = Pair.first;
							NameInfos[Key] = Pair.second.MyName;
							CharacterTypeInfos[Key] = static_cast<int>(Pair.second.GetMyCharacterType());
							ColorInfos[Key] = static_cast<int>(Pair.second.GetMyColorType());
							ExistInfos[Key] = Pair.second.GetIsExist();
						}

						Packet->NameInfos = NameInfos;
						Packet->CharacterTypeInfos = CharacterTypeInfos;
						Packet->ColorInfos = ColorInfos;
						Packet->ExistInfos = ExistInfos;
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

	Dis.AddHandler<UEndSession>([=](std::shared_ptr<UEndSession> _Packet)
		{
			PushUpdate([=]()
				{
					int a = _Packet->GetSessionToken();
					UCrazyArcadeCore::Net->Send(_Packet);
					APlayer* OtherPlayer = dynamic_cast<APlayer*>(AllNetObject[_Packet->GetSessionToken() * 1000]);
					if (OtherPlayer != nullptr) {
						{
							AMainPlayLevel* PlayLevel = dynamic_cast<AMainPlayLevel*>(OtherPlayer->GetWorld()->GetGameMode().get());
							PlayLevel->GetMap()->PlayerDelete(OtherPlayer);
						}

						OtherPlayer->Destroy();
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
						Infos[Key].SetIsExist(_Packet->GetExist(Key));
					}

					ConnectionInfo::GetInst().SetUserInfos(Infos);
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
			ConnectionInfo::GetInst().GetUserInfos()[_Packet->Order].SetIsDead(_Packet->DeadValue);
			ConnectionInfo::GetInst().TeamCount();
			ECharacterColor Win = ConnectionInfo::GetInst().WinCheck();
			ConnectionInfo::GetInst().SetWins(Win);
		});

	Dis.AddHandler<UEndSession>([=](std::shared_ptr<UEndSession> _Packet)
		{
			PushUpdate([=]()
				{
					int a = _Packet->GetSessionToken();
					APlayer* OtherPlayer = dynamic_cast<APlayer*>(AllNetObject[_Packet->GetSessionToken() * 1000]);
					if (OtherPlayer != nullptr) {
						{
							AMainPlayLevel* PlayLevel = dynamic_cast<AMainPlayLevel*>(OtherPlayer->GetWorld()->GetGameMode().get());
							PlayLevel->GetMap()->PlayerDelete(OtherPlayer);
						}
						OtherPlayer->Destroy();
					}
					ConnectionInfo::GetInst().SetEmpty(_Packet->GetSessionToken());
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
