#pragma once
#include "Widget.h"
#include "EngineFont.h"

// Ό³Έν :
class UTextWidget : public UWidget
{
public:
	// constrcuter destructer
	UTextWidget();
	~UTextWidget();

	// delete Function
	UTextWidget(const UTextWidget& _Other) = delete;
	UTextWidget(UTextWidget&& _Other) noexcept = delete;
	UTextWidget& operator=(const UTextWidget& _Other) = delete;
	UTextWidget& operator=(UTextWidget&& _Other) noexcept = delete;

	void SetFont(std::string_view _FontName);

	void SetFlag(FW1_TEXT_FLAG _Flag)
	{
		Flag = _Flag;
	}
	void SetScale(float _Scale)
	{
		Scale = _Scale;
	}
	void SetColor(Color8Bit _Color)
	{
		Color = _Color;
	}

	void SetText(std::string _Text)
	{
		Text = _Text;
	}

protected:
	bool Render(float _DeltaTime) override;

private:
	std::string Text = "NONE";
	int Flag = FW1_TEXT_FLAG::FW1_CENTER | FW1_TEXT_FLAG::FW1_VCENTER;
	float Scale = 20.0f;
	Color8Bit Color = Color8Bit::Red;
	std::shared_ptr<UEngineFont> Font = nullptr;
};

