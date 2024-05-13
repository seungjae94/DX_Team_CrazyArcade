#pragma once
#include <EngineBase/Transform.h>

#include <vector>
#include "TickObject.h"
#include "WorldObject.h"
#include "Level.h"


// 설명 : 액터가 트랜스폼을 가지는게 아니라
class ULevel;
class UActorComponent;
class USceneComponent;
class AActor : public UTickObject, public UWorldObject, public UNameObject
{
	friend ULevel;
	GENERATED_BODY(UTickObject)

public:
	// constrcuter destructer
	AActor();
	~AActor();

	// delete Function
	AActor(const AActor& _Other) = delete;
	AActor(AActor&& _Other) noexcept = delete;
	AActor& operator=(const AActor& _Other) = delete;
	AActor& operator=(AActor&& _Other) noexcept = delete;

	// 오로지 생성자에서만 호출될수 있게 만들어 놓는다.
	// 언리얼 따라할려고 그냥 함.
	template<typename ComponentType>
	ComponentType* CreateDefaultSubObject(std::string_view _Name)
	{
		if (false == ULevel::IsActorConstructer)
		{
			MsgBoxAssert("언리얼에서는 생성자에서밖에 컴포넌트를 생성할수 없습니다.");
		}

		std::shared_ptr<UActorComponent> NewComponent = std::make_shared<ComponentType>();

		PushComponent(NewComponent, _Name);

		return dynamic_cast<ComponentType*>(NewComponent.get());
	}

	FTransform& GetActorTransform();
	void SetActorTransform(const FTransform& _Transform);

	FVector GetActorForwardVector();
	FVector GetActorRightVector();
	FVector GetActorUpVector();

	FVector GetActorLocation();
	FVector GetActorScale3D();

	void SetActorScale3D(FVector _Value);
	void SetActorRotation(FVector _Value);
	void SetActorLocation(FVector _Value);

	void AddActorScale3D(FVector _Value);
	void AddActorRotation(FVector _Value);
	void AddActorLocation(FVector _Value);

	inline USceneComponent* GetRoot() const
	{
		if (nullptr == RootComponent)
		{
			MsgBoxAssert("아직 루트를 지정하지 않았습니다.");
		}

		return RootComponent;
	}

	void SetRoot(USceneComponent* _Root)
	{
		if (nullptr != RootComponent)
		{
			MsgBoxAssert("이미 루트를 지정한 상태입니다.");
		}

		RootComponent = _Root;
	}

	bool IsDestroy()
	{
		return IsDestroyValue;
	}

	void Destroy()
	{
		IsDestroyValue = true;
	}

	virtual void End() {};

	// 걷뵈만 똑같게 만들려고 만든 인터페이스
	template<typename WidgetType>
	WidgetType* CreateWidget(ULevel* _Level, std::string_view _Name)
	{
		std::shared_ptr<UWidget> NewWidget = std::make_shared<WidgetType>();

		WidgetInit(NewWidget, _Name);

		return dynamic_cast<WidgetType*>(NewWidget.get());
	}

	template<typename Class>
	std::vector<std::shared_ptr<Class>> GetComponentToClass()
	{
		std::vector<std::shared_ptr<Class>> FindVector;

		for (size_t i = 0; i < Components.size(); i++)
		{
			std::shared_ptr<Class> ClassType = std::dynamic_pointer_cast<Class>(Components[i]);

			if (nullptr != ClassType)
			{
				FindVector.push_back(ClassType);
			}
		}

		return FindVector;
	}



protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	// 언리얼이 왜 액터가 트랜스폼을 가지지 못하게 했을까?
	// GameMode 기능적인 면에서 트랜스폼이 필요 없는 애들도 많아요.
	// 액터란 이 어떠한 레벨에서 어떠한 역할을 해주시면 하면 된다.
	// 거기에 필요한 기능만 만들면 되기 때문에 
	// 컴포넌트 구조라는 것.
	// 뭘만들든 동적으로 만들수 있는 구조를 만드는것.
	USceneComponent* RootComponent = nullptr;
	std::vector<std::shared_ptr<UActorComponent>> Components;

	void PushComponent(std::shared_ptr<UActorComponent> _Component, std::string_view _Name);
	/////////////////////// 인풋





public:
	void InputOff();
	void InputOn();

	// 이녀석을 쓰면
	// UEngineInput <= 항상동작 키누르면

	// 액터에서만 인풋 처리가 가능하게 되었습니다.
	bool IsDoubleClick(int _Key, float _ClickTime);
	bool IsDown(int _Key);
	float GetPressTime(int _Key);
	bool IsPress(int _Key);
	bool IsUp(int _Key);
	bool IsFree(int _Key);
	bool IsAnykeyDown();
	bool IsAnykeyPress();
	bool IsAnykeyUp();
	bool IsAnykeyFree();

	static void OnlyInput(AActor* _this);
	static void OnlyInputStop();

private:
	bool IsDestroyValue = false;
	// set은 굉장히 간단한 자료구조로서
	// Value 없는 맵입니다.
	static std::set<AActor*> InputActors;
	static std::set<AActor*> PrevInputActors;


	void WidgetInit(std::shared_ptr<UWidget> _Widget, std::string_view _Name);

};

