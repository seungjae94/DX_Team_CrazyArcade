#include"PreCompile.h"
#include "MouseUI.h"
#include "MainPlayLevel.h"

AMouse::AMouse()
{
	GEngine->EngineWindow.CursorOff(); //커서 끄기
	
	UDefaultSceneComponent* Default = CreateDefaultSubObject<UDefaultSceneComponent>("Default");

	SetRoot(Default);
	
}

AMouse::~AMouse()
{
}

void AMouse::BeginPlay()
{
	Super::BeginPlay();
	MouseRender = CreateWidget<UImage>(GetWorld(), "MouseUI");
	MouseRender->SetSprite("MouseNormal.png");
	MouseRender->SetAutoSize(1.0f, true);
	MouseRender->AddToViewPort(10);


	MouseRender->SetDown([=] {
		MouseRender->SetSprite("MouseClick.png");
		});
	MouseRender->SetUp([=] {

		MouseRender->SetSprite("MouseNormal.png");
		});

}

void AMouse::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	SetMousePos(); // 따라다니기 
	
}


void AMouse::SetMousePos()
{
	FVector CamPos = GetWorld()->GetMainCamera()->GetActorLocation();
	FVector MPos = GEngine->EngineWindow.GetScreenMousePos();
	FVector WindowScale = GEngine->EngineWindow.GetWindowScale();
	FVector TargetPos = FVector(CamPos.X, CamPos.Y, 0.0f) + FVector(MPos.X+10 - WindowScale.hX(), -(MPos.Y - WindowScale.hY()+14), 0.0f);

	
	AMainPlayLevel* PlayLevel = dynamic_cast<AMainPlayLevel*>(GetWorld()->GetGameMode().get());

	if (nullptr != PlayLevel)
	{
		MouseRender->SetWidgetLocation(TargetPos - FVector{400.0f, 300.0f, 0.0f});
	}
	else
	{
		MouseRender->SetWidgetLocation(TargetPos);
	}

}
