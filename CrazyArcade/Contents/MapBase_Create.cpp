#include "PreCompile.h"
#include "MapBase.h"

#include "MapConstant.h"
#include "BlockBase.h"
#include "Wall.h"
#include "Box.h"
#include "MoveBox.h"

void AMapBase::CreateWall(int _X, int _Y, std::string_view _ImgName)
{
	MapInfo[_Y][_X].Block = GetWorld()->SpawnActor<AWall>("Wall");
	MapInfo[_Y][_X].Block->SetBlockImg(_ImgName);
	//MapInfo[_Y][_X].Block->GetBody()->SetOrder(-_Y);

	FVector Pos = StartPos;
	Pos.X += _X * BlockSize;
	Pos.Y += _Y * BlockSize;
	MapInfo[_Y][_X].Block->SetActorLocation(Pos);
}

void AMapBase::CreateBox(int _X, int _Y, std::string_view _ImgName)
{
	MapInfo[_Y][_X].Block = GetWorld()->SpawnActor<ABox>("Box");

	MapInfo[_Y][_X].Block->GetBody()->CreateAnimation(MapAnim::block_idle, _ImgName, 0.1f, false, 0, 0);
	MapInfo[_Y][_X].Block->GetBody()->CreateAnimation(MapAnim::block_destroy, _ImgName, 0.1f, false);
	MapInfo[_Y][_X].Block->GetBody()->ChangeAnimation(MapAnim::block_idle);
	//MapInfo[_Y][_X].Block->GetBody()->SetOrder(-_Y);

	FVector Pos = StartPos;
	Pos.X += _X * BlockSize;
	Pos.Y += _Y * BlockSize;
	MapInfo[_Y][_X].Block->SetActorLocation(Pos);
}

void AMapBase::CreateMoveBox(int _X, int _Y, std::string_view _ImgName)
{
	MapInfo[_Y][_X].Block = GetWorld()->SpawnActor<AMoveBox>("MoveBox");

	MapInfo[_Y][_X].Block->GetBody()->CreateAnimation(MapAnim::block_idle, _ImgName, 0.1f, false, 0, 0);
	MapInfo[_Y][_X].Block->GetBody()->CreateAnimation(MapAnim::block_destroy, _ImgName, 0.1f, false);
	MapInfo[_Y][_X].Block->GetBody()->ChangeAnimation(MapAnim::block_idle);
	//MapInfo[_Y][_X].Block->GetBody()->SetOrder(-_Y);

	FVector Pos = StartPos;
	Pos.X += _X * BlockSize;
	Pos.Y += _Y * BlockSize;
	MapInfo[_Y][_X].Block->SetActorLocation(Pos);
}
