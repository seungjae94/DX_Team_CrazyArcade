#include "PreCompile.h"
#include "EngineConstantBuffer.h"
#include "EngineCore.h"

std::map<EShaderType, std::map<std::string, std::map<int, std::shared_ptr<UEngineConstantBuffer>>>> UEngineConstantBuffer::ConstantBuffers;

UEngineConstantBuffer::UEngineConstantBuffer() 
{
}

UEngineConstantBuffer::~UEngineConstantBuffer() 
{
}

void UEngineConstantBuffer::ResCreate(UINT _ByteSize)
{
	BufferInfo.ByteWidth = _ByteSize;
	BufferInfo.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	// CPU에서 상수버퍼의 내용을 덮어 씌우겠다.
	BufferInfo.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
	// 바뀐다.
	// 전에 잘못 설명한거 같습니다.
	// D3D11_USAGE_DEFAULT
	BufferInfo.Usage = D3D11_USAGE_DYNAMIC;

	if (S_OK != GEngine->GetDirectXDevice()->CreateBuffer(&BufferInfo, nullptr, &Buffer))
	{
		MsgBoxAssert("버텍스 버퍼 생성에 실패했습니다.");
		return;
	}
}

void UEngineConstantBuffer::Setting(EShaderType _Type, UINT _Slot)
{
	switch (_Type)
	{
	case EShaderType::Vertex:
		GEngine->GetDirectXContext()->VSSetConstantBuffers(_Slot, 1, &Buffer);
		break;
	case EShaderType::Pixel:
		GEngine->GetDirectXContext()->PSSetConstantBuffers(_Slot, 1, &Buffer);
		break;
	case EShaderType::NONE:
	default:
		MsgBoxAssert("처리가 완료되지 않은 상수버퍼 쉐이더 세팅 타입입니다");
		break;
	}
}

void UEngineConstantBuffer::Reset(EShaderType _Type, UINT _Slot)
{
	ID3D11Buffer* Buffer = nullptr;

	switch (_Type)
	{
	case EShaderType::Vertex:
		GEngine->GetDirectXContext()->VSSetConstantBuffers(_Slot, 1, &Buffer);
		break;
	case EShaderType::Pixel:
		GEngine->GetDirectXContext()->PSSetConstantBuffers(_Slot, 1, &Buffer);
		break;
	case EShaderType::NONE:
	default:
		MsgBoxAssert("처리가 완료되지 않은 상수버퍼 쉐이더 세팅 타입입니다");
		break;
	}
}

void UEngineConstantBuffer::ChangeData(const void* _Data, UINT _Size)
{
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
	memcpy_s(Data.pData, BufferInfo.ByteWidth, _Data, BufferInfo.ByteWidth);
	
	// 다썼어 다시 잠궈
	GEngine->GetDirectXContext()->Unmap(Buffer, 0);

}