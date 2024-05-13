#include "PreCompile.h"
#include "TileMapBase.h"
#include "MapConstant.h"

ATileMapBase::ATileMapBase()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");

	PlayUI_BackGround = CreateDefaultSubObject<USpriteRenderer>("PlayUI_BackGround");
	PlayUI_BackGround->SetSprite(MapImgRes::play_ui_background);
	PlayUI_BackGround->SetAutoSize(1.0f, true);
	PlayUI_BackGround->SetOrder(0);

	BackGround = CreateDefaultSubObject<USpriteRenderer>("BackGround");
	BackGround->SetSprite(MapImgRes::village_background);
	BackGround->SetAutoSize(1.0f, true);
	BackGround->SetOrder(1);

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
