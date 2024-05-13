#include "PreCompile.h"
#include "EngineDebug3D.h"
#include "Camera.h"
#include "EngineCore.h"

int DebugIndex;
std::vector<UDebugRenderInfo> DebugRenderUnits;

// 랜더링은 무조건 renderStart와 RenderEnd
void UDebugRenderClass::DebugRender(ULevel* _Level)
{
	if (false == GEngine->IsDebug)
	{
		DebugRenderUnits.clear();
		DebugIndex = 0;
		return;
	}

	std::shared_ptr<UCamera> Camera = _Level->GetMainCamera();

	for (size_t i = 0; i < DebugIndex; i++)
	{
		DebugRenderUnits[i].Trans.CalculateViewAndProjection(Camera->GetView(), Camera->GetProjection());
		// 하나가 그려지는 거죠.
		DebugRenderUnits[i].Unit.Resources->SettingAllShaderResources();
		DebugRenderUnits[i].Unit.RenderingSetting();
		DebugRenderUnits[i].Unit.GetMesh()->IndexedDraw();
	}

	DebugRenderUnits.clear();
	DebugIndex = 0;
}

namespace UEngineDebug
{
	void DrawDebugRender(EDebugRenderType _DebugText, FTransform& _Transform, float4 _Color)
	{
		if (false == GEngine->IsDebug)
		{
			return;
		}
		
		if (DebugIndex >= DebugRenderUnits.size())
		{
			// 메모리아끼려고 지연생성
			DebugRenderUnits.resize(DebugIndex + 10);
		}

		UDebugRenderInfo& CurInfo = DebugRenderUnits[DebugIndex];

		CurInfo.Trans = _Transform;

		switch (_DebugText)
		{
		case EDebugRenderType::Rect:
			CurInfo.Unit.SetMesh("Rect");
			break;
		case EDebugRenderType::CirCle:
			CurInfo.Trans.SetScale({ CurInfo.Trans.GetScale().X, CurInfo.Trans.GetScale().X , CurInfo.Trans.GetScale().X });
			CurInfo.Unit.SetMesh("Sphere");
			break;
		default:
			break;
		}

		CurInfo.Color = _Color;
		CurInfo.Unit.SetMaterial("Debug");
		CurInfo.Unit.Resources->SettingConstantBuffer("DebugColorValue", CurInfo.Color);
		CurInfo.Unit.Resources->SettingConstantBuffer("FTransform", CurInfo.Trans);

		++DebugIndex;
		
	}
}
