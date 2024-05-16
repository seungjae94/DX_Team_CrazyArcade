#include "PreCompile.h"
#include "MapBase.h"

#include "MapConstant.h"
#include "BlockBase.h"
#include "Wall.h"
#include "Box.h"
#include "MoveBox.h"

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
	Pos.X += _Point.Y * BlockSize;
	Pos.Y += _Point.Y * BlockSize;
	MapInfo[_Point.Y][_Point.X].Block->SetActorLocation(Pos);
}

void AMapBase::CreateItem(EPlayerItem _ItemType)
{
}