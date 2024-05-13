#include "PreCompile.h"
#include "EngineNet.h"
#include "NetStartUpHelper.h"
#include "Session.h"
#include "EngineClient.h"
#include "EngineDebug.h"
#include "EngineProtocol.h"

UEngineNet::UEngineNet() 
{
	UNetStartUpHelper::NetStartUp();
	IsActiveValue = true;
}

UEngineNet::~UEngineNet() 
{
	IsActiveValue = false;
}


void UEngineNet::RecvThreadFunction(USession* _Session, UEngineNet* _Net)
{
	UEngineSerializer Ser;
	Ser.BufferResize(1024);

	UEngineDispatcher& Dis = _Net->Dispatcher;

	bool IsClient = false;

	if (nullptr != dynamic_cast<UEngineClient*>(_Net))
	{
		IsClient = true;
	}

	while (_Net->IsActiveValue)
	{
		int Size = recv(_Session->GetSocket(), Ser.DataCharPtr(), Ser.BufferSize(), 0);

		if (SOCKET_ERROR == Size)
		{
			return;
		}

		Ser.SetWriteOffset(Size);

		// 우린 16바이트를 먼저 받지 않으면 아무런 의미가 없기때문
		// 무조건 16바이트 이상을 받을때까지 계속한다.
		if (16 > Ser.GetWriteOffset())
		{
			continue;
		}

		UEngineProtocol Protocol;
		Protocol.DeSerialize(Ser);

		if (Protocol.GetPacketType() == -2)
		{
			_Session->TokenInitOn();
			_Session->SetSessionToken(Protocol.GetSessionToken());
			if (nullptr != _Net->TokenPacketFunction)
			{
				_Net->TokenPacketFunction(reinterpret_cast<USessionTokenPacket*>(&Protocol));
			}
			if (true == IsClient)
			{
				// 클라이언트 일때만 응답
				_Session->Send(Protocol);
			}
			Ser.Reset();
			continue;
		}

		if (Protocol.GetPacketType() == -2)
		{
			MsgBoxAssert("단한번만 교환되어야할 토큰패킷이 또 교환되었습니다.");
		}

		Ser.ResetRead();

		std::shared_ptr<UEngineProtocol> Protocal = Dis.ConvertProtocol(Protocol.GetPacketType(), Ser);
		Dis.ProcessPacket(Protocal);


		Ser.Reset();
	}
}
