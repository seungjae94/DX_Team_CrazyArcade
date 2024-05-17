#pragma once

// ¼³¸í : ¹° ÆøÅº ÆÄµµ
class AWave : public ANetActor
{
	GENERATED_BODY(ANetActor)
public:
	// constrcuter destructer
	AWave();
	~AWave();

	// delete Function
	AWave(const AWave& _Other) = delete;
	AWave(AWave&& _Other) noexcept = delete;
	AWave& operator=(const AWave& _Other) = delete;
	AWave& operator=(AWave&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void SetImgCutting();
	void CreateAnimation();

private:
	USpriteRenderer* Body = nullptr;

};

