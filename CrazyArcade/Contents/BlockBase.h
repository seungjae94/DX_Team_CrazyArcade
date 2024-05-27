#pragma once
#include "MapHelper.h"

class AMainPlayLevel;

// 설명 : Block 기본 클래스
class ABlockBase : public ANetActor
{
	GENERATED_BODY(ANetActor)
public:
	// constrcuter destructer
	ABlockBase();
	~ABlockBase();

	// delete Function
	ABlockBase(const ABlockBase& _Other) = delete;
	ABlockBase(ABlockBase&& _Other) noexcept = delete;
	ABlockBase& operator=(const ABlockBase& _Other) = delete;
	ABlockBase& operator=(ABlockBase&& _Other) noexcept = delete;

	inline void StateChange(std::string_view _State)
	{
		State.ChangeState(_State);
	}

	inline std::string GetCurState() const
	{
		return State.GetCurStateName();
	}

	inline EBlockType GetBlockType() const
	{
		return BlockType;
	}

	inline void SetBlockType(EBlockType _Type)
	{
		BlockType = _Type;
	}

	void SetBlockImg(std::string_view _ImgName)
	{
		Body->SetSprite(_ImgName);
	}

	inline USpriteRenderer* GetBody() const
	{
		return Body;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelEnd(ULevel* _NextLevel) override;

protected:
	AMainPlayLevel* PlayLevel = nullptr;

private:
	USpriteRenderer* Body = nullptr;
	EBlockType BlockType;

// FSM
protected:
	UStateManager State;
	virtual void StateInit();

};

