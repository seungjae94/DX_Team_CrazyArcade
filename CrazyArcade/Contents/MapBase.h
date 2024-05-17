#pragma once
#include "MapHelper.h"

class ABlockBase;
class ABombBase;
class AItemBase;
class UTileInfo;
class APlayer;
class AWave;
class ABox;

// Tile 정보
class UTileInfo
{
public:
	std::shared_ptr<ABlockBase> Block = nullptr;
	std::shared_ptr<AItemBase> Item = nullptr;
	std::shared_ptr<ABombBase> Bomb = nullptr;
};

// 설명 : Map 기초 클래스
class AMapBase : public AActor
{
	GENERATED_BODY(AActor)

	friend ABombBase;
	friend AWave;
public:
	// constrcuter destructer
	AMapBase();
	~AMapBase();

	// delete Function
	AMapBase(const AMapBase& _Other) = delete;
	AMapBase(AMapBase&& _Other) noexcept = delete;
	AMapBase& operator=(const AMapBase& _Other) = delete;
	AMapBase& operator=(AMapBase&& _Other) noexcept = delete;

	static int GetRenderOrder(const FVector& _Pos);
	static FPoint ConvertLocationToPoint(const FVector& _Pos);
	static FVector ConvertPointToLocation(const FPoint& _Point);
	
	bool CanMovePos(const FVector& _NextPos, const FVector& _Dir);
	EItemType IsItemTile(const FVector& _Pos);
	ABombBase* SpawnBomb(const FVector& _Pos, APlayer* _Player);
	
	// Tile의 한변의 길이를 반환
	static float GetBlockSize()
	{
		return BlockSize;
	}

	// 해당 좌표 Tile의 블록을 반환
	std::shared_ptr<ABlockBase> GetMapBlock(FPoint _Point) const
	{
		return TileInfo[_Point.Y][_Point.X].Block;
	}

	// 해당 좌표 Tile에 블록을 설정
	void SetMapBlock(FPoint _Point, std::shared_ptr<ABlockBase> _Block)
	{
		TileInfo[_Point.Y][_Point.X].Block = _Block;
	}

protected:
	inline void SetBackGround(std::string_view _Name)
	{
		BackGround->SetSprite(_Name);
	}

	void SetMapInfoSize(int _SizeX, int _SizeY);
	void CreateWall(FPoint _Point, std::string_view _ImgName);
	void CreateBox(FPoint _Point, std::string_view _ImgName);
	void CreateMoveBox(FPoint _Point, std::string_view _ImgName);
	void CreateItem(FPoint _Point, EItemType _ItemType);

private:
	// 해당 좌표의 Tile 정보의 참조를 반환
	UTileInfo& GetTileInfo(FPoint _Point)
	{
		return TileInfo[_Point.Y][_Point.X];
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelEnd(ULevel* _NextLevel) override;

private:
	USpriteRenderer* BackGround = nullptr;
	USpriteRenderer* PlayUI_BackGround = nullptr;

	std::vector<std::vector<UTileInfo>> TileInfo;

	static FVector StartPos;
	static float BlockSize;
	int SizeX = 0;
	int SizeY = 0;

	static float BombAdjustPosY;

};

