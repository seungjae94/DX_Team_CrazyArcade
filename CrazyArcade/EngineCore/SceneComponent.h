#pragma once
#include <EngineBase/TransformObject.h>
#include "ActorComponent.h"

// Ό³Έν :
class USceneComponent : public UActorComponent, public UTransformObject
{
public:
	// constrcuter destructer
	USceneComponent();
	~USceneComponent();

	// delete Function
	USceneComponent(const USceneComponent& _Other) = delete;
	USceneComponent(USceneComponent&& _Other) noexcept = delete;
	USceneComponent& operator=(const USceneComponent& _Other) = delete;
	USceneComponent& operator=(USceneComponent&& _Other) noexcept = delete;

	void SetupAttachment(USceneComponent* _Parent);

	bool IsActive() override;

protected:

private:
	USceneComponent* ComponentParent = nullptr;
};

