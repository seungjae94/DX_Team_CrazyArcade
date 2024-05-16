#include "PreCompile.h"
#include "BlockBase.h"

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
	State.ChangeState("Idle");
}

void ABlockBase::StateInit()
{
	// State Create
	State.CreateState("Idle");

	// State Start
	State.SetStartFunction("Idle", [=] {});

	// State Update
	State.SetUpdateFunction("Idle", [=](float _DeltaTime) {});

}

void ABlockBase::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}
