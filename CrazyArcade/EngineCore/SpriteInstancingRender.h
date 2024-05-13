#pragma once
#include "SpriteRenderer.h"
#include "InstancingRender.h"

// Ό³Έν :
class USpriteInstancingRender : public UInstancingRender
{
public:
	// constrcuter destructer
	USpriteInstancingRender();
	~USpriteInstancingRender();
protected:
	void InstancingDataCheck(URenderUnit* _Renderer, int _Count) override;

private:

};

