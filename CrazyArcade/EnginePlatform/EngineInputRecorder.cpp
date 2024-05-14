#include "PreCompile.h"
#include "EngineInputRecorder.h"
#include <EnginePlatform/EngineInput.h>

bool UEngineInputRecorder::Activeness = false;
bool UEngineInputRecorder::ImeTickCalled = false;
std::wstring UEngineInputRecorder::WText = L"";
std::string UEngineInputRecorder::CombLetter = "";
std::string UEngineInputRecorder::CompLetter = "";
HWND UEngineInputRecorder::hWnd = nullptr;
HIMC UEngineInputRecorder::hIMC = nullptr;
const std::string UEngineInputRecorder::AllAlpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string UEngineInputRecorder::AllNumeric = "0123456789";
UEngineInputRecorder::EFinalLetterState UEngineInputRecorder::FinalLetterState;
UEngineInputRecorder::UEngineInputRecorderReleaser UEngineInputRecorder::Releaser;

UEngineInputRecorder::UEngineInputRecorder()
{
}

UEngineInputRecorder::~UEngineInputRecorder()
{
}

void UEngineInputRecorder::RecordStart()
{
	Activeness = true;
	WText = L"";
	ImmNotifyIME(hIMC, NI_COMPOSITIONSTR, CPS_CANCEL, 0);
}

void UEngineInputRecorder::RecordEnd()
{
	Activeness = false;
}

std::string UEngineInputRecorder::GetText()
{
	
	std::string ReturnText = "";
	
	if (WText.size() > 0)
	{
		ReturnText = UEngineString::UniCodeToAnsi(WText);
	}

	if (CombLetter.size() > 0)
	{
		ReturnText += CombLetter;
	}

	return ReturnText;
}

void UEngineInputRecorder::Init(HWND _hWnd)
{
	hWnd = _hWnd;
	hIMC = ImmGetContext(_hWnd);
}

void UEngineInputRecorder::ImeTick(LPARAM _lParam)
{
	if (false == Activeness)
	{
		return;
	}

	if (false == IsNative())
	{
		return;
	}

	int Len = 0;

	if (_lParam & GCS_RESULTSTR)
	{
		Len = ImmGetCompositionString(hIMC, GCS_RESULTSTR, NULL, 0);
		if (Len > 0)
		{
			CompLetter.resize(Len);
			ImmGetCompositionString(hIMC, GCS_RESULTSTR, &CompLetter[0], Len);
			CompLetter.resize(Len);
			WText += UEngineString::AnsiToUniCode(CompLetter);
			CombLetter.clear();
			CompLetter.clear();
		}
	}
	else if (_lParam & GCS_COMPSTR)
	{
		Len = ImmGetCompositionString(hIMC, GCS_COMPSTR, NULL, 0);

		if (Len > 0)
		{
			CombLetter.resize(Len);
			ImmGetCompositionString(hIMC, GCS_COMPSTR, &CombLetter[0], Len);
			CombLetter.resize(Len);
		}
		else
		{
			CombLetter.clear();
		}
	}

	ImeTickCalled = true;
}

void UEngineInputRecorder::Tick()
{
	if (false == Activeness)
	{
		return;
	}

	if (true == ImeTickCalled)
	{
		ImeTickCalled = false;
		return;
	}

	if (true == UEngineInput::IsDown(VK_BACK))
	{
		if (CombLetter.size() > 0)
		{
			for (char Ch : CombLetter)
			{
				if (Ch == 0)
				{
					MsgBoxAssert("문자가 0입니다.");
				}
			}

			WText += UEngineString::AnsiToUniCode(CombLetter);
			CombLetter.clear();
			ImmNotifyIME(hIMC, NI_COMPOSITIONSTR, CPS_CANCEL, 0);
		}

		if (0 == WText.size())
		{
			return;
		}

		WText.pop_back();
		return;
	}

	for (char c : AllNumeric)
	{
		if (true == UEngineInput::IsDown(c))
		{
			if (CombLetter.size() > 0)
			{
				for (char Ch : CombLetter)
				{
					if (Ch == 0)
					{
						MsgBoxAssert("문자가 0입니다.");
					}
				}

				WText += UEngineString::AnsiToUniCode(CombLetter);
				CombLetter.clear();
				ImmNotifyIME(hIMC, NI_COMPOSITIONSTR, CPS_CANCEL, 0);
			}

			WText += UEngineString::AnsiToUniCode(std::string(1, c));
			FinalLetterState = EFinalLetterState::AlphaNumeric;
			return;
		}
	}

	if (true == IsNative())
	{
		return;
	}

	for (char c : AllAlpha)
	{
		if (true == UEngineInput::IsDown(c))
		{
			if (CombLetter.size() > 0)
			{
				for (char Ch : CombLetter)
				{
					if (Ch == 0)
					{
						MsgBoxAssert("문자가 0입니다.");
					}
				}

				WText += UEngineString::AnsiToUniCode(CombLetter);
				CombLetter.clear();
				ImmNotifyIME(hIMC, NI_COMPOSITIONSTR, CPS_CANCEL, 0);
			}

			WText += UEngineString::AnsiToUniCode(std::string(1, c));
			FinalLetterState = EFinalLetterState::AlphaNumeric;
			return;
		}
	}
}

void UEngineInputRecorder::Release()
{
	ImmReleaseContext(hWnd, hIMC);
}

bool UEngineInputRecorder::IsNative()
{
	DWORD dwConversion;
	DWORD dwSentence;
	ImmGetConversionStatus(hIMC, &dwConversion, &dwSentence);

	return IME_CMODE_NATIVE == dwConversion;
}

//class UEngineInputRecorderReleaser
//{
//public:
//	~UEngineInputRecorderReleaser()
//	{
//		UEngineInputRecorder::Release();
//	}
//};