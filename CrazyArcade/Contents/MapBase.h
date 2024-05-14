#pragma once

class ABlockBase;
class UMapInfo;
class ABox;

class UMapInfo
{
public:
	std::shared_ptr<ABlockBase> Block = nullptr;
};

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

	int GetRenderOrder(const FVector& _CurPos);
	bool CanMovePos(const FVector& _NextPos, const FVector& _Dir);
	static float GetBlockSize()
	{
		return BlockSize;
	}

protected:
	inline void SetBackGround(std::string_view _Name)
	{
		BackGround->SetSprite(_Name);
	}

	void SetMapInfoSize(int _X, int _Y);
	void CreateWall(int _X, int _Y, std::string_view _ImgName);
	void CreateBox(int _X, int _Y, std::string_view _ImgName);
	void CreateMoveBox(int _X, int _Y, std::string_view _ImgName);


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* BackGround = nullptr;
	USpriteRenderer* PlayUI_BackGround = nullptr;

	std::vector<std::vector<UMapInfo>> MapInfo;

	FVector StartPos = { 20.0f, 40.0f, 0.0f };
	static float BlockSize;
	int SizeX = 0;
	int SizeY = 0;

};

