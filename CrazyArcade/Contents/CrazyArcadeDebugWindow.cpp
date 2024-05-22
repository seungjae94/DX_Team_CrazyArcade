#include "PreCompile.h"
#include "CrazyArcadeDebugWindow.h"
#include "CrazyArcadeCore.h"
#include "MainTitleGameMode.h"


UCrazyArcadeDebugWindow::UCrazyArcadeDebugWindow()
{
}

UCrazyArcadeDebugWindow::~UCrazyArcadeDebugWindow()
{
}

void UCrazyArcadeDebugWindow::OnGui(ULevel* Level, float _Delta)
{
	
	On();

	if (true == ImGui::Button("Sunming IP"))
	{
		AMainTitleGameMode::Title->SungMinChangeIP();
	}

	if (true == ImGui::Button("My IP"))
	{
		AMainTitleGameMode::Title->MyChangeIP();
	}

	if (true == ImGui::Button("Lobby Title Level"))
	{
		GEngine->ChangeLevel("LobbyTitleTestLevel");
	}

	if (true == ImGui::Button("MainPlayLevel"))
	{
		GEngine->ChangeLevel("MainPlayLevel");
	}

	if (true == ImGui::Button("ServerGameMode"))
	{
		GEngine->ChangeLevel("ServerGameMode");
	}

	if (true == ImGui::Button("MainTitleGameMode"))
	{
		GEngine->ChangeLevel("TitleTestLevel");
	}

	if (true == ImGui::Button("Engine Test Level"))
	{
		GEngine->ChangeLevel("EngineTestLevel");
	}
}
