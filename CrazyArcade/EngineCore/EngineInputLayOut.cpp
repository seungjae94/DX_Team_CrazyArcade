#include "PreCompile.h"
#include "EngineInputLayOut.h"
#include "EngineCore.h"
#include "EngineVertex.h"
#include "EngineVertexBuffer.h"
#include "EngineVertexShader.h"

UEngineInputLayOut::UEngineInputLayOut() 
{
}

UEngineInputLayOut::~UEngineInputLayOut() 
{
	if (nullptr != LayOut)
	{
		LayOut->Release();
	}
}

// 쉐이더도 앞으로 여러종 나올겁니다. ABC 쉐이더가 있다.
// 버텍스도 여러종이 나올수 있다. DEG 버텍스가 있다고 칩시다.
// A D의 조합으로 만들어지는 인풋 레이아웃은 A D의 조합으로 만들어진 랜더링 환경에서만 사용이 가능하죠.

void UEngineInputLayOut::ResCreate(std::shared_ptr<UEngineVertexBuffer> _Buffer, std::shared_ptr<UEngineVertexShader> _Shader)
{
	if (nullptr == _Buffer)
	{
		MsgBoxAssert("인풋레이아웃을 만들때 버퍼가 nullptr 이었습니다.");
	}

	// 버텍스 그자체가 들고 있다
	// 그주소값을 버텍스 버퍼가 가지고 있다.
	// UEngineVertexBuffer
	UVertexLayOutInfo* Ptr = _Buffer->LayOutInfoPtr;
	std::vector<D3D11_INPUT_ELEMENT_DESC>& Desc = Ptr->Descs;

	if (nullptr == _Shader)
	{
		MsgBoxAssert("인풋레이아웃을 만들때 쉐이더가 nullptr 이었습니다.");
	}

	// 버텍스 쉐이더가 들고 있다.
	// UEngineVertexShader
	ID3DBlob* VertexShaderCodeBlob = _Shader->ShaderCodeBlob;

	HRESULT Result = GEngine->GetDirectXDevice()->CreateInputLayout(
		&Desc[0], 
		static_cast<UINT>(Desc.size()), 
		VertexShaderCodeBlob->GetBufferPointer(), 
		VertexShaderCodeBlob->GetBufferSize(),
		&LayOut
	);

	if (S_OK != Result)
	{
		MsgBoxAssert("인풋 레이아웃 생성에 실패했습니다.");
		return;
	}
}

void UEngineInputLayOut::Setting()
{
#ifdef _DEBUG
	if (nullptr == LayOut)
	{
		MsgBoxAssert("만들어지지도 않은 인풋레이아웃을 세팅할수는 없습니다.");
	}
#endif

	GEngine->GetDirectXContext()->IASetInputLayout(LayOut);
}