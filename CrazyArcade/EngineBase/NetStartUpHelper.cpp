#include "PreCompile.h"
#include "EngineDebug.h"
#include "NetStartUpHelper.h"
#include <atomic>

UNetStartUpHelper::UNetStartUpHelper() 
{
}

UNetStartUpHelper::~UNetStartUpHelper() 
{
}

void UNetStartUpHelper::NetStartUp()
{
	static std::atomic<bool> StartUpCheck = false;

	if (true == StartUpCheck)
	{
		return;
	}

	WSAData WsaData;
	int Error = WSAStartup(MAKEWORD(2, 2), &WsaData);
	if (SOCKET_ERROR == Error)
	{
		MsgBoxAssert("네트워크 스타트에 실패했습니다.");
		return;
	}

	StartUpCheck = true;
}