#include "PreCompile.h"
#include "TileMapBase.h"
#include "MapConstant.h"

ATileMapBase::ATileMapBase()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");

	PlayUI_BackGround = CreateDefaultSubObject<USpriteRenderer>("PlayUI_BackGround");
	PlayUI_BackGround->SetSprite(MapImgRes::play_ui_background);
	PlayUI_BackGround->SetSamplering(ETextureSampling::LINEAR);
	PlayUI_BackGround->SetAutoSize(1.0f, true);
	PlayUI_BackGround->SetupAttachment(Root);
	PlayUI_BackGround->SetOrder(0);

	BackGround = CreateDefaultSubObject<USpriteRenderer>("BackGround");
	BackGround->SetPosition({ -80.0f, 0.0f, 0.0f });
	BackGround->SetAutoSize(1.0f, true);	
	BackGround->SetupAttachment(Root);
	BackGround->SetOrder(1);

	SetRoot(Root);
}

ATileMapBase::~ATileMapBase()
{
}

void ATileMapBase::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetMainCamera()->SetActorLocation({ 400.0f, 300.0f, -100.0f });
	SetActorLocation({ 400.0f, 300.0f, 0.0f });
}

void ATileMapBase::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ATileMapBase::SetTileSize(int _X, int _Y)
{
	TileInfo.resize(_Y);
	for (size_t i = 0; i < TileInfo.resize(_X); i++)
	{

	}
}
