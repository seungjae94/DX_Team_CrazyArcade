#include "PreCompile.h"
#include "EngineEditorWindow.h"
#include "imgui.h"

UEngineEditorWindow::UEngineEditorWindow() 
{
}

UEngineEditorWindow::~UEngineEditorWindow() 
{
}

void UEngineEditorWindow::Tick(ULevel* Level, float _Delta)
{

}

void UEngineEditorWindow::Begin()
{
	std::string Name = GetName();

	// 이름이 없으면 터진다.
	ImGui::Begin(Name.c_str(), &IsActive);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
}

void UEngineEditorWindow::End()
{
	ImGui::End();
}