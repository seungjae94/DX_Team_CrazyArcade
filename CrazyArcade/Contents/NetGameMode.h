#pragma once

class ANetGameMode : public AGameMode
{
	GENERATED_BODY(AGameMode)
public:
	// constructor destructor
	ANetGameMode();
	~ANetGameMode();

	// delete Function
	ANetGameMode(const ANetGameMode& _Other) = delete;
	ANetGameMode(ANetGameMode&& _Other) noexcept = delete;
	ANetGameMode& operator=(const ANetGameMode& _Other) = delete;
	ANetGameMode& operator=(ANetGameMode&& _Other) noexcept = delete;

protected:
	virtual void HandlerInit() {};
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	bool IsHandlerInit = false;
};

