#pragma once
#include "RenderUnit.h"

// Ό³Έν :
class ULevel;
class UInstancingRender : public URenderUnit
{
	friend ULevel;
public:
	// constrcuter destructer
	UInstancingRender();
	~UInstancingRender();

	// delete Function
	UInstancingRender(const UInstancingRender& _Other) = delete;
	UInstancingRender(UInstancingRender&& _Other) noexcept = delete;
	UInstancingRender& operator=(const UInstancingRender& _Other) = delete;
	UInstancingRender& operator=(UInstancingRender&& _Other) noexcept = delete;

protected:
	virtual void InstancingDataCheck(URenderUnit* _Renderer, int _Count) = 0;

private:

};

