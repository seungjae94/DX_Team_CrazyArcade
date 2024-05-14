#pragma once
#include <EngineCore/Widget.h>
#include <EngineCore/TextWidget.h>
#include<vector>
class AMainTitleGameMode : public AGameMode
{
	GENERATED_BODY(AGameMode)
public:
	// constructor destructor
	AMainTitleGameMode();
	~AMainTitleGameMode();

	// delete Function
	AMainTitleGameMode(const AMainTitleGameMode& _Other) = delete;
	AMainTitleGameMode(AMainTitleGameMode&& _Other) noexcept = delete;
	AMainTitleGameMode& operator=(const AMainTitleGameMode& _Other) = delete;
	AMainTitleGameMode& operator=(AMainTitleGameMode&& _Other) = delete;


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImage* TitleBackGround = nullptr;
	
	UImage* LoginUI = nullptr;

	UImage* StartButton = nullptr;

	UImage* PlayerNameBox = nullptr;

	UTextWidget* TextWidget = nullptr;
	std::vector<char> NameText;
	std::string PlayerName = " ";
	std::vector<UTextWidget*> TextWidgets = {};
	inline void SetText(const char _Text)
	{
		
		NameText.push_back( _Text);
	}
};

