#include "PreCompile.h"
#include "MapBase.h"

#include "BlockBase.h"
#include "Wall.h"

void AMapBase::CreateWall(int _X, int _Y, std::string_view _ImgName)
{
	MapInfo[_Y][_X] = GetWorld()->SpawnActor<AWall>("Wall");
	MapInfo[_Y][_X]->SetBlockImg(_ImgName);

	FVector Pos = StartPos;
	Pos.X += _X * BlockSize;
	Pos.Y += _Y * BlockSize;
	MapInfo[_Y][_X]->SetActorLocation(Pos);
}