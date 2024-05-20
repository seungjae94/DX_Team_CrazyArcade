#pragma once

class ABlockBase;

// 설명 : Item 생성 블록
class USpawnItemBlock
{
public:
	// constructor destructor
	USpawnItemBlock();
	~USpawnItemBlock();

	// delete Function
	USpawnItemBlock(const USpawnItemBlock& _Other) = delete;
	USpawnItemBlock(USpawnItemBlock&& _Other) noexcept = delete;
	USpawnItemBlock& operator=(const USpawnItemBlock& _Other) = delete;
	USpawnItemBlock& operator=(USpawnItemBlock&& _Other) noexcept = delete;

	inline EItemType GetSpawnItemType()
	{
		return ItemType;
	}

	inline void SetSpawnItemType(EItemType _ItemType)
	{
		ItemType = _ItemType;
	}

protected:
	inline void SetBlock(ABlockBase* _Block)
	{
		Block = _Block;
	}

private:
	ABlockBase* Block = nullptr;
	EItemType ItemType = EItemType::None;
};

