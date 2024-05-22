#pragma once
#include <EngineCore/StateManager.h>

class AMainPlayLevel;

// 설명 : Bush 기본 클래스
class ABushBase : public ANetActor
{
	GENERATED_BODY(ANetActor)
public:
	// constructor destructor
	ABushBase();
	~ABushBase();
	
	// delete Function
	ABushBase(const ABushBase& _Other) = delete;
	ABushBase(ABushBase&& _Other) noexcept = delete;
	ABushBase& operator=(const ABushBase& _Other) = delete;
	ABushBase& operator=(ABushBase&& _Other) noexcept = delete;

	inline USpriteRenderer* GetBody() const
	{
		return Body;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	AMainPlayLevel* PlayLevel = nullptr;
	USpriteRenderer* Body = nullptr;

	std::vector<float> ShakingPosY;
	int ShakingIdx = 0;

// FSM
private:
	UStateManager State;
	void StateInit();


};

