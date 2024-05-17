#include "PreCompile.h"
#include "BlockBase.h"

#include "MapConstant.h"

ABlockBase::ABlockBase()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");

	Body = CreateDefaultSubObject<USpriteRenderer>("Block");
	Body->SetPivot(EPivot::LEFTBOTTOM);
	Body->SetAutoSize(1.0f, true);
	Body->SetupAttachment(Root);

	SetRoot(Root);
}

ABlockBase::~ABlockBase()
{
}

void ABlockBase::BeginPlay()
{
	Super::BeginPlay();

	StateInit();
	State.ChangeState(BlockBaseState::idle);
}

void ABlockBase::StateInit()
{
	// State Create
	State.CreateState(BlockBaseState::idle);

	// State Start
	State.SetStartFunction(BlockBaseState::idle, [=] {});

	// State Update
	State.SetUpdateFunction(BlockBaseState::idle, [=](float _DeltaTime) {});

}

void ABlockBase::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}
