#pragma once
#include <EnginePlatform/EngineResources.h>

#include "ThirdParty\FW1FontWrapper\inc\FW1FontWrapper.h"

// 글꼴이 있어야 그 글꼴로 나옵니다.

// 설명 :
class UEngineFont : public UEngineResources<UEngineFont>
{
	friend class FontInit;
public:
	// constrcuter destructer
	UEngineFont();
	~UEngineFont();

	// delete Function
	UEngineFont(const UEngineFont& _Other) = delete;
	UEngineFont(UEngineFont&& _Other) noexcept = delete;
	UEngineFont& operator=(const UEngineFont& _Other) = delete;
	UEngineFont& operator=(UEngineFont&& _Other) noexcept = delete;

	static std::shared_ptr<UEngineFont> Load(std::string_view _FontName)
	{
		std::shared_ptr<UEngineFont> NewRes = CreateResName(_FontName, _FontName);
		NewRes->ResLoad();
		return NewRes;
	}

	void TextDraw(float4 _ScreenPos,
			std::string _Text,
			float _Scale,
			Color8Bit _Color,
			int _Flag
	);

	//FW1_LEFT = 0x0,
	//	FW1_CENTER = 0x1,
	//	FW1_RIGHT = 0x2,
	//	FW1_TOP = 0x0,
	//	FW1_VCENTER = 0x4,
	//	FW1_BOTTOM = 0x8,

	// FW1_TEXT_FLAG::FW1_CENTER | FW1_VCENTER


protected:

private:
	// 생성용 인터페이스
	static IFW1Factory* Factory;

	IFW1FontWrapper* Font = nullptr;

	void ResLoad();

};

