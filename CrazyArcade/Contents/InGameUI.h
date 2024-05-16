#pragma once

class AInGameUI : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constructor destructor
	AInGameUI();
	~AInGameUI();

	// delete Function
	AInGameUI(const AInGameUI& _Other) = delete;
	AInGameUI(AInGameUI&& _Other) noexcept = delete;
	AInGameUI& operator=(const AInGameUI& _Other) = delete;
	AInGameUI& operator=(AInGameUI&& _Other) = delete;

	
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTIme) override;

private:
	void CountDown(float _DeltaTime);
	void TimerText();
	void IntToText();


	std::string MinText;
	std::string SecText;

	int Min = 0;
	
	
	UImage* CancelBtn = nullptr;
	UImage* ResultBackGround = nullptr;
	UImage* ResultSummary = nullptr;
	std::vector<UImage*> ScoreUI = {nullptr,};


};

