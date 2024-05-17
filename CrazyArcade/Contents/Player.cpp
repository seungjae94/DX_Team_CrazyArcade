#include "PreCompile.h"
#include "Player.h"

#include "MainPlayLevel.h"
#include "MapBase.h"
#include "CrazyArcadeCore.h"

std::map<int, bool> FPlayerInfo::IsDeads;
std::map<int, std::string> FPlayerInfo::Names;

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

	//SetPlayerColor(ECharacterColor::Yellow);

	PlayLevel = dynamic_cast<AMainPlayLevel*>(GetWorld()->GetGameMode().get());
	BlockSize = AMapBase::GetBlockSize();

	// 이미지 컷팅
	UEngineSprite::CreateCutting("Bazzi_R_1.png", 5, 18);
	UEngineSprite::CreateCutting("Bazzi_2.png", 5, 2);
	UEngineSprite::CreateCutting("Bazzi_3.png", 5, 4);
	UEngineSprite::CreateCutting("Bazzi_4.png", 5, 7);

	UEngineSprite::CreateCutting("Bazzi_Y_1.png", 5, 18);
	//UEngineSprite::CreateCutting("Bazzi_Y_2.png", 5, 2);
	//UEngineSprite::CreateCutting("Bazzi_Y_3.png", 5, 4);
	//UEngineSprite::CreateCutting("Bazzi_Y_4.png", 5, 7);

	UEngineSprite::CreateCutting("Bazzi_G_1.png", 5, 18);
	UEngineSprite::CreateCutting("Bazzi_P_1.png", 5, 18);

	// 애니메이션 생성
	//Bazzi
	PlayerCreateAnimation("Bazzi_R");
	Renderer->CreateAnimation("Bazzi_R_TrapStart", "Bazzi_4.png", 0.07f, false, 6, 10);
	Renderer->CreateAnimation("Bazzi_R_Traped", "Bazzi_4.png", 0.2f, false, 11, 23);
	Renderer->CreateAnimation("Bazzi_R_TrapEnd", "Bazzi_4.png", 0.25f, false, 24, 31);
	Renderer->CreateAnimation("Bazzi_R_Die", "Bazzi_2.png", 0.15f, false, 0, 5);
	Renderer->CreateAnimation("Bazzi_R_Revival", "Bazzi_2.png", 0.15f, false, 6, 9);

	PlayerCreateAnimation("Bazzi_Y");
	PlayerCreateAnimation("Bazzi_G");
	PlayerCreateAnimation("Bazzi_P");

	Renderer->ChangeAnimation(Type + PlayerColorText + "_Idle_Down");
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
	// 임의 적용 테스트
	if (true == IsDown('Y'))
	{
		SetPlayerColor(ECharacterColor::Yellow);
	}

	PlayerPos = GetActorLocation();

	PickUpItem();
}

void APlayer::PlayerCreateAnimation(std::string _CharacterType_Color)
{
	Renderer->CreateAnimation(_CharacterType_Color + "_Ready", _CharacterType_Color + "_1.png", 0.06f, false, 37, 53);
	Renderer->CreateAnimation(_CharacterType_Color + "_Idle_Left", _CharacterType_Color + "_1.png", 1.0f, false, 0, 0);
	Renderer->CreateAnimation(_CharacterType_Color + "_Idle_Right", _CharacterType_Color + "_1.png", 1.0f, false, 6, 6);
	Renderer->CreateAnimation(_CharacterType_Color + "_Idle_Up", _CharacterType_Color + "_1.png", 1.0f, false, 12, 12);
	Renderer->CreateAnimation(_CharacterType_Color + "_Idle_Down", _CharacterType_Color + "_1.png", 1.0f, false, 20, 20);
	Renderer->CreateAnimation(_CharacterType_Color + "_Run_Left", _CharacterType_Color + "_1.png", 0.1f, true, 1, 5);
	Renderer->CreateAnimation(_CharacterType_Color + "_Run_Right", _CharacterType_Color + "_1.png", 0.1f, true, 7, 11);
	Renderer->CreateAnimation(_CharacterType_Color + "_Run_Up", _CharacterType_Color + "_1.png", 0.1f, true, 13, 19);
	Renderer->CreateAnimation(_CharacterType_Color + "_Run_Down", _CharacterType_Color + "_1.png", 0.1f, true, 21, 28);
	Renderer->CreateAnimation(_CharacterType_Color + "_Win", _CharacterType_Color + "_1.png", 0.1f, true, 29, 36);
	//Renderer->CreateAnimation(_CharacterType_Color + "_TrapStart", "Bazzi_4.png", 0.07f, false, 6, 10);
	//Renderer->CreateAnimation(_CharacterType_Color + "_Traped", "Bazzi_4.png", 0.2f, false, 11, 23);
	//Renderer->CreateAnimation(_CharacterType_Color + "_TrapEnd", "Bazzi_4.png", 0.25f, false, 24, 31);
	//Renderer->CreateAnimation(_CharacterType_Color + "_Die", "Bazzi_2.png", 0.15f, false, 0, 5);
	//Renderer->CreateAnimation(_CharacterType_Color + "_Revival", "Bazzi_2.png", 0.15f, false, 6, 9);
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
		Speed = MaxSpeed - BaseSpeed;
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

	AddItemCount(ItemType);
}

void APlayer::AddItemCount(EItemType _ItemType)
{
	int Count = MPlayerItem[_ItemType];
	++Count;
	MPlayerItem[_ItemType] = Count;
}

void APlayer::SetPlayerDead()
{
	IsDead = true;
	PlayerInfoUpdate();
}

void APlayer::SetCharacterType(ECharacterType _Character)
{
	switch (_Character)
	{
	case ECharacterType::Random:
		break;
	case ECharacterType::Dao:
		break;
	case ECharacterType::Dizni:
		break;
	case ECharacterType::Mos:
		break;
	case ECharacterType::Ethi:
		break;
	case ECharacterType::Marid:
		break;
	case ECharacterType::Bazzi:
		PlayerType = ECharacterType::Bazzi;
		Type = "Bazzi";
		break;
	case ECharacterType::Uni:
		break;
	case ECharacterType::Kephi:
		break;
	case ECharacterType::Su:
		break;
	case ECharacterType::HooU:
		break;
	case ECharacterType::Ray:
		break;
	default:
		break;
	}
}

void APlayer::SetPlayerColor(ECharacterColor _Color)
{
	switch (_Color)
	{
	case ECharacterColor::Red:
		PlayerColor = ECharacterColor::Red;
		PlayerColorText = "_R";
		break;
	case ECharacterColor::Yellow:
		PlayerColor = ECharacterColor::Yellow;
		PlayerColorText = "_Y";
		break;
	case ECharacterColor::Green:
		PlayerColor = ECharacterColor::Green;
		PlayerColorText = "_G";
		break;
	default:
		PlayerColorText = "";
		break;
	}
}

void APlayer::PlayerInfoUpdate()
{
	if (nullptr != UCrazyArcadeCore::Net)
	{
		int MySessionToken = UCrazyArcadeCore::Net->GetSessionToken();
		FPlayerInfo::IsDeads[MySessionToken] = IsDead;
	}
	else
	{
		return;
	}
}
