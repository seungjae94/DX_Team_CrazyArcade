#pragma once

class BlockBase;

// 설명 : Map 기초 클래스
class AMapBase : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	AMapBase();
	~AMapBase();

	// delete Function
	AMapBase(const AMapBase& _Other) = delete;
	AMapBase(AMapBase&& _Other) noexcept = delete;
	AMapBase& operator=(const AMapBase& _Other) = delete;
	AMapBase& operator=(AMapBase&& _Other) noexcept = delete;

	inline void SetBackGround(std::string_view _Name)
	{
		BackGround->SetSprite(_Name);
	}

	void SetTileInfoSize(int _X, int _Y);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* BackGround = nullptr;
	USpriteRenderer* PlayUI_BackGround = nullptr;

	std::vector<std::vector<BlockBase*>> TileInfo;

	FVector StartPos = { 20.0f, 40.0f, 0.0f };
	float TileSize = 40.0f;

};

