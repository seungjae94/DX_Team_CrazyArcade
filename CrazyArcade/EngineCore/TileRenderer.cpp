#include "PreCompile.h"
#include "TileRenderer.h"
#include "SpriteRenderer.h"
#include "EngineShaderResources.h"
#include "EngineSprite.h"

UTileRenderer::UTileRenderer() 
{
	SetMesh("Rect");
	SetMaterial("2DImage");
}

UTileRenderer::~UTileRenderer() 
{
}

void UTileRenderer::BeginPlay()
{
	Super::BeginPlay();
	Resources->SettingConstantBuffer("ResultColorValue", ColorData);
	Resources->SettingConstantBuffer("FCuttingData", CuttingDataValue);
	Resources->SettingConstantBuffer("FVertexUV", VertexUVValue);
}

void UTileRenderer::CreateTileMap(std::string_view _TileSet, float4 _TileSize, int _X, int _Y, int _DefaultIndex)
{
	// 오로지 랜더링적 요소만 가진것.

	TileSprite = UEngineSprite::FindRes(_TileSet);

	TileSize = _TileSize;

	if (nullptr == TileSprite)
	{
		MsgBoxAssert("존재하지 않는 스프라이트로 타일맵을 만들려고 했습니다.");
		return;
	}

	FSpriteInfo Info = TileSprite->GetSpriteInfo(0);

	Resources->SettingTexture("Image", Info.Texture, "POINT");

	Tiles.resize(_Y);
	for (size_t i = 0; i < Tiles.size(); i++)
	{
		Tiles[i].resize(_X);
	}

	SetAllTile(_DefaultIndex);
}

void UTileRenderer::SetAllTile(int _Index)
{
	for (size_t y = 0; y < Tiles.size(); y++)
	{
		for (size_t x = 0; x < Tiles[y].size(); x++)
		{
			Tiles[y][x] = _Index;
		}
	}
}

float4 UTileRenderer::ConvertTileIndex(float4 _WorldXY)
{
	_WorldXY.X /= TileSize.X;
	_WorldXY.Y /= TileSize.Y;
	return _WorldXY;
}

void UTileRenderer::SetTile(float4 _WorldXY, int _Index)
{
	_WorldXY.X /= TileSize.X;
	_WorldXY.Y /= TileSize.Y;

	SetTile(_WorldXY.iX(), _WorldXY.iY(), _Index);
}

void UTileRenderer::SetTile(int _X, int _Y, int _Index)
{
	if (0 > _Y)
	{
		return;
	}

	if (0 > _X)
	{
		return;
	}

	if (Tiles.size() <= _Y)
	{
		return;
	}

	if (Tiles[0].size() <= _X)
	{
		return;
	}

	Tiles[_Y][_X] = _Index;
}

bool UTileRenderer::Render(float _DeltaTime)
{
	RenderingSetting();

	float4 StartPos = {0,0};

	for (size_t y = 0; y < Tiles.size(); y++)
	{
		for (size_t x = 0; x < Tiles[y].size(); x++)
		{
			FSpriteInfo Info = TileSprite->GetSpriteInfo(Tiles[y][x]);

			CuttingDataValue.CuttingPosition = Info.CuttingPosition;
			CuttingDataValue.CuttingSize = Info.CuttingSize;

			float4 CurPos = { TileSize.X* x, TileSize.Y* y };
			CurPos += TileSize.Half2D();

			Transform.SetPosition(StartPos + CurPos);
			Transform.SetScale(TileSize);

			Resources->SettingAllShaderResources();

			GetMesh()->IndexedDraw();
		}
	}

	return true;
}

