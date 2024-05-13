#include "PreCompile.h"
#include "EngineBlend.h"
#include "EngineCore.h"

UEngineBlend::UEngineBlend() 
{
}

UEngineBlend::~UEngineBlend() 
{
	if (nullptr != State)
	{
		State->Release();
	}
}


void UEngineBlend::ResCreate(const D3D11_BLEND_DESC& _Info)
{
	HRESULT Result = GEngine->GetDirectXDevice()->CreateBlendState(&_Info, &State);
#ifdef _DEBUG
	if (S_OK != Result)
	{
		MsgBoxAssert("블랜드 생성에 실패했습니다.");
		return;
	}
#endif
}

void UEngineBlend::Setting()
{
#ifdef _DEBUG
	if (nullptr == State)
	{
		MsgBoxAssert("만들어지지 않은 블랜드를 세팅하려고 했습니다" + GetName());
	}
#endif

	// 블랜드가 영향 미칠 범위
	GEngine->GetDirectXContext()->OMSetBlendState(State, Factor.Arr1D, Mask);
}