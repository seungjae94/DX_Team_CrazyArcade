#include "PreCompile.h"
#include "EngineSprite.h"

UEngineSprite::UEngineSprite() 
{
}

UEngineSprite::~UEngineSprite() 
{
}


void UEngineSprite::ResLoad()
{
	FSpriteInfo TextureInfo;

	std::shared_ptr<UEngineTexture> Texture = UEngineTexture::FindRes(GetName());

	if (nullptr == Texture)
	{
		Texture = UEngineTexture::Load(GetPath());
	}

	TextureInfo.Texture = Texture;

	Infos.push_back(TextureInfo);
}

void UEngineSprite::ResLoadFolder()
{
	UEngineDirectory Dir = GetEnginePath();

	std::vector<UEngineFile> Files = Dir.GetAllFile({".png", ".jpg", ".jpeg", ".gif", ".bmp" });

	for (size_t i = 0; i < Files.size(); i++)
	{
		std::string FileName = Files[i].GetFileName();

		std::shared_ptr<UEngineTexture> Texture = UEngineTexture::FindRes(FileName);

		if (nullptr == Texture)
		{
			Texture = UEngineTexture::Load(Files[i].GetFullPath());
		}
		FSpriteInfo TextureInfo;
		TextureInfo.Texture = Texture;
		Infos.push_back(TextureInfo);
	}
}


void UEngineSprite::ThreadSafeResLoad()
{
	FSpriteInfo TextureInfo;

	std::shared_ptr<UEngineTexture> Texture = UEngineTexture::FindRes(GetName());

	if (nullptr == Texture)
	{
		Texture = UEngineTexture::ThreadSafeLoad(GetPath());
	}

	TextureInfo.Texture = Texture;

	Infos.push_back(TextureInfo);
}

void UEngineSprite::ThreadSafeResLoadFolder()
{
	UEngineDirectory Dir = GetEnginePath();

	std::vector<UEngineFile> Files = Dir.GetAllFile({ ".png", ".jpg", ".jpeg", ".gif", ".bmp" });

	for (size_t i = 0; i < Files.size(); i++)
	{
		std::string FileName = Files[i].GetFileName();

		std::shared_ptr<UEngineTexture> Texture = UEngineTexture::FindRes(FileName);

		if (nullptr == Texture)
		{
			Texture = UEngineTexture::ThreadSafeLoad(Files[i].GetFullPath());
		}
		FSpriteInfo TextureInfo;
		TextureInfo.Texture = Texture;
		Infos.push_back(TextureInfo);
	}
}

void UEngineSprite::Cutting(std::shared_ptr<UEngineTexture> Texture, UINT _X, UINT _Y)
{
	Infos.clear();
	float4 Position = float4::Zero;
	float4 Size = { 1.0f / static_cast<float>(_X), 1.0f / static_cast<float>(_Y) };

	for (size_t y = 0; y < _Y; y++)
	{
		for (size_t x = 0; x < _X; x++)
		{
			FSpriteInfo TextureInfo;
			TextureInfo.CuttingPosition = Position;
			TextureInfo.CuttingSize = Size;
			TextureInfo.Texture = Texture;
			Position.X += Size.X;
			Infos.push_back(TextureInfo);
		}

		Position.X = 0.0f;
		Position.Y += Size.Y;
	}
}