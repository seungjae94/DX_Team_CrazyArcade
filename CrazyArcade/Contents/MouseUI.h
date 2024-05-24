#pragma once

class AMouse : public AActor
{

	GENERATED_BODY(AActor)
public:
	// constructor destructor
	AMouse();
	~AMouse();

	// delete Function
	AMouse(const AMouse& _Other) = delete;
	AMouse(AMouse&& _Other) noexcept = delete;
	AMouse& operator=(const AMouse& _Other) = delete;
	AMouse& operator=(AMouse&& _Other) = delete;
	void SetMousePos();
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTIme) override;
private:
	
	UImage* MouseRender = nullptr;
	
};

