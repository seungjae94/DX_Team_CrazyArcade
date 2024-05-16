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
	MapInfo[_Point.Y][_Point.X].Block = GetWorld()->SpawnActor<AWall>("Wall");
	MapInfo[_Point.Y][_Point.X].Block->SetBlockImg(_ImgName);
	MapInfo[_Point.Y][_Point.X].Block->GetBody()->SetOrder(Const::MaxOrder - _Point.Y);

	FVector Pos = StartPos;
	Pos.X += _Point.X * BlockSize;
	Pos.Y += _Point.Y * BlockSize;
	MapInfo[_Point.Y][_Point.X].Block->SetActorLocation(Pos);
}

void AMapBase::CreateBox(FPoint _Point, std::string_view _ImgName)
{
	MapInfo[_Point.Y][_Point.X].Block = GetWorld()->SpawnActor<ABox>("Box");

	MapInfo[_Point.Y][_Point.X].Block->GetBody()->CreateAnimation(MapAnim::block_idle, _ImgName, 0.1f, false, 0, 0);
	MapInfo[_Point.Y][_Point.X].Block->GetBody()->CreateAnimation(MapAnim::block_destroy, _ImgName, 0.1f, false);
	MapInfo[_Point.Y][_Point.X].Block->GetBody()->ChangeAnimation(MapAnim::block_idle);
	MapInfo[_Point.Y][_Point.X].Block->GetBody()->SetOrder(Const::MaxOrder - _Point.Y);

	FVector Pos = StartPos;
	Pos.X += _Point.X * BlockSize;
	Pos.Y += _Point.Y * BlockSize;
	MapInfo[_Point.Y][_Point.X].Block->SetActorLocation(Pos);
}

void AMapBase::CreateMoveBox(FPoint _Point, std::string_view _ImgName)
{
	MapInfo[_Point.Y][_Point.X].Block = GetWorld()->SpawnActor<AMoveBox>("MoveBox");

	MapInfo[_Point.Y][_Point.X].Block->GetBody()->CreateAnimation(MapAnim::block_idle, _ImgName, 0.1f, false, 0, 0);
	MapInfo[_Point.Y][_Point.X].Block->GetBody()->CreateAnimation(MapAnim::block_destroy, _ImgName, 0.1f, false);
	MapInfo[_Point.Y][_Point.X].Block->GetBody()->ChangeAnimation(MapAnim::block_idle);
	MapInfo[_Point.Y][_Point.X].Block->GetBody()->SetOrder(Const::MaxOrder - _Point.Y);

	FVector Pos = StartPos;
	Pos.X += _Point.X * BlockSize;
	Pos.Y += _Point.Y * BlockSize;
	MapInfo[_Point.Y][_Point.X].Block->SetActorLocation(Pos);
}

void AMapBase::CreateItem(FPoint _Point, EPlayerItem _ItemType)
{
	MapInfo[_Point.Y][_Point.X].Item = GetWorld()->SpawnActor<AItemBase>("Item");
	MapInfo[_Point.Y][_Point.X].Item->SetItem(_ItemType);

	FVector Pos = StartPos;
	Pos.X += (_Point.X * BlockSize) + (0.5f * BlockSize);
	Pos.Y += (_Point.Y * BlockSize) + (0.5f * BlockSize);
	MapInfo[_Point.Y][_Point.X].Item->SetActorLocation(Pos);
}