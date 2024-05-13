#pragma once

class ATimerUI : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constructor destructor
	ATimerUI();
	~ATimerUI();

	// delete Function
	ATimerUI(const ATimerUI& _Other) = delete;
	ATimerUI(ATimerUI&& _Other) noexcept = delete;
	ATimerUI& operator=(const ATimerUI& _Other) = delete;
	ATimerUI& operator=(ATimerUI&& _Other) = delete;

	inline void SetTimer(float _Time)
	{
		Timer = _Time;
	}

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
	

	int Sec = 0;
	int Secint = 0;
	int SecInt2 = 0;
	float Timer = 0.0;

	UImage* MinUI = nullptr;
	UImage* MinUI2 = nullptr;
		
	UImage* SecUI = nullptr;
	UImage* SecUI2 = nullptr;
	

};	

