#pragma once
#include <EnginePlatform/EngineResources.h>

#include <vector>
#include "EngineTexture.h"
#include "EngineStruct.h"

// 설명 :
class UEngineSprite : public UEngineResources<UEngineSprite>
{
public:
	// constrcuter destructer
	UEngineSprite();
	~UEngineSprite();

	// delete Function
	UEngineSprite(const UEngineSprite& _Other) = delete;
	UEngineSprite(UEngineSprite&& _Other) noexcept = delete;
	UEngineSprite& operator=(const UEngineSprite& _Other) = delete;
	UEngineSprite& operator=(UEngineSprite&& _Other) noexcept = delete;

	static std::shared_ptr<UEngineSprite> Load(std::string_view _Path)
	{
		UEnginePath NewPath = UEnginePath(std::filesystem::path(_Path));
		std::string FileName = NewPath.GetFileName();
		return Load(_Path, FileName);
	}

	static std::shared_ptr<UEngineSprite> Load(std::string_view _Path, std::string_view _Name)
	{
		std::shared_ptr<UEngineSprite> NewRes = CreateResName(_Path, _Name);
		NewRes->ResLoad();
		return NewRes;
	}

	static std::shared_ptr<UEngineSprite> LoadFolder(std::string_view _Path)
	{
		UEnginePath NewPath = UEnginePath(std::filesystem::path(_Path));
		std::string FileName = NewPath.GetFileName();

		std::shared_ptr<UEngineSprite> NewRes = CreateResName(_Path, FileName);
		NewRes->ResLoadFolder();
		return NewRes;
	}



	static std::shared_ptr<UEngineSprite> ThreadSafeLoad(std::string_view _Path)
	{
		UEnginePath NewPath = UEnginePath(std::filesystem::path(_Path));
		std::string FileName = NewPath.GetFileName();
		return ThreadSafeLoad(_Path, FileName);
	}

	static std::shared_ptr<UEngineSprite> ThreadSafeLoad(std::string_view _Path, std::string_view _Name)
	{
		std::shared_ptr<UEngineSprite> NewRes = ThreadSafeCreateResName(_Path, _Name);
		NewRes->ThreadSafeResLoad();
		return NewRes;
	}

	static std::shared_ptr<UEngineSprite> ThreadSafeLoadFolder(std::string_view _Path)
	{
		UEnginePath NewPath = UEnginePath(std::filesystem::path(_Path));
		std::string FileName = NewPath.GetFileName();

		std::shared_ptr<UEngineSprite> NewRes = ThreadSafeCreateResName(_Path, FileName);
		NewRes->ThreadSafeResLoadFolder();
		return NewRes;
	}



	static std::shared_ptr<UEngineSprite> CreateCutting(std::string_view _Name, UINT _X, UINT _Y)
	{
		std::shared_ptr<UEngineSprite> FindSprite = FindRes(_Name);
		std::shared_ptr<UEngineTexture> Texture = nullptr;

		if (nullptr == FindSprite)
		{
			Texture = UEngineTexture::FindRes(_Name);

			if (nullptr == Texture)
			{
				MsgBoxAssert("로드되지 않은 텍스처를 스프라이트로 만들어서 컷팅할수 없습니다." + std::string(_Name));
				return nullptr;
			}

			FindSprite = CreateResName(Texture->GetPath(), Texture->GetName());
		}
		else {
			FSpriteInfo Info = FindSprite->GetSpriteInfo(0);
			Texture = Info.Texture;
		}

		FindSprite->Cutting(Texture, _X, _Y);
		return FindSprite;
	}

	size_t GetInfoSize()
	{
		return Infos.size();
	}

	FSpriteInfo GetSpriteInfo(UINT _Index)
	{
		return Infos[_Index];
	}

	void Cutting(std::shared_ptr<UEngineTexture> Texture, UINT _X, UINT _Y);

protected:

private:
	std::vector<FSpriteInfo> Infos;

	void ResLoad();
	void ResLoadFolder();

	void ThreadSafeResLoad();
	void ThreadSafeResLoadFolder();
};

