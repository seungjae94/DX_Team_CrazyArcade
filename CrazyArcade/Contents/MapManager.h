#pragma once

// Ό³Έν :
class UMapManager
{
public:
	// constrcuter destructer
	UMapManager();
	~UMapManager();

	// delete Function
	UMapManager(const UMapManager& _Other) = delete;
	UMapManager(UMapManager&& _Other) noexcept = delete;
	UMapManager& operator=(const UMapManager& _Other) = delete;
	UMapManager& operator=(UMapManager&& _Other) noexcept = delete;

protected:

private:

};

