#include "PreCompile.h"
#include "Level.h"
#include "GameMode.h"
#include "Renderer.h"
#include "Collision.h"
#include "Camera.h"
#include "EngineCore.h"
#include "EngineRenderTarget.h"
#include "EngineGraphicDevice.h"
#include "InstancingRender.h"
#include "Widget.h"
#include <EngineBase/NetObject.h>

bool ULevel::IsActorConstructer = true;

ULevel::ULevel() 
{
	// MainCamera = std::make_shared<UCamera>();

	MainCamera = SpawnActor<UCamera>("MainCamera");
	UICamera = SpawnActor<UCamera>("NewActor");
	UICamera->SetActorLocation(FVector(0.0f, 0.0f, -100.0f));
	UICamera->InputOff();

	LastTarget = UEngineRenderTarget::Create();
	// 내가 바라보는 애들을 모아서 그릴수 있는 랜더타겟을 만들고 싶어.
	float4 Scale = GEngine->EngineWindow.GetWindowScale();
	LastTarget->CreateTexture(DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, Scale, float4::Zero);
}

ULevel::~ULevel() 
{
	MainCamera = nullptr;
	UICamera = nullptr;
	GameMode = nullptr;
	Actors.clear();
	Renderers.clear();
	Collisions.clear();
	Widgets.clear();

}

void ULevel::Tick(float _DeltaTime)
{
	{
		std::lock_guard<std::mutex> Lock(FunctionLock);
		for (std::function<void()> Function : Functions)
		{
			Function();
		}
		Functions.clear();
	}

	// UNetObject::UpdateProtocol();

	// 1 플레이어 그룹 [][]
	// 2 몬스터 그룹 [][]

	Super::Tick(_DeltaTime);
	for (std::pair<const int, std::list<std::shared_ptr<AActor>>>& TickGroup : Actors)
	{
		if (false == GEngine->TimeScales.contains(TickGroup.first))
		{
			GEngine->TimeScales[TickGroup.first] = 1.0f;
		}

		float TimeScale = GEngine->TimeScales[TickGroup.first];

		std::list<std::shared_ptr<AActor>>& GroupActors = TickGroup.second;

		for (std::shared_ptr<AActor> Actor : GroupActors)
		{
			if (false == Actor->IsActive())
			{
				continue;
			}

			Actor->Tick(_DeltaTime * TimeScale);
		}
	}
}

void ULevel::Render(float _DeltaTime)
{
	MainCamera->ViewPortSetting();

	GEngine->GetEngineDevice().BackBufferRenderTarget->Setting();
	
	MainCamera->CameraTarget->Clear();
	MainCamera->CameraTarget->Setting();
	MainCamera->CameraTransformUpdate();

	for (std::pair<const int, std::list<std::shared_ptr<URenderer>>>& RenderGroup : Renderers)
	{
		std::list<std::shared_ptr<URenderer>>& GroupRenderers = RenderGroup.second;

		if (true == GroupRenderers.empty())
		{
			continue;
		}

		if (true == InstancingRenders.contains(RenderGroup.first))
		{
			std::shared_ptr<UInstancingRender> Inst = InstancingRenders[RenderGroup.first];
			// 첫번째 랜더러 어차피 뒤에 있는 모든애들은 같은 텍스처
			// 같은 샘플러
			// 같은 상수 버퍼 쓰고 있을것이다.
			std::shared_ptr<URenderUnit> Unit = GroupRenderers.front();
			Inst->Resources->OtherResCopy(Unit->Resources);

			int Count = 0;
			for (std::shared_ptr<URenderer> Renderer : GroupRenderers)
			{
				// 액터는 존재하는게 중요하지 
				// 그리거나 충돌할때가 문제이기 때문에
				if (nullptr == Renderer->GetActor()->RootComponent)
				{
					MsgBoxAssert("루트컴포넌트가 지정되지 않은 액터가 있습니다" + Renderer->GetActor()->GetName());
					continue;
				}

				if (false == Renderer->IsActive())
				{
					continue;
				}
				Renderer->RenderingTransformUpdate(MainCamera);
				Renderer->Update(_DeltaTime);
				Inst->InstancingDataCheck(Renderer.get(), Count++);
			}

			Inst->RenderInstancing(_DeltaTime, static_cast<int>(RenderGroup.second.size()));
			continue;
		}

		for (std::shared_ptr<URenderer> Renderer : GroupRenderers)
		{
			// 액터는 존재하는게 중요하지 
			// 그리거나 충돌할때가 문제이기 때문에
			if (nullptr == Renderer->GetActor()->RootComponent)
			{
				MsgBoxAssert("루트컴포넌트가 지정되지 않은 액터가 있습니다" + Renderer->GetActor()->GetName());
				continue;
			}


			if (false == Renderer->IsActive())
			{
				continue;
			}

			Renderer->RenderingTransformUpdate(MainCamera);
			Renderer->Update(_DeltaTime);
			if (false == Renderer->Render(_DeltaTime))
			{
				MsgBoxAssert("랜더링에 실패했습니다." + Renderer->GetName());
			}
		}
	}

	MainCamera->CameraTarget->Effect(_DeltaTime);

	// 모든 일반오브젝트들이 랜더링을 하고

	// 언리얼은 제약이 많다.
	UICamera->CameraTarget->Clear();
	UICamera->CameraTarget->Setting();
	UICamera->CameraTransformUpdate();

	WidgetInits.clear();

	for (std::pair<const int, std::list<std::shared_ptr<UWidget>>>& WidgetGroup : Widgets)
	{
		std::list<std::shared_ptr<UWidget>>& GroupRenderers = WidgetGroup.second;

		for (std::shared_ptr<UWidget> Widget : GroupRenderers)
		{
			// 액터는 존재하는게 중요하지 
			if (false == Widget->IsActive())
			{
				continue;
			}

			Widget->Tick(_DeltaTime);
			Widget->RenderingTransformUpdate(UICamera);
			if (false == Widget->Render(_DeltaTime))
			{
				MsgBoxAssert("랜더링에 실패했습니다." + Widget->GetName());
			}
		}
	}

	UICamera->CameraTarget->Effect(_DeltaTime);

	UEngineGraphicDevice& Device = GEngine->GetEngineDevice();

	// 백버퍼는 그냥 마지막 출력을 위해서 한번만 복제되는게 맞다.

	// 1-r g b a

	LastTarget->Clear();
	LastTarget->Merge(MainCamera->CameraTarget);
	LastTarget->Merge(UICamera->CameraTarget);
	LastTarget->Effect(_DeltaTime);

	// 여기 이순간.
	// 포스트 이팩트
	// 효과를 준다.
	// LastTarget->AddEffect<UBlurEffect>();

	Device.BackBufferRenderTarget->Copy(LastTarget);
}

void ULevel::Destroy()
{

	for (std::pair<const int, std::list<std::shared_ptr<UCollision>>>& Group : Collisions)
	{
		std::list<std::shared_ptr<UCollision>>& GroupCollisions = Group.second;

		std::list<std::shared_ptr<UCollision>>::iterator StartIter = GroupCollisions.begin();
		std::list<std::shared_ptr<UCollision>>::iterator EndIter = GroupCollisions.end();


		for (; StartIter != EndIter; )
		{
			std::shared_ptr<UCollision> CurCollision = *StartIter;

			if (false == CurCollision->GetActor()->IsDestroy())
			{
				++StartIter;
				continue;
			}

			StartIter = GroupCollisions.erase(StartIter);
		}
	}

	for (std::pair<const int, std::list<std::shared_ptr<URenderer>>>& RenderGroup : Renderers)
	{
		std::list<std::shared_ptr<URenderer>>& GroupRenderers = RenderGroup.second;

		std::list<std::shared_ptr<URenderer>>::iterator StartIter = GroupRenderers.begin();
		std::list<std::shared_ptr<URenderer>>::iterator EndIter = GroupRenderers.end();


		for (; StartIter != EndIter; )
		{
			std::shared_ptr<URenderer> CurRenderer = *StartIter;

			if (false == CurRenderer->GetActor()->IsDestroy())
			{
				++StartIter;
				continue;
			}

			StartIter = GroupRenderers.erase(StartIter);
		}
	}

	for (std::pair<const int, std::list<std::shared_ptr<AActor>>>& TickGroup : Actors)
	{
		std::list<std::shared_ptr<AActor>>& GroupActors = TickGroup.second;

		std::list<std::shared_ptr<AActor>>::iterator StartIter = GroupActors.begin();
		std::list<std::shared_ptr<AActor>>::iterator EndIter = GroupActors.end();

		for ( ; StartIter != EndIter; )
		{
			std::shared_ptr<AActor> CurActor = *StartIter;

			if (false == CurActor->IsDestroy())
			{
				++StartIter;
				continue;
			}

			CurActor->End();
			StartIter = GroupActors.erase(StartIter);
		}
	}

}

void ULevel::PushActor(std::shared_ptr<AActor> _Actor)
{
	if (nullptr == _Actor)
	{
		MsgBoxAssert("만들지 않은 액터를 추가하려고 했습니다.");
		return;
	}
	
	_Actor->SetWorld(this);
	_Actor->BeginPlay();

	Actors[_Actor->GetOrder()].push_back(_Actor);
}

void ULevel::ConstructorActor(std::shared_ptr<AActor> _Actor, std::string_view _Name, int _Order)
{
	_Actor->SetName(_Name);
	_Actor->SetOrder(_Order);
}

void ULevel::PushRenderer(std::shared_ptr<URenderer> _Renderer)
{
	Renderers[_Renderer->GetOrder()].push_front(_Renderer);
}

void ULevel::PushCollision(std::shared_ptr<UCollision> _Collision)
{
	Collisions[_Collision->GetOrder()].push_front(_Collision);
}

void ULevel::ChangeOrderRenderer(std::shared_ptr<URenderer> _Renderer, int _PrevOrder, int _ChangeOrder)
{
	// 안지워지고 
	Renderers[_PrevOrder].remove(_Renderer);

	Renderers[_ChangeOrder].push_front(_Renderer);
}

void ULevel::ChangeOrderCollision(std::shared_ptr<UCollision> _Collision, int _PrevOrder, int _ChangeOrder)
{
	// 안지워지고 
	Collisions[_PrevOrder].remove(_Collision);

	Collisions[_ChangeOrder].push_front(_Collision);
}


void ULevel::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelStart(_NextLevel);
	
	Functions.clear();
	for (std::pair<const int, std::list<std::shared_ptr<AActor>>>& TickGroup : Actors)
	{
		std::list<std::shared_ptr<AActor>>& GroupActors = TickGroup.second;

		for (std::shared_ptr<AActor> Actor : GroupActors)
		{
			Actor->LevelEnd(_NextLevel);
		}
	}
}
void ULevel::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelEnd(_PrevLevel);
	
	Functions.clear();
	for (std::pair<const int, std::list<std::shared_ptr<AActor>>>& TickGroup : Actors)
	{
		std::list<std::shared_ptr<AActor>>& GroupActors = TickGroup.second;

		for (std::shared_ptr<AActor> Actor : GroupActors)
		{
			Actor->LevelStart(_PrevLevel);
		}
	}
}

void ULevel::PushWidget(std::shared_ptr<UWidget> _Widget)
{
	if (nullptr == _Widget)
	{
		MsgBoxAssert("만들지 않은 위젯를 추가하려고 했습니다.");
		return;
	}

	_Widget->SetWorld(this);

	WidgetInits.remove(_Widget);
	Widgets[_Widget->GetOrder()].push_back(_Widget);
}


