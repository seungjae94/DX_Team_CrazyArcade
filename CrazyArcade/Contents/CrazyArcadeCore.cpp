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
	GEngine->ChangeLevel("InitTestLevel");
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
		Dir.Move("Bazzi");

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