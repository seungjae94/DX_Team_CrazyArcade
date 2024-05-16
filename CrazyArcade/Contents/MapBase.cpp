#include "PreCompile.h"
#include "MapBase.h"

#include "MapConstant.h"
#include "BombBase.h"
#include "BlockBase.h"
#include "ItemBase.h"
#include "MoveBox.h"

float AMapBase::BlockSize = 40.0f;

AMapBase::AMapBase()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");

	BackGround = CreateDefaultSubObject<USpriteRenderer>("BackGround");
	BackGround->SetPosition({ -80.0f, 0.0f, 0.0f });
	BackGround->SetAutoSize(1.0f, true);
	BackGround->SetupAttachment(Root);

	PlayUI_BackGround = CreateDefaultSubObject<USpriteRenderer>("PlayUI_BackGround");
	PlayUI_BackGround->SetSprite(MapImgRes::play_ui_background);
	PlayUI_BackGround->SetSamplering(ETextureSampling::LINEAR);
	PlayUI_BackGround->SetAutoSize(1.0f, true);
	PlayUI_BackGround->SetupAttachment(Root);

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

void AMapBase::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);

	for (size_t Y = 0; Y < MapInfo.size(); Y++)
	{
		for (size_t X = 0; X < MapInfo[Y].size(); X++)
		{
			if (nullptr != MapInfo[Y][X].Block)
			{
				MapInfo[Y][X].Block->Destroy();
				MapInfo[Y][X].Block = nullptr;
			}

			if (nullptr != MapInfo[Y][X].Item)
			{
				MapInfo[Y][X].Item->Destroy();
				MapInfo[Y][X].Item = nullptr;
			}
		}
	}
}

void AMapBase::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AMapBase::SetMapInfoSize(int _SizeX, int _SizeY)
{
	SizeY = _SizeY;
	SizeX = _SizeX;
	MapInfo.resize(SizeY);
	for (size_t Y = 0; Y < MapInfo.size(); Y++)
	{
		MapInfo[Y].resize(SizeX);
	}

	BackGround->SetOrder(ERenderOrder::BackGround);
	PlayUI_BackGround->SetOrder(ERenderOrder::BackGround);
}

// 위치 정보를 Tile 좌표값으로 반환
FPoint AMapBase::ConvertLocationToPoint(const FVector& _Pos)
{
	FPoint Result = FPoint();
	FVector Pos = _Pos - StartPos;

	Result.X = static_cast<int>(Pos.X / BlockSize);
	Result.Y = static_cast<int>(Pos.Y / BlockSize);

	return Result;
}

// 해당 좌표 Tile의 중앙 위치 정보를 반환
FVector AMapBase::ConvertPointToLocation(const FPoint& _Point)
{
	FVector Result = StartPos;

	Result.X += (_Point.X * BlockSize) + (0.5f * BlockSize);
	Result.Y += (_Point.Y * BlockSize) + (0.5f * BlockSize);

	return Result;
}

// 해당 위치 Tile의 RenderOrder를 반환
int AMapBase::GetRenderOrder(const FVector& _Pos)
{
	FVector CurPos = _Pos;
	CurPos.Y -= StartPos.Y;
	int CurY = static_cast<int>(CurPos.Y / BlockSize);
	return Const::MaxOrder - CurY;
} 

// 움직일 수 있는 위치인지를 반환
bool AMapBase::CanMovePos(const FVector& _NextPos, const FVector& _Dir)
{
	// MapInfo
	FVector NextPos = _NextPos - StartPos;

	if (0.0f < _Dir.X)
	{
		NextPos.X += 20.0f;
	}
	else if (0.0f > _Dir.X)
	{
		NextPos.X -= 20.0f;
	}
	else if (0.0f < _Dir.Y)
	{
		NextPos.Y += 30.0f;
	}
	else if (0.0f > _Dir.Y)
	{
		NextPos.Y -= 10.0f;
	}

	float NextPlayerFX = NextPos.X / BlockSize;
	float NextPlayerFY = NextPos.Y / BlockSize;

	FPoint NextPoint = FPoint();
	NextPoint.X = static_cast<int>(NextPos.X / BlockSize);
	NextPoint.Y = static_cast<int>(NextPos.Y / BlockSize);
	
	// 맵 범위 밖일때
	if (SizeX <= NextPoint.X || 0 > NextPlayerFX || SizeY <= NextPoint.Y || 0 > NextPlayerFY)
	{
		return false;
	}
	
	// 빈 공간일때
	if (nullptr == MapInfo[NextPoint.Y][NextPoint.X].Block)
	{
		return true;
	}

	// 오브젝트 존재할때
	EBlockType BlockType = MapInfo[NextPoint.Y][NextPoint.X].Block->GetBlockType();
	if (EBlockType::Wall == BlockType || EBlockType::Box == BlockType)
	{
		return false;
	}

	// MoveBox 체크
	if (EBlockType::MoveBox == BlockType)
	{
		std::shared_ptr<AMoveBox> MoveBox = std::dynamic_pointer_cast<AMoveBox>(MapInfo[NextPoint.Y][NextPoint.X].Block);
		MoveBox->SetMoveDir(_Dir);
		FPoint TwoStepPoint = NextPoint;

		if (0.0f < _Dir.X)
		{
			TwoStepPoint.X += 1;
		}
		else if (0.0f > _Dir.X)
		{
			TwoStepPoint.X -= 1;
		}
		else if (0.0f < _Dir.Y)
		{
			TwoStepPoint.Y += 1;
		}
		else if (0.0f > _Dir.Y)
		{
			TwoStepPoint.Y -= 1;
		}

		if (0 > TwoStepPoint.X || SizeX <= TwoStepPoint.X 
		||  0 > TwoStepPoint.Y || SizeY <= TwoStepPoint.Y
		|| nullptr != MapInfo[TwoStepPoint.Y][TwoStepPoint.X].Block)
		{
			return false;
		}
		
		if (MoveBoxState::idle == MoveBox->GetCurState())
		{
			MoveBox->StateChange(MoveBoxState::move);
			return false;
		}
		
		return false;
	}

	return true;
}

// 해당 위치 Tile의 ItemType을 반환
EItemType AMapBase::IsItemTile(const FVector& _Pos)
{
	FPoint CurPoint = ConvertLocationToPoint(_Pos);

	if (0 > CurPoint.X || SizeX <= CurPoint.X || 0 > CurPoint.Y || SizeY <= CurPoint.Y)
	{
		return EItemType::None;
	}

	if (nullptr == MapInfo[CurPoint.Y][CurPoint.X].Item)
	{
		return EItemType::None;
	}
	else
	{
		EItemType ItemType = MapInfo[CurPoint.Y][CurPoint.X].Item->GetItemType();
		MapInfo[CurPoint.Y][CurPoint.X].Item->Destroy();
		MapInfo[CurPoint.Y][CurPoint.X].Item = nullptr;
		return ItemType;
	}
}

// 현재 위치 Tile에 Bomb 스폰 함수 (성공시 true, 실패시 false 반환)
bool AMapBase::SpawnBomb(const FVector& _Pos, APlayer* _Player)
{
	FPoint CurPoint = ConvertLocationToPoint(_Pos);

	if (0 > CurPoint.X || SizeX <= CurPoint.X || 0 > CurPoint.Y || SizeY <= CurPoint.Y)
	{
		return false;
	}

	if (nullptr == MapInfo[CurPoint.Y][CurPoint.X].Bomb)
	{
		FVector TargetPos = ConvertPointToLocation(CurPoint);
		MapInfo[CurPoint.Y][CurPoint.X].Bomb = GetWorld()->SpawnActor<ABombBase>("Bomb");
		MapInfo[CurPoint.Y][CurPoint.X].Bomb->SetActorLocation(TargetPos);
		MapInfo[CurPoint.Y][CurPoint.X].Bomb->SetPlayer(_Player);



		//
		MapInfo[CurPoint.Y][CurPoint.X].Bomb = nullptr;
		return true;
	}
	else
	{
		return false;
	}
}

