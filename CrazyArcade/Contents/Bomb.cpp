#include "PreCompile.h"
#include "Bomb.h"
#include "MainPlayLevel.h"
#include "MapBase.h"

ABomb::ABomb()
{
	DefaultComponent = CreateDefaultSubObject<UDefaultSceneComponent>("DefaultComponent");
	SetRoot(DefaultComponent);

	BombRenderer = CreateDefaultSubObject<USpriteRenderer>("BombRenderer");
	BombRenderer->SetupAttachment(DefaultComponent);

	//EffectRenderer_C = CreateDefaultSubObject<USpriteRenderer>("EffectRenderer_C");
	//EffectRenderer_C->SetupAttachment(DefaultComponent);
	//EffectRenderer_C->SetOrder(10000);

	//EffectRenderer_L = CreateDefaultSubObject<USpriteRenderer>("EffectRenderer_L");
	//EffectRenderer_L->SetupAttachment(DefaultComponent);
	//EffectRenderer_L->SetOrder(10000);

	//EffectRenderer_R = CreateDefaultSubObject<USpriteRenderer>("EffectRenderer_R");
	//EffectRenderer_R->SetupAttachment(DefaultComponent);
	//EffectRenderer_R->SetOrder(10000);

	//EffectRenderer_U = CreateDefaultSubObject<USpriteRenderer>("EffectRenderer_U");
	//EffectRenderer_U->SetupAttachment(DefaultComponent);
	//EffectRenderer_U->SetOrder(10000);

	//EffectRenderer_D = CreateDefaultSubObject<USpriteRenderer>("EffectRenderer_D");
	//EffectRenderer_D->SetupAttachment(DefaultComponent);
	//EffectRenderer_D->SetOrder(10000);
}

ABomb::~ABomb()
{
}

void ABomb::BeginPlay()
{
	Super::BeginPlay();

	PlayLevel = dynamic_cast<AMainPlayLevel*>(GetWorld()->GetGameMode().get());

	UEngineSprite::CreateCutting("Bomb.png", 3, 1);
	UEngineSprite::CreateCutting("center.png", 3, 1);
	UEngineSprite::CreateCutting("left1.png", 11, 1);
	UEngineSprite::CreateCutting("left2.png", 11, 1);
	UEngineSprite::CreateCutting("right1.png", 11, 1);
	UEngineSprite::CreateCutting("right2.png", 11, 1);
	UEngineSprite::CreateCutting("up1.png", 11, 1);
	UEngineSprite::CreateCutting("up2.png", 11, 1);
	UEngineSprite::CreateCutting("down1.png", 11, 1);
	UEngineSprite::CreateCutting("down2.png", 11, 1);

	BombRenderer->SetAutoSize(1.0f, true);
	BombRenderer->CreateAnimation("Bomb", "Bomb.png", 0.1f, true, 0, 2);
	
	//EffectRenderer_C->CreateAnimation("CenterEffect", "center.png", 0.1f, true, 0, 2);
	//EffectRenderer_L->CreateAnimation("LeftEffect", "left1.png", 0.1f, true, 0, 10);
	//EffectRenderer_R->CreateAnimation("RigthEffect", "right1.png", 0.1f, true, 0, 10);
	//EffectRenderer_U->CreateAnimation("UpEffect", "up1.png", 0.1f, true, 0, 10);
	//EffectRenderer_D->CreateAnimation("DownEffect", "down1.png", 0.1f, true, 0, 10);

	BombRenderer->ChangeAnimation("Bomb");
}

void ABomb::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	int BombOrder = PlayLevel->GetMap()->GetRenderOrder(GetActorLocation());
	BombRenderer->SetOrder(BombOrder-2);
}

