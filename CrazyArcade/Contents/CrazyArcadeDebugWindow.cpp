#include "PreCompile.h"
#include "CrazyArcadeDebugWindow.h"
#include "CrazyArcadeCore.h"
#include "MainTitleGameMode.h"
#include "ConnectionInfo.h"


UCrazyArcadeDebugWindow::UCrazyArcadeDebugWindow()
{
}

UCrazyArcadeDebugWindow::~UCrazyArcadeDebugWindow()
{
}

void UCrazyArcadeDebugWindow::OnGui(ULevel* Level, float _Delta)
{
	int RedCount = ConnectionInfo::GetInst().GetRedCount();
	int BlueCount = ConnectionInfo::GetInst().GetBlueCount();
	ECharacterColor Test = ConnectionInfo::GetInst().GetWins();
	std::string WinText;
	switch (Test)
	{
	case ECharacterColor::Red:
		WinText = "Red Team Wins";
		break;
	case ECharacterColor::Blue:
		WinText = "Blue Team Wins";
		break;
	case ECharacterColor::Green:
		WinText = "Draw";
		break;
	case ECharacterColor::None:
		WinText = "No One Wins";
		break;
	}
	ImGui::Text((std::string("Red : ") + std::to_string(RedCount)).c_str());
	ImGui::Text((std::string("Blue : ") + std::to_string(BlueCount)).c_str());
	ImGui::Text(WinText.c_str());
	
	float Fps = 1.0f / _Delta;
	LowFps = (LowFps < Fps) ? LowFps : Fps;

	std::string FpsText = std::string("FPS: ") + std::to_string(Fps);
	std::string LowFpsText = std::string("Low FPS: ") + std::to_string(LowFps);

	ImGui::Text(FpsText.c_str());
	ImGui::Text(LowFpsText.c_str());

	if (true == ImGui::Button("Reset FPS"))
	{
		LowFps = 1000000.0f;
	}

	if (true == ImGui::Button("Sunming IP"))
	{
		AMainTitleGameMode::Title->SungMinChangeIP();
	}

	if (true == ImGui::Button("My IP"))
	{
		LowFps = 1000000.0f;
		AMainTitleGameMode::Title->MyChangeIP();
	}

	if (true == ImGui::Button("Intro Level"))
	{
		GEngine->ChangeLevel("IntroLevel");
	}

	if (true == ImGui::Button("Lobby Title Level"))
	{
		GEngine->ChangeLevel("LobbyLevel");
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
		GEngine->ChangeLevel("MainTitleLevel");
	}

	if (true == ImGui::Button("Engine Test Level"))
	{
		GEngine->ChangeLevel("EngineTestLevel");
	}
}
