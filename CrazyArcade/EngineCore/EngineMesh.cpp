#include "PreCompile.h"
#include "EngineMesh.h"
#include "EngineCore.h"

UEngineMesh::UEngineMesh() 
{
}

UEngineMesh::~UEngineMesh() 
{
}

void UEngineMesh::ResCreate(std::string_view _VertexName, std::string_view _IndexName)
{
	VertexBuffer = UEngineVertexBuffer::FindRes(_VertexName);
	IndexBuffer = UEngineIndexBuffer::FindRes(_IndexName);

	if (nullptr == VertexBuffer || nullptr == IndexBuffer)
	{
		MsgBoxAssert("매쉬 생성에 실패했습니다.");
		return;
	}


}

void UEngineMesh::InputAssembler1Setting()
{
#ifdef _DEBUG
	if (nullptr == VertexBuffer)
	{
		MsgBoxAssert("버텍스 버퍼가 세팅되지 않은 매쉬입니다" + GetName());
		return;
	}
#endif

	VertexBuffer->Setting();
}

void UEngineMesh::InputAssembler2Setting()
{
#ifdef _DEBUG
	if (nullptr == IndexBuffer)
	{
		MsgBoxAssert("인덱스 버퍼가 세팅되지 않은 매쉬입니다" + GetName());
		return;
	}
#endif

	IndexBuffer->Setting();

	// D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST 삼각형으로 그려라.
	GEngine->GetDirectXContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void UEngineMesh::IndexedDraw()
{
	// 10만개의 버텍스로 이루어진 매쉬가 있다고치자.
	// 전신이 다 있는거다.
	// 머리
	// 팔
	// 몸통
	// 다리
	// 꼭 게임 만들다보면 머리만 써야할때가 있는데?
	// 애초에 매쉬들을 아예 다 쪼개서 만드는 경우와.
	// 하나의 매쉬인데. 머리만 써야겠는데?
	// 50만 53만 까지는 머리 버텍스다.
	// GEngine->GetDirectXContext()->DrawIndexed(IndexBuffer->Count, 500000, 480000);

	GEngine->GetDirectXContext()->DrawIndexed(IndexBuffer->Count, 0, 0);
}

void UEngineMesh::DrawIndexedInstanced(int _InstancingCount)
{
	GEngine->GetDirectXContext()->DrawIndexedInstanced(IndexBuffer->Count, _InstancingCount, 0, 0, 0);
}