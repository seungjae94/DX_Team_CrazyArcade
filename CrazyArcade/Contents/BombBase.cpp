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


	////
	//Effect_Center = CreateDefaultSubObject<USpriteRenderer>("Effect_Center");
	//Effect_Center->SetupAttachment(Root);

	//Effect_Left = CreateDefaultSubObject<USpriteRenderer>("Effect_Left");
	//Effect_Left->SetupAttachment(Root);

	//Effect_Right = CreateDefaultSubObject<USpriteRenderer>("Effect_Right");
	//Effect_Right->SetupAttachment(Root);

	//Effect_Up = CreateDefaultSubObject<USpriteRenderer>("Effect_Up");
	//Effect_Up->SetupAttachment(Root);

	//Effect_Down = CreateDefaultSubObject<USpriteRenderer>("Effect_Down");
	//Effect_Down->SetupAttachment(Root);
	////

	SetRoot(Root);
}

ABombBase::~ABombBase()
{
}

void ABombBase::BeginPlay()
{
	Super::BeginPlay();

	SetImgCutting();
	RendererInit();
	StateInit();

	PlayLevel = dynamic_cast<AMainPlayLevel*>(GetWorld()->GetGameMode().get());	
	State.ChangeState(BombState::idle);
}

void ABombBase::SetImgCutting()
{
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
}

void ABombBase::RendererInit()
{
	float BlockSize = AMapBase::GetBlockSize();

	Body->CreateAnimation(MapAnim::bomb, MapImgRes::bomb, 0.25f, true);
	Body->CreateAnimation(MapAnim::bomb_effect_center, MapImgRes::bomb_effect_center, 0.1f, false);
	Body->SetAutoSize(1.0f, true);
	Body->SetActive(false);
	
	//Effect_Left->CreateAnimation(MapAnim::bomb_effect_left1, MapImgRes::bomb_effect_left1, 0.05f, false, 0, 10);
	//Effect_Left->SetPosition({ -BlockSize, 0.0f, 0.0f });
	//Effect_Left->SetAutoSize(1.0f, true);
	//Effect_Left->SetActive(false);

	//Effect_Right->CreateAnimation(MapAnim::bomb_effect_right1, MapImgRes::bomb_effect_right1, 0.05f, false, 0, 10);
	//Effect_Right->SetPosition({ BlockSize, 0.0f, 0.0f });
	//Effect_Right->SetAutoSize(1.0f, true);
	//Effect_Right->SetActive(false);

	//Effect_Up->CreateAnimation(MapAnim::bomb_effect_up1, MapImgRes::bomb_effect_up1, 0.05f, false, 0, 10);
	//Effect_Up->SetPosition({ 0.0f, BlockSize, 0.0f });
	//Effect_Up->SetAutoSize(1.0f, true);
	//Effect_Up->SetActive(false);

	//Effect_Down->CreateAnimation(MapAnim::bomb_effect_down1, MapImgRes::bomb_effect_down1, 0.05f, false, 0, 10);
	//Effect_Down->SetPosition({ 0.0f, -BlockSize, 0.0f });
	//Effect_Down->SetAutoSize(1.0f, true);
	//Effect_Down->SetActive(false);
}

void ABombBase::StateInit()
{
	// State Create
	State.CreateState(BombState::idle);
	State.CreateState(BombState::explosion);

	// State Start
	State.SetStartFunction(BombState::idle, [=] 
		{
			int BombOrder = PlayLevel->GetMap()->GetRenderOrder(GetActorLocation());
			Body->ChangeAnimation(MapAnim::bomb);
			Body->SetOrder(BombOrder);
			Body->SetActive(true);

			ExplosionTimeCount = ExplosionTime;



			//Effect_Left->SetOrder(BombOrder);
			//Effect_Right->SetOrder(BombOrder);
			//Effect_Up->SetOrder(BombOrder);
			//Effect_Down->SetOrder(BombOrder);
		}
	);

	State.SetStartFunction(BombState::explosion, [=] 
		{
			Body->ChangeAnimation(MapAnim::bomb_effect_center);

			//Effect_Left->ChangeAnimation(MapAnim::bomb_effect_left1);
			//Effect_Right->ChangeAnimation(MapAnim::bomb_effect_right1);
			//Effect_Up->ChangeAnimation(MapAnim::bomb_effect_up1);
			//Effect_Down->ChangeAnimation(MapAnim::bomb_effect_down1);
			
			//Effect_Left->SetActive(true);
			//Effect_Right->SetActive(true);
			//Effect_Up->SetActive(true);
			//Effect_Down->SetActive(true);

		}
	);

	// State Update
	State.SetUpdateFunction(BombState::idle, [=](float _DeltaTime) 
		{
			ExplosionTimeCount -= _DeltaTime;
			if (0.0f > ExplosionTimeCount)
			{
				if (nullptr != Player)
				{
					Player->IncreaseBombCount();
				}

				State.ChangeState(BombState::explosion);
				return;
			}
		}
	);

	State.SetUpdateFunction(BombState::explosion, [=](float _DeltaTime) 
		{
			if (Body->IsCurAnimationEnd())
			{
				PlayLevel->GetMap()->GetTileInfo(CurPoint).Bomb = nullptr;
				Destroy();
			}
		}
	);

}

void ABombBase::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void ABombBase::SetPlayer(APlayer* _Player)
{
	Player = _Player;
}

void ABombBase::SetCurPoint(FPoint _Point)
{
	CurPoint = _Point;
}
