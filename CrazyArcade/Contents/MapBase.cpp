#include "PreCompile.h"
#include "MapBase.h"

#include <EngineBase/EngineRandom.h>

#include "MainPlayLevel.h"
#include "MapConstant.h"
#include "BlockBase.h"
#include "BombBase.h"
#include "BushBase.h"
#include "ItemBase.h"
#include "Player.h"

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
}

void AMapBase::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetMainCamera()->SetActorLocation({ 400.0f, 300.0f, -100.0f });
	SetActorLocation({ 400.0f, 300.0f, 0.0f });
	
	AMainPlayLevel* NewPlayLevel = dynamic_cast<AMainPlayLevel*>(GetWorld()->GetGameMode().get());
	if (nullptr != NewPlayLevel)
	{
		PlayLevel = NewPlayLevel;
	}
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
				TileInfo[Y][X].Block = nullptr;
			}

			std::list<std::shared_ptr<ABombBase>>::iterator Iter; 
			for (Iter = TileInfo[Y][X].AllBomb.begin(); Iter != TileInfo[Y][X].AllBomb.end(); ++Iter)
			{
				(*Iter) = nullptr;
			}

			if (nullptr != TileInfo[Y][X].Item)
			{
				TileInfo[Y][X].Item = nullptr;
			}

			if (nullptr != TileInfo[Y][X].Bush)
			{
				TileInfo[Y][X].Bush = nullptr;
			}
		}
	}

	for (size_t i = 0; i < AllPlayer.size(); i++)
	{
		if (AllPlayer[i] != nullptr) 
		{
			AllPlayer[i]->Destroy();
			AllPlayer[i] = nullptr;
		}
	}

	TileInfo.clear();
	AllPlayer.clear();
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

// 물폭탄 위치면 true 반환
bool AMapBase::IsBombPos(const FVector& _Pos, const FVector& _Dir)
{
	bool Result = false;
	FVector NextPos = _Pos;

	if (0.0f < _Dir.X)			// 우
	{
		NextPos.X += BlockCheckAdjPosX;
	}
	else if (0.0f > _Dir.X)		// 좌
	{
		NextPos.X -= BlockCheckAdjPosX;
	}
	else if (0.0f < _Dir.Y)		// 상
	{
		NextPos.Y += BlockCheckAdjUpPos;
	}
	else if (0.0f > _Dir.Y)		// 하
	{
		NextPos.Y -= BlockCheckAdjDownPos;
	}

	FPoint Point = ConvertLocationToPoint(NextPos);

	if (true == MapRangeCheckByPoint(Point)
	&&	false == TileInfo[Point.Y][Point.X].AllBomb.empty())
	{
		Result = true;
	}

	return Result;
}

// Bush 위치면 true 반환
bool AMapBase::IsBushPos(const FVector& _Pos, bool _IsInBush)
{
	bool Result = false;
	FPoint Point = ConvertLocationToPoint(_Pos);

	if (nullptr != TileInfo[Point.Y][Point.X].Bush)
	{
		if (_IsInBush == false)
		{
			TileInfo[Point.Y][Point.X].Bush->SetShaking();
		}

		Result = true;
	}

	return Result;
}

// 다른 플레이어와 충돌시 true 반환
ECharacterColor AMapBase::IsColOtherPlayer(const FVector& _Pos, APlayer* _Player)
{
	ECharacterColor Color = ECharacterColor::None;
	FVector CurPos = _Pos;

	for (size_t i = 0; i < AllPlayer.size(); i++)
	{
		if (nullptr == AllPlayer[i] || _Player == AllPlayer[i]
		||  true == AllPlayer[i]->GetIsDead() || true == AllPlayer[i]->GetIsTrapped())
		{
			continue;
		}

		FVector OtherPos = AllPlayer[i]->GetActorLocation();
		FVector DiffPos = CurPos - OtherPos;
		float DiffLen = sqrtf(powf(DiffPos.X, 2.0f) + powf(DiffPos.Y, 2.0f));

		if (20.0f > DiffLen)
		{
			Color = AllPlayer[i]->GetPlayerColor();
		}
	}

	return Color;
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
		UEngineSound::SoundPlay("GetItem.mp3").SetVolume(0.5f);
		return ItemType;
	}
}

// 현재 위치 Tile에 Bomb 스폰 함수 (실패시 nullptr 반환)
std::shared_ptr<ABombBase> AMapBase::SpawnBomb(const FVector& _Pos, APlayer* _Player)
{
	FPoint CurPoint = ConvertLocationToPoint(_Pos);

	if (0 > CurPoint.X || SizeX <= CurPoint.X || 0 > CurPoint.Y || SizeY <= CurPoint.Y)
	{
		return nullptr;
	}

	if (true == TileInfo[CurPoint.Y][CurPoint.X].AllBomb.empty())
	{
		FVector TargetPos = ConvertPointToLocation(CurPoint);
		TargetPos.Y += BombAdjustPosY;
		std::shared_ptr<ABombBase> NewBomb = GetWorld()->SpawnActor<ABombBase>("Bomb");
		NewBomb->SetActorLocation(TargetPos);
		NewBomb->SetPlayer(_Player);
		NewBomb->SetCurPoint(CurPoint);
		NewBomb->SetIdle();
		TileInfo[CurPoint.Y][CurPoint.X].AllBomb.push_back(NewBomb);
		UEngineSound::SoundPlay("BombSpawn.mp3");
		return NewBomb;
	}
	else
	{
		return nullptr;
	}
}

// 현재 위치 Tile에 Bomb 스폰 함수 (무조건 생성됨)
std::shared_ptr<ABombBase> AMapBase::ServerSpawnBomb(const FVector& _Pos, APlayer* _Player)
{
	FPoint CurPoint = ConvertLocationToPoint(_Pos);
	FVector TargetPos = ConvertPointToLocation(CurPoint);
	TargetPos.Y += BombAdjustPosY;
	std::shared_ptr<ABombBase> NewBomb = GetWorld()->SpawnActor<ABombBase>("Bomb");
	NewBomb->SetActorLocation(TargetPos);
	NewBomb->SetPlayer(_Player);
	NewBomb->SetCurPoint(CurPoint);
	NewBomb->SetIdle();
	TileInfo[CurPoint.Y][CurPoint.X].AllBomb.push_back(NewBomb);
	return NewBomb;
}

// 플레이어 종료시 삭제 시키는 함수
void AMapBase::PlayerDelete(APlayer* _Player)
{
	for (size_t i = 0; i < AllPlayer.size(); i++)
	{
		if (AllPlayer[i] == _Player)
		{
			AllPlayer[i] = nullptr;
		}
	}
}

// 플레이어 시작 위치 반환
FVector AMapBase::GetPlayerStartPos(int _Index)
{
	int Index = _Index % static_cast<int>(PlayerStartPoint.size());
	FVector PlayerStartPos = ConvertPointToLocation(PlayerStartPoint[Index]);
	return PlayerStartPos;
}
