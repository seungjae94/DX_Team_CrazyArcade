#include "PreCompile.h"
#include "BlockBase.h"

#include "MainPlayLevel.h"
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
	PlayLevel = dynamic_cast<AMainPlayLevel*>(GetWorld()->GetGameMode().get());
	State.ChangeState(BlockState::idle);
}

void ABlockBase::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);

	Destroy();
}

void ABlockBase::StateInit()
{
	// State Create
	State.CreateState(BlockState::idle);

	// State Start
	State.SetStartFunction(BlockState::idle, [=] {});

	// State Update
	State.SetUpdateFunction(BlockState::idle, [=](float _DeltaTime) {});

}

void ABlockBase::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}
