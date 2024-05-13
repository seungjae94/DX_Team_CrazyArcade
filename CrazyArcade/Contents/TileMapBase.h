#pragma once

class UTileInfo
{
public:
	bool IsWall = false;

};

// 설명 : TileMap 기초 클래스
class ATileMapBase : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	ATileMapBase();
	~ATileMapBase();

	// delete Function
	ATileMapBase(const ATileMapBase& _Other) = delete;
	ATileMapBase(ATileMapBase&& _Other) noexcept = delete;
	ATileMapBase& operator=(const ATileMapBase& _Other) = delete;
	ATileMapBase& operator=(ATileMapBase&& _Other) noexcept = delete;

	inline void SetBackGround(std::string_view _Name)
	{
		BackGround->SetSprite(_Name);
	}

	void SetTileSize(int _X, int _Y);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* BackGround = nullptr;
	USpriteRenderer* PlayUI_BackGround = nullptr;

	std::vector<std::vector<UTileInfo>> TileInfo;

	FVector StartPos = { 20.0f, 40.0f, 0.0f };

};

