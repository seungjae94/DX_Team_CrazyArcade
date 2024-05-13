#pragma once

// 설명 : 사실 멀티플랫폼 엔진이면 OpenGl을 사용할수 있고
//        Directx를 사용할수도 있을것이다.
//        일반적으로 걷으로 보기에는 이게 어떤 라이브러리로 동작하는지 보여서는 안된다.

class ULevel;
class UEngineCore;
class UEngineWindow;
class UEngineRenderTarget;

class UEngineGraphicDevice
{
	friend UEngineCore;
	friend ULevel;

public:
	// constrcuter destructer
	UEngineGraphicDevice();
	~UEngineGraphicDevice();

	// delete Function
	UEngineGraphicDevice(const UEngineGraphicDevice& _Other) = delete;
	UEngineGraphicDevice(UEngineGraphicDevice&& _Other) noexcept = delete;
	UEngineGraphicDevice& operator=(const UEngineGraphicDevice& _Other) = delete;
	UEngineGraphicDevice& operator=(UEngineGraphicDevice&& _Other) noexcept = delete;

	// nullptr의 가능성을 없애버리기 위해서
	void Initialize(const UEngineWindow& _Window, const float4& _ClearColor);

	struct ID3D11Device* GetDevice()
	{
		return Device;
	}

	struct ID3D11DeviceContext* GetContext()
	{
		return Context;
	}

	void RenderStart();

	void RenderEnd();

protected:

private:
	// 9버전까지는 Device라는 인터페이스 밖에 없었다.
	// 당연히 마소가 만들었으니까 핸들 방식이다.
	// ID3D9Device* Device; <= com객체 방식의 표현이라는데
	// Device->MeshRender(); 그릴때
	// Device->LoadTexture(); 리소스 관리할때
	// 위와 같이 단순하지 않습니다.

	// 11와서 2가지 분야로 인터페이스를 분리했다.

	// Device->LoadTexture(); 메모리(그림, 이미지, 점, 등등등등등) 관리할때
	struct ID3D11Device* Device = nullptr;

	// Context->MeshRender(); 그릴때
	struct ID3D11DeviceContext* Context = nullptr;

	const class UEngineWindow* WindowPtr;

	// 더블 버퍼링
	struct IDXGISwapChain* SwapChain = nullptr;

	struct IDXGIAdapter* Adapter = nullptr;

	std::shared_ptr<UEngineRenderTarget> BackBufferRenderTarget = nullptr;

	// 그래픽카드중 가장 사양이 높은 그래픽카드를 가져오는 함수
	struct IDXGIAdapter* GetHighPerFormanceAdapter();
	void CreateSwapChain(const float4& _ClearColor);
	void EngineResourcesInit();
	void EngineResourcesRelease();

	std::shared_ptr<UEngineRenderTarget> GetBackBufferRenderTarget()
	{
		return BackBufferRenderTarget;
	}
};

