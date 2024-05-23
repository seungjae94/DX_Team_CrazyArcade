#include "PreCompile.h"
#include "EngineInputRecorder.h"
#include <EnginePlatform/EngineInput.h>

bool UEngineInputRecorder::Activeness = false;
int UEngineInputRecorder::MaxLength = 100;
bool UEngineInputRecorder::IgnoreCompositionResult = false;
std::wstring UEngineInputRecorder::WText = L"";
std::string UEngineInputRecorder::CombLetter = "";
HWND UEngineInputRecorder::hWnd = nullptr;
HIMC UEngineInputRecorder::hIMC = nullptr;
const std::string UEngineInputRecorder::AllAlpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string UEngineInputRecorder::AllNumericAndSpecial = "0123456789.";

UEngineInputRecorder::UEngineInputRecorderReleaser UEngineInputRecorder::Releaser;

UEngineInputRecorder::UEngineInputRecorder()
{
}

UEngineInputRecorder::~UEngineInputRecorder()
{
}

void UEngineInputRecorder::RecordStart(std::string_view _Text, int _MaxLength)
{
    Activeness = true;
    MaxLength = _MaxLength;

    if (0 == _Text.size())
    {
        WText = L"";
    }
    else
    {
        WText = UEngineString::AnsiToUniCode(_Text);
    }
    CombLetter.clear();
    ImmSetCompositionString(hIMC, SCS_SETSTR, NULL, 0, NULL, 0);
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

void UEngineInputRecorder::ImeCompositionTick(LPARAM _lParam)
{
    if (false == Activeness)
    {
        return;
    }

    if (WText.size() + 1 > MaxLength)
    {
        return;
    }

    int Len = 0;

    if (_lParam & GCS_RESULTSTR)
    {
        Len = ImmGetCompositionString(hIMC, GCS_RESULTSTR, NULL, 0);
        if (Len > 0 && false == IgnoreCompositionResult)
        {
            std::string CompLetter;
            CompLetter.resize(Len);
            ImmGetCompositionString(hIMC, GCS_RESULTSTR, &CompLetter[0], Len);
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
        }
        else
        {
            CombLetter.clear();
        }
    }

    IgnoreCompositionResult = false;
}

void UEngineInputRecorder::CharTick(WPARAM _wParam)
{
    if (false == Activeness)
    {
        return;
    }

    // 백스페이스
    if (_wParam == '\b')
    {
        MergeCombLetter();

        if (0 == WText.size())
        {
            return;
        }

        WText.pop_back();
        return;
    }

    if (_wParam == VK_RETURN)
    {
        return;
    }

    if (WText.size() + 1 > MaxLength)
    {
        return;
    }

    char NewChar = _wParam & 0xff;

    // 입력 가능한 문자가 아닐 경우 리턴
    if (NewChar != ' ' && false == (NewChar >= 33 && NewChar <= 126))
    {
        return;
    }

    MergeCombLetter();
    WText += std::wstring(1, NewChar);
    IgnoreCompositionResult = true;
}

void UEngineInputRecorder::Release()
{
    ImmReleaseContext(hWnd, hIMC);
}

void UEngineInputRecorder::MergeCombLetter()
{
    if (CombLetter.size() > 0)
    {
        WText += UEngineString::AnsiToUniCode(CombLetter);
        CombLetter.clear();
        ImmNotifyIME(hIMC, NI_COMPOSITIONSTR, CPS_CANCEL, 0);
    }
}

bool UEngineInputRecorder::IsNative()
{
    DWORD dwConversion;
    DWORD dwSentence;
    ImmGetConversionStatus(hIMC, &dwConversion, &dwSentence);

    return IME_CMODE_NATIVE == dwConversion;
}
