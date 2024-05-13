#pragma once
#include <thread>
#include <functional>
#include "NameObject.h"

// Ό³Έν :
class UEngineThread : public UNameObject
{
public:
	// constrcuter destructer
	UEngineThread();
	~UEngineThread();

	// true
	bool IsEnd()
	{
		return Thread.joinable();
	}

	// delete Function
	void SetFunction(std::function<void()> _Function);

	void Start(std::function<void()> _Function = nullptr);

protected:
	std::thread Thread;
	std::function<void()> CallBack;
	bool End = false;

private:
	static void ThreadStartFunction(UEngineThread* _Thread);
};

