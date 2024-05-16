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

	ShadowRenderer = CreateDefaultSubObject<USpriteRenderer>("ShadowRenderer");
	ShadowRenderer->SetupAttachment(DefaultComponent);

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

	SetPlayerColor(EPlayerColor::Yellow);

	PlayLevel = dynamic_cast<AMainPlayLevel*>(GetWorld()->GetGameMode().get());
	BlockSize = AMapBase::GetBlockSize();

	// 이미지 컷팅
	//UEngineSprite::CreateCutting("down.png", 8, 1);
	//UEngineSprite::CreateCutting("up.png", 8, 1);
	//UEngineSprite::CreateCutting("right.png", 6, 1);
	//UEngineSprite::CreateCutting("left.png", 6, 1);
	UEngineSprite::CreateCutting("Bazzi" + PlayerColor + "_1.png", 5, 18);
	UEngineSprite::CreateCutting("Bazzi_2.png", 5, 2);
	UEngineSprite::CreateCutting("Bazzi_3.png", 5, 4);
	UEngineSprite::CreateCutting("Bazzi_4.png", 5, 7);

	UEngineSprite::CreateCutting("Bazzi_Y_1.png", 5, 18);
	//UEngineSprite::CreateCutting("Bazzi_Y_2.png", 5, 2);
	//UEngineSprite::CreateCutting("Bazzi_Y_3.png", 5, 4);
	//UEngineSprite::CreateCutting("Bazzi_Y_4.png", 5, 7);

	// 애니메이션 생성
	//Renderer->CreateAnimation("Idle_Down", "down.png", 0.1f, false, 0, 0);
	//Renderer->CreateAnimation("Idle_Up", "up.png", 0.1f, false, 0, 0);
	//Renderer->CreateAnimation("Idle_Right", "right.png", 0.1f, false, 0, 0);
	//Renderer->CreateAnimation("Idle_Left", "left.png", 0.1f, false, 0, 0);
	//Renderer->CreateAnimation("Run_Down", "down.png", 0.1f, true, 0, 7);
	//Renderer->CreateAnimation("Run_Up", "up.png", 0.1f, true, 0, 7);
	//Renderer->CreateAnimation("Run_Right", "right.png", 0.1f, true, 0, 5);
	//Renderer->CreateAnimation("Run_Left", "left.png", 0.1f, true, 0, 5);
	Renderer->CreateAnimation("Ready", "Bazzi" + PlayerColor + "_1.png", 0.06f, false, 37, 53);
	Renderer->CreateAnimation("Idle_Left", "Bazzi" + PlayerColor + "_1.png", 1.0f, false, 0, 0);
	Renderer->CreateAnimation("Idle_Right", "Bazzi" + PlayerColor + "_1.png", 1.0f, false, 6, 6);
	Renderer->CreateAnimation("Idle_Up", "Bazzi" + PlayerColor + "_1.png", 1.0f, false, 12, 12);
	Renderer->CreateAnimation("Idle_Down", "Bazzi" + PlayerColor + "_1.png", 1.0f, false, 20, 20);
	Renderer->CreateAnimation("Run_Left", "Bazzi" + PlayerColor + "_1.png", 0.1f, true, 1, 5);
	Renderer->CreateAnimation("Run_Right", "Bazzi" + PlayerColor + "_1.png", 0.1f, true, 7, 11);
	Renderer->CreateAnimation("Run_Up", "Bazzi" + PlayerColor + "_1.png", 0.1f, true, 13, 19);
	Renderer->CreateAnimation("Run_Down", "Bazzi" + PlayerColor + "_1.png", 0.1f, true, 21, 28);
	Renderer->CreateAnimation("Win", "Bazzi" + PlayerColor + "_1.png", 0.1f, true, 29, 36);
	Renderer->CreateAnimation("DamagedStart_", "Bazzi_4.png", 0.07f, false, 6, 10);
	Renderer->CreateAnimation("Damaged_", "Bazzi_4.png", 0.2f, true, 11, 23);
	Renderer->CreateAnimation("Fade_", "Bazzi_4.png", 0.25f, true, 24, 31);
	Renderer->CreateAnimation("Die_", "Bazzi_2.png", 0.15f, false, 0, 5);
	Renderer->CreateAnimation("Revival_", "Bazzi_2.png", 0.15f, false, 6, 9);

	Renderer->ChangeAnimation("Idle_Down");
	Renderer->SetAutoSize(0.9f, true);
	Renderer->AddPosition({ 0.0f, BlockSize / 2.0f, 0.0f });

	ShadowRenderer->SetSprite("Shadow.png");
	ShadowRenderer->SetAutoSize(1.0f, true);
	ShadowRenderer->SetMulColor({ 1.0f, 1.0f, 1.0f, 0.7f });
	ShadowRenderer->SetOrder(ERenderOrder::Shadow);
	ShadowRenderer->AddPosition({ 0.0f, -BlockSize / 4.0f });

	DebugRenderer->SetScale({ 5,5,10 });
	DebugRenderer->SetOrder(9999);

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
	//if (true == IsDown('R'))
	//{
	//	PickUpItem(EPlayerItem::Roller);
	//}
	//if (true == IsDown('B'))
	//{
	//	PickUpItem(EPlayerItem::Bubble);
	//}

	PlayerPos = GetActorLocation();

	PickUpItem();
}

void APlayer::PickUpItem()
{
	EPlayerItem ItemType = PlayLevel->GetMap()->IsItemTile(GetActorLocation());
	switch (ItemType)
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

	//AddItemCount(_ItemType);
}

void APlayer::AddItemCount(EPlayerItem _ItemType)
{
	int Count = MPlayerItem[_ItemType];
	++Count;
	MPlayerItem[_ItemType] = Count;
}

void APlayer::SetPlayerColor(EPlayerColor _Color)
{
	switch (_Color)
	{
	case EPlayerColor::Red:
		PlayerColor = "";
		break;
	case EPlayerColor::Yellow:
		PlayerColor = "_Y";
		break;
	default:
		PlayerColor = "";
		break;
	}
}