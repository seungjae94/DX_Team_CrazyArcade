#include "PreCompile.h"
#include "CrazyArcadeCore.h"
#include "MainPlayLevel.h"
#include "CrazyArcadeDebugWindow.h"
#include <EngineCore/EngineEditorGUI.h>
#include "MainTitleGameMode.h"
#include "LobbyGameMode.h"
#include "ServerGameMode.h"
#include "IntroGameMode.h"

#include "Packets.h"
#include "ConnectionInfo.h"
#include "ServerManager.h"



std::shared_ptr<UEngineNet> UCrazyArcadeCore::Net = nullptr;
UServerManager UCrazyArcadeCore::NetManager;

UCrazyArcadeCore::UCrazyArcadeCore()
{
}

void UCrazyArcadeCore::End()
{
	std::shared_ptr<UEndSession> EndPacket = std::make_shared<UEndSession>();
	if (UCrazyArcadeCore::Net != nullptr) {
		EndPacket->SetSessionToken(UCrazyArcadeCore::Net->GetSessionToken());
		int a = UCrazyArcadeCore::Net->GetSessionToken();
		UCrazyArcadeCore::Net->Send(EndPacket);
		if (nullptr != Net)
		{
			Net->Off();
		}
		Net = nullptr;
	}
}

UCrazyArcadeCore::~UCrazyArcadeCore()
{
}

void UCrazyArcadeCore::Initialize()
{
	UEngineFont::Load("±¼¸²");
	ResLoad();

#ifdef _DEBUG
	UEngineEditorGUI::CreateEditorWindow<UCrazyArcadeDebugWindow>("CrazyArcadeDebugWindow");
#endif

	GEngine->CreateLevel<AMainPlayLevel>("MainPlayLevel");
	GEngine->CreateLevel<AMainTitleGameMode>("MainTitleLevel");
	GEngine->CreateLevel<AServerGameMode>("ServerGameMode");
	GEngine->CreateLevel<ALobbyGameMode>("LobbyLevel");
	GEngine->CreateLevel<AIntroGameMode>("IntroLevel");
	//GEngine->ChangeLevel("MainTitleLevel");
	GEngine->ChangeLevel("IntroLevel");
}

void UCrazyArcadeCore::Tick(float _DeltaTime)
{
	UCrazyArcadeCore::NetManager.Update(_DeltaTime);
}

void UCrazyArcadeCore::ResLoad()
{
	std::list<std::string> ImageFolderNames = {"UI", "Map", "Player", "Bomb", "Item", "Intro"};

	for (std::string_view ImageFolderName : ImageFolderNames)
	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("ContentsResources");
		Dir.Move(ImageFolderName);

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

	UEngineDirectory Dir;
	Dir.MoveToSearchChild("ContentsResources");
	Dir.Move("Sound");

	std::vector<UEngineFile> AllFiles = Dir.GetAllFile({ ".wav", ".mp3" }, true);
	for (UEngineFile& File : AllFiles)
	{
		UEngineSound::Load(File.GetFullPath());
	}
}