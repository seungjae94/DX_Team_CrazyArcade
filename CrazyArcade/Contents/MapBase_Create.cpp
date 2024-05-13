#include "PreCompile.h"
#include "MapBase.h"
#include "BlockBase.h"

void AMapBase::CreateWall(int _X, int _Y, std::string_view _ImgName)
{
	MapInfo[_Y][_X] = GetWorld()->SpawnActor<ABlockBase>("Wall");
	MapInfo[_Y][_X]->SetBlockType(EBlockType::Wall);
	MapInfo[_Y][_X]->SetBlockImg(_ImgName);

	FVector Pos = StartPos;
	Pos.X += _X * BlockSize;
	Pos.Y += _Y * BlockSize;
	MapInfo[_Y][_X]->SetActorLocation(Pos);
}