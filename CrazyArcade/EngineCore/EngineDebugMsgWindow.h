#pragma once
#include "EngineDefines.h"
#include "EngineEditorWindow.h"
#include <vector>

// Ό³Έν :
class UEngineDebugMsgWindow : public UEngineEditorWindow
{
	GENERATED_BODY(UEngineEditorWindow);

public:
	// constrcuter destructer
	UEngineDebugMsgWindow();
	~UEngineDebugMsgWindow();

	// delete Function
	UEngineDebugMsgWindow(const UEngineDebugMsgWindow& _Other) = delete;
	UEngineDebugMsgWindow(UEngineDebugMsgWindow&& _Other) noexcept = delete;
	UEngineDebugMsgWindow& operator=(const UEngineDebugMsgWindow& _Other) = delete;
	UEngineDebugMsgWindow& operator=(UEngineDebugMsgWindow&& _Other) noexcept = delete;

	static void PushMsg(std::string_view _Msg);

protected:
	void Init() override;
	void OnGui(ULevel* Level, float _Delta) override;

private:
	static std::vector<std::string> Msg;
};

