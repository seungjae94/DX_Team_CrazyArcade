#include "PreCompile.h"
#include "TickObject.h"

UTickObject::UTickObject() 
{
}

UTickObject::~UTickObject() 
{
}

void UTickObject::BeginPlay()
{

}

void UTickObject::Tick(float _DeltaTime)
{
	if (false == IsActive())
	{
		return;
	}

	for (size_t i = 0; i < CallBacks.size(); i++)
	{
		if (nullptr == CallBacks[i])
		{
			continue;
		}

		CallBacks[i]->Time -= _DeltaTime;
		if (0 >= CallBacks[i]->Time)
		{
			if (nullptr == CallBacks[i]->CallBack)
			{
				MsgBoxAssert("함수를 세팅하지 않은 딜레이 콜백기능을 사용하려고 했습니다.");
			}
			
			CallBacks[i]->CallBack();
			CallBacks[i] = nullptr;
		}
	}
}