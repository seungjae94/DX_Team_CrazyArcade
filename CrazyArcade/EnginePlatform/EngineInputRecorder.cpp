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
			//ImmSetCompositionString(hIMC, SCS_SETSTR, NULL, 0, NULL, 0);
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
				//ImmSetCompositionString(hIMC, SCS_SETSTR, NULL, 0, NULL, 0);
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
				//ImmSetCompositionString(hIMC, SCS_SETSTR, NULL, 0, NULL, 0);
				//ImmSetCompositionString(hIMC, SCS_)
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
//
//void UEngineInputRecorder::AppendKoreanLetter(char _Alphabet)
//{
//	// c를 한글 글자로 번역
//	wchar_t KorAlphabet;
//
//	if (true == UEngineInput::IsPress(VK_SHIFT) && true == EngAlphaToKorAlphaDouble.contains(_Alphabet))
//	{
//		KorAlphabet = EngAlphaToKorAlphaDouble[_Alphabet];
//	}
//	else
//	{
//		KorAlphabet = EngAlphaToKorAlpha[_Alphabet];
//	}
//
//	if (0 == WText.size())
//	{
//		WText += KorAlphabet;
//		return;
//	}
//
//	wchar_t PrevChar = WText.back();
//
//	if (PrevChar < 44032)
//	{
//		WText += KorAlphabet;
//		return;
//	}
//
//	// 이전 글자가 한글이다.
//
//
//	// 한글 한 글자의 십진수 유니코드 = [{(초성)×588} + {(중성)×28} + (종성)] + 44032
//	wchar_t First = (PrevChar - 44032) / 588;
//	wchar_t Mid = (PrevChar - 44032) % 588 / 28;
//	wchar_t Last = (PrevChar - 44032) % 588 % 28;
//
//	if (0 == Mid)
//	{
//
//	}
//	if (0 == Last)
//	{
//
//	}
//}

bool UEngineInputRecorder::IsNative()
{
	DWORD dwConversion;
	DWORD dwSentence;
	ImmGetConversionStatus(hIMC, &dwConversion, &dwSentence);

	return IME_CMODE_NATIVE == dwConversion;
}

//class EngineInputRecorderInitializer
//{
//public:
//	EngineInputRecorderInitializer()
//	{
//		UEngineInputRecorder::EngAlphaToKorAlpha['A'] = L'ㅁ';
//		UEngineInputRecorder::EngAlphaToKorAlpha['B'] = L'ㅠ';
//		UEngineInputRecorder::EngAlphaToKorAlpha['C'] = L'ㅊ';
//		UEngineInputRecorder::EngAlphaToKorAlpha['D'] = L'ㅇ';
//		UEngineInputRecorder::EngAlphaToKorAlpha['E'] = L'ㄷ';
//		UEngineInputRecorder::EngAlphaToKorAlpha['F'] = L'ㄹ';
//		UEngineInputRecorder::EngAlphaToKorAlpha['G'] = L'ㅎ';
//		UEngineInputRecorder::EngAlphaToKorAlpha['H'] = L'ㅗ';
//		UEngineInputRecorder::EngAlphaToKorAlpha['I'] = L'ㅑ';
//		UEngineInputRecorder::EngAlphaToKorAlpha['J'] = L'ㅓ';
//		UEngineInputRecorder::EngAlphaToKorAlpha['K'] = L'ㅏ';
//		UEngineInputRecorder::EngAlphaToKorAlpha['L'] = L'ㅣ';
//		UEngineInputRecorder::EngAlphaToKorAlpha['M'] = L'ㅡ';
//		UEngineInputRecorder::EngAlphaToKorAlpha['N'] = L'ㅜ';
//		UEngineInputRecorder::EngAlphaToKorAlpha['O'] = L'ㅐ';
//		UEngineInputRecorder::EngAlphaToKorAlpha['P'] = L'ㅔ';
//		UEngineInputRecorder::EngAlphaToKorAlpha['Q'] = L'ㅂ';
//		UEngineInputRecorder::EngAlphaToKorAlpha['R'] = L'ㄱ';
//		UEngineInputRecorder::EngAlphaToKorAlpha['S'] = L'ㄴ';
//		UEngineInputRecorder::EngAlphaToKorAlpha['T'] = L'ㅅ';
//		UEngineInputRecorder::EngAlphaToKorAlpha['U'] = L'ㅕ';
//		UEngineInputRecorder::EngAlphaToKorAlpha['V'] = L'ㅍ';
//		UEngineInputRecorder::EngAlphaToKorAlpha['W'] = L'ㅈ';
//		UEngineInputRecorder::EngAlphaToKorAlpha['X'] = L'ㅌ';
//		UEngineInputRecorder::EngAlphaToKorAlpha['Y'] = L'ㅛ';
//		UEngineInputRecorder::EngAlphaToKorAlpha['Z'] = L'ㅋ';
//
//		UEngineInputRecorder::EngAlphaToKorAlphaDouble['R'] = L'ㄲ';
//		UEngineInputRecorder::EngAlphaToKorAlphaDouble['E'] = L'ㄸ';
//		UEngineInputRecorder::EngAlphaToKorAlphaDouble['Q'] = L'ㅃ';
//		UEngineInputRecorder::EngAlphaToKorAlphaDouble['T'] = L'ㅆ';
//		UEngineInputRecorder::EngAlphaToKorAlphaDouble['W'] = L'ㅉ';
//	}
//};
//
//EngineInputRecorderInitializer Initializer;