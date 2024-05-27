#include "PreCompile.h"
#include "ItemBase.h"

#include "MainPlayLevel.h"
#include "MapConstant.h"
#include "MapBase.h"

AItemBase::AItemBase()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");

	Body = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Body->SetPosition({ 0.0f, 20.0f, 0.0f });
	Body->SetAutoSize(1.0f, true);
	Body->SetupAttachment(Root);

	Shadow = CreateDefaultSubObject<USpriteRenderer>("ShadowRenderer");
	Shadow->CreateAnimation(MapAnim::item_shadow, MapImgRes::item_shadow, 0.5f, true);
	Shadow->ChangeAnimation(MapAnim::item_shadow);
	Shadow->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.7f });
	Shadow->SetOrder(ERenderOrder::Shadow);
	Shadow->SetAutoSize(1.0f, true);
	Shadow->SetupAttachment(Root);
	
	SetRoot(Root);
}

AItemBase::~AItemBase()
{
}

void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	
	PlayLevel = dynamic_cast<AMainPlayLevel*>(GetWorld()->GetGameMode().get());
	StateInit();
}

void AItemBase::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);

	Destroy();
}

void AItemBase::StateInit()
{
	// State Create
	State.CreateState(ItemState::idle);

	// State Start
	State.SetStartFunction(ItemState::idle, [=]
		{
			int Order = AMapBase::GetRenderOrder(GetActorLocation());
			Body->SetOrder(Order);
			UEngineSound::SoundPlay("ItemSpawn.mp3");
		}
	);

	// State Update
	State.SetUpdateFunction(ItemState::idle, [=](float _DeltaTime) 
		{
			MoveUpDown(_DeltaTime);
		}
	);		
}

void AItemBase::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void AItemBase::SetItem(EItemType _Type)
{
	ItemType = _Type;

	switch (ItemType)
	{
	case EItemType::Bubble:
		Body->SetSprite(MapImgRes::item_bubble);
		break;
	case EItemType::Devil:
		Body->SetSprite(MapImgRes::item_devil);
		break;
	case EItemType::Fluid:
		Body->SetSprite(MapImgRes::item_fluid);
		break;
	case EItemType::Glove:
		Body->SetSprite(MapImgRes::item_glove);
		break;
	case EItemType::RedDevil:
		Body->SetSprite(MapImgRes::item_reddevil);
		break;
	case EItemType::Roller:
		Body->SetSprite(MapImgRes::item_roller);
		break;
	case EItemType::Shoes:
		Body->SetSprite(MapImgRes::item_shoes);
		break;
	case EItemType::Ultra:
		Body->SetSprite(MapImgRes::item_ultra);
		break;
	case EItemType::Superman:
		Body->SetSprite(MapImgRes::item_superman);
		break;
	case EItemType::Owl:
		Body->SetSprite(MapImgRes::item_owl);
		break;
	case EItemType::Turtle:
		Body->SetSprite(MapImgRes::item_turtle);
		break;
	case EItemType::UFO:
		Body->SetSprite(MapImgRes::item_ufo);
		break;
	case EItemType::Needle:
		Body->SetSprite(MapImgRes::item_needle);
		break;
	}

	State.ChangeState(ItemState::idle);
}

void AItemBase::MoveUpDown(float _DeltaTime)
{
	if (0.0f <= MoveTime && MoveTime < 0.5f)
	{
		Body->AddPosition(FVector::Up * MoveSpeed * _DeltaTime);
	}
	else if (0.5f <= MoveTime && MoveTime < 1.0f)
	{
		Body->AddPosition(FVector::Down * MoveSpeed * _DeltaTime);
	}
	else
	{
		MoveTime = 0.0f;
	}

	MoveTime += _DeltaTime;
}

