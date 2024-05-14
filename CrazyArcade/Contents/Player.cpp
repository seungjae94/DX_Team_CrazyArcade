#include "PreCompile.h"
#include "Player.h"

APlayer::APlayer()
{
	DefaultComponent = CreateDefaultSubObject<UDefaultSceneComponent>("DefaultComponent");
	SetRoot(DefaultComponent);

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(DefaultComponent);
	Renderer->AddPosition({ 0.0f, -BlockSize / 2.0f });

	ShadowRenderer = CreateDefaultSubObject<USpriteRenderer>("ShadowRenderer");
	ShadowRenderer->SetupAttachment(DefaultComponent);
	ShadowRenderer->AddPosition({ 0.0f, -BlockSize / 2.0f });

	DebugRenderer = CreateDefaultSubObject<USpriteRenderer>("DebugRenderer");
	DebugRenderer->SetupAttachment(DefaultComponent);

	for (MPlayerItemIter = MPlayerItem.begin(); MPlayerItemIter != MPlayerItem.end(); ++MPlayerItemIter)
	{
		int Clear = 0;
		//*MPlayerItemIter = Clear;
	}

	InputOn();
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
	Super::BeginPlay();

	UEngineSprite::CreateCutting("down.png", 8, 1);
	UEngineSprite::CreateCutting("up.png", 8, 1);
	UEngineSprite::CreateCutting("right.png", 6, 1);
	UEngineSprite::CreateCutting("left.png", 6, 1);

	Renderer->CreateAnimation("Idle_Down", "down.png", 0.1f, false, 0, 0);
	Renderer->CreateAnimation("Idle_Up", "up.png", 0.1f, false, 0, 0);
	Renderer->CreateAnimation("Idle_Right", "right.png", 0.1f, false, 0, 0);
	Renderer->CreateAnimation("Idle_Left", "left.png", 0.1f, false, 0, 0);

	Renderer->CreateAnimation("Run_Down", "down.png", 0.1f, true, 0, 7);
	Renderer->CreateAnimation("Run_Up", "up.png", 0.1f, true, 0, 7);
	Renderer->CreateAnimation("Run_Right", "right.png", 0.1f, true, 0, 5);
	Renderer->CreateAnimation("Run_Left", "left.png", 0.1f, true, 0, 5);

	Renderer->ChangeAnimation("Idle_Down");
	Renderer->SetAutoSize(1.0f, true);

	ShadowRenderer->SetSprite("Shadow.png");
	ShadowRenderer->SetAutoSize(1.0f, true);

	DebugRenderer->SetScale({ 5,5,5 });

	StateInit();
}

void APlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);

	PlayerPos = GetActorLocation();
}

void APlayer::PickUpItem(EPlayerItem _PickUpItem)
{
	switch (_PickUpItem)
	{
	case EPlayerItem::Bubble:
		++BombCount;
		break;
	case EPlayerItem::Fluid:
		break;
	case EPlayerItem::Ultra:
		break;
	case EPlayerItem::Roller:
		break;
	case EPlayerItem::RedDevil:
		break;
	case EPlayerItem::Glove:
		break;
	case EPlayerItem::Shoes:
		break;
	default:
		break;
	}
}