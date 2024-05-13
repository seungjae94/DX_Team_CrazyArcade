#include "PreCompile.h"
#include "EngineTexture.h"
#include "EngineCore.h"

// 라이브러리가 release거나 debug거나 이름이 같아서
// 굳이 #ifdef _DEBUG로 구분할 필요가 없다.
#pragma comment (lib, "DirectXTex.lib")

UEngineTexture::UEngineTexture()
{
}

UEngineTexture::~UEngineTexture()
{
	if (nullptr != SRV)
	{
		SRV->Release();
	}

	if (nullptr != RTV)
	{
		RTV->Release();
	}

	if (nullptr != Texture2D)
	{
		Texture2D->Release();
	}
}

void UEngineTexture::ResCreate(const D3D11_TEXTURE2D_DESC& _Desc)
{
	Desc = _Desc;

	GEngine->GetDirectXDevice()->CreateTexture2D(&Desc, nullptr, &Texture2D);

	if (Desc.BindFlags & D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET)
	{
		CreateRenderTargetView();
	}
	if (Desc.BindFlags & D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET)
	{
		CreateShaderResourceView();
	}
}

void UEngineTexture::ResCreate(ID3D11Texture2D* _Texture)
{
	Texture2D = _Texture;

	Texture2D->GetDesc(&Desc);

	CreateRenderTargetView();
}

void UEngineTexture::CreateShaderResourceView()
{
	if (nullptr != SRV)
	{
		return;
	}

	if (nullptr == Texture2D)
	{
		MsgBoxAssert("만들어지지 않은 텍스처로 랜더타겟뷰를 생성하려고 했습니다.");
		return;
	}

	// 이제 텍스처 메모리에서 이미지를 수정할수 있는 권한을 만든다
	// 다이렉트에서 뭔가를 하려면 근본적으로 2가지 관련되어 있습니다.
	// 메모리 => Device
	// 랜더링 => Context
	HRESULT Result = GEngine->GetDirectXDevice()->CreateShaderResourceView(Texture2D, nullptr, &SRV);

	if (S_OK != Result)
	{
		MsgBoxAssert("쉐이더 리소스 뷰 생성에 실패했습니다.");
		return;
	}
}

void UEngineTexture::CreateRenderTargetView()
{
	if (nullptr != RTV)
	{
		return;
	}

	if (nullptr == Texture2D)
	{
		MsgBoxAssert("만들어지지 않은 텍스처로 랜더타겟뷰를 생성하려고 했습니다.");
		return;
	}

	// 이제 텍스처 메모리에서 이미지를 수정할수 있는 권한을 만든다
	// 다이렉트에서 뭔가를 하려면 근본적으로 2가지 관련되어 있습니다.
	// 메모리 => Device
	// 랜더링 => Context
	HRESULT Result = GEngine->GetDirectXDevice()->CreateRenderTargetView(Texture2D, nullptr, &RTV);

	if (S_OK != Result)
	{
		MsgBoxAssert("랜더타겟 뷰 생성에 실패했습니다.");
		return;
	}
}

void UEngineTexture::ResLoad()
{
	// 8196 정도였나?
	// 너무 크면 안될수도 있다.
	UEnginePath File = GetEnginePath();

	std::string Ext = UEngineString::ToUpper(File.GetExtension());

	std::wstring wPath = UEngineString::AnsiToUniCode(File.GetFullPath());

	if (Ext == ".DDS")
	{
		// Image 이미지 로딩 결과물
		if (S_OK != DirectX::LoadFromDDSFile(wPath.c_str(), DirectX::DDS_FLAGS_NONE, &Data, Image))
		{
			MsgBoxAssert("DDS 파일로드에 실패했습니다.");
		};
	}
	else if (Ext == ".TGA")
	{
		if (S_OK != DirectX::LoadFromTGAFile(wPath.c_str(), DirectX::TGA_FLAGS_NONE, &Data, Image))
		{
			MsgBoxAssert("TGA 파일로드에 실패했습니다.");
		};
	}
	else
	{
		// Png jpg 등등이 else
		if (S_OK != DirectX::LoadFromWICFile(wPath.c_str(), DirectX::WIC_FLAGS_NONE, &Data, Image))
		{
			MsgBoxAssert("PNG 파일로드에 실패했습니다.");
		};
	}

	// HRESULT Result = GEngine->GetDirectXDevice()->CreateShaderResourceView(Texture2D, nullptr, &SRV);

	// 마소 사람이 만들어준 전역 함수로 자신이 로드한 데이터를 가지고 쉐이더 리소스 뷰를 만들수 있게 처리해 놨습니다.
	// DirectX::CreateShaderResourceView 
	if (S_OK != DirectX::CreateShaderResourceView(
		GEngine->GetDirectXDevice(),
		Image.GetImages(),
		Image.GetImageCount(),
		Image.GetMetadata(),
		&SRV
	))
	{
		MsgBoxAssert("텍스처 쉐이더 세팅권한 생성에 실패했습니다" + GetName());
		return;
	}

	Desc.Width = static_cast<UINT>(Data.width);
	Desc.Height = static_cast<UINT>(Data.height);

}

void UEngineTexture::Setting(EShaderType _Type, UINT _Slot)
{
	switch (_Type)
	{
	case EShaderType::Vertex:
		GEngine->GetDirectXContext()->VSSetShaderResources(_Slot, 1, &SRV);
		break;
	case EShaderType::Pixel:
		GEngine->GetDirectXContext()->PSSetShaderResources(_Slot, 1, &SRV);
		break;
	case EShaderType::NONE:
	default:
		MsgBoxAssert("타입이 불분명한 텍스처 세팅입니다.");
		break;
	}
}

void UEngineTexture::Reset(EShaderType _Type, UINT _Slot)
{
	ID3D11ShaderResourceView* NullptrSRV = nullptr;

	switch (_Type)
	{
	case EShaderType::Vertex:
		GEngine->GetDirectXContext()->VSSetShaderResources(_Slot, 1, &NullptrSRV);
		break;
	case EShaderType::Pixel:
		GEngine->GetDirectXContext()->PSSetShaderResources(_Slot, 1, &NullptrSRV);
		break;
	case EShaderType::NONE:
	default:
		MsgBoxAssert("타입이 불분명한 텍스처 세팅입니다.");
		break;
	}
}


Color8Bit UEngineTexture::GetColor(unsigned int _X, unsigned int _Y, Color8Bit _DefaultColor)
{
	if (_X < 0)
	{
		return _DefaultColor;
	}

	if (_Y < 0)
	{
		return _DefaultColor;
	}


	if (_X >= GetScale().uiX())
	{
		return _DefaultColor;
	}

	if (_Y >= GetScale().uiY())
	{
		return _DefaultColor;
	}

	// 이미지의 포맷이 굉장히 다양하다.
	// RGBA

	// 4바이트 컬러?
	DXGI_FORMAT Fmt = Image.GetMetadata().format;

	// 로드한 이미지만 픽셀충돌이 될것이다.
	// 1바이트 짜리 자료형
	unsigned char* Ptr = Image.GetPixels();

	// 22
	// 
	// [4][4]
	// [4][4]

	// Ptr
	// Ptr
	// Ptr += 12;
	// _X, _Y
	
	//  1        2              1
	// ((_Y * GetScale().ix()) + _X) * 4 ;
	// 3 * 4

	// |
	// [][][][] [][][][]
	// [][][][] [][][][]

	// DXGI_FORMAT_B8G8R8A8_UNORM 색상1픽셀이 4바이트

	switch (Fmt)
	{
	case DXGI_FORMAT_B8G8R8A8_UNORM:
	case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
	{
		Color8Bit Result;
		Ptr += ((_Y * GetScale().iX()) + _X) * 4;
		Result.B = Ptr[0];
		Result.G = Ptr[1];
		Result.R = Ptr[2];
		Result.A = Ptr[3];
		return Result;
	}
	default:
		MsgBoxAssert("아직 처리할수 없는 GetPixel 포맷입니다");
		break;
	}


	return Color8Bit();
}