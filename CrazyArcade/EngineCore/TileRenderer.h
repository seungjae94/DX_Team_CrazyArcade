#pragma once
#include "Renderer.h"
#include "EngineEnums.h"
#include "EngineSprite.h"
#include "EngineStruct.h"

// Ό³Έν :
class UTileRenderer : public URenderer
{
public:
	GENERATED_BODY(URenderer)
	// constrcuter destructer
	UTileRenderer();
	~UTileRenderer();

	// delete Function
	UTileRenderer(const UTileRenderer& _Other) = delete;
	UTileRenderer(UTileRenderer&& _Other) noexcept = delete;
	UTileRenderer& operator=(const UTileRenderer& _Other) = delete;
	UTileRenderer& operator=(UTileRenderer&& _Other) noexcept = delete;

	void CreateTileMap(std::string_view _TileSetSprite, float4 _TileSize, int _X, int _Y, int _DefaultIndex);

	float4 ConvertTileIndex(float4 _WorldXY);

	void SetTile(float4 _WorldXY, int _Index);

	void SetTile(int _X, int _Y, int _Index);

	void SetAllTile(int _Index);

	std::vector<std::vector<int>> GetTileMapData()
	{
		return Tiles;
	}

protected:
	void BeginPlay() override;
	bool Render(float _DeltaTime) override;

	std::vector<std::vector<int>> Tiles;
	FResultColorValue ColorData;
	FCuttingData CuttingDataValue;
	std::shared_ptr<UEngineSprite> TileSprite;
	float4 TileSize = {64, 64};
	FVertexUV VertexUVValue;
};

