#pragma once

// 설명 : Block 기본 클래스
class ABlockBase : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	ABlockBase();
	~ABlockBase();

	// delete Function
	ABlockBase(const ABlockBase& _Other) = delete;
	ABlockBase(ABlockBase&& _Other) noexcept = delete;
	ABlockBase& operator=(const ABlockBase& _Other) = delete;
	ABlockBase& operator=(ABlockBase&& _Other) noexcept = delete;

	inline EBlockType GetBlockType() const
	{
		return BlockType;
	}

	inline void SetBlockType(EBlockType _Type)
	{
		BlockType = _Type;
	}

	void SetBlockImg(std::string_view _ImgName)
	{
		Body->SetSprite(_ImgName);
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	USpriteRenderer* Body = nullptr;
	EBlockType BlockType;
};

