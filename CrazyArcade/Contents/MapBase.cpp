#include "PreCompile.h"
#include "MapBase.h"

#include "MapConstant.h"
#include "BlockBase.h"
#include "BombBase.h"
#include "BushBase.h"
#include "ItemBase.h"
#include "MoveBox.h"

FVector AMapBase::StartPos = { 20.0f, 40.0f, 0.0f };
float AMapBase::BlockSize = 40.0f;
float AMapBase::BombAdjustPosY = 6.0f;	
int AMapBase::SizeX = 0;
int AMapBase::SizeY = 0;

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
	for (size_t Y = 0; Y < TileInfo.size(); Y++)
	{
		for (size_t X = 0; X < TileInfo[Y].size(); X++)
		{
			if (nullptr != TileInfo[Y][X].Block)
			{
				TileInfo[Y][X].Block->Destroy();
				TileInfo[Y][X].Block = nullptr;
			}

			if (nullptr != TileInfo[Y][X].Bomb)
			{
				TileInfo[Y][X].Bomb->Destroy();
				TileInfo[Y][X].Bomb = nullptr;
			}

			if (nullptr != TileInfo[Y][X].Item)
			{
				TileInfo[Y][X].Item->Destroy();
				TileInfo[Y][X].Item = nullptr;
			}

			if (nullptr != TileInfo[Y][X].Bush)
			{
				TileInfo[Y][X].Bush->Destroy();
				TileInfo[Y][X].Bush = nullptr;
			}
		}
	}

	TileInfo.clear();
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

	for (size_t Y = 0; Y < TileInfo.size(); Y++)
	{
		for (size_t X = 0; X < TileInfo[Y].size(); X++)
		{
			if (nullptr != TileInfo[Y][X].Block)
			{
				TileInfo[Y][X].Block->Destroy();
				TileInfo[Y][X].Block = nullptr;
			}

			if (nullptr != TileInfo[Y][X].Item)
			{
				TileInfo[Y][X].Item->Destroy();
				TileInfo[Y][X].Item = nullptr;
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
	TileInfo.resize(SizeY);
	for (size_t Y = 0; Y < TileInfo.size(); Y++)
	{
		TileInfo[Y].resize(SizeX);
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

// 맵 범위 안의 좌표인지 체크
bool AMapBase::MapRangeCheckByPoint(FPoint _Point)
{
	if (0 > _Point.X || SizeX <= _Point.X || 0 > _Point.Y || SizeY <= _Point.Y)
	{
		return false;
	}

	return true;
}

// 해당 좌표 Tile의 중앙 위치 정보를 반환
FVector AMapBase::ConvertPointToLocation(FPoint _Point)
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
	//// 위치 계산 Start
	FVector NextPos = _NextPos - StartPos;	// 중심 위치
	FVector NextPos1 = FVector::Zero;		// 보조 위치 1
	FVector NextPos2 = FVector::Zero;		// 보조 위치 2

	if (0.0f < _Dir.X)			// 우
	{
		NextPos.X += 20.0f;

		NextPos1 = NextPos;
		NextPos1.Y += BlockCheckAdjustPosY;

		NextPos2 = NextPos;
		NextPos2.Y -= BlockCheckAdjustPosY;
	}
	else if (0.0f > _Dir.X)		// 좌
	{
		NextPos.X -= 20.0f;

		NextPos1 = NextPos;
		NextPos1.Y += BlockCheckAdjustPosY;

		NextPos2 = NextPos;
		NextPos2.Y -= BlockCheckAdjustPosY;
	}	
	else if (0.0f < _Dir.Y)		// 상
	{
		NextPos.Y += 20.0f;

		NextPos1 = NextPos;
		NextPos1.X += BlockCheckAdjustPosX;

		NextPos2 = NextPos;
		NextPos2.X -= BlockCheckAdjustPosX;
	}
	else if (0.0f > _Dir.Y)		// 하
	{
		NextPos.Y -= 17.0f;

		NextPos1 = NextPos;
		NextPos1.X += BlockCheckAdjustPosX;

		NextPos2 = NextPos;
		NextPos2.X -= BlockCheckAdjustPosX;
	}

	float NextPlayerFX = NextPos.X / BlockSize;
	float NextPlayerFY = NextPos.Y / BlockSize;

	FPoint NextPoint = FPoint();
	NextPoint.X = static_cast<int>(NextPos.X / BlockSize);
	NextPoint.Y = static_cast<int>(NextPos.Y / BlockSize);

	FPoint NextPoint1 = FPoint();
	NextPoint1.X = static_cast<int>(NextPos1.X / BlockSize);
	NextPoint1.Y = static_cast<int>(NextPos1.Y / BlockSize);

	FPoint NextPoint2 = FPoint();
	NextPoint2.X = static_cast<int>(NextPos2.X / BlockSize);
	NextPoint2.Y = static_cast<int>(NextPos2.Y / BlockSize);
	//// 위치 계산 End

	bool Result = false;

	// 맵 범위 밖일때
	if (SizeX <= NextPoint.X || 0.0f > NextPlayerFX || SizeY <= NextPoint.Y || 0.0f > NextPlayerFY)
	{
		Result = false;
		return Result;
	}
	
	// 빈 공간일때
	if (nullptr == TileInfo[NextPoint.Y][NextPoint.X].Block)
	{
		Result = true;

		// 보조 위치1 체크
		if (nullptr != TileInfo[NextPoint1.Y][NextPoint1.X].Block)
		{
			EBlockType BlockType1 = TileInfo[NextPoint1.Y][NextPoint1.X].Block->GetBlockType();
			if (EBlockType::Wall == BlockType1 || EBlockType::Box == BlockType1)
			{
				Result = false;
				return Result;
			}

			Result = MoveBoxCheck(NextPoint1, _Dir);
		}

		// 보조 위치2 체크
		if (nullptr != TileInfo[NextPoint2.Y][NextPoint2.X].Block)
		{
			EBlockType BlockType2 = TileInfo[NextPoint2.Y][NextPoint2.X].Block->GetBlockType();
			if (EBlockType::Wall == BlockType2 || EBlockType::Box == BlockType2)
			{
				Result = false;
				return Result;
			}

			Result = MoveBoxCheck(NextPoint2, _Dir);
		}

		return Result;
	}

	// 오브젝트 존재할때
	EBlockType BlockType = TileInfo[NextPoint.Y][NextPoint.X].Block->GetBlockType();
	if (EBlockType::Wall == BlockType || EBlockType::Box == BlockType)
	{
		Result = false;
		return Result;
	}
	 
	// MoveBox 체크
	Result = MoveBoxCheck(NextPoint, _Dir);

	return Result;
}

bool AMapBase::MoveBoxCheck(FPoint _NextPoint, const FVector& _Dir)
{
	if (nullptr == TileInfo[_NextPoint.Y][_NextPoint.X].Block)
	{
		return false;
	}

	EBlockType BlockType = TileInfo[_NextPoint.Y][_NextPoint.X].Block->GetBlockType();
	if (EBlockType::MoveBox == BlockType)
	{
		AMoveBox* MoveBox = dynamic_cast<AMoveBox*>(TileInfo[_NextPoint.Y][_NextPoint.X].Block);
		MoveBox->SetMoveDir(_Dir);
		FPoint TwoStepPoint = _NextPoint;

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
			|| 0 > TwoStepPoint.Y || SizeY <= TwoStepPoint.Y
			|| nullptr != TileInfo[TwoStepPoint.Y][TwoStepPoint.X].Block)
		{
			return false;
		}

		if (BlockState::idle == MoveBox->GetCurState())
		{
			MoveBox->StateChange(BlockState::move);
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

	if (nullptr == TileInfo[CurPoint.Y][CurPoint.X].Item)
	{
		return EItemType::None;
	}
	else
	{
		EItemType ItemType = TileInfo[CurPoint.Y][CurPoint.X].Item->GetItemType();
		TileInfo[CurPoint.Y][CurPoint.X].Item->Destroy();
		TileInfo[CurPoint.Y][CurPoint.X].Item = nullptr;
		return ItemType;
	}
}

// 현재 위치 Tile에 Bomb 스폰 함수 (실패시 nullptr 반환)
ABombBase* AMapBase::SpawnBomb(const FVector& _Pos, APlayer* _Player)
{
	FPoint CurPoint = ConvertLocationToPoint(_Pos);

	if (0 > CurPoint.X || SizeX <= CurPoint.X || 0 > CurPoint.Y || SizeY <= CurPoint.Y)
	{
		return nullptr;
	}

	if (nullptr == TileInfo[CurPoint.Y][CurPoint.X].Bomb)
	{
		FVector TargetPos = ConvertPointToLocation(CurPoint);
		TargetPos.Y += BombAdjustPosY;
		TileInfo[CurPoint.Y][CurPoint.X].Bomb = GetWorld()->SpawnActor<ABombBase>("Bomb").get();
		TileInfo[CurPoint.Y][CurPoint.X].Bomb->SetActorLocation(TargetPos);
		TileInfo[CurPoint.Y][CurPoint.X].Bomb->SetPlayer(_Player);
		TileInfo[CurPoint.Y][CurPoint.X].Bomb->SetCurPoint(CurPoint);
		TileInfo[CurPoint.Y][CurPoint.X].Bomb->SetIdle();
		return TileInfo[CurPoint.Y][CurPoint.X].Bomb;
	}
	else
	{
		return nullptr;
	}
}

