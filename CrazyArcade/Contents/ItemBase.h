#pragma once
#include <EngineCore/StateManager.h>

class AMainPlayLevel;

class AItemBase : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	AItemBase();
	~AItemBase();

	// delete Function
	AItemBase(const AItemBase& _Other) = delete;
	AItemBase(AItemBase&& _Other) noexcept = delete;
	AItemBase& operator=(const AItemBase& _Other) = delete;
	AItemBase& operator=(AItemBase&& _Other) noexcept = delete;

	inline EItemType GetItemType() const
	{
		return ItemType;
	}

	void SetItem(EItemType _Type);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelEnd(ULevel* _NextLevel) override;

private:
	void MoveUpDown(float _DeltaTime);

private:
	USpriteRenderer* Body = nullptr;
	USpriteRenderer* Shadow = nullptr;

	AMainPlayLevel* PlayLevel = nullptr;

	EItemType ItemType = EItemType::None;
	float MoveTime = 0.25f;
	float MoveSpeed = 10.0f;

// FSM
private:
	UStateManager State;
	void StateInit();

};

