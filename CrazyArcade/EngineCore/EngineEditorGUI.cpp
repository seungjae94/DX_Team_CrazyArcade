#include "PreCompile.h"
#include "EngineCore.h"

#include "EngineEditorGUI.h"
#include "EngineEditorWindow.h"


std::map<std::string, std::shared_ptr<UEngineEditorWindow>> UEngineEditorGUI::EditorWindows;
bool UEngineEditorGUI::FocusTest = true;

UEngineEditorGUI::UEngineEditorGUI() 
{
}

UEngineEditorGUI::~UEngineEditorGUI() 
{
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void UEngineEditorGUI::GUIInit()
{

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
    //io.ConfigViewportsNoAutoMerge = true;
    //io.ConfigViewportsNoTaskBarIcon = true;
    //io.ConfigViewportsNoDefaultParent = true;
    //io.ConfigDockingAlwaysTabBar = true;
    //io.ConfigDockingTransparentPayload = true;
    //io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleFonts;     // FIXME-DPI: Experimental. THIS CURRENTLY DOESN'T WORK AS EXPECTED. DON'T USE IN USER APP!
    //io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleViewports; // FIXME-DPI: Experimental.

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer backends

    ImGui_ImplWin32_Init(GEngine->EngineWindow.GetHWND());
    ImGui_ImplDX11_Init(GEngine->GetDirectXDevice(), GEngine->GetDirectXContext());

    GEngine->EngineWindow.SetUserWindowCallBack(ImGui_ImplWin32_WndProcHandler);

}

void UEngineEditorGUI::GUIRelease()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

void UEngineEditorGUI::GUIRender(ULevel* Level, float _DeltaTime)
{
    if (true == FocusTest)
    {
        HWND CurHWnd = GetFocus();
        if (GEngine->EngineWindow.GetHWND() != CurHWnd)
        {
            GEngine->EngineWindow.SetFocus();
            FocusTest = false;
        }
    }
	// imgui는 자신만의 스왑체인을 더 만들어낸다.
	// 여기서 한번다 지워 imgui에 속하는 GUI들을 다 지운다.
	// 스타트
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	{
        for (std::pair<const std::string, std::shared_ptr<UEngineEditorWindow>> WindowPair : EditorWindows)
        {
            std::shared_ptr<UEngineEditorWindow> Window = WindowPair.second;

            Window->Tick(Level, _DeltaTime);

            if (true == Window->IsActive)
            {
                Window->Begin();

                Window->OnGui(Level, _DeltaTime);

                Window->End();
            }
        }
	}

	// 랜더링
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    ImGuiIO& io = ImGui::GetIO();


	// Update and Render additional Platform Windows
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}

}

void UEngineEditorGUI::WindowInit(std::shared_ptr<UEngineEditorWindow> _Window, std::string_view _Name)
{
    _Window->SetName(_Name);
    _Window->Init();
}