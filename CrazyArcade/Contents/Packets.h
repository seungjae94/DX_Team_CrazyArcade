#pragma once
#include <EngineBase/EngineMath.h>
#include <EngineBase/EngineProtocol.h>

// 맵은 어차피 모두 공통

// 서버만 오브젝트를 만들수 있어.
// 서버만 오브젝트를 만들수 있어야 한다.
enum ServerObjectType
{
	Player,
	Bomb,
};

enum EContentPacket
{
	ActorUpdatePacket = 99,
	SpawnUpdatePacket,
	ConnectUpdatePacket,
	ConnectInitPacket,
};

// 우리는 최소 16바이트는 있어야 뭔가할수 있다.
// 16바이트 이상 왔다고 해도
// 그보다 더 큰 패킷들도 있다.

// 최소 16바이트는 있어야 하고 + 32
// 설명 :
class UActorUpdatePacket : public UEngineProtocol
{
public: 
	static const EContentPacket Type = EContentPacket::ActorUpdatePacket;
public: 
	UActorUpdatePacket()
	{ 
		SetType(EContentPacket::ActorUpdatePacket);
	}

	void Serialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::Serialize(_Ser);
		_Ser << Pos;
		_Ser << SpriteName;

		int a = 0;
	}

	void DeSerialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::DeSerialize(_Ser);
		_Ser >> Pos;
		_Ser >> SpriteName;
	}

public:
	float4 Pos = float4::Zero;
	std::string SpriteName; // ?? 랜덤
};

class USpawnUpdatePacket : public UEngineProtocol {
public:
	static const EContentPacket Type = EContentPacket::SpawnUpdatePacket;
public:
	USpawnUpdatePacket()
	{
		SetType(EContentPacket::SpawnUpdatePacket);
	}

	void Serialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::Serialize(_Ser);
		_Ser << Pos;
		_Ser << SpawnSelect;
		_Ser << SpawnTime;
	}

	void DeSerialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::DeSerialize(_Ser);
		_Ser >> Pos;
		_Ser >> SpawnSelect;
		_Ser >> SpawnTime;
	}

public:
	float4 Pos = float4::Zero;
	int SpawnSelect = 0; // ?? 랜덤
	float SpawnTime = 0.0f;
};

class UConnectNumberPacket : public UEngineProtocol {
public:
	static const EContentPacket Type = EContentPacket::ConnectUpdatePacket;
public:
	UConnectNumberPacket()
	{
		SetType(EContentPacket::ConnectUpdatePacket);
	}

	void Serialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::Serialize(_Ser);
		_Ser << ConnectNum;
		_Ser << UserName;
		_Ser << Infos;

		UEngineSerializer Test;
		Test = _Ser;

		std::shared_ptr<UConnectNumberPacket> asdf = std::make_shared<UConnectNumberPacket>();
		asdf->DeSerialize(_Ser);


		int a = 0; 
	}

	void DeSerialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::DeSerialize(_Ser);
		_Ser >> ConnectNum;
		_Ser >> UserName;
		_Ser >> Infos;
	}

public:
	int ConnectNum = 0;
	std::string UserName = "";
	std::map<int, std::string> Infos;
};

class UConnectInitPacket : public UEngineProtocol {
public:
	static const EContentPacket Type = EContentPacket::ConnectInitPacket;
public:
	UConnectInitPacket()
	{
		SetType(EContentPacket::ConnectInitPacket);
	}

	void Serialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::Serialize(_Ser);
		_Ser << Session;
	}

	void DeSerialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::DeSerialize(_Ser);
		_Ser >> Session;
	}

public:
	int Session = 0;
};