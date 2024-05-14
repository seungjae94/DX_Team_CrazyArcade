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
		// 오브젝트 업데이트 패킷의 크기는?
		// 18
		// 30바이트
		int Size = recv(_Session->GetSocket(), Ser.DataCharPtrToWriteOffset(), Ser.RemainSize(), 0);

		if (SOCKET_ERROR == Size)
		{
			return;
		}

		if (-1 == Size)
		{
			return;
		}

		// 30 + 20
		Ser.AddWriteOffset(Size);

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
			UEngineProtocol::ObjectTokenInit(Protocol.GetObjectToken());
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

		// 30바이트

		//       32                     30
		if (Protocol.GetPacketSize() > Ser.WriteSize())
		{
			continue;
		}

		while(true)
		{
			std::shared_ptr<UEngineProtocol> Protocal = Dis.ConvertProtocol(Protocol.GetPacketType(), Ser);
			Dis.ProcessPacket(Protocal);

			int Size = *(reinterpret_cast<int*>(Ser.DataPtr()));
			int WriteOffset = Ser.GetWriteOffset();
			int ReadOffset = Ser.GetReadOffset();
			int RemainOffset = WriteOffset - ReadOffset;
			// 받은만큼 다 읽었어.
			if (WriteOffset == ReadOffset)
			{
				// 깔끔하게 읽었다.
				Ser.Reset();
				break;
			}

			if (16 > RemainOffset)
			{
				Ser.DataToReadOffsetPush();
				break;
			}
		} 
	}
}
