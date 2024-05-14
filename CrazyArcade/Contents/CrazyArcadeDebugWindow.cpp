#include "PreCompile.h"
#include "CrazyArcadeDebugWindow.h"

UCrazyArcadeDebugWindow::UCrazyArcadeDebugWindow()
{
}

UCrazyArcadeDebugWindow::~UCrazyArcadeDebugWindow()
{
}

void UCrazyArcadeDebugWindow::OnGui(ULevel* Level, float _Delta)
{
	if (true == ImGui::Button("Main Title Level"))
	{
		//GEngine->ChangeLevel("MainTitleLevel");
	}

	if (true == ImGui::Button("Lobby Title Level"))
	{
		GEngine->ChangeLevel("LobbyTitleTestLevel");
	}

	if (true == ImGui::Button("MainPlayLevel"))
	{
		GEngine->ChangeLevel("MainPlayLevel");
	}

	if (true == ImGui::Button("Play Level"))
	{
		GEngine->ChangeLevel("PlayGameMode");
	}

	if (true == ImGui::Button("ServerGameMode"))
	{
		GEngine->ChangeLevel("ServerGameMode");
	}
	if (true == ImGui::Button("MainTitleGameMode"))
	{
		GEngine->ChangeLevel("TitleTestLevel");
	}
}
