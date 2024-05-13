#include "PreCompile.h"
#include "CrazyArcadeCore.h"
#include "InitTestGameMode.h"

UCrazyArcadeCore::UCrazyArcadeCore()
{
}

UCrazyArcadeCore::~UCrazyArcadeCore()
{
}

void UCrazyArcadeCore::Initialize()
{
	ResLoad();

	GEngine->CreateLevel<AInitTestGameMode>("InitTestLevel");
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
}