#include "PreCompile.h"
#include "MapBase.h"

#include "MapConstant.h"
#include "BlockBase.h"
#include "Wall.h"
#include "Box.h"

void AMapBase::CreateWall(int _X, int _Y, std::string_view _ImgName)
{
	MapInfo[_Y][_X] = GetWorld()->SpawnActor<AWall>("Wall");
	MapInfo[_Y][_X]->SetBlockImg(_ImgName);

	FVector Pos = StartPos;
	Pos.X += _X * BlockSize;
	Pos.Y += _Y * BlockSize;
	MapInfo[_Y][_X]->SetActorLocation(Pos);
}

std::shared_ptr<ABox> AMapBase::CreateBox(int _X, int _Y, std::string_view _ImgName)
{
	std::shared_ptr<ABox> NewBlock = GetWorld()->SpawnActor<ABox>("Box");
	MapInfo[_Y][_X] = NewBlock;

	MapInfo[_Y][_X]->GetBody()->CreateAnimation(MapAnim::block_idle, _ImgName, 0.1f, false, 0, 0);
	MapInfo[_Y][_X]->GetBody()->CreateAnimation(MapAnim::block_destroy, _ImgName, 0.1f, false);
	MapInfo[_Y][_X]->GetBody()->ChangeAnimation(MapAnim::block_idle);

	FVector Pos = StartPos;
	Pos.X += _X * BlockSize;
	Pos.Y += _Y * BlockSize;
	MapInfo[_Y][_X]->SetActorLocation(Pos);

	return NewBlock;
}
