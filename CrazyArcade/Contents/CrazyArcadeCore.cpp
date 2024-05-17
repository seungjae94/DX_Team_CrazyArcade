#include "PreCompile.h"
#include "CrazyArcadeCore.h"
#include "InitTestGameMode.h"
#include "MainPlayLevel.h"
#include "PlayGameMode.h"
#include "CrazyArcadeDebugWindow.h"
#include <EngineCore/EngineEditorGUI.h>
#include "MainTitleGameMode.h"
#include "LobbyTitleGameMode.h"
#include "ServerGameMode.h"
#include "InputRecorderTestGameMode.h"

#include "Packets.h"
#include "ServerNumber.h"

std::shared_ptr<UEngineNet> UCrazyArcadeCore::Net = nullptr;

UCrazyArcadeCore::UCrazyArcadeCore()
{
}

UCrazyArcadeCore::~UCrazyArcadeCore()
{
}

void UCrazyArcadeCore::Initialize()
{
	UEngineFont::Load("굴림");
	ResLoad();

	UEngineEditorGUI::CreateEditorWindow<UCrazyArcadeDebugWindow>("CrazyArcadeDebugWindow");

	GEngine->CreateLevel<AInitTestGameMode>("InitTestLevel");
	GEngine->CreateLevel<AMainPlayLevel>("MainPlayLevel");
	GEngine->CreateLevel<AServerGameMode>("ServerGameMode");
	GEngine->CreateLevel<AMainTitleGameMode>("TitleTestLevel");
	GEngine->CreateLevel<ALobbyTitleGameMode>("LobbyTitleTestLevel");
	GEngine->CreateLevel<AInputRecorderTestGameMode>("InputRecorderTestLevel");
	//GEngine->ChangeLevel("InitTestLevel");
	GEngine->ChangeLevel("TitleTestLevel");
}

void UCrazyArcadeCore::Tick(float _DeltaTime)
{
	int Count = ServerNumber::GetInst().GetCurSessionCount();
	int a = 0;
	if (false == IsFunctionInit)
	{
		if (nullptr == UCrazyArcadeCore::Net)
		{
			return;
		}


		IsFunctionInit = true;
		UEngineDispatcher& Dis = UCrazyArcadeCore::Net->Dispatcher;
		Dis.AddHandler<UConnectNumberPacket>([=](std::shared_ptr<UConnectNumberPacket> _Packet)
			{
				GEngine->GetCurLevel()->PushFunction([=]()
					{
						int Order = _Packet->ConnectNum;
						std::string Name = _Packet->UserName;
						ServerNumber::GetInst().SetSessionCount(Order);
						ServerNumber::GetInst().SetOrder(Order);
						ServerNumber::GetInst().SetMyName(Name);
						ServerNumber::GetInst().SetUserInfos(Order, Name);
						/*UCrazyArcadeCore::Net->SetSessionCount(_Packet->ConnectNum);*/
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
		std::shared_ptr<UEngineClient> Client = dynamic_pointer_cast<UEngineClient>(UCrazyArcadeCore::Net);
		if (nullptr != Client)
		{
			std::shared_ptr<UConnectInitPacket> ConnectNumPacket = std::make_shared<UConnectInitPacket>();
			ConnectNumPacket->Session = UCrazyArcadeCore::Net->GetSessionToken();
			UCrazyArcadeCore::Net->Send(ConnectNumPacket);
			return;
		}
	}

	if (true == IsFunctionInit)
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
				ConnectNumPacket->ConnectNum = Count;
				ServerNumber::GetInst().SetOrder(Count);
				ServerNumber::GetInst().SetUserInfos(Count, Name);
				ConnectNumPacket->UserName = Name;

				UCrazyArcadeCore::Net->Send(ConnectNumPacket);
			}
		}
	}
}

void UCrazyArcadeCore::ResLoad()
{
	// UI 리소스 로드
	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("ContentsResources");
		Dir.Move("UI");

		std::vector<UEngineFile> AllFiles = Dir.GetAllFile({ ".png" }, true);
		for (UEngineFile& File : AllFiles)
		{
			UEngineSprite::Load(File.GetFullPath());
		}

		std::vector<UEngineDirectory> AllDirectorys = Dir.GetAllDirectory();
		for (size_t i = 0; i < AllDirectorys.size(); i++)
		{
			UEngineSprite::LoadFolder(AllDirectorys[i].GetFullPath());
		}
	}
	// Map 리소스 로드
	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("ContentsResources");
		Dir.Move("Map");

		std::vector<UEngineFile> AllFiles = Dir.GetAllFile({ ".png" }, true);
		for (UEngineFile& File : AllFiles)
		{
			UEngineSprite::Load(File.GetFullPath());
		}

		std::vector<UEngineDirectory> AllDirectorys = Dir.GetAllDirectory();
		for (size_t i = 0; i < AllDirectorys.size(); i++)
		{
			UEngineSprite::LoadFolder(AllDirectorys[i].GetFullPath());
		}
	}

	// Player 리소스 로드
	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("ContentsResources");
		Dir.Move("Player");

		std::vector<UEngineFile> AllFiles = Dir.GetAllFile({ ".png" }, true);
		for (UEngineFile& File : AllFiles)
		{
			UEngineSprite::Load(File.GetFullPath());
		}

		std::vector<UEngineDirectory> AllDirectorys = Dir.GetAllDirectory();
		for (size_t i = 0; i < AllDirectorys.size(); i++)
		{
			UEngineSprite::LoadFolder(AllDirectorys[i].GetFullPath());
		}
	}

	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("ContentsResources");
		Dir.Move("Bomb");

		std::vector<UEngineFile> AllFiles = Dir.GetAllFile({ ".png" }, true);
		for (UEngineFile& File : AllFiles)
		{
			UEngineSprite::Load(File.GetFullPath());
		}

		std::vector<UEngineDirectory> AllDirectorys = Dir.GetAllDirectory();
		for (size_t i = 0; i < AllDirectorys.size(); i++)
		{
			UEngineSprite::LoadFolder(AllDirectorys[i].GetFullPath());
		}
	}

	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("ContentsResources");
		Dir.Move("Item");

		std::vector<UEngineFile> AllFiles = Dir.GetAllFile({ ".png" }, true);
		for (UEngineFile& File : AllFiles)
		{
			UEngineSprite::Load(File.GetFullPath());
		}

		std::vector<UEngineDirectory> AllDirectorys = Dir.GetAllDirectory();
		for (size_t i = 0; i < AllDirectorys.size(); i++)
		{
			UEngineSprite::LoadFolder(AllDirectorys[i].GetFullPath());
		}
	}
}