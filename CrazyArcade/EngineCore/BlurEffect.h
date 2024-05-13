#pragma once
#include "EngineRenderTarget.h"

// Ό³Έν :
class UBlurEffect : public UEffect
{
public:
	// constrcuter destructer
	UBlurEffect();
	~UBlurEffect();

	// delete Function
	UBlurEffect(const UBlurEffect& _Other) = delete;
	UBlurEffect(UBlurEffect&& _Other) noexcept = delete;
	UBlurEffect& operator=(const UBlurEffect& _Other) = delete;
	UBlurEffect& operator=(UBlurEffect&& _Other) noexcept = delete;

protected:
	void Init() override;
	void Effect(std::shared_ptr<UEngineRenderTarget> EffectTarget) override;


private:
	std::shared_ptr<UEngineRenderTarget> CopyTarget;

};

