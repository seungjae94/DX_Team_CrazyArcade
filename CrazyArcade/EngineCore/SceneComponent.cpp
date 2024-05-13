#include "PreCompile.h"
#include "SceneComponent.h"

USceneComponent::USceneComponent() 
{
}

USceneComponent::~USceneComponent() 
{
}

void USceneComponent::SetupAttachment(USceneComponent* _Parent)
{
	SetParent(_Parent);
	ComponentParent = _Parent;
}

bool USceneComponent::IsActive() 
{
	if (nullptr != ComponentParent)
	{
		return ComponentParent->IsActive() && UActorComponent::IsActive();
	}

	return UActorComponent::IsActive();
}