#include "PreCompile.h"
#include "EngineFont.h"
#include "EngineCore.h"

#pragma comment (lib, "FW1FontWrapper.lib")

// 팩토리는 1번만 
IFW1Factory* UEngineFont::Factory = nullptr;

class FontInit
{
public:
	FontInit()
	{
		FW1CreateFactory(FW1_VERSION, &UEngineFont::Factory);

		int a = 0;
	}

	~FontInit()
	{
		if (nullptr == UEngineFont::Factory)
		{
			UEngineFont::Factory->Release();
			UEngineFont::Factory = nullptr;
		}
	}
};

FontInit Init;

UEngineFont::UEngineFont() 
{
}

UEngineFont::~UEngineFont() 
{
	if (nullptr != Font)
	{
		Font->Release();
	}
}

void UEngineFont::ResLoad()
{
	std::string Name = GetName();
	std::wstring WName = UEngineString::AnsiToUniCode(Name);

	if (S_OK != UEngineFont::Factory->CreateFontWrapper(GEngine->GetDirectXDevice(), WName.c_str(), &Font))
	{
		MsgBoxAssert("폰트 로딩에 실패했습니다.");
	}
}

void UEngineFont::TextDraw(float4 _ScreenPos,
	std::string _Text,
	float _Scale,
	Color8Bit _Color,
	int _Flag)
{
	//FW1_LEFT = 0x0,
	//	/// <summary>Text is centered horizontally.</summary>
	//	FW1_CENTER = 0x1,
	//	/// <summary>Text is right-aligned.</summary>
	//	FW1_RIGHT = 0x2,
	//	/// <summary>Text is aligned at the top of the layout-box. This is the default.</summary>
	//	FW1_TOP = 0x0,
	//	/// <summary>Text is centered vertically.</summary>
	//	FW1_VCENTER = 0x4,
	//	/// <summary>Text is aligned at the bottom of the layout-box.</summary>
	//	FW1_BOTTOM = 0x8,


	Color8Bit Bit;

	std::wstring Text = UEngineString::AnsiToUniCode(_Text);

	Font->DrawString(GEngine->GetDirectXContext(), Text.c_str(), _Scale, _ScreenPos.X, _ScreenPos.Y, _Color.Color, _Flag);
}