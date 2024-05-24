#include "PreCompile.h"
#include "MapBase.h"

#include "MapConstant.h"
#include "BlockBase.h"
#include "BushBase.h"
#include "ItemBase.h"
#include "MoveBox.h"
#include "Wall.h"
#include "Box.h"

void AMapBase::CreateWall(FPoint _Point, std::string_view _ImgName)
{
	TileInfo[_Point.Y][_Point.X].Block = GetWorld()->SpawnActor<AWall>("Wall").get();
	TileInfo[_Point.Y][_Point.X].Block->SetBlockImg(_ImgName);
	TileInfo[_Point.Y][_Point.X].Block->GetBody()->SetOrder(Const::MaxOrder - _Point.Y);

	FVector Pos = StartPos;
	Pos.X += _Point.X * BlockSize;
	Pos.Y += _Point.Y * BlockSize;
	TileInfo[_Point.Y][_Point.X].Block->SetActorLocation(Pos);
}

void AMapBase::CreateAnimationWall(FPoint _Point, std::string_view _ImgName)
{
	TileInfo[_Point.Y][_Point.X].Block = GetWorld()->SpawnActor<AWall>("Wall").get();
	TileInfo[_Point.Y][_Point.X].Block->GetBody()->CreateAnimation(MapAnim::block_idle, _ImgName, 0.3f, true);
	TileInfo[_Point.Y][_Point.X].Block->GetBody()->SetOrder(Const::MaxOrder - _Point.Y);
	TileInfo[_Point.Y][_Point.X].Block->GetBody()->ChangeAnimation(MapAnim::block_idle);

	FVector Pos = StartPos;
	Pos.X += _Point.X * BlockSize;
	Pos.Y += _Point.Y * BlockSize;
	TileInfo[_Point.Y][_Point.X].Block->SetActorLocation(Pos);
}


void AMapBase::CreateBox(FPoint _Point, std::string_view _ImgName, EItemType _SpawnItemType)
{
	ABox* NewBox = GetWorld()->SpawnActor<ABox>("Box").get();
	NewBox->SetSpawnItemType(_SpawnItemType);

	TileInfo[_Point.Y][_Point.X].Block = NewBox;

	TileInfo[_Point.Y][_Point.X].Block->GetBody()->CreateAnimation(MapAnim::block_idle, _ImgName, 0.05f, false, 0, 0);
	TileInfo[_Point.Y][_Point.X].Block->GetBody()->CreateAnimation(MapAnim::block_destroy, _ImgName, 0.05f, false);
	TileInfo[_Point.Y][_Point.X].Block->GetBody()->ChangeAnimation(MapAnim::block_idle);
	TileInfo[_Point.Y][_Point.X].Block->GetBody()->SetOrder(Const::MaxOrder - _Point.Y);

	FVector Pos = StartPos;
	Pos.X += _Point.X * BlockSize;
	Pos.Y += _Point.Y * BlockSize;
	TileInfo[_Point.Y][_Point.X].Block->SetActorLocation(Pos);
}

void AMapBase::CreateMoveBox(FPoint _Point, std::string_view _ImgName, EItemType _SpawnItemType)
{
	AMoveBox* NewMoveBox = GetWorld()->SpawnActor<AMoveBox>("MoveBox").get();
	NewMoveBox->SetSpawnItemType(_SpawnItemType);

	TileInfo[_Point.Y][_Point.X].Block = NewMoveBox;

	TileInfo[_Point.Y][_Point.X].Block->GetBody()->CreateAnimation(MapAnim::block_idle, _ImgName, 0.05f, false, 0, 0);
	TileInfo[_Point.Y][_Point.X].Block->GetBody()->CreateAnimation(MapAnim::block_destroy, _ImgName, 0.05f, false);
	TileInfo[_Point.Y][_Point.X].Block->GetBody()->ChangeAnimation(MapAnim::block_idle);
	TileInfo[_Point.Y][_Point.X].Block->GetBody()->SetOrder(Const::MaxOrder - _Point.Y);

	FVector Pos = StartPos;
	Pos.X += _Point.X * BlockSize;
	Pos.Y += _Point.Y * BlockSize;
	TileInfo[_Point.Y][_Point.X].Block->SetActorLocation(Pos);
}

void AMapBase::CreateBush(FPoint _Point, std::string_view _ImgName)
{
	TileInfo[_Point.Y][_Point.X].Bush = GetWorld()->SpawnActor<ABushBase>("Bush");

	TileInfo[_Point.Y][_Point.X].Bush->GetBody()->SetSprite(_ImgName);
	TileInfo[_Point.Y][_Point.X].Bush->GetBody()->SetOrder(Const::MaxOrder - _Point.Y);

	FVector Pos = StartPos;
	Pos.X += _Point.X * BlockSize;
	Pos.Y += _Point.Y * BlockSize;
	TileInfo[_Point.Y][_Point.X].Bush->SetActorLocation(Pos);
}

void AMapBase::CreateHollowWall(FPoint _Point)
{
	TileInfo[_Point.Y][_Point.X].Block = GetWorld()->SpawnActor<AWall>("Hollow_Wall").get();
	TileInfo[_Point.Y][_Point.X].Block->GetBody()->SetActive(false);

	FVector Pos = StartPos;
	Pos.X += _Point.X * BlockSize;
	Pos.Y += _Point.Y * BlockSize;
	TileInfo[_Point.Y][_Point.X].Block->SetActorLocation(Pos);
}

void AMapBase::CreateItem(FPoint _Point, EItemType _ItemType)
{
	if (false == MapRangeCheckByPoint(_Point) || EItemType::None == _ItemType)
	{
		return;
	}

	TileInfo[_Point.Y][_Point.X].Item = GetWorld()->SpawnActor<AItemBase>("Item");

	FVector Pos = StartPos;
	Pos.X += (_Point.X * BlockSize) + (0.5f * BlockSize);
	Pos.Y += (_Point.Y * BlockSize) + (0.5f * BlockSize);
	TileInfo[_Point.Y][_Point.X].Item->SetActorLocation(Pos);
	TileInfo[_Point.Y][_Point.X].Item->SetItem(_ItemType);
}