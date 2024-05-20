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
	State.ChangeState(BlockState::idle);
}

void ABushBase::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void ABushBase::StateInit()
{
	// State Create
	State.CreateState(BlockState::idle);

	// State Start
	State.SetStartFunction(BlockState::idle, [=] {});

	// State Update
	State.SetUpdateFunction(BlockState::idle, [=](float _DeltaTime) {});
}
