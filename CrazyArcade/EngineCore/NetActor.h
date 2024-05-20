#pragma once
#include "Actor.h"
#include <EngineBase/NetObject.h>

class ANetActor : public AActor, public UNetObject
{
public:
	ANetActor();
	~ANetActor();

	ANetActor(const ANetActor& _Other) = delete;
	ANetActor(ANetActor&& _Other) noexcept = delete;
	ANetActor& operator=(const ANetActor& _Other) = delete;
	ANetActor& operator=(ANetActor&& _Other) noexcept = delete;

protected:


	void ProtocolTick(std::function<void(std::shared_ptr< UEngineProtocol>)> _ProtocolFun) {

		std::shared_ptr<UEngineProtocol> Protocol = nullptr;
		do
		{
			Protocol = PopProtocol();
			if (nullptr == Protocol)
			{
				break;
			}


			_ProtocolFun(Protocol);

		} while (nullptr != Protocol);
	}


private:


};

