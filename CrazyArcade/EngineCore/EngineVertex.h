#pragma once
#include <EngineBase/EngineMath.h>
#include "DirectXHelper.h"

// 3D로 그려지는 점은 위치만 가질필요가 없습니다.
// 자유
// 위치 빼고는 다 자유

// 이걸 내가 마음껏 넣으면 된다.
// 점 1개를 구성하는 요소들을 내가 마음대로 넣을수 있다.
// 그걸 directx는 알아요 몰라요?
// 점을 만들었어
// 그 점이 어디에 있어야 합니까?
// 저장장치중에 어디에 있냐?
// 그래픽카드 램에 들어가게 됩니다.
// => 그래픽카드야 나 도형만들래
//    크기

class UVertexLayOutInfo
{
public:
	std::vector<D3D11_INPUT_ELEMENT_DESC> Descs;
	UINT OffsetSize = 0;

	void AddInputLayOut(
		LPCSTR _SemanticName,
		DXGI_FORMAT _Format, // float4 DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT
		UINT _SemanticIndex = 0, // POSITION0 POSITION1
		UINT _InputSlot = 0,
		UINT _AlignedByteOffset = -1, // -1
		D3D11_INPUT_CLASSIFICATION _InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA,
		UINT _InstanceDataStepRate = 0
	)
	{
		D3D11_INPUT_ELEMENT_DESC Desc;

		Desc.SemanticName = _SemanticName; // "POSITION"
		Desc.SemanticIndex = _SemanticIndex;
		Desc.Format = _Format;

		// 이 레이아웃을 여러개 낄수 있는데.
		// 그때 끼는 위치입니다.
		// 추후에 인스턴싱이랑 연관이 있습니다.
		// 일단 0 넣어놓으면 됨.
		Desc.InputSlot = _InputSlot;
		Desc.AlignedByteOffset = _InputSlot;

		// 자동계산해라.
		if (-1 == _AlignedByteOffset)
		{
			Desc.AlignedByteOffset += OffsetSize;
		}

		OffsetSize += UDirectXHelper::DirectFormatSize(_Format);

		// D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;
		// D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_INSTANCE_DATA
		Desc.InputSlotClass = _InputSlotClass;
		Desc.InstanceDataStepRate = _InstanceDataStepRate;

		Descs.push_back(Desc);
	}

};

#define VERTEXMEM(Type, Name) Type Name
// FEngineVertex::Info.AddInputLayOut("POSITION", DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT);

struct FEngineVertex
{
	// 무조건 이름도 Info여야 합니다.
	static UVertexLayOutInfo Info;

	float4 POSITION;
	float4 TEXCOORD;
};