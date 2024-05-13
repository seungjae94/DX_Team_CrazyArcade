#include "PreCompile.h"
#include "EngineDebugMsgWindow.h"
#include "EngineCore.h"

std::vector<std::string> UEngineDebugMsgWindow::Msg;

UEngineDebugMsgWindow::UEngineDebugMsgWindow() 
{
}

UEngineDebugMsgWindow::~UEngineDebugMsgWindow() 
{
}

void UEngineDebugMsgWindow::Init()
{
	
}

void UEngineDebugMsgWindow::PushMsg(std::string_view _Msg)
{
	Msg.push_back(_Msg.data());
}

void UEngineDebugMsgWindow::OnGui(ULevel* Level, float _Delta)
{
	if (true == ImGui::Button("DebugSwitch"))
	{
		GEngine->IsDebug = !GEngine->IsDebug;
	}
	// imgui는 윈도우 메세지를 이용한다.
	// 여기 내부에 하고 싶은걸 치면 된다.
	for (size_t i = 0; i < Msg.size(); i++)
	{
		ImGui::Text(Msg[i].c_str());
	}

	Msg.clear();
}