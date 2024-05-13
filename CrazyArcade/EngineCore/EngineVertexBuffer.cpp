#include "PreCompile.h"
#include "EngineVertexBuffer.h"
#include "EngineCore.h"
#include "EngineGraphicDevice.h"

UEngineVertexBuffer::UEngineVertexBuffer() 
{
}

UEngineVertexBuffer::~UEngineVertexBuffer() 
{
}

void UEngineVertexBuffer::ResCreate(const void* _Data, UINT _Size, UINT _Count)
{
	// 다이렉트에서 어떤 메모리를 할당할때 초기값을 넣어주고 싶으면
	// 이걸로 넣어줘야 합니다.
	D3D11_SUBRESOURCE_DATA Data;
	Data.pSysMem = _Data;

	Size = _Size;
	Count = _Count;

	// 크기
	BufferInfo.ByteWidth = static_cast<UINT>(Size * Count);
	// 용도
	BufferInfo.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	// CPU에서 접근가능한가?
	BufferInfo.CPUAccessFlags = 0;
	// 어디저장할거야?
	// D3D11_USAGE_DEFAULT 그래픽카드에 저장해죠.
	// D3D11_USAGE_DYNAMIC 일단 그래픽카드 만약 없으면 Ram
	BufferInfo.Usage = D3D11_USAGE_DEFAULT;


	// CreateVertexBuffer 같은 함수가 아라
	// 버퍼계열은 아래의 함수로 통일
	if (S_OK != GEngine->GetDirectXDevice()->CreateBuffer(&BufferInfo, &Data, &Buffer))
	{
		MsgBoxAssert("버텍스 버퍼 생성에 실패했습니다.");
		return;
	}
}

void UEngineVertexBuffer::Setting()
{
#ifdef _DEBUG
	if (nullptr == Buffer)
	{
		MsgBoxAssert("만들어지지 않은 버텍스 버퍼를 세팅하려고 했습니다" + GetName());
	}
#endif

	// std::vector<ID3D11Buffer*> Buffer

	// 한번에 여러개의 버텍스 버퍼를 세팅해줄수 있습니다.
	//UINT StartSlot, // 버텍스 버퍼가 여러개 세팅됐다면 그중 몇번재 버퍼부터 세팅할거냐? 우리는 그런 생각안함 0
	//UINT NumBuffers, // 그여러개의 버텍스 버퍼가 몇개에요? 여러개 만들지를 않아서 1
	//ID3D11Buffer* const* ppVertexBuffers, 버퍼의 포인터 배열을 넣어주라. 어차피 우린 버퍼를 1개 만들었죠
	//const UINT* pStrides, 버퍼의 사이즈
	//const UINT* pOffsets 점이 4개라면 그중 몇번째부터 할까

	// 우린 그냥 1개의 버텍스 버퍼만 세팅하는 설정으로한다.
	GEngine->GetDirectXContext()->IASetVertexBuffers(0, 1, &Buffer, &Size, &Offset);
}