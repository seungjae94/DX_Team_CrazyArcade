#include "PreCompile.h"
#include "Box.h"

#include "MainPlayLevel.h"
#include "MapConstant.h"
#include "MapBase.h"

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
	State.CreateState(BlockState::destroy);

	// State Start
	State.SetStartFunction(BlockState::destroy, [=]
		{
			GetBody()->ChangeAnimation(MapAnim::block_destroy);
		}
	);

	// State Update
	State.SetUpdateFunction(BlockState::destroy, [=](float _DeltaTime)
		{
			if (true == GetBody()->IsCurAnimationEnd())
			{
				FPoint CurPoint = AMapBase::ConvertLocationToPoint(GetActorLocation());
				PlayLevel->GetMap()->SetMapBlock(CurPoint, nullptr);
				Destroy();
			}
		}
	);
}
