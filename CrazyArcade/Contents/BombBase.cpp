#include "PreCompile.h"
#include "BombBase.h"

#include "MainPlayLevel.h"
#include "MapBase.h"

ABombBase::ABombBase()
{
	DefaultComponent = CreateDefaultSubObject<UDefaultSceneComponent>("DefaultComponent");
	SetRoot(DefaultComponent);

	BombRenderer = CreateDefaultSubObject<USpriteRenderer>("BombRenderer");
	BombRenderer->SetupAttachment(DefaultComponent);

	EffectRenderer_C = CreateDefaultSubObject<USpriteRenderer>("EffectRenderer_C");
	EffectRenderer_C->SetupAttachment(DefaultComponent);

	EffectRenderer_L = CreateDefaultSubObject<USpriteRenderer>("EffectRenderer_L");
	EffectRenderer_L->SetupAttachment(DefaultComponent);

	EffectRenderer_R = CreateDefaultSubObject<USpriteRenderer>("EffectRenderer_R");
	EffectRenderer_R->SetupAttachment(DefaultComponent);

	EffectRenderer_U = CreateDefaultSubObject<USpriteRenderer>("EffectRenderer_U");
	EffectRenderer_U->SetupAttachment(DefaultComponent);

	EffectRenderer_D = CreateDefaultSubObject<USpriteRenderer>("EffectRenderer_D");
	EffectRenderer_D->SetupAttachment(DefaultComponent);

	CurExplosionTime = ExplosionTime;
}

ABombBase::~ABombBase()
{
}

void ABombBase::BeginPlay()
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
	EffectRenderer_C->SetAutoSize(1.0f, true);
	EffectRenderer_L->SetAutoSize(1.0f, true);
	EffectRenderer_R->SetAutoSize(1.0f, true);
	EffectRenderer_U->SetAutoSize(1.0f, true);
	EffectRenderer_D->SetAutoSize(1.0f, true);

	BombRenderer->CreateAnimation("Bomb", "Bomb.png", 0.1f, true, 0, 2);
	EffectRenderer_C->CreateAnimation("CenterEffect", "center.png", 0.1f, false, 0, 2);
	EffectRenderer_L->CreateAnimation("LeftEffect", "left1.png", 0.05f, false, 0, 10);
	EffectRenderer_R->CreateAnimation("RigthEffect", "right1.png", 0.05f, false, 0, 10);
	EffectRenderer_U->CreateAnimation("UpEffect", "up1.png", 0.05f, false, 0, 10);
	EffectRenderer_D->CreateAnimation("DownEffect", "down1.png", 0.05f, false, 0, 10);

	BlockSize = AMapBase::GetBlockSize();
	EffectRenderer_C->SetPosition({ 0.0f, 0.0f, 0.0f });
	EffectRenderer_L->SetPosition({ -BlockSize, 0.0f, 0.0f });
	EffectRenderer_R->SetPosition({ BlockSize, 0.0f, 0.0f });
	EffectRenderer_U->SetPosition({ 0.0f, BlockSize, 0.0f });
	EffectRenderer_D->SetPosition({ 0.0f, -BlockSize, 0.0f });

	BombRenderer->ChangeAnimation("Bomb");
}

void ABombBase::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	int BombOrder = PlayLevel->GetMap()->GetRenderOrder(GetActorLocation());
	BombRenderer->SetOrder(BombOrder - 1);
	EffectRenderer_C->SetOrder(BombOrder - 1);
	EffectRenderer_L->SetOrder(BombOrder - 1);
	EffectRenderer_R->SetOrder(BombOrder - 1);
	EffectRenderer_U->SetOrder(BombOrder - 1);
	EffectRenderer_D->SetOrder(BombOrder - 1);

	//CurExplosionTime -= _DeltaTime;
	if (CurExplosionTime < 0)
	{
		BombRenderer->SetActive(false);
		EffectRenderer_C->ChangeAnimation("CenterEffect");
		EffectRenderer_L->ChangeAnimation("LeftEffect");
		EffectRenderer_R->ChangeAnimation("RigthEffect");
		EffectRenderer_U->ChangeAnimation("UpEffect");
		EffectRenderer_D->ChangeAnimation("DownEffect");

		if (EffectRenderer_C->IsCurAnimationEnd())
		{
			EffectRenderer_C->SetActive(false);
		}
		if (EffectRenderer_L->IsCurAnimationEnd())
		{
			Destroy();
		}
	}
}

