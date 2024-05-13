#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/NetObject.h>

// Ό³Έν :
class AOtherPlayer : public AActor, public UNetObject
{
public:
	// constrcuter destructer
	AOtherPlayer();
	~AOtherPlayer();

	// delete Function
	AOtherPlayer(const AOtherPlayer& _Other) = delete;
	AOtherPlayer(AOtherPlayer&& _Other) noexcept = delete;
	AOtherPlayer& operator=(const AOtherPlayer& _Other) = delete;
	AOtherPlayer& operator=(AOtherPlayer&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

