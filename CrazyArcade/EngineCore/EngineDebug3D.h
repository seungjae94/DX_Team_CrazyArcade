#pragma once
#include "EngineEnums.h"
#include <EngineBase/Transform.h>
#include "RenderUnit.h"

class UDebugRenderInfo
{
public:
	FTransform Trans;
	float4 Color;
	URenderUnit Unit;
};

class UEngineCore;
class UDebugRenderClass
{
	// 함수 firend 
	friend UEngineCore;

public:


	static void DebugRender(ULevel* _Level);
};

namespace UEngineDebug
{
	//                   박스를                        여기에                   이색으로 그려줘.
	void DrawDebugRender(EDebugRenderType _DebugText, FTransform& _Transform, float4 _Color);
}

