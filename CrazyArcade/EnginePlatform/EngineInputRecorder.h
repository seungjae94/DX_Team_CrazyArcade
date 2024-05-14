#pragma once

class UEngineWindow;
class UEngineCore;
class UEngineInputRecorderReleaser;

class UEngineInputRecorder
{
	friend UEngineWindow;
	friend UEngineCore;
public:
	UEngineInputRecorder();
	~UEngineInputRecorder();

	UEngineInputRecorder(const UEngineInputRecorder& _Other) = delete;
	UEngineInputRecorder(UEngineInputRecorder&& _Other) noexcept = delete;
	UEngineInputRecorder& operator=(const UEngineInputRecorder& _Other) = delete;
	UEngineInputRecorder& operator=(UEngineInputRecorder&& _Other) noexcept = delete;

	static void RecordStart();
	static void RecordEnd();
	static std::string GetText();

protected:


private:
	enum class EFinalLetterState
	{
		Empty,
		First,
		Mid,
		Last,
		AlphaNumeric
	};

	static bool Activeness;
	static bool ImeTickCalled;

	static std::wstring WText;
	static std::string CombLetter;
	static std::string CompLetter;
	static HWND hWnd;
	static HIMC hIMC;
	static const std::string AllAlpha;
	static const std::string AllNumeric;
	static EFinalLetterState FinalLetterState;

	static void Init(HWND _hWnd);
	static bool IsNative();
	static void Tick();
	static void ImeTick(LPARAM _lParam);
	static void Release();

private:
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

