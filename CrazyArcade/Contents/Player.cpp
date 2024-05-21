#include "PreCompile.h"
#include "Player.h"
#include <EngineBase/EngineRandom.h>
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
	PlayerCreateCuttingBazzi("_R");
	PlayerCreateCuttingBazzi("_B");

	PlayerCreateCutting("Dao_R");
	PlayerCreateCutting("Dao_B");

	PlayerCreateCutting("luxMarid_R");
	PlayerCreateCutting("luxMarid_O");
	PlayerCreateCutting("luxMarid_B");

	// 애니메이션 생성
	//Bazzi
	PlayerCreateBazziAnimation("_R");
	PlayerCreateBazziAnimation("_B");

	PlayerCreateAnimation("Dao_R");
	PlayerCreateAnimation("Dao_B");

	PlayerCreateAnimation("luxMarid_R");
	PlayerCreateAnimation("luxMarid_O");
	PlayerCreateAnimation("luxMarid_B");

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
	if (true == IsDown('C'))
	{
		if (ECharacterColor::Red == PlayerColor)
		{
			SetPlayerColor(ECharacterColor::Blue);
		}
		else if (ECharacterColor::Blue == PlayerColor)
		{
			SetPlayerColor(ECharacterColor::Red);
		}
	}
	if (true == IsDown('B'))
	{
		SetCharacterType(ECharacterType::Bazzi);
	}
	if (true == IsDown('O'))
	{
		SetCharacterType(ECharacterType::Dao);
	}
	if (true == IsDown('M'))
	{
		SetCharacterType(ECharacterType::Marid);
	}

	PlayerPos = GetActorLocation();

	PickUpItem();

	Devil(_DeltaTime);
}

void APlayer::PlayerCreateCuttingBazzi(std::string _Color)
{
	UEngineSprite::CreateCutting("Bazzi" + _Color + "_1.png", 5, 18);
	UEngineSprite::CreateCutting("Bazzi" + _Color + "_2.png", 5, 2);
	UEngineSprite::CreateCutting("Bazzi" + _Color + "_3.png", 5, 4);
	UEngineSprite::CreateCutting("Bazzi" + _Color + "_4.png", 5, 7);
}

void APlayer::PlayerCreateCutting(std::string _CharacterType_Color)
{
	UEngineSprite::CreateCutting(_CharacterType_Color + "_1.png", 5, 12);
	UEngineSprite::CreateCutting(_CharacterType_Color + "_2.png", 5, 2);
	UEngineSprite::CreateCutting(_CharacterType_Color + "_3.png", 5, 4);
	UEngineSprite::CreateCutting(_CharacterType_Color + "_4.png", 5, 4);
	UEngineSprite::CreateCutting(_CharacterType_Color + "_5.png", 5, 6);
}

void APlayer::PlayerCreateBazziAnimation(std::string _Color)
{

	Renderer->CreateAnimation("Bazzi" + _Color + "_Ready", "Bazzi" + _Color + "_1.png", 0.06f, false, 37, 53);
	Renderer->CreateAnimation("Bazzi" + _Color + "_Idle_Left", "Bazzi" + _Color + "_1.png", 1.0f, false, 0, 0);
	Renderer->CreateAnimation("Bazzi" + _Color + "_Idle_Right", "Bazzi" + _Color + "_1.png", 1.0f, false, 6, 6);
	Renderer->CreateAnimation("Bazzi" + _Color + "_Idle_Up", "Bazzi" + _Color + "_1.png", 1.0f, false, 12, 12);
	Renderer->CreateAnimation("Bazzi" + _Color + "_Idle_Down", "Bazzi" + _Color + "_1.png", 1.0f, false, 20, 20);
	Renderer->CreateAnimation("Bazzi" + _Color + "_Run_Left", "Bazzi" + _Color + "_1.png", 0.1f, true, 1, 5);
	Renderer->CreateAnimation("Bazzi" + _Color + "_Run_Right", "Bazzi" + _Color + "_1.png", 0.1f, true, 7, 11);
	Renderer->CreateAnimation("Bazzi" + _Color + "_Run_Up", "Bazzi" + _Color + "_1.png", 0.1f, true, 13, 19);
	Renderer->CreateAnimation("Bazzi" + _Color + "_Run_Down", "Bazzi" + _Color + "_1.png", 0.1f, true, 21, 28);
	Renderer->CreateAnimation("Bazzi" + _Color + "_Win", "Bazzi" + _Color + "_1.png", 0.1f, true, 29, 36);
	Renderer->CreateAnimation("Bazzi" + _Color + "_TrapStart", "Bazzi" + _Color + "_4.png", 0.07f, false, 6, 10);
	Renderer->CreateAnimation("Bazzi" + _Color + "_Traped", "Bazzi" + _Color + "_4.png", 0.2f, false, 11, 23);
	Renderer->CreateAnimation("Bazzi" + _Color + "_TrapEnd", "Bazzi" + _Color + "_4.png", 0.25f, false, 24, 31);
	Renderer->CreateAnimation("Bazzi" + _Color + "_Die", "Bazzi" + _Color + "_2.png", 0.15f, false, 0, 5);
	Renderer->CreateAnimation("Bazzi" + _Color + "_Revival", "Bazzi" + _Color + "_2.png", 0.15f, false, 6, 9);
}

void APlayer::PlayerCreateAnimation(std::string _CharacterType_Color)
{
	// Idle
	Renderer->CreateAnimation(_CharacterType_Color + "_Ready", _CharacterType_Color + "_4.png", 0.06f, false, 0, 17);
	Renderer->CreateAnimation(_CharacterType_Color + "_Idle_Right", _CharacterType_Color + "_1.png", 1.0f, false, 0, 0 );
	Renderer->CreateAnimation(_CharacterType_Color + "_Idle_Left", _CharacterType_Color + "_1.png", 1.f, false, 6, 6);
	Renderer->CreateAnimation(_CharacterType_Color + "_Idle_Up", _CharacterType_Color + "_1.png", 1.f, false, 12, 12);
	Renderer->CreateAnimation(_CharacterType_Color + "_Idle_Down", _CharacterType_Color + "_1.png", 1.f, false, 18, 18);

	// Move
	Renderer->CreateAnimation(_CharacterType_Color + "_Run_Right", _CharacterType_Color + "_1.png", 0.1f, true, 1, 5);
	Renderer->CreateAnimation(_CharacterType_Color + "_Run_Left", _CharacterType_Color + "_1.png", 0.1f, true, 7, 11);
	Renderer->CreateAnimation(_CharacterType_Color + "_Run_Up", _CharacterType_Color + "_1.png", 0.09f, true, 13, 17);
	Renderer->CreateAnimation(_CharacterType_Color + "_Run_Down", _CharacterType_Color + "_1.png", 0.09f, true, 19, 23);

	Renderer->CreateAnimation(_CharacterType_Color + "_Win", _CharacterType_Color + "_1.png", 0.1f, true, 29, 36);
	Renderer->CreateAnimation(_CharacterType_Color + "_TrapStart", _CharacterType_Color + "_5.png", 0.07f, false, 0, 4); // 0.2   0.25
	Renderer->CreateAnimation(_CharacterType_Color + "_Traped", _CharacterType_Color + "_5.png", 0.2f, true, 5, 18); // 0.2   0.25
	Renderer->CreateAnimation(_CharacterType_Color + "_TrapEnd", _CharacterType_Color + "_5.png", 0.25f, false, 19, 25);
	Renderer->CreateAnimation(_CharacterType_Color + "_Die", _CharacterType_Color + "_2.png", 0.15f, false, 0, 5);
	Renderer->CreateAnimation(_CharacterType_Color + "_Revival", _CharacterType_Color + "_2.png", 0.15f, false, 6, 9);

	Renderer->CreateAnimation(_CharacterType_Color + "_IdleOwl_Left", _CharacterType_Color + "_3.png", 0.15f, false, 0, 0);
	Renderer->CreateAnimation(_CharacterType_Color + "_IdleOwl_Right", _CharacterType_Color + "_3.png", 0.15f, false, 2, 2);
	Renderer->CreateAnimation(_CharacterType_Color + "_IdleOwl_Up", _CharacterType_Color + "_3.png", 0.15f, false, 4, 4);
	Renderer->CreateAnimation(_CharacterType_Color + "_IdleOwl_Down", _CharacterType_Color + "_3.png", 0.15f, false, 6, 6);
	Renderer->CreateAnimation(_CharacterType_Color + "_IdleTurtle_Left", _CharacterType_Color + "_3.png", 0.15f, false, 8, 8);
	Renderer->CreateAnimation(_CharacterType_Color + "_IdleTurtle_Right", _CharacterType_Color + "_3.png", 0.15f, false, 10, 10);
	Renderer->CreateAnimation(_CharacterType_Color + "_IdleTurtle_Down", _CharacterType_Color + "_3.png", 0.15f, false, 12, 12);
	Renderer->CreateAnimation(_CharacterType_Color + "_IdleTurtle_Up", _CharacterType_Color + "_3.png", 0.15f, false, 14, 14);
	Renderer->CreateAnimation(_CharacterType_Color + "_RidingOwl_Left", _CharacterType_Color + "_3.png", 0.15f, true, 0, 1);
	Renderer->CreateAnimation(_CharacterType_Color + "_RidingOwl_Right", _CharacterType_Color + "_3.png", 0.15f, true, 2, 3);
	Renderer->CreateAnimation(_CharacterType_Color + "_RidingOwl_Up", _CharacterType_Color + "_3.png", 0.15f, true, 4, 5);
	Renderer->CreateAnimation(_CharacterType_Color + "_RidingOwl_Down", _CharacterType_Color + "_3.png", 0.15f, true, 6, 7);
	Renderer->CreateAnimation(_CharacterType_Color + "_RidingTurtle_Left", _CharacterType_Color + "_3.png", 0.2f, true, 8, 9);
	Renderer->CreateAnimation(_CharacterType_Color + "_RidingTurtle_Right", _CharacterType_Color + "_3.png", 0.2f, true, 10, 11);
	Renderer->CreateAnimation(_CharacterType_Color + "_RidingTurtle_Up", _CharacterType_Color + "_3.png", 0.2f, true, 14, 15);
	Renderer->CreateAnimation(_CharacterType_Color + "_RidingTurtle_Down", _CharacterType_Color + "_3.png", 0.2f, true, 12, 13);
	Renderer->CreateAnimation(_CharacterType_Color + "_RidingUFO_Left", _CharacterType_Color + "_3.png", 0.09f, true, 16, 16);
	Renderer->CreateAnimation(_CharacterType_Color + "_RidingUFO_Right", _CharacterType_Color + "_3.png", 0.09f, true, 17, 17);
	Renderer->CreateAnimation(_CharacterType_Color + "_RidingUFO_Up", _CharacterType_Color + "_3.png", 0.09f, true, 18, 18);
	Renderer->CreateAnimation(_CharacterType_Color + "_RidingUFO_Down", _CharacterType_Color + "_3.png", 0.09f, true, 19, 19);

	Renderer->CreateAnimation(_CharacterType_Color + "_OnOwl_", _CharacterType_Color + "_3.png", 0.035f, true, 0, 7);
	Renderer->CreateAnimation(_CharacterType_Color + "_OnTurtle_", _CharacterType_Color + "_3.png", 0.035f, true, 8, 15);
	Renderer->CreateAnimation(_CharacterType_Color + "_OnUFO_", _CharacterType_Color + "_3.png", 0.05f, true, 16, 19);
}

void APlayer::PickUpItem()
{
	EItemType ItemType = PlayLevel->GetMap()->IsItemTile(GetActorLocation());
	switch (ItemType)
	{
	case EItemType::Bubble:
		++BombCount;
		break;
	case EItemType::Devil:
		IsDevil = true;
		//MoveDevil = UEngineRandom::MainRandom.RandomInt(0, 1);
		MoveDevil = true;
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

void APlayer::Devil(float _DeltaTime)
{
	if (true == IsDevil)
	{
		if (0.0f <= RenderChangeTime && RenderChangeTime < 0.5f)
		{
			Renderer->SetMulColor({ 0.7f, 0.0f, 1.0f, 1.0f });
		}
		else if (0.5f <= RenderChangeTime && RenderChangeTime < 1.0f)
		{
			Renderer->SetMulColor(FVector::One);
		}
		else
		{
			FSpriteInfo SpriteInfo = Renderer->GetCurInfo();
			RenderChangeTime = 0.0f;
		}

		RenderChangeTime += _DeltaTime;
		if (false == MoveDevil)
		{

		}

		DevilTime -= _DeltaTime;

		if (0.0f >= DevilTime)
		{
			IsDevil = false;
			DevilTime = 10.0f;
		}
	}
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
		PlayerType = ECharacterType::Dao;
		Type = "Dao";
		break;
	case ECharacterType::Dizni:
		break;
	case ECharacterType::Mos:
		break;
	case ECharacterType::Ethi:
		break;
	case ECharacterType::Marid:
		PlayerType = ECharacterType::Marid;
		Type = "luxMarid";
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
	case ECharacterColor::Blue:
		PlayerColor = ECharacterColor::Blue;
		PlayerColorText = "_B";
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
		// 0번 세션
		// 스폰을 할 때 0~999
		// 플레이어 액터도 오브젝트 토큰이 0~999 사이고
		// 오브젝트 토큰 / 1000 => 0

		// 1번 세션
		// 스폰을 할 때 1000~1999
		// 플레이어 액터도 오브젝트 토큰이 1000~1999 사이
		// 오브젝트 토큰 / 1000 => 1

		int ObjectToken = GetObjectToken();
		int SessionToken = ObjectToken / 1000;
		FPlayerInfo::IsDeads[SessionToken] = IsDead;
	}
	else
	{
		return;
	}
}
