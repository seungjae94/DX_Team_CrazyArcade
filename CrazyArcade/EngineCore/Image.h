#pragma once
#include "Widget.h"
#include "EngineEnums.h"
#include "EngineSprite.h"
#include "EngineStruct.h"

class UImage;
class UIAnimation : public UNameObject
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
class UImage : public UWidget
{
	GENERATED_BODY(UWidget);
	
public:
	UImage();
	~UImage();

	// delete Function
	UImage(const UImage& _Other) = delete;
	UImage(UImage&& _Other) noexcept = delete;
	UImage& operator=(const UImage& _Other) = delete;
	UImage& operator=(UImage&& _Other) noexcept = delete;

	void SetSprite(std::string_view _Name, UINT _Index = 0);
	void SetSpriteInfo(const FSpriteInfo& _Info);
	void SetAutoSize(float _ScaleRatio, bool _AutoSize);
	void SetSamplering(ETextureSampling _Value);

	void SetFrameCallback(std::string_view _AnimationName, int _Index, std::function<void()> _Function);
	

	void CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, float _Inter = 0.1f, bool _Loop = true, int _Start = -1, int _End = -1);

	void CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, std::vector<float> _Inter, std::vector<int> _Frame, bool _Loop = true);

	void ChangeAnimation(std::string_view _AnimationName);

	bool IsCurAnimationEnd();

	void SetPlusColor(float4 _Color)
	{
		ColorData.PlusColor = _Color;
	}

	void SetMulColor(float4 _Color)
	{
		ColorData.MulColor = _Color;
	}

	void SetDir(EEngineDir _Dir);

	inline EEngineDir GetDir() const
	{
		return Dir;
	}

	void SetVertexUVPlus(float4 _UVPlus)
	{
		VertexUVValue.PlusUV = _UVPlus;
	}

protected:
	void MaterialSettingEnd() override;
	void Tick(float _DetaTime) override;

private:
	bool AutoSize = false;
	float ScaleRatio = 1.0f;
	FSpriteInfo CurInfo;
	EPivot Pivot = EPivot::MAX;
	std::shared_ptr<UEngineTexture> CurTexture = nullptr;
	//추가한 부분
	std::map<std::string, std::shared_ptr<UIAnimation>> Animations;
	std::shared_ptr<UIAnimation> CurAnimation = nullptr;
	//
	ETextureSampling SamplingValue = ETextureSampling::POINT;
	EEngineDir Dir = EEngineDir::MAX;

	FResultColorValue ColorData;
	FCuttingData CuttingDataValue;
	FVertexUV VertexUVValue;

	// 여기에 자기자신의 std::shared_ptr
	// std::shared_ptr<UWidget> This = ;

};

