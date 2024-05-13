#pragma once
#include "Renderer.h"
#include "EngineEnums.h"
#include "EngineSprite.h"
#include "EngineStruct.h"

class UEngineSprite;
class USpriteAnimation : public UNameObject
{

public:
	std::shared_ptr<UEngineSprite> Sprite;
	std::vector<float> Inter;
	std::vector<int> Frame;

	std::map<int, std::function<void()>> FrameCallback;

	int CurFrame = 0;
	float CurTime = 0.0f;
	bool Loop = true;
	bool IsEnd = false;

	void Update(float _DeltaTime);

	void FrameCallBackCheck();

	FSpriteInfo GetCurSpriteInfo()
	{
		return Sprite->GetSpriteInfo(Frame[CurFrame]);
	}

	void Reset()
	{
		CurTime = 0.0f;
		CurFrame = 0;
	}
};

// 설명 :
class UEngineTexture;
class USpriteInstancingRender;
class USpriteRenderer : public URenderer
{
	friend USpriteInstancingRender;
	GENERATED_BODY(URenderer);

public:
	// constrcuter destructer
	USpriteRenderer();
	~USpriteRenderer();

	// delete Function
	USpriteRenderer(const USpriteRenderer& _Other) = delete;
	USpriteRenderer(USpriteRenderer&& _Other) noexcept = delete;
	USpriteRenderer& operator=(const USpriteRenderer& _Other) = delete;
	USpriteRenderer& operator=(USpriteRenderer&& _Other) noexcept = delete;

	void SetSprite(std::string_view _Name, UINT _Index = 0);
	void SetSamplering(ETextureSampling _Value);

	void CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, float _Inter = 0.1f, bool _Loop = true, int _Start = -1, int _End = -1);

	void CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, std::vector<float> _Inter, std::vector<int> _Frame, bool _Loop = true);
	
	void ChangeAnimation(std::string_view _AnimationName, int StartFrame = 0);

	void SetAutoSize(float _ScaleRatio, bool _AutoSize);
	void SetSpriteInfo(const FSpriteInfo& _Info);

	void SetFrameCallback(std::string_view _AnimationName, int _Index, std::function<void()> _Function);
	void SetLastFrameCallback(std::string_view _AnimationName, std::function<void()> _Function);

	void SetDir(EEngineDir _Dir);

	inline EEngineDir GetDir() const
	{
		return Dir;
	}

	inline void AnimationReset()
	{
		CurAnimation = nullptr;
	}

	bool IsCurAnimationEnd();

	void SetPlusColor(float4 _Color)
	{
		ColorData.PlusColor = _Color;
	}

	void SetMulColor(float4 _Color)
	{
		ColorData.MulColor = _Color;
	}

	void SetAlpha(float _Alpha)
	{
		ColorData.AlphaColor.A = _Alpha;
	}

	void SetPivot(EPivot _Pivot)
	{
		Pivot = _Pivot;
	}

	inline FSpriteInfo GetCurInfo() const
	{
		return CurInfo;
	}

	void SetCurInfo(FSpriteInfo _CurInfo)
	{
		CurInfo = _CurInfo;
		SetSpriteInfo(CurInfo);
		CurAnimation = nullptr;
	}

	inline int GetCurAnimationFrame() const
	{
		if (nullptr == CurAnimation)
		{
			MsgBoxAssert("애니메이션이 지정되지 않았습니다.")
		}

		return CurAnimation->CurFrame;
	}

	void SetVertexUVPlus(float4 _UVPlus)
	{
		VertexUVValue.PlusUV = _UVPlus;
	}
	
protected:
	void Tick(float _DeltaTime) override;
	void MaterialSettingEnd() override;

private:
	bool AutoSize = false;
	float ScaleRatio = 1.0f;
	FSpriteInfo CurInfo;
	EPivot Pivot = EPivot::MAX;
	EEngineDir Dir = EEngineDir::MAX;
	std::shared_ptr<UEngineTexture> CurTexture = nullptr;
	std::map<std::string, std::shared_ptr<USpriteAnimation>> Animations;
	std::shared_ptr<USpriteAnimation> CurAnimation = nullptr;
	ETextureSampling SamplingValue = ETextureSampling::POINT;

	FVertexUV VertexUVValue;
	FResultColorValue ColorData;
	FCuttingData CuttingDataValue;
};

