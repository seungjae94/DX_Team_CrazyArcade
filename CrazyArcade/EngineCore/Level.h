#pragma once
#include "TickObject.h"
#include <EngineBase/NameObject.h>
#include <set>
#include <map>



// final을 사용하면 이제 ULevel 상속받은 클래스를 만들수가 없어요.

// 설명 :
class AActor;
class UCamera;
class URenderer;
class UCollision;
class AGameMode;
class UEngineCore;
class UWidget;
class UEngineRenderTarget;
class UInstancingRender;
class UEngineProtocol;
class ULevel final : public UTickObject, public UNameObject
{
	GENERATED_BODY(UTickObject)

	friend AActor;
	friend URenderer;
	friend UCollision;
	friend UEngineCore;
	friend UWidget;
	static bool IsActorConstructer;

public:
	// constrcuter destructer
	ULevel();
	~ULevel();

	// delete Function
	ULevel(const ULevel& _Other) = delete;
	ULevel(ULevel&& _Other) noexcept = delete;
	ULevel& operator=(const ULevel& _Other) = delete;
	ULevel& operator=(ULevel&& _Other) noexcept = delete;

	template<typename ActorType, typename EnumType>
	std::shared_ptr<ActorType> SpawnActor(std::string_view _Name, EnumType _Order)
	{
		return SpawnActor<ActorType>(_Name, static_cast<int>(_Order));
	}

	template<typename ActorType>
	std::shared_ptr<ActorType> SpawnActor(std::string_view _Name, int _Order = 0)
	{
		// 이 사이에서만 컴포넌트를 생성할수 있어야 한다.
		IsActorConstructer = true;
		std::shared_ptr<AActor> NewActor = std::make_shared<ActorType>();
		ConstructorActor(NewActor, _Name, _Order);
		IsActorConstructer = false;

		PushActor(NewActor);


		return std::dynamic_pointer_cast<ActorType>(NewActor);
		// Actors[_Order].push_back(NewActor);
	}

	std::shared_ptr<UCamera> GetMainCamera()
	{
		return MainCamera;
	}

	std::shared_ptr<UCamera> GetUICamera()
	{
		return UICamera;
	}

	std::shared_ptr<AGameMode> GetGameMode()
	{
		return GameMode;
	}

	template<typename EnumType>
	std::list<std::shared_ptr<AActor>> GetTickGroup(EnumType _Type)
	{
		return GetTickGroup(static_cast<int>(_Type));
	}

	// 복사. <= 부담이 만된다.
	std::list<std::shared_ptr<AActor>> GetTickGroup(int _Order)
	{
		return Actors[_Order];
	}

	std::shared_ptr<UEngineRenderTarget> GetLastTarget()
	{
		return LastTarget;
	}

	template<typename InstancingType, typename EnumType>
	void InstancingOn(EnumType _Order)
	{
		InstancingOn<InstancingType>(static_cast<int>(_Order));
	}

	template<typename InstancingType>
	void InstancingOn(int _Order)
	{
		if (true == InstancingRenders.contains(_Order))
		{
			return;
		}

		InstancingRenders[_Order] = std::make_shared<InstancingType>();
	}

	void PushFunction(std::function<void()> _Function)
	{
		std::lock_guard<std::mutex> Lock(FunctionLock);
		Functions.push_back(_Function);
	}

protected:
	void Tick(float _DeltaTime) override;
	void Render(float _DeltaTime);

	void LevelEnd(ULevel* _NextLevel) override;
	void LevelStart(ULevel* _PrevLevel) override;

	void Destroy();

private:
	std::shared_ptr<UEngineRenderTarget> LastTarget = nullptr;

	std::shared_ptr<UCamera> MainCamera = nullptr;
	std::shared_ptr<UCamera> UICamera = nullptr;

	std::shared_ptr<AGameMode> GameMode;
	std::map<int, std::list<std::shared_ptr<AActor>>> Actors;

	std::map<int, std::list<std::shared_ptr<URenderer>>> Renderers;
	std::map<int, std::shared_ptr<UInstancingRender>> InstancingRenders;
	std::map<int, std::list<std::shared_ptr<UCollision>>> Collisions;

	// Widget이라고 불리고
	// 아예 액터랑 분리되어 있다.
	std::map<int, std::list<std::shared_ptr<UWidget>>> Widgets;
	std::list<std::shared_ptr<UWidget>> WidgetInits; 

	std::mutex FunctionLock;
	std::list<std::function<void()>> Functions;

	void ConstructorActor(std::shared_ptr<AActor> _Actor, std::string_view _Name, int Order);
	void PushActor(std::shared_ptr<AActor> _Actor);
	void PushRenderer(std::shared_ptr<URenderer> _Renderer);
	void PushCollision(std::shared_ptr<UCollision> _Collision);
	void PushWidget(std::shared_ptr<UWidget> _Widget);
	void ChangeOrderRenderer(std::shared_ptr<URenderer> _Renderer, int _PrevOrder, int _ChangeOrder);
	void ChangeOrderCollision(std::shared_ptr<UCollision> _Collision, int _PrevOrder, int _ChangeOrder);

	void SetGameMode(std::shared_ptr<AGameMode> _GameMode)
	{
		GameMode = _GameMode;
	}

};

