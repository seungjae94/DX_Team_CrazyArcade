#include "PreCompile.h"
#include "ThreadPool.h"
#include "EngineDebug.h"

UThreadPool::UThreadPool() 
{
}

UThreadPool::~UThreadPool() 
{
	End();
}

void UThreadPool::Initialize(const std::string_view& _ThreadName, int _ThreadCount/* = 0*/)
{
	ThreadCount = _ThreadCount;

	// 아 그냥 적적한 양으로 만들어달라는 거구나.
	// 적적한 양 코어 * 2 + 1
	// cpu 수 * (cpu 목표 사용량) * (1+대기 시간/서비스 시간) + tomcat
	// 그냥 상황에 따라서 적절한 수로 만들면 됩니다. 경험
	// 선생님은 코어 개수만큼 만들겠습니다.
	if (0 >= ThreadCount)
	{
		SYSTEM_INFO Info;
		GetSystemInfo(&Info);
		ThreadCount = Info.dwNumberOfProcessors;
	}


	// IOCP를 쓰겠다. => IOCP를 만들겠다.
	// CreateIoCompletionPort 
	// 1. IOCP를 만든다.
	// 2. io포트를 를 등록한다.<= 서버 등록하는 법은 

	// 이렇게 쓰면 iocp를 만들겠다는 뜻이 됩니다.
	IOCPHandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, ThreadCount);

	if (nullptr == IOCPHandle)
	{
		MsgBoxAssert("iocp 핸들 생성에 실패했습니다.");
	}

	Threads.resize(ThreadCount);

	IsRun = true;

	RunThreadCount = ThreadCount;

	for (size_t i = 0; i < Threads.size(); i++)
	{
		Threads[i] = std::make_shared<UEngineThread>();
		Threads[i]->SetName(std::string(_ThreadName) + std::to_string(i));
		Threads[i]->Start(std::bind(ThreadPoolWorkFunction, this, IOCPHandle));
	}

	int a = 0;
}

void UThreadPool::ThreadPoolWorkFunction(UThreadPool* _Pool, HANDLE _IOCPHandle)
{
	DWORD Byte; // 날아온 패킷이나 파일의 크기
	ULONG_PTR Ptr; // 전달해주고 싶은 어떤 파일등을 읽거나 일이 있을때 8바이트 정수를 전달해 줄수 있다.
	LPOVERLAPPED OverLapped = nullptr; // 서버나 파일입출력시 현재 얼마나 읽어들였는지에 대한 정보를 받을수 있습니다.


	while (_Pool->IsRun)
	{
		// 일이 생기면 깨우고 일이 없는 애들은 무한 Sleep()
		// 파일입출력을 위해서 만들어졌다.
		// INFINITE 기다리는 시간 
		// 일정시간마다 일어나 이유없어 일어나
		// 무한대 시간 지나면 일어나.
		// 우리가 일을 맡겼을때만 일어나
		GetQueuedCompletionStatus(_IOCPHandle, &Byte, &Ptr, &OverLapped, INFINITE);
		// GetQueuedCompletionStatus(_IOCPHandle, &Byte, &Ptr, &OverLapped, 2000);

		EThreadWorkType Type = static_cast<EThreadWorkType>(Byte);

		if (Type == EThreadWorkType::Destroy)
		{
			break;
		}

		FJob* NewJob = reinterpret_cast<FJob*>(Ptr);
		NewJob->WorkFunction();
		delete NewJob;
		NewJob = nullptr;
	}

	--_Pool->RunThreadCount;
}

void UThreadPool::Work(std::function<void()> _Function)
{
	// 8바이트 정수를 
	
	// 강제로 iocp를 깨우는 함수
	// IOCPHandle 로 관리받고 있는 애들중에 하나 일어나
	// PostQueuedCompletionStatus(IOCPHandle, 999, reinterpret_cast<__int64>(312321));

	FJob* NewJob = new FJob();
	NewJob->WorkFunction = _Function;
	PostQueuedCompletionStatus(IOCPHandle, static_cast<BYTE>(EThreadWorkType::Work), reinterpret_cast<__int64>(NewJob), nullptr);
}

void UThreadPool::End()
{
	IsRun = false;

	while(RunThreadCount)
	{
		PostQueuedCompletionStatus(IOCPHandle, static_cast<BYTE>(EThreadWorkType::Destroy), 3333333, nullptr);
	}
	
}