#include "PreCompile.h"
#include "BushBase.h"

#include "MainPlayLevel.h"
#include "MapConstant.h"

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
	ShakingPosY = { 2.0f, 2.0f, 2.0f, -2.0f, -2.0f, -2.0f };
	State.ChangeState(BlockState::idle);
}

void ABushBase::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);

	if (UEngineInput::IsDown('B'))
	{
		State.ChangeState(BlockState::shaking);
		return;
	}
}

void ABushBase::StateInit()
{
	// State Create
	State.CreateState(BlockState::idle);
	State.CreateState(BlockState::shaking);

	// State Start
	State.SetStartFunction(BlockState::idle, [=] {});
	State.SetStartFunction(BlockState::shaking, [=] 
		{
			ShakingIdx = 0;
		}
	);

	// State Update
	State.SetUpdateFunction(BlockState::idle, [=](float _DeltaTime) {});
	State.SetUpdateFunction(BlockState::shaking, [=](float _DeltaTime) 
		{
			if (ShakingPosY.size() <= ShakingIdx)
			{
				State.ChangeState(BlockState::idle);
				return;
			}

			Body->AddPosition({ 0.0f, 0.0f, 0.0f });
			++ShakingIdx;
		}
	);
}
