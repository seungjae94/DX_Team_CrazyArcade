#include "PreCompile.h"
#include "BombBase.h"

#include "MainPlayLevel.h"
#include "MapConstant.h"
#include "MapBase.h"
#include "Player.h"

ABombBase::ABombBase()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");

	Body = CreateDefaultSubObject<USpriteRenderer>("Bomb");
	Body->SetupAttachment(Root);

	Effect_Center = CreateDefaultSubObject<USpriteRenderer>("Effect_Center");
	Effect_Center->SetupAttachment(Root);

	Effect_Left = CreateDefaultSubObject<USpriteRenderer>("Effect_Left");
	Effect_Left->SetupAttachment(Root);

	Effect_Right = CreateDefaultSubObject<USpriteRenderer>("Effect_Right");
	Effect_Right->SetupAttachment(Root);

	Effect_Up = CreateDefaultSubObject<USpriteRenderer>("Effect_Up");
	Effect_Up->SetupAttachment(Root);

	Effect_Down = CreateDefaultSubObject<USpriteRenderer>("Effect_Down");
	Effect_Down->SetupAttachment(Root);
	
	CurExplosionTime = ExplosionTime;

	SetRoot(Root);
}

ABombBase::~ABombBase()
{
}

void ABombBase::BeginPlay()
{
	Super::BeginPlay();

	PlayLevel = dynamic_cast<AMainPlayLevel*>(GetWorld()->GetGameMode().get());

	UEngineSprite::CreateCutting(MapImgRes::bomb, 3, 1);
	UEngineSprite::CreateCutting(MapImgRes::bomb_effect_center, 3, 1);
	UEngineSprite::CreateCutting(MapImgRes::bomb_effect_left1, 11, 1);
	UEngineSprite::CreateCutting(MapImgRes::bomb_effect_left2, 11, 1);
	UEngineSprite::CreateCutting(MapImgRes::bomb_effect_right1, 11, 1);
	UEngineSprite::CreateCutting(MapImgRes::bomb_effect_right2, 11, 1);
	UEngineSprite::CreateCutting(MapImgRes::bomb_effect_up1, 11, 1);
	UEngineSprite::CreateCutting(MapImgRes::bomb_effect_up2, 11, 1);
	UEngineSprite::CreateCutting(MapImgRes::bomb_effect_down1, 11, 1);
	UEngineSprite::CreateCutting(MapImgRes::bomb_effect_down2, 11, 1);

	Body->SetAutoSize(1.0f, true);
	Effect_Center->SetAutoSize(1.0f, true);
	Effect_Left->SetAutoSize(1.0f, true);
	Effect_Right->SetAutoSize(1.0f, true);
	Effect_Up->SetAutoSize(1.0f, true);
	Effect_Down->SetAutoSize(1.0f, true);

	Body->CreateAnimation(MapAnim::bomb, MapImgRes::bomb, 0.1f, true, 0, 2);
	Effect_Center->CreateAnimation(MapAnim::bomb_effect_center, MapImgRes::bomb_effect_center, 0.1f, false, 0, 2);
	Effect_Left->CreateAnimation(MapAnim::bomb_effect_left1, MapImgRes::bomb_effect_left1, 0.05f, false, 0, 10);
	Effect_Right->CreateAnimation(MapAnim::bomb_effect_right1, MapImgRes::bomb_effect_right1, 0.05f, false, 0, 10);
	Effect_Up->CreateAnimation(MapAnim::bomb_effect_up1, MapImgRes::bomb_effect_up1, 0.05f, false, 0, 10);
	Effect_Down->CreateAnimation(MapAnim::bomb_effect_down1, MapImgRes::bomb_effect_down1, 0.05f, false, 0, 10);

	BlockSize = AMapBase::GetBlockSize();
	Effect_Center->SetPosition({ 0.0f, 0.0f, 0.0f });
	Effect_Left->SetPosition({ -BlockSize, 0.0f, 0.0f });
	Effect_Right->SetPosition({ BlockSize, 0.0f, 0.0f });
	Effect_Up->SetPosition({ 0.0f, BlockSize, 0.0f });
	Effect_Down->SetPosition({ 0.0f, -BlockSize, 0.0f });

	Body->ChangeAnimation(MapAnim::bomb);
}

void ABombBase::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	int BombOrder = PlayLevel->GetMap()->GetRenderOrder(GetActorLocation());
	Body->SetOrder(BombOrder - 1);
	Effect_Center->SetOrder(BombOrder - 1);
	Effect_Left->SetOrder(BombOrder - 1);
	Effect_Right->SetOrder(BombOrder - 1);
	Effect_Up->SetOrder(BombOrder - 1);
	Effect_Down->SetOrder(BombOrder - 1);

	CurExplosionTime -= _DeltaTime;
	if (CurExplosionTime < 0)
	{
		Body->SetActive(false);
		Effect_Center->ChangeAnimation(MapAnim::bomb_effect_center);
		Effect_Left->ChangeAnimation(MapAnim::bomb_effect_left1);
		Effect_Right->ChangeAnimation(MapAnim::bomb_effect_right1);
		Effect_Up->ChangeAnimation(MapAnim::bomb_effect_up1);
		Effect_Down->ChangeAnimation(MapAnim::bomb_effect_down1);
		

		if (Effect_Center->IsCurAnimationEnd())
		{
			Effect_Center->SetActive(false);
		}

		if (Effect_Left->IsCurAnimationEnd())
		{
			if (nullptr != Player)
			{
				Player->IncreaseBombCount();
			}
			Destroy();
		}
	}
}

void ABombBase::SetPlayer(APlayer* _Player)
{
	Player = _Player;
}