#include "PreCompile.h"
#include "Player.h"

#include "MainPlayLevel.h"
#include "MapBase.h"

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

	MPlayerItem.insert(std::pair(EPlayerItem::Bubble, 0));
	MPlayerItem.insert(std::pair(EPlayerItem::Fluid, 0));
	MPlayerItem.insert(std::pair(EPlayerItem::Ultra, 0));
	MPlayerItem.insert(std::pair(EPlayerItem::Roller, 0));
	MPlayerItem.insert(std::pair(EPlayerItem::RedDevil, 0));
	MPlayerItem.insert(std::pair(EPlayerItem::Glove, 0));
	MPlayerItem.insert(std::pair(EPlayerItem::Shoes, 0));

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
	ShadowRenderer->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.7f });
	ShadowRenderer->SetOrder(ERenderOrder::Shadow);

	DebugRenderer->SetScale({ 5,5,5 });

	PlayLevel = dynamic_cast<AMainPlayLevel*>(GetWorld()->GetGameMode().get());
	BlockSize = AMapBase::GetBlockSize();

	StateInit();
}

void APlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);

	int PlayerOrder = PlayLevel->GetMap()->GetRenderOrder(GetActorLocation());
	Renderer->SetOrder(PlayerOrder);

	{
		std::string Msg = std::format("PlayerOrder : {}\n", PlayerOrder);
		UEngineDebugMsgWindow::PushMsg(Msg);
	}
	{
		std::string Msg = std::format("Bubble : {}\n", MPlayerItem[EPlayerItem::Bubble]);
		UEngineDebugMsgWindow::PushMsg(Msg);
	}
	// Item 임의 적용 테스트
	if (true == IsDown('R'))
	{
		PickUpItem(EPlayerItem::Roller);
	}
	if (true == IsDown('B'))
	{
		PickUpItem(EPlayerItem::Bubble);
	}

	PlayerPos = GetActorLocation();
}

void APlayer::PickUpItem(EPlayerItem _ItemType)
{
	switch (_ItemType)
	{
	case EPlayerItem::Bubble:
		++BombCount;
		break;
	case EPlayerItem::Fluid:
		if (BombPower < MaxBombPower)
		{
			++BombPower;
		}
		break;
	case EPlayerItem::Ultra:
		BombPower = MaxBombPower;
		break;
	case EPlayerItem::Roller:
		Speed += 10.0f;
		CurSpeed = BaseSpeed + Speed;
		if (MaxSpeed < CurSpeed)
		{
			CurSpeed = MaxSpeed;
		}
		break;
	case EPlayerItem::RedDevil:
		CurSpeed = MaxSpeed;
		break;
	case EPlayerItem::Glove:
		Throw = true;
		break;
	case EPlayerItem::Shoes:
		Push = true;
		break;
	default:
		break;
	}

	AddItemCount(_ItemType);
}

void APlayer::AddItemCount(EPlayerItem _ItemType)
{
	int Count = MPlayerItem[_ItemType];
	++Count;
	MPlayerItem[_ItemType] = Count;
}