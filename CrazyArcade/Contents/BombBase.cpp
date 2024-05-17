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
}

void ABombBase::RendererInit()
{
	float BlockSize = AMapBase::GetBlockSize();

	Body->CreateAnimation(MapAnim::bomb, MapImgRes::bomb, 0.25f, true);
	Body->CreateAnimation(MapAnim::bomb_effect_center, MapImgRes::bomb_effect_center, 0.1f, false);
	Body->SetAutoSize(1.0f, true);
	Body->SetActive(false);
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
		}
	);

	State.SetStartFunction(BombState::explosion, [=] 
		{
			Body->ChangeAnimation(MapAnim::bomb_effect_center);
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
