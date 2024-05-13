#include "PreCompile.h"
#include "Renderer.h"
#include "EngineInputLayOut.h"
#include "EngineShaderResources.h"
#include "Camera.h"
#include "EngineCore.h"

URenderer::URenderer()
{
	Resources = std::make_shared<UEngineShaderResources>();
}

URenderer::~URenderer()
{
}

void URenderer::BeginPlay()
{
	Super::BeginPlay();

	// ÇØÁà¾ß ÇÑ´Ù
	if (nullptr != GetWorld())
	{
		GetWorld()->PushRenderer(shared_from_this());
	}
	else if (nullptr != UEngineCore::GetCurCreateLevel())
	{
		UEngineCore::GetCurCreateLevel()->PushRenderer(shared_from_this());
	}
}

void URenderer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}


void URenderer::SetOrder(int _Order)
{
	// UTickObject::SetOrder(_Order);
	

	int PrevOrder = GetOrder();

	if (_Order == PrevOrder) {
		return;
	}

	Super::SetOrder(_Order);

	if (nullptr != GetWorld())
	{
		GetWorld()->ChangeOrderRenderer(shared_from_this(), PrevOrder, _Order);
	}
}


void URenderer::RenderingTransformUpdate(std::shared_ptr<UCamera> _Camera)
{
	Transform.CalculateViewAndProjection(_Camera->GetView(), _Camera->GetProjection());
}

void URenderer::MaterialSettingEnd() 
{
	if (true == Resources->IsConstantBuffer("FTransform"))
	{
		Resources->SettingConstantBuffer("FTransform", Transform);
	}
}