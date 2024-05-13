#pragma once
#include "EngineDefines.h"
#include <functional>
#include <memory>
#include <EngineBase/EngineDebug.h>

class UEngineTickCallBack
{
public:
	float Time;
	std::function<void()> CallBack;
};

// 설명 :
class ULevel;
class UTickObject
{
public:
	// constrcuter destructer
	UTickObject();
	virtual ~UTickObject();

	// delete Function
	UTickObject(const UTickObject& _Other) = delete;
	UTickObject(UTickObject&& _Other) noexcept = delete;
	UTickObject& operator=(const UTickObject& _Other) = delete;
	UTickObject& operator=(UTickObject&& _Other) noexcept = delete;


	int GetOrder()
	{
		return Order;
	}

	template<typename EnumType>
	void SetOrder(EnumType _Order)
	{
		SetOrder(static_cast<int>(_Order));
	}


	virtual void SetOrder(int _Order)
	{
		Order = _Order;
	}

	void DelayCallBack(float _Time, std::function<void()> _CallBack)
	{
		if (nullptr == _CallBack)
		{
			MsgBoxAssert("콜백기능이 nullptr 입니다.");
		}

		for (size_t i = 0; i < CallBacks.size(); i++)
		{
			if (nullptr == CallBacks[i])
			{
				CallBacks[i] = std::make_shared<UEngineTickCallBack>(_Time, _CallBack);
				return;
			}
		}

		CallBacks.push_back(std::make_shared<UEngineTickCallBack>( _Time ,_CallBack ));
	}

	virtual bool IsActive()
	{
		return ActiveValue;
	}

	virtual void SetActive(bool _Value)
	{
		ActiveValue = _Value;
	}

protected:
	virtual void BeginPlay();
	virtual void Tick(float _DeltaTime);

	virtual void LevelEnd(ULevel* _NextLevel) {};
	virtual void LevelStart(ULevel* _PrevLevel) {};

private:
	bool ActiveValue = true;

	int Order = 0;

	std::vector<std::shared_ptr<UEngineTickCallBack>> CallBacks;
};

