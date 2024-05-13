#pragma once
#include <map>
#include <string>
#include <memory>
#include <list>

#include <EngineBase/EngineString.h>
#include <EnginePlatform/EngineResources.h>

// #include나 이런걸 사용하더라도 실제로 그 코드가 실행되지 않으면
// 컴파일러가 무시한다.
#include "ThirdParty\DirectXTex\inc\DirectXTex.h"


#include "EngineSampler.h"

class UEngineTextureSetter;
class UEngineTexture : public UEngineResources<UEngineTexture>
{
public:
	friend UEngineTextureSetter;
	// constrcuter destructer
	UEngineTexture();
	~UEngineTexture();

	// delete Function
	UEngineTexture(const UEngineTexture& _Other) = delete;
	UEngineTexture(UEngineTexture&& _Other) noexcept = delete;
	UEngineTexture& operator=(const UEngineTexture& _Other) = delete;
	UEngineTexture& operator=(UEngineTexture&& _Other) noexcept = delete;

	static std::shared_ptr<UEngineTexture> Create(ID3D11Texture2D* _Texture)
	{
		std::shared_ptr<UEngineTexture> NewRes = CreateResUnName();
		NewRes->ResCreate(_Texture);
		return NewRes;
	}

	static std::shared_ptr<UEngineTexture> Create(const D3D11_TEXTURE2D_DESC& _Desc)
	{
		std::shared_ptr<UEngineTexture> NewRes = CreateResUnName();
		NewRes->ResCreate(_Desc);
		return NewRes;
	}

	static std::shared_ptr<UEngineTexture> Load(std::string_view _Path)
	{
		UEnginePath NewPath = UEnginePath(std::filesystem::path(_Path));
		std::string FileName = NewPath.GetFileName();
		return Load(_Path, FileName);
	}

	static std::shared_ptr<UEngineTexture> Load(std::string_view _Path, std::string_view _Name)
	{
		std::shared_ptr<UEngineTexture> NewRes = CreateResName(_Path, _Name);
		NewRes->ResLoad();
		return NewRes;
	}

	///

	static std::shared_ptr<UEngineTexture> ThreadSafeCreate(ID3D11Texture2D* _Texture)
	{
		std::shared_ptr<UEngineTexture> NewRes = ThreadSafeCreateResUnName();
		NewRes->ResCreate(_Texture);
		return NewRes;
	}

	static std::shared_ptr<UEngineTexture> ThreadSafeCreate(const D3D11_TEXTURE2D_DESC& _Desc)
	{
		std::shared_ptr<UEngineTexture> NewRes = ThreadSafeCreateResUnName();
		NewRes->ResCreate(_Desc);
		return NewRes;
	}

	static std::shared_ptr<UEngineTexture> ThreadSafeLoad(std::string_view _Path)
	{
		UEnginePath NewPath = UEnginePath(std::filesystem::path(_Path));
		std::string FileName = NewPath.GetFileName();
		return ThreadSafeLoad(_Path, FileName);
	}

	static std::shared_ptr<UEngineTexture> ThreadSafeLoad(std::string_view _Path, std::string_view _Name)
	{
		std::shared_ptr<UEngineTexture> NewRes = ThreadSafeCreateResName(_Path, _Name);
		NewRes->ResLoad();
		return NewRes;
	}


	ID3D11RenderTargetView* GetRTV()
	{
		return RTV;
	}

	ID3D11ShaderResourceView* GetSRV()
	{
		return SRV;
	}

	float4 GetScale()
	{
		return float4(Desc.Width, Desc.Height);
	}

	// float 자체가 오차의 자료형
	// 대략적인 값 실수오차는 무조건 발생한다.

	// float4 GetColor(unsigned)

	// Color8Bit _DefaultColor => 화면 바깥에 있는 컬러를 가져와 달라고 하면  _DefaultColor가 리턴된다.

	Color8Bit GetColor(float4 _Pos, Color8Bit _DefaultColor)
	{
		return GetColor(_Pos.iX(), _Pos.iY(), _DefaultColor);
	}

	Color8Bit GetColor(unsigned int _X, unsigned int _Y, Color8Bit _DefaultColor);

protected:


private:

	// 이미지 그 자체.
	// Directx에서는 메모리를 의미하는 핸들
	// 그리고 그런 메모리가 있어야 메모리 수정권한
	ID3D11Texture2D* Texture2D = nullptr;

	// Directx에서는 이미지(메모리) 수정 권한(여기에 그릴수 있는 권한)
	ID3D11RenderTargetView* RTV = nullptr;
	// directx에서 이미지를 쉐이더에 세팅할수 있는 권한.
	ID3D11ShaderResourceView* SRV = nullptr;

	D3D11_TEXTURE2D_DESC Desc;

	DirectX::TexMetadata Data;
	DirectX::ScratchImage Image;

	std::shared_ptr<UEngineSampler> Sampler;

	void ResCreate(const D3D11_TEXTURE2D_DESC& _Desc);

	void ResCreate(ID3D11Texture2D* _Texture);

	void ResLoad();

	void CreateRenderTargetView();
	void CreateShaderResourceView();

	void Setting(EShaderType _Type, UINT _Slot);
	void Reset(EShaderType _Type, UINT _Slot);
};

