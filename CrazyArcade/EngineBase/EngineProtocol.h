#pragma once
#include "EngineSerializer.h"
#include <memory>

// 설명 :
class UNetObject;
class UEngineProtocol : public std::enable_shared_from_this<UEngineProtocol>, public UEngineSerializeObject
{
	friend UNetObject;

private:
	int PacketSize = 0; // 가장 마지막에 계산될수 밖에 없다.
	int PacketType = 0; // 내가 공격이다. 그래서 int Enum이 될수 없다.
	int SessionToken = 0; // 내가 보낸 패킷을 받아할 애들
	int ObjectToken = 0; // 내가 보낸 패킷을 받아야할 오브젝트

	UEngineSerializer GetSerializer()
	{

	}

public:
	int GetPacketSize()
	{
		return PacketSize;
	}
	int GetPacketType()
	{
		return PacketType;
	}
	int GetObjectToken()
	{
		return ObjectToken;
	}
	int GetSessionToken()
	{
		return SessionToken;
	}

	void SetSessionToken(int _Token)
	{
		SessionToken = _Token;
	}

	void SetObjectToken(int _ObjectToken)
	{
		ObjectToken = _ObjectToken;
	}

	template<typename PType>
	void SetType(PType _Type)
	{
		PacketType = static_cast<int>(_Type);
	}

	void SizeCal()
	{

	}

	UEngineSerializer GetSerialize()
	{
		UEngineSerializer Ser;
		Serialize(Ser);
		return Ser;
	}


	void Serialize(UEngineSerializer& _Ser) override
	{
		// [PacketSize][PacketType][Token][][][][][][][][][][][][][][][][][][][][][][][]
		_Ser << PacketSize;
		_Ser << PacketType;
		_Ser << SessionToken;
		_Ser << ObjectToken;
	}

	void DeSerialize(UEngineSerializer& _Ser) override
	{
		_Ser >> PacketSize;
		_Ser >> PacketType;
		_Ser >> SessionToken;
		_Ser >> ObjectToken;
	}
};

class USessionTokenPacket : public UEngineProtocol
{
public:
	USessionTokenPacket()
	{
		SetType(-2);
	}
};

#define ProtocolHeader(EnumType, TypeName) \
public: static const EnumType Type = EnumType##::##TypeName; public: U##TypeName##() { SetType(##EnumType##::##TypeName); }