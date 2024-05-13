#include "PreCompile.h"
#include "NetObject.h"

// 이 토큰을 부여해줄수 있는건 보통 서버입니다.
std::atomic<int> UNetObject::CurObjectToken = 0;
std::map<int, UNetObject*> UNetObject::AllNetObject;

UNetObject::UNetObject() 
{
}

UNetObject::~UNetObject() 
{
}


void UNetObject::Send(std::shared_ptr<UEngineProtocol> _Protocol)
{
	if (nullptr == Net)
	{
		return;
	}

	// 오브젝트 토큰과 세션토큰은 무조건 채워져 있어야 한다.
	// 채워서 보내야 하고.
	_Protocol->SetSessionToken(Net->GetSessionToken());
	_Protocol->ObjectToken = ObjectToken;

	Net->Send(_Protocol);
}



std::shared_ptr<UEngineProtocol> UNetObject::PopProtocol()
{
	if (true == ProtocolQueue.empty())
	{
		return nullptr;
	}

	std::shared_ptr<UEngineProtocol> Protocol = ProtocolQueue.front();
	ProtocolQueue.pop();
	return Protocol;
}