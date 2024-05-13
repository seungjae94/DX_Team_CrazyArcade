#include "PreCompile.h"
#include "EngineThread.h"
#include "EngineString.h"

UEngineThread::UEngineThread() 
{
}

UEngineThread::~UEngineThread() 
{
	// 지금 쓰레드 실행중이야?
	if (true == Thread.joinable())
	{
		Thread.join();
	}
}

void UEngineThread::SetFunction(std::function<void()> _Function)
{
	CallBack = _Function;
}

void UEngineThread::ThreadStartFunction(UEngineThread* _Thread)
{
	// 쓰레드안에서 
	// 여기서부터 이미 쓰레드
	std::string Name = _Thread->GetName();

	if (Name == "")
	{
		Name = "None Thread";
	}

	std::wstring WName = UEngineString::AnsiToUniCode(Name);
	SetThreadDescription(GetCurrentThread(), WName.c_str());

	// 여러분들의 함수가 실행됩니다.
	_Thread->CallBack();

	_Thread->End = true;
}

void UEngineThread::Start(std::function<void()> _Function /*= nullptr*/)
{
	if (true == Thread.joinable())
	{
		return;
	}

	if (nullptr != _Function)
	{
		SetFunction(_Function);
	}

	if (nullptr == CallBack)
	{
		return;
	}

	// Thread = std::thread(CallBack);

	Thread = std::thread(std::bind(ThreadStartFunction, this));

	
}