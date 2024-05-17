#include "PreCompile.h"
#include "Box.h"

#include "MapConstant.h"

ABox::ABox()
{
}

ABox::~ABox()
{
}

void ABox::BeginPlay()
{
	Super::BeginPlay();

	SetBlockType(EBlockType::Box);
}

void ABox::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ABox::StateInit()
{
	Super::StateInit();

	// State Create
	State.CreateState(BoxState::destroy);

	// State Start
	State.SetStartFunction(BoxState::destroy, [=] 
		{

		}
	);

	// State Update
	State.SetUpdateFunction(BoxState::destroy, [=](float _DeltaTime) 
		{

		}
	);
}
