#include "PreCompile.h"
#include "CrazyArcadeCore.h"
#include "InitTestGameMode.h"
#include "MapTestLevel.h"
#include "PlayGameMode.h"
#include "CrazyArcadeDebugWindow.h"
#include <EngineCore/EngineEditorGUI.h>
#include "ServerGameMode.h"

std::shared_ptr<UEngineNet> UCrazyArcadeCore::Net = nullptr;

UCrazyArcadeCore::UCrazyArcadeCore()
{
}

UCrazyArcadeCore::~UCrazyArcadeCore()
{
}

void UCrazyArcadeCore::Initialize()
{
	ResLoad();

	UEngineEditorGUI::CreateEditorWindow<UCrazyArcadeDebugWindow>("CrazyArcadeDebugWindow");

	GEngine->CreateLevel<AInitTestGameMode>("InitTestLevel");
	GEngine->CreateLevel<AMapTestLevel>("MapTestLevel");
	GEngine->CreateLevel<APlayGameMode>("PlayGameMode");
	GEngine->CreateLevel<AServerGameMode>("ServerGameMode");
	GEngine->ChangeLevel("InitTestLevel");
}

void UCrazyArcadeCore::ResLoad()
{
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
}