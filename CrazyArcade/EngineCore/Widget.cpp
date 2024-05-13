#include "PreCompile.h"
#include "Widget.h"
#include "Level.h"
#include "EngineSprite.h"
#include "EngineCore.h"
#include "EngineDebugMsgWindow.h"

UWidget::UWidget() 
{
}

UWidget::~UWidget() 
{
}

void UWidget::AddToViewPort(int _Order)
{
	SetOrder(_Order);
	if (nullptr == WidgetParent)
	{
		GetWorld()->PushWidget(shared_from_this());
	}
}

void UWidget::SetupAttachment(UWidget* _Parent)
{
	SetParent(_Parent);
	WidgetParent = _Parent;
	_Parent->ChildWidgets.push_back(shared_from_this());
}

void UWidget::MaterialSettingEnd() 
{
	Super::MaterialSettingEnd();
	if (true == Resources->IsConstantBuffer("FTransform"))
	{
		Resources->SettingConstantBuffer("FTransform", Transform);
	}
}

void UWidget::WidgetInit(std::shared_ptr<UWidget> _Widget, std::string_view _Name)
{
	_Widget->UWorldObject::SetWorld(GetWorld());
	_Widget->SetName(_Name);
	_Widget->BeginPlay();
	GetWorld()->WidgetInits.push_back(_Widget);
}

void UWidget::RenderingTransformUpdate(std::shared_ptr<UCamera> _Camera)
{
	Transform.CalculateViewAndProjection(_Camera->GetView(), _Camera->GetProjection());

	for (std::shared_ptr<UWidget> ChildWidget : ChildWidgets)
	{
		ChildWidget->RenderingTransformUpdate(_Camera);
	}
}


void UWidget::Tick(float _DeltaTime)
{
	float4 Mouse = GEngine->EngineWindow.GetScreenMousePos();
	float4 UIPos = GetWorld()->GetUICamera()->ScreenPosToWorldPos(Mouse);

	FTransform Trans;
	Trans.SetPosition(UIPos);

	float4x4 UIView = GetWorld()->GetUICamera()->GetView();
	float4x4 UIProjection = GetWorld()->GetUICamera()->GetProjection();
	Trans.CalculateViewAndProjection(UIView, UIProjection);

	if (true == Transform.Collision(ECollisionType::Rect, ECollisionType::Point, Trans))
	{
		IsHover = true;
		if (nullptr != Hover)
		{
			Hover();
		}

		if (true == UEngineInput::IsDown(VK_LBUTTON) && nullptr != Down)
		{
			Down();
		}
	}
	else 
	{
		if (true == IsHover)
		{
			IsHover = false;

			if (nullptr != UnHover)
			{
				UnHover();
			}
		}
	}

	// GEngine->EngineWindow.mouse
}

bool UWidget::Render(float _DeltaTime)
{
	Transform;
	if (nullptr != GetMesh())
	{
		URenderUnit::Render(_DeltaTime);
	}

	for (std::shared_ptr<UWidget> ChildWidget : ChildWidgets)
	{
		if (false == ChildWidget->IsActive())
		{
			continue;
		}

		ChildWidget->Render(_DeltaTime);
	}

	return true;
}


FVector UWidget::GetWidgetScale3D()
{
	return GetWorldScale();
}

FVector UWidget::GetWidgetLocation()
{
	return GetWorldPosition();
}

void UWidget::SetWidgetLocation(FVector _Value)
{
	SetPosition(_Value);
}

void UWidget::SetWidgetScale3D(FVector _Value)
{
	SetScale(_Value);
}

void UWidget::SetWidgetRotation(FVector _Value)
{
	SetRotationDeg(_Value);
}

void UWidget::AddWidgetLocation(FVector _Value)
{
	AddPosition(_Value);
}

void UWidget::AddWidgetRotation(FVector _Value)
{
	AddRotationDeg(_Value);
}

void UWidget::AddWidgetScale3D(FVector _Value)
{
	AddScale(_Value);
}
