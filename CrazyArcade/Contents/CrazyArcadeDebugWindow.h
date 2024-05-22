#pragma once

class UCrazyArcadeDebugWindow : public UEngineEditorWindow
{
public:
	UCrazyArcadeDebugWindow();
	~UCrazyArcadeDebugWindow();

	UCrazyArcadeDebugWindow(const UCrazyArcadeDebugWindow& _Other) = delete;
	UCrazyArcadeDebugWindow(UCrazyArcadeDebugWindow&& _Other) noexcept = delete;
	UCrazyArcadeDebugWindow& operator=(const UCrazyArcadeDebugWindow& _Other) = delete;
	UCrazyArcadeDebugWindow& operator=(UCrazyArcadeDebugWindow&& _Other) noexcept = delete;

protected:


private:
	void OnGui(ULevel* Level, float _Delta) override;

	float LowFps = 1000000.0f;
};

