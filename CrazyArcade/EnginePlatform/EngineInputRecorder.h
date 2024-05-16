#pragma once

class UEngineWindow;
class UEngineCore;
class UEngineInputRecorderReleaser;

class UEngineInputRecorder
{
	friend UEngineWindow;
	friend UEngineCore;
public:
	static void RecordStart(std::string_view _Text = "");
	static void RecordEnd();
	static std::string GetText();

protected:


private:
	static bool Activeness;
	static bool ImeTickCalled;
	static bool IgnoreCompositionResult;

	static std::wstring WText;
	static std::string CombLetter;
	static HWND hWnd;
	static HIMC hIMC;
	static const std::string AllAlpha;
	static const std::string AllNumeric;

	static void Init(HWND _hWnd);
	static bool IsNative();
	static void Tick();
	static void ImeTick(LPARAM _lParam);
	static void Release();

private:
	// 객체 생성 금지
	UEngineInputRecorder();
	~UEngineInputRecorder();

	class UEngineInputRecorderReleaser
	{
	public:
		~UEngineInputRecorderReleaser()
		{
			UEngineInputRecorder::Release();
		}
	};

	static UEngineInputRecorderReleaser Releaser;
};

