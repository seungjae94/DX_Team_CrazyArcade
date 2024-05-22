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
