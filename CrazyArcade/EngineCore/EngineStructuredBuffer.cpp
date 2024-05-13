#include "PreCompile.h"
#include "EngineStructuredBuffer.h"
#include "EngineCore.h"
#include "EngineGraphicDevice.h"

std::map<EShaderType, std::map<std::string, std::map<int, std::shared_ptr<UEngineStructuredBuffer>>>> UEngineStructuredBuffer::StructuredBuffers;

UEngineStructuredBuffer::UEngineStructuredBuffer() 
{
}

UEngineStructuredBuffer::~UEngineStructuredBuffer() 
{
	Release();
}

void UEngineStructuredBuffer::Release()
{
	if (nullptr != SRV)
	{
		SRV->Release();
		SRV = nullptr;
	}
	if (nullptr != Buffer)
	{
		Buffer->Release();
		Buffer = nullptr;
	}
}

void UEngineStructuredBuffer::Setting(EShaderType _Type, UINT _Slot)
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


void UEngineStructuredBuffer::Reset(EShaderType _Type, UINT _Slot)
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

void UEngineStructuredBuffer::Resize(int _Size)
{
	if (BufferInfo.ByteWidth >= static_cast<unsigned int>(_Size))
	{
		return;
	}

	// 이전에 이미 만들어져 있을수가 있어
	Release();

	BufferInfo.ByteWidth = _Size;
	BufferInfo.StructureByteStride = Size;


	BufferInfo.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	BufferInfo.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	BufferInfo.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
	BufferInfo.Usage = D3D11_USAGE_DYNAMIC;

	if (S_OK != GEngine->GetDirectXDevice()->CreateBuffer(&BufferInfo, nullptr, &Buffer))
	{
		MsgBoxAssert("버텍스 버퍼 생성에 실패했습니다.");
		return;
	}

	//srv를 만들어 내야 한다.
	// 텍스처에서 만들어내는건 쉬운데

	D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc = {};
	// srv를 버퍼로 만들겠다.
	SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
	SRVDesc.Format = DXGI_FORMAT_UNKNOWN;
	SRVDesc.BufferEx.FirstElement = 0;
	SRVDesc.BufferEx.Flags = 0;

	//                             288000  672
	SRVDesc.BufferEx.NumElements = _Size / Size;

	if (S_OK != GEngine->GetDirectXDevice()->CreateShaderResourceView(Buffer, &SRVDesc, &SRV))
	{
		MsgBoxAssert("구조화 버퍼의 쉐이더 리소스 생성에 실패했습니다.");
	}

}

void UEngineStructuredBuffer::ChangeData(const void* _Data, UINT _Size)
{
	// 이시점에서는 세팅해야할 최대치가 결저나 있다.

	Resize(_Size);

#ifdef _DEBUG
	if (nullptr == _Data)
	{
		MsgBoxAssert(GetName() + " 상수버퍼에 nullptr인 데이터를 세팅하려고 했습니다.");
	}

	if (0 >= _Size)
	{
		MsgBoxAssert(GetName() + " 상수버퍼에 0이하의 데이터를 세팅하려고 했습니다.");
	}
#endif

	D3D11_MAPPED_SUBRESOURCE Data = {};

	// 버퍼를 잠시 변경하기 위해서 열겠다.
	// 그래픽카드야 이거 쓰지마!
	// Map 최대한 적게 사용하는게 좋다.
	GEngine->GetDirectXContext()->Map(Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &Data);

#ifdef _DEBUG
	if (nullptr == Data.pData)
	{
		MsgBoxAssert(GetName() + " 그래픽카드가 수정을 거부했습니다.");
	}
#endif

	// Data.pData 그래픽카드에 넣어주는 주소
	memcpy_s(Data.pData, BufferInfo.ByteWidth, _Data, _Size);

	// 다썼어 다시 잠궈
	GEngine->GetDirectXContext()->Unmap(Buffer, 0);
}