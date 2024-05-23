#pragma once
#include "EngineSerializer.h"
#include <memory>

// 설명 :
class UNetObject;
class UEngineProtocol : public std::enable_shared_from_this<UEngineProtocol>, public UEngineSerializeObject
{
	friend UNetObject;

protected:
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

	template<typename EnumType>
	EnumType GetPacketType()
	{
		return static_cast<EnumType>(PacketType);
	}

	int GetPacketType()
	{
		return PacketType;
	}
	int GetObjectToken()
	{
		if (ObjectToken == 1) {
			int a = 0;
		}
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
		// 시리얼라이즈 만으로는 패킷 사이즈를 알수가 없어요.
		UEngineSerializer Ser;
		Serialize(Ser);
		PacketSize = Ser.GetWriteOffset();
		Ser.Paste(0, &PacketSize, sizeof(PacketSize));
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