#pragma once
#include "EngineVertexBuffer.h"
#include "EngineIndexBuffer.h"

// Ό³Έν :
class URenderUnit;
class UEngineMesh : public UEngineResources<UEngineMesh>
{
	friend URenderUnit;
	friend URenderer;

public:
	// constrcuter destructer
	UEngineMesh();
	~UEngineMesh();

	// delete Function
	UEngineMesh(const UEngineMesh& _Other) = delete;
	UEngineMesh(UEngineMesh&& _Other) noexcept = delete;
	UEngineMesh& operator=(const UEngineMesh& _Other) = delete;
	UEngineMesh& operator=(UEngineMesh&& _Other) noexcept = delete;

	static std::shared_ptr<UEngineMesh> Create(std::string_view _Name)
	{
		return Create(_Name, _Name, _Name);
	}

	static std::shared_ptr<UEngineMesh> Create(std::string_view _MeshName, std::string_view _VertexName, std::string_view _IndexName)
	{
		std::shared_ptr<UEngineMesh> Res = CreateResName(_MeshName);
		Res->ResCreate(_VertexName, _IndexName);
		return Res;
	}

	void IndexedDraw();
	void DrawIndexedInstanced(int _InstancingCount);

protected:
	void ResCreate(std::string_view _VertexName, std::string_view _IndexName);

private:
	std::shared_ptr<UEngineVertexBuffer> VertexBuffer = nullptr;
	std::shared_ptr<UEngineIndexBuffer> IndexBuffer = nullptr;

	void InputAssembler1Setting();
	void InputAssembler2Setting();
};

