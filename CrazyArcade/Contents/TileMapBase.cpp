#include "PreCompile.h"
#include "TileMapBase.h"
#include "MapConstant.h"

ATileMapBase::ATileMapBase()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");

	BackGround = CreateDefaultSubObject<USpriteRenderer>("BackGround");
	BackGround->SetSprite(MapImgRes::village_background);
	BackGround->SetAutoSize(1.0f, true);
	BackGround->SetOrder(0);

	SetRoot(Root);
}

ATileMapBase::~ATileMapBase()
{
}

void ATileMapBase::BeginPlay()
{
	Super::BeginPlay();


}

void ATileMapBase::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);


}
