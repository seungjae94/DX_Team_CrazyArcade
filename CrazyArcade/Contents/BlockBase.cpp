#include "PreCompile.h"
#include "BlockBase.h"

ABlockBase::ABlockBase()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");

	Body = CreateDefaultSubObject<USpriteRenderer>("Block");
	Body->SetOrder(ERenderOrder::Block);
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
}

void ABlockBase::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
