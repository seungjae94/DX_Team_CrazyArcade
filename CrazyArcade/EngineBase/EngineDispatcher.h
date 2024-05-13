#pragma once
#include <map>
#include <functional>
#include <memory>
#include "EngineDebug.h"
#include "EngineProtocol.h"

// 설명 :
class UEngineDispatcher
{
public:
	// constrcuter destructer
	UEngineDispatcher();
	~UEngineDispatcher();

	// delete Function
	UEngineDispatcher(const UEngineDispatcher& _Other) = delete;
	UEngineDispatcher(UEngineDispatcher&& _Other) noexcept = delete;
	UEngineDispatcher& operator=(const UEngineDispatcher& _Other) = delete;
	UEngineDispatcher& operator=(UEngineDispatcher&& _Other) noexcept = delete;

	// UActorUpdatePacket
	template<typename PacketType>
	void AddHandler(std::function<void(std::shared_ptr<PacketType>)> _CallBack)
	{
		int Type = static_cast<int>(PacketType::Type);
		AddHandler(Type, _CallBack);
	}

	template<typename PacketType>
	void AddHandler(int Type, std::function<void(std::shared_ptr<PacketType>)> _CallBack)
	{
		if (true == PacketHandlers.contains(Type))
		{
			MsgBoxAssert("이미 등록된 핸들러를 또 등록시킬수는 없습니다.");
		}

		ConvertPacketHandlers[Type] = [=](UEngineSerializer& _Ser)
			{
				std::shared_ptr<PacketType> NewPacket = std::make_shared<PacketType>();
				NewPacket->DeSerialize(_Ser);
				return NewPacket;
			};

		PacketHandlers[Type] = [=](std::shared_ptr<UEngineProtocol> _Packet)
			{
				std::shared_ptr<PacketType> ConvertPacket = std::dynamic_pointer_cast<PacketType>(_Packet);
				if (nullptr == ConvertPacket)
				{
					MsgBoxAssert("타입이 일치하지 않는 패킷이 도달했습니다.");
				}

				_CallBack(ConvertPacket);
			};
	}

	std::shared_ptr<UEngineProtocol> ConvertProtocol(int Type, UEngineSerializer& _Ser)
	{
		if (false == ConvertPacketHandlers.contains(Type))
		{
			MsgBoxAssert("처리방법이 지정되지 않은 패킷입니다.");
			return nullptr;
		}

		return ConvertPacketHandlers[Type](_Ser);
	}

	void ProcessPacket(std::shared_ptr<UEngineProtocol> _Packet)
	{
		if (false == ConvertPacketHandlers.contains(_Packet->GetPacketType()))
		{
			MsgBoxAssert("처리방법이 지정되지 않은 패킷입니다.");
			return;
		}

		return PacketHandlers[_Packet->GetPacketType()](_Packet);
	}

protected:

private:
	std::map<int, std::function<std::shared_ptr<UEngineProtocol>(UEngineSerializer& _Ser)>> ConvertPacketHandlers;

	// int 타입
	std::map<int, std::function<void(std::shared_ptr<UEngineProtocol>)>> PacketHandlers;

};

