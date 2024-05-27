#include "PreCompile.h"
#include "BushBase.h"

#include "MainPlayLevel.h"
#include "MapConstant.h"
#include "MapBase.h"
#include "Player.h"

ABushBase::ABushBase()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");

	Body = CreateDefaultSubObject<USpriteRenderer>("Bush");
	Body->SetPivot(EPivot::LEFTBOTTOM);
	Body->SetAutoSize(1.0f, true);
	Body->SetupAttachment(Root);

	SetRoot(Root);
}

ABushBase::~ABushBase()
{
}

void ABushBase::BeginPlay()
{
	Super::BeginPlay();

	StateInit();
	PlayLevel = dynamic_cast<AMainPlayLevel*>(GetWorld()->GetGameMode().get());
	ShakingPosY = { 2.0f, 2.0f, -2.0f, -2.0f, -2.0f, 2.0f };
	State.ChangeState(BushState::idle);
}

void ABushBase::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);

	Destroy();
}

void ABushBase::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void ABushBase::StateInit()
{
	// State Create
	State.CreateState(BushState::idle);
	State.CreateState(BushState::shaking);
	State.CreateState(BushState::player_in);

	// State Start
	State.SetStartFunction(BushState::idle, [=] {});
	State.SetStartFunction(BushState::shaking, [=]
		{
			ShakingIdx = 0;
			ShakingDelayTimeCount = ShakingDelayTime;
		}
	);

	State.SetStartFunction(BushState::player_in, [=]
		{

		}
	);

	// State Update
	State.SetUpdateFunction(BushState::idle, [=](float _DeltaTime) {});
	State.SetUpdateFunction(BushState::shaking, [=](float _DeltaTime) 
		{
			if (0.0f < ShakingDelayTimeCount)
			{
				ShakingDelayTimeCount -= _DeltaTime;
				return;
			}

			if (ShakingPosY.size() <= ShakingIdx)
			{
				State.ChangeState(BushState::player_in);
				return;
			}

			Body->AddPosition({ 0.0f, ShakingPosY[ShakingIdx], 0.0f});
			ShakingDelayTimeCount = ShakingDelayTime;
			++ShakingIdx;
		}
	);

	State.SetUpdateFunction(BushState::player_in, [=](float _DeltaTime)
		{
			FPoint BushPoint = AMapBase::ConvertLocationToPoint(GetActorLocation());
			bool IsInPlayer = false;

			for (size_t i = 0; i < PlayLevel->GetMap()->AllPlayer.size(); i++)
			{
				APlayer* Player = PlayLevel->GetMap()->AllPlayer[i];
				if (nullptr == Player || true == Player->GetIsDead())
				{
					continue;
				}

				FVector PlayerPos = Player->GetActorLocation();
				FPoint PlayerPoint = AMapBase::ConvertLocationToPoint(PlayerPos);
				if (PlayerPoint == BushPoint)
				{
					IsInPlayer = true;
				}
			}

			if (false == IsInPlayer)
			{
				State.ChangeState(BushState::idle);
				return;
			}
		}
	);
}

void ABushBase::SetShaking()
{
	if (BushState::shaking == State.GetCurStateName())
	{
		return;
	}

	State.ChangeState(BushState::shaking);
}