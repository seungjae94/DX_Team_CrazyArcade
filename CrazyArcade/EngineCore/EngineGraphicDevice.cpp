#include "PreCompile.h"
#include "EngineGraphicDevice.h"
#include "EngineTexture.h"
#include "EngineRenderTarget.h"

// 다이렉트 라이브러리를 사용하기 위해서

UEngineGraphicDevice::UEngineGraphicDevice() 
{
}

UEngineGraphicDevice::~UEngineGraphicDevice() 
{
	if (nullptr != SwapChain)
	{
		SwapChain->Release();
	}

	if (nullptr != Context)
	{
		Context->Release();
	}

	if (nullptr != Device)
	{
		Device->Release();
	}
}

IDXGIAdapter* UEngineGraphicDevice::GetHighPerFormanceAdapter()
{
	// 그래픽카드가 2개면

	IDXGIFactory* Factory = nullptr;
	IDXGIAdapter* Adapter = nullptr;

	// IDXGIFactory* Factory는 다이렉트x 라이브러리를 만드는 용도의 
	// 인터페이스입니다
	// Adapter를 만들어 내려면  Factory 필요하다.
	// CreateDXGIFactory()
	
	// 문법 이해 안되면 물어보세요
	HRESULT HR = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&Factory));

	if (nullptr == Factory)
	{
		MsgBoxAssert("그래픽카드에서 팩토리 인터페이스를 생성하지 못했습니다");
		return nullptr;
	}

	size_t VideoMemory = 0;
	// 그래픽카드 램이 큰애가
	// 가장 성능이 좋은 그래픽카드라고 생각하겠다

	for (int Index = 0;; Index++)
	{
		IDXGIAdapter* CurAdapter = nullptr;

		Factory->EnumAdapters(Index, &CurAdapter);

		if (nullptr == CurAdapter)
		{
			break;
		}

		DXGI_ADAPTER_DESC Desc;
		CurAdapter->GetDesc(&Desc);

		if (VideoMemory <= Desc.DedicatedVideoMemory)
		{
			VideoMemory = Desc.DedicatedVideoMemory;

			if (nullptr != Adapter)
			{
				// 기존에 만약 어뎁터가 있다면
				// 그 어뎁터는 날려버리고
				Adapter->Release();
			}

			Adapter = CurAdapter;
			continue;
		}

		CurAdapter->Release();
	}

	Factory->Release();
	return Adapter;
}

void UEngineGraphicDevice::Initialize(const UEngineWindow& _Window, const float4& _ClearColor)
{
	if (nullptr == _Window.GetHWND())
	{
		MsgBoxAssert("Open 되지 않은 윈도우로 그래픽카드 장치를 초기화하려고 했습니다.");
		return;
	}

	int iFlag = 0;

#ifdef _DEBUG
	// 디버그 모드일때만
	//  D3D11_CREATE_DEVICE_SINGLETHREADED = 0x1,
	//	D3D11_CREATE_DEVICE_DEBUG = 0x2,
	//	D3D11_CREATE_DEVICE_SWITCH_TO_REF = 0x4,
	//	D3D11_CREATE_DEVICE_PREVENT_INTERNAL_THREADING_OPTIMIZATIONS = 0x8,
	//	D3D11_CREATE_DEVICE_BGRA_SUPPORT = 0x20,
	//	D3D11_CREATE_DEVICE_DEBUGGABLE = 0x40,
	//	D3D11_CREATE_DEVICE_PREVENT_ALTERING_LAYER_SETTINGS_FROM_REGISTRY = 0x80,
	//	D3D11_CREATE_DEVICE_DISABLE_GPU_TIMEOUT = 0x100,
	//	D3D11_CREATE_DEVICE_VIDEO_SUPPORT = 0x800


	iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif

	// 내 그래픽카드가 다이렉트 x를 몇버전까지 지원할수 있는지 알아내기 위한 변수
	D3D_FEATURE_LEVEL Level = D3D_FEATURE_LEVEL_11_0;

	// 그래픽카드를 대표하는 핸들
	// 최대 성능 그래픽카드를 찾기 위한 함수
	Adapter = GetHighPerFormanceAdapter();

	if (nullptr == Adapter)
	{
		MsgBoxAssert("그래픽카드가 존재하지 않는 컴퓨터 입니다");
		return;
	}

	// 그래픽카드를 찾았으니
	// Adapter 그래픽카드에 명령을 내릴수 있느 그래픽카드에 명령을 내릴수 있는 디바이스와 컨텍스트를 만들겁니다.

	// D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_UNKNOWN  // 니가 알아서 해줘
	// D3D_DRIVER_TYPE_HARDWARE	= ( D3D_DRIVER_TYPE_UNKNOWN + 1 ) , 그래픽카드로
	// D3D_DRIVER_TYPE_REFERENCE = (D3D_DRIVER_TYPE_HARDWARE + 1), // 특화된 뭘할께
	// D3D_DRIVER_TYPE_NULL = (D3D_DRIVER_TYPE_REFERENCE + 1),
	// D3D_DRIVER_TYPE_SOFTWARE = (D3D_DRIVER_TYPE_NULL + 1), Cpu로 연산할께.
	// D3D_DRIVER_TYPE_WARP = (D3D_DRIVER_TYPE_SOFTWARE + 1)

	// 함수가 용도가 2개인거야

	HRESULT Result = D3D11CreateDevice(
		Adapter, // nullptr; 다이렉트 x가 
		D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_UNKNOWN, // -0 
		nullptr,
		iFlag,
		nullptr, // 팩처레벨 강제지정인데
		0, // 그중에서 내가 선택가능한 팩처레벨을 리턴해줘요 
		D3D11_SDK_VERSION, // 
		&Device,
		&Level, // 내가 선택한 팩처레벨
		&Context
	);

	if (nullptr == Context)
	{
		MsgBoxAssert("그래픽카드가 랜더링 제어 권한 컨텍스트를 생성하는데 실패했습니다.");
		return;
	}

	if (nullptr == Device)
	{
		MsgBoxAssert("그래픽카드가 메모리제어 권한 디바이스를 생성하는데 실패했습니다.");
		return;
	}
	
	// 나 포인터 썼다 무조건 null검사
	// 생각자체를 하지마 그냥 하는거니까.
	//if (nullptr != Adapter)
	//{
	//	Adapter->Release();
	//}

	if (S_OK != Result)
	{
		MsgBoxAssert("디바이스 생성에 실패했습니다.");
		// DWORD Result = GetLastError(); // 이 에러에 대해서 자세하게 알수 있다.
		// 지금은 무시
		return;
	}

	if (D3D_FEATURE_LEVEL_11_0 != Level)
	{
		MsgBoxAssert("다이렉트 11버전을 사용할수 없는 그래픽카드 입니다.");
		return;
	}

	// CPU에서 쓰는 멀티쓰레드로도 안전하게 동작하게 하겠다.
	Result = CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	//0x80010106;
	//E_INVALIDARG;
	//E_OUTOFMEMORY;
	//E_UNEXPECTED;
	//S_OK;
	//S_FALSE;
	//RPC_E_CHANGED_MODE;

	// 멀티쓰레드로 잘 바뀡었어요
	if (S_OK != Result)
	{
		if (RPC_E_CHANGED_MODE != Result)
		{
			MsgBoxAssert("멀티쓰레드 옵션을 사용할 수가 없습니다.");
			return;
		}
	}


	WindowPtr = &_Window;

	CreateSwapChain(_ClearColor);

	EngineResourcesInit();
}

void UEngineGraphicDevice::CreateSwapChain(const float4& _ClearColor)
{
	// 스왑체인 자체가 기능입니다.
	// 제공 최종적으로 나오는 이미지를 처리하기 때문에.
	// 안사용할수가 없다.
	// 그림이 그려지기 까지 고정되어있는 과정의 마지막단계라고 보면되는데.
	// 그림이 그려지기 까지 벌어지는 이 고정되어있는 과정을 랜더링파이프라인이라고 하고
	// 이건 간혹가다 회사가리지 않고 물어볼때가 있어서
	// 스왑체인은 그 랜더링 파이프라인의 가장 마지막단계를 담당합니다.
	// 모니터에 출력.
	// 랜더링에서 기존에 있던 그림을 깨끗히 지우고 다시그리는건 어느 랜더링이 거의 공통적인
	// 모니터라고 하는 하드웨어에 뭔가를 출력하는 과정안에 우리가 낑겨서 출력하는 것이다.

	// 해상도라고 부른다.
	float4 Resolution = WindowPtr->GetWindowScale();

	// 스왑체인을 만들기 위한 구조체를 만들고 설정한다.
	DXGI_SWAP_CHAIN_DESC ScInfo = { 0 };

	ScInfo.BufferCount = 2;
	ScInfo.BufferDesc.Width = Resolution.iX();
	ScInfo.BufferDesc.Height = Resolution.iY();
	ScInfo.OutputWindow = WindowPtr->GetHWND();

	// 주사율 모니터에 얼마나 빠르게 갱신할거냐
	ScInfo.BufferDesc.RefreshRate.Denominator = 1;
	ScInfo.BufferDesc.RefreshRate.Numerator = 60;

	// 색깔 포맷
	ScInfo.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	// 모니터 픽셀을 갱신하는 순서 모니터 그대로
	ScInfo.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	// 아예 기억안남
	ScInfo.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// 이 스왑체인을 무슨용도로 쓰실건가요?
	// RENDER_TARGET 텍스처 1장을 말합니다.
	// DXGI_USAGE_SHADER_INPUT 쉐이더에 입력하는 형태로 하겠다.
	// 쉐이더가
	ScInfo.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;

	// 이거 이외에 할필요가 없다.
	// 샘플링
	ScInfo.SampleDesc.Quality = 0;
	ScInfo.SampleDesc.Count = 1;

	// 버퍼가 있으면
	// 교체하는 순서인데 010101010101
	// 알고 있어봐야 의미 없죠.
	// DXGI_SWAP_EFFECT_FLIP_DISCARD 2개를 교대로 보여줘라.
	// 이거때문에 화면이 깜빡임
	// ScInfo.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_FLIP_DISCARD;
	ScInfo.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD;
	// 전혀 기억 안난다.
	ScInfo.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	// 전체화면이냐 아니야.
	// 중간에 전체화면에서 원래대로 바꾸는 
	// 전체화면이 프레임이 빠르다.
	ScInfo.Windowed = true;

	// 기존의 이건 삭제해야 한다.

	// 옵션끝
	// 스왑체인을 만들겁니다.
	// 메모리를 할당하는거네. 디바이스
	// 그냥 예제 배꼈어요 ㅠㅠ

	// 스왑체인을 만들게되면 
	// DC를 만들면 내부에 화면크기만한 텍스처를 만들어 줍니다.

	// 디바이스를 얻어오고 그안에 있는 어뎁터를 얻어옵니다.
	// IDXGIDevice* pD = 
	// Device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>())

	// 이 장치와 관련된 생성기(팩토리)를 얻어내는 함수

	IDXGIFactory* pF = nullptr;

	Adapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&pF));

	// 메모리할당하는 무슨함수건 일단 디바이스 넣어달라고할겁니다.
	pF->CreateSwapChain(Device, &ScInfo, &SwapChain);

	Adapter->Release();
	pF->Release();

	// 끄집어 내서 쓸것이다.
	
	// 내가 설정한 화면크기만한 directx용 image가 들어있다.
	// ID3d11Texture2D
	// 쉽게말하자면 IDXGISwapChain 내부에 맵을 들고 있는데
	// 맵의 키가 key게 긴 문자열이라고 생각해라.
	// MIDL_INTERFACE("7b7166ec-21c7-44ae-b21a-c9ae321ae369")
	// IDXGIFactory: public IDXGIObject

	ID3D11Texture2D* DXBackBufferTexture = nullptr;
	if (S_OK != SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&DXBackBufferTexture)))
	{
		MsgBoxAssert("백버퍼 텍스처를 얻어오지 못했습니다");
		return;
	}

	// 싱글톤 안씀
	// 이제부터 그냥 그 클래스가 관리함.
	// 당연히 static으로 모든 리소스는 관리방식이 동일해야 한다.
	// 우리가 말하는 랜더리잉란 이녀석이 가장 중요한 텍스처 결국 여기에 그려야 화면에 나온다.
	// 하지만 그릴수 있는 권한은 아직 없어요
	std::shared_ptr<UEngineTexture> Texture = UEngineTexture::Create(DXBackBufferTexture);

	// 그릴수 있는 권한이나 지우는 기능들은 다 랜더타겟이라는 걸로 
	// 텍스처 그대로는 편집기능을 사용하지 않고
	// 오로지 랜더타겟 뷰로만 사용할 겁니다.
	// 이미지에대 이미지로 그린다.
	BackBufferRenderTarget = UEngineRenderTarget::Create(Texture, _ClearColor);
	// 우리 winapi HDC를 HDC그대로 사용했나요?
	// 


	
}

void UEngineGraphicDevice::RenderStart()
{
	BackBufferRenderTarget->Clear();
}

void UEngineGraphicDevice::RenderEnd()
{
	// BackBufferRenderTarget에 그려진걸 화면에 그려라
	// tn
	HRESULT Result = SwapChain->Present(0, 0);

	if (Result == DXGI_ERROR_DEVICE_REMOVED || Result == DXGI_ERROR_DEVICE_RESET)
	{
		MsgBoxAssert("해상도나 디바이스 관련 설정이 변경 되었습니다");
		return;
	}

}

