#include "PreCompile.h"
#include "SpriteInstancingRender.h"
#include "SpriteRenderer.h"
#include "EngineStructuredBuffer.h"

USpriteInstancingRender::USpriteInstancingRender() 
{
	SetMesh("Rect");
	SetMaterial("2DImageInstancing");
}

USpriteInstancingRender::~USpriteInstancingRender() 
{
}

void USpriteInstancingRender::InstancingDataCheck(URenderUnit* _Renderer, int _Count)
{
	USpriteRenderer* SpriteRenderer = dynamic_cast<USpriteRenderer*>(_Renderer);

	if (nullptr == SpriteRenderer)
	{
		MsgBoxAssert("스프라이트 랜더러가 아닌 존재를 인스턴싱 할수는 없습니다.");
		return;
	}

	FTransform& Transform = SpriteRenderer->Transform;
	FCuttingData& CuttingData = SpriteRenderer->CuttingDataValue;
	FResultColorValue& ColorData = SpriteRenderer->ColorData;

	// 스트럭처드 버퍼에 쌓아주려고
	// 그럼 그 스트럭처드 버퍼 여기 있어야 

	UEngineStructuredBufferSetter* TransInstancing = Resources->GetStructuredBuffer("TransInstancing");
	UEngineStructuredBufferSetter* CuttingDataInstancing = Resources->GetStructuredBuffer("CuttingDataInstancing");
	UEngineStructuredBufferSetter* ResultColorValueInstancing = Resources->GetStructuredBuffer("ResultColorValueInstancing");

	TransInstancing->PushData(Transform);
	CuttingDataInstancing->PushData(CuttingData);
	ResultColorValueInstancing->PushData(ColorData);
}