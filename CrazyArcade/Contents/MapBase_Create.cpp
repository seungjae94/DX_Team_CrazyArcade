#include "PreCompile.h"
#include "MapBase.h"

#include "MapConstant.h"
#include "BlockBase.h"
#include "ItemBase.h"
#include "MoveBox.h"
#include "Wall.h"
#include "Box.h"

void AMapBase::CreateWall(FPoint _Point, std::string_view _ImgName)
{
	TileInfo[_Point.Y][_Point.X].Block = GetWorld()->SpawnActor<AWall>("Wall");
	TileInfo[_Point.Y][_Point.X].Block->SetBlockImg(_ImgName);
	TileInfo[_Point.Y][_Point.X].Block->GetBody()->SetOrder(Const::MaxOrder - _Point.Y);

	FVector Pos = StartPos;
	Pos.X += _Point.X * BlockSize;
	Pos.Y += _Point.Y * BlockSize;
	TileInfo[_Point.Y][_Point.X].Block->SetActorLocation(Pos);
}

void AMapBase::CreateBox(FPoint _Point, std::string_view _ImgName)
{
	TileInfo[_Point.Y][_Point.X].Block = GetWorld()->SpawnActor<ABox>("Box");

	TileInfo[_Point.Y][_Point.X].Block->GetBody()->CreateAnimation(MapAnim::block_idle, _ImgName, 0.1f, false, 0, 0);
	TileInfo[_Point.Y][_Point.X].Block->GetBody()->CreateAnimation(MapAnim::block_destroy, _ImgName, 0.1f, false);
	TileInfo[_Point.Y][_Point.X].Block->GetBody()->ChangeAnimation(MapAnim::block_idle);
	TileInfo[_Point.Y][_Point.X].Block->GetBody()->SetOrder(Const::MaxOrder - _Point.Y);

	FVector Pos = StartPos;
	Pos.X += _Point.X * BlockSize;
	Pos.Y += _Point.Y * BlockSize;
	TileInfo[_Point.Y][_Point.X].Block->SetActorLocation(Pos);
}

void AMapBase::CreateMoveBox(FPoint _Point, std::string_view _ImgName)
{
	TileInfo[_Point.Y][_Point.X].Block = GetWorld()->SpawnActor<AMoveBox>("MoveBox");

	TileInfo[_Point.Y][_Point.X].Block->GetBody()->CreateAnimation(MapAnim::block_idle, _ImgName, 0.1f, false, 0, 0);
	TileInfo[_Point.Y][_Point.X].Block->GetBody()->CreateAnimation(MapAnim::block_destroy, _ImgName, 0.1f, false);
	TileInfo[_Point.Y][_Point.X].Block->GetBody()->ChangeAnimation(MapAnim::block_idle);
	TileInfo[_Point.Y][_Point.X].Block->GetBody()->SetOrder(Const::MaxOrder - _Point.Y);

	FVector Pos = StartPos;
	Pos.X += _Point.X * BlockSize;
	Pos.Y += _Point.Y * BlockSize;
	TileInfo[_Point.Y][_Point.X].Block->SetActorLocation(Pos);
}

void AMapBase::CreateItem(FPoint _Point, EItemType _ItemType)
{
	TileInfo[_Point.Y][_Point.X].Item = GetWorld()->SpawnActor<AItemBase>("Item");

	FVector Pos = StartPos;
	Pos.X += (_Point.X * BlockSize) + (0.5f * BlockSize);
	Pos.Y += (_Point.Y * BlockSize) + (0.5f * BlockSize);
	TileInfo[_Point.Y][_Point.X].Item->SetActorLocation(Pos);

	TileInfo[_Point.Y][_Point.X].Item->SetItem(_ItemType);
}