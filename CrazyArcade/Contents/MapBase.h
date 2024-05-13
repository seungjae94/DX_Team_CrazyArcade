#pragma once

class ABlockBase;

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

	bool CanMovePos(const FVector _CurPos, const FVector& _MoveDir);

protected:
	inline void SetBackGround(std::string_view _Name)
	{
		BackGround->SetSprite(_Name);
	}

	void SetMapInfoSize(int _X, int _Y);
	void CreateWall(int _X, int _Y, std::string_view _ImgName);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* BackGround = nullptr;
	USpriteRenderer* PlayUI_BackGround = nullptr;

	std::vector<std::vector<std::shared_ptr<ABlockBase>>> MapInfo;

	FVector StartPos = { 20.0f, 40.0f, 0.0f };
	float BlockSize = 40.0f;

};

