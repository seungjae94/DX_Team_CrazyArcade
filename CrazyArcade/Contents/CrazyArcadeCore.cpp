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
#include "ServerManager.h"



std::shared_ptr<UEngineNet> UCrazyArcadeCore::Net = nullptr;
std::shared_ptr<ServerManager> UCrazyArcadeCore::NetWindow = nullptr;

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


	//std::shared_ptr<UEngineNetWindow> NetWindow = UEngineEditorGUI::CreateEditorWindow<UEngineNetWindow>("NetWindow");
	//UCrazyArcadeCore::Net = NetWindow;




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
	UCrazyArcadeCore::NetWindow->Update(_DeltaTime);
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