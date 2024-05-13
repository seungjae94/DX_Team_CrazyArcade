#include "PreCompile.h"
#include "MapBase.h"
#include "MapConstant.h"
#include "BlockBase.h"

AMapBase::AMapBase()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");

	BackGround = CreateDefaultSubObject<USpriteRenderer>("BackGround");
	BackGround->SetPosition({ -80.0f, 0.0f, 0.0f });
	BackGround->SetAutoSize(1.0f, true);
	BackGround->SetupAttachment(Root);
	BackGround->SetOrder(ERenderOrder::Map);

	PlayUI_BackGround = CreateDefaultSubObject<USpriteRenderer>("PlayUI_BackGround");
	PlayUI_BackGround->SetSprite(MapImgRes::play_ui_background);
	PlayUI_BackGround->SetSamplering(ETextureSampling::LINEAR);
	PlayUI_BackGround->SetAutoSize(1.0f, true);
	PlayUI_BackGround->SetupAttachment(Root);
	PlayUI_BackGround->SetOrder(ERenderOrder::Map);

	SetRoot(Root);
}

AMapBase::~AMapBase()
{
}

void AMapBase::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetMainCamera()->SetActorLocation({ 400.0f, 300.0f, -100.0f });
	SetActorLocation({ 400.0f, 300.0f, 0.0f });
}

void AMapBase::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AMapBase::SetMapInfoSize(int _X, int _Y)
{
	MapInfo.resize(_Y);
	for (size_t Y = 0; Y < MapInfo.size(); Y++)
	{
		MapInfo[Y].resize(_X);
	}
}

void AMapBase::CreateWall(int _X, int _Y, std::string_view _ImgName)
{
	MapInfo[_Y][_X] = GetWorld()->SpawnActor<ABlockBase>("Wall");
	MapInfo[_Y][_X]->SetBlockType(EBlockType::Wall);
	MapInfo[_Y][_X]->SetBlockImg(_ImgName);

	FVector Pos = StartPos;
	Pos.X += _X * BlockSize;
	Pos.Y += _Y * BlockSize;
	MapInfo[_Y][_X]->SetActorLocation(Pos);
}
