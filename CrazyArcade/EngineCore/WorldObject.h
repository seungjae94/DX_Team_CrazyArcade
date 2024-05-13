#pragma once
#include "Level.h"

// Ό³Έν :
class AActor;
class ULevel;
class UWorldObject
{
public:
	friend AActor;
	friend ULevel;
	friend UWidget;
	// constrcuter destructer
	UWorldObject();
	~UWorldObject();

	// delete Function
	UWorldObject(const UWorldObject& _Other) = delete;
	UWorldObject(UWorldObject&& _Other) noexcept = delete;
	UWorldObject& operator=(const UWorldObject& _Other) = delete;
	UWorldObject& operator=(UWorldObject&& _Other) noexcept = delete;

	virtual ULevel* GetWorld()
	{
		return World;
	}

protected:

private:
	ULevel* World = nullptr;

	void SetWorld(ULevel* _World)
	{
		World = _World;
	}
};

