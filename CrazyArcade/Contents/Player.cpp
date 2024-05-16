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

	MPlayerItem.insert(std::pair(EItemType::Bubble, 0));
	MPlayerItem.insert(std::pair(EItemType::Fluid, 0));
	MPlayerItem.insert(std::pair(EItemType::Ultra, 0));
	MPlayerItem.insert(std::pair(EItemType::Roller, 0));
	MPlayerItem.insert(std::pair(EItemType::RedDevil, 0));
	MPlayerItem.insert(std::pair(EItemType::Glove, 0));
	MPlayerItem.insert(std::pair(EItemType::Shoes, 0));

	InputOn();
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
	Super::BeginPlay();

	//SetPlayerColor(EPlayerColor::Yellow);

	PlayLevel = dynamic_cast<AMainPlayLevel*>(GetWorld()->GetGameMode().get());
	BlockSize = AMapBase::GetBlockSize();

	// 이미지 컷팅
	UEngineSprite::CreateCutting("Bazzi_1.png", 5, 18);
	UEngineSprite::CreateCutting("Bazzi_2.png", 5, 2);
	UEngineSprite::CreateCutting("Bazzi_3.png", 5, 4);
	UEngineSprite::CreateCutting("Bazzi_4.png", 5, 7);

	UEngineSprite::CreateCutting("Bazzi_Y_1.png", 5, 18);
	//UEngineSprite::CreateCutting("Bazzi_Y_2.png", 5, 2);
	//UEngineSprite::CreateCutting("Bazzi_Y_3.png", 5, 4);
	//UEngineSprite::CreateCutting("Bazzi_Y_4.png", 5, 7);

	// 애니메이션 생성
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
	Renderer->CreateAnimation("TrapStart", "Bazzi_4.png", 0.07f, false, 6, 10);
	Renderer->CreateAnimation("Traped", "Bazzi_4.png", 0.2f, false, 11, 23);
	Renderer->CreateAnimation("TrapEnd", "Bazzi_4.png", 0.25f, false, 24, 31);
	Renderer->CreateAnimation("Die", "Bazzi_2.png", 0.15f, false, 0, 5);
	Renderer->CreateAnimation("Revival", "Bazzi_2.png", 0.15f, false, 6, 9);

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
		std::string Msg = std::format("Bubble : {}\n", MPlayerItem[EItemType::Bubble]);
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
	EItemType ItemType = PlayLevel->GetMap()->IsItemTile(GetActorLocation());
	switch (ItemType)
	{
	case EItemType::Bubble:
		++BombCount;
		break;
	case EItemType::Fluid:
		if (BombPower < MaxBombPower)
		{
			++BombPower;
		}
		break;
	case EItemType::Ultra:
		BombPower = MaxBombPower;
		break;
	case EItemType::Roller:
		Speed += 10.0f;
		CurSpeed = BaseSpeed + Speed;
		if (MaxSpeed < CurSpeed)
		{
			CurSpeed = MaxSpeed;
		}
		break;
	case EItemType::RedDevil:
		CurSpeed = MaxSpeed;
		break;
	case EItemType::Glove:
		Throw = true;
		break;
	case EItemType::Shoes:
		Push = true;
		break;
	default:
		break;
	}

	//AddItemCount(_ItemType);
}

void APlayer::AddItemCount(EItemType _ItemType)
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