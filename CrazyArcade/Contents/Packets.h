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
		_Ser << SpawnSelect;
	}

	void DeSerialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::DeSerialize(_Ser);
		_Ser >> Pos;
		_Ser >> SpriteName;
		_Ser >> SpawnSelect;
	}

public:
	float4 Pos = float4::Zero;
	std::string SpriteName; // ?? 랜덤
	int SpawnSelect = 0;
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
	int SpawnSelect = 0;
	float SpawnTime = 0.0f;
};

class UConnectPacket : public UEngineProtocol {
public:
	static const EContentPacket Type = EContentPacket::ConnectUpdatePacket;
public:
	UConnectPacket()
	{
		SetType(EContentPacket::ConnectUpdatePacket);
	}

	void Serialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::Serialize(_Ser);
		_Ser << Infos;
	}

	void DeSerialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::DeSerialize(_Ser);
		_Ser >> Infos;
	}

public:
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
		_Ser << Name;
	}

	void DeSerialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::DeSerialize(_Ser);
		_Ser >> Session;
		_Ser >> Name;
	}

public:
	int Session = 0;
	std::string Name = "";
};