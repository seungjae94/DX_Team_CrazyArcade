#pragma once

// 설명 : Block 기본 클래스
class ABlockBase : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	ABlockBase();
	~ABlockBase();

	// delete Function
	ABlockBase(const ABlockBase& _Other) = delete;
	ABlockBase(ABlockBase&& _Other) noexcept = delete;
	ABlockBase& operator=(const ABlockBase& _Other) = delete;
	ABlockBase& operator=(ABlockBase&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

