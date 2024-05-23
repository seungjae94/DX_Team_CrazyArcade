#pragma once

class UEngineWindow;
class UEngineCore;
class UEngineInputRecorderReleaser;

class UEngineInputRecorder
{
	friend UEngineWindow;
	friend UEngineCore;
public:
	static void RecordStart(std::string_view _Text = "", int _MaxLength = 100);
	static void RecordEnd();
	static std::string GetText();

protected:


private:
	static bool Activeness;
	static int MaxLength;
	static bool IgnoreCompositionResult;

	static std::wstring WText;
	static std::string CombLetter;
	static HWND hWnd;
	static HIMC hIMC;
	static const std::string AllAlpha;
	static const std::string AllNumericAndSpecial;
	static const std::vector<int> AllSpecial;

	static void Init(HWND _hWnd);
	static bool IsNative();
	static void ImeCompositionTick(LPARAM _lParam);
	static void CharTick(WPARAM _wParam);
	static void Release();
	static void MergeCombLetter();

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

