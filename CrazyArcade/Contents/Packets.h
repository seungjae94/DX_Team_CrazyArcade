#pragma once
#include <EngineBase/EngineMath.h>
#include <EngineBase/EngineProtocol.h>
#include "ConnectionInfo.h"

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
	EndSession = -3,
	ActorUpdatePacket = 99,
	SpawnUpdatePacket,
	ConnectUpdatePacket,
	ConnectInitPacket,
	ChangeLevelPacket,
	CharacterTypePacket,
	ColorTypePacket,
	DeadUpdatePacket,
	BlockUpdatePacket = 200,
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
		_Ser << Power;
		_Ser << SpawnTime;
	}

	void DeSerialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::DeSerialize(_Ser);
		_Ser >> Pos;
		_Ser >> SpawnSelect;
		_Ser >> Power;
		_Ser >> SpawnTime;
	}

public:
	float4 Pos = float4::Zero;
	int SpawnSelect = 0;
	float SpawnTime = 0.0f;
	int Power = 0;
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
		_Ser << NameInfos;
		_Ser << CharacterTypeInfos;
		_Ser << ColorInfos;
		_Ser << ExistInfos;
	}

	void DeSerialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::DeSerialize(_Ser);
		_Ser >> NameInfos;
		_Ser >> CharacterTypeInfos;
		_Ser >> ColorInfos;
		_Ser >> ExistInfos;
	}

	void SetMyCharacterType(int _Key, ECharacterType _Type)
	{
		int MyCharacterType = static_cast<int>(_Type);
		CharacterTypeInfos[_Key] = MyCharacterType;
	}
	ECharacterType GetMyCharacterType(int _Key)
	{
		return static_cast<ECharacterType>(CharacterTypeInfos[_Key]);
	}

	void SetMyColorType(int _Key, ECharacterColor _Color)
	{
		int MyColor = static_cast<int>(_Color);
		ColorInfos[_Key] = MyColor;
	}
	ECharacterColor GetMyColorType(int _Key)
	{
		return static_cast<ECharacterColor>(ColorInfos[_Key]);
	}

	void SetExist(int _Key, bool _IsExist)
	{
		ExistInfos[_Key] = _IsExist;
	}
	bool GetExist(int _Key)
	{
		return ExistInfos[_Key];
	}

public:
	//std::map<int, ConnectUserInfo> Infos;
	std::map<int, std::string> NameInfos;
	std::map<int, int> CharacterTypeInfos;
	std::map<int, int> ColorInfos;
	std::map<int, bool> ExistInfos;
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

class UChangeLevelPacket : public UEngineProtocol {
public:
	static const EContentPacket Type = EContentPacket::ChangeLevelPacket;
public:
	UChangeLevelPacket()
	{
		SetType(EContentPacket::ChangeLevelPacket);
	}

	void Serialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::Serialize(_Ser);
		_Ser << LevelName;
	}

	void DeSerialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::DeSerialize(_Ser);
		_Ser >> LevelName;
	}

public:
	std::string LevelName = "";
};

class UBlockUpdatePacket : public UEngineProtocol {
public:
	static const EContentPacket Type = EContentPacket::BlockUpdatePacket;
public:
	UBlockUpdatePacket()
	{
		SetType(EContentPacket::BlockUpdatePacket);
	}

	void Serialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::Serialize(_Ser);
		_Ser << IsMoveValue;
		_Ser << MoveDir;
	}

	void DeSerialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::DeSerialize(_Ser);
		_Ser >> IsMoveValue;
		_Ser >> MoveDir;
	}

public:
	bool IsMoveValue = false;
	FVector MoveDir = {};
};

class UEndSession : public UEngineProtocol {
public:
	static const EContentPacket Type = EContentPacket::EndSession;
public:
	UEndSession()
	{
		SetType(EContentPacket::EndSession);
	}

	void Serialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::Serialize(_Ser);
	}

	void DeSerialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::DeSerialize(_Ser);
	}

};


class UDeadUpdatePacket : public UEngineProtocol {
public:
	static const EContentPacket Type = EContentPacket::DeadUpdatePacket;
public:
	UDeadUpdatePacket()
	{
		SetType(EContentPacket::DeadUpdatePacket);
	}

	void Serialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::Serialize(_Ser);
		_Ser << Order;
		_Ser << DeadValue;
	}

	void DeSerialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::DeSerialize(_Ser);
		_Ser >> Order;
		_Ser >> DeadValue;
	}

public:
	int Order = 0;
	bool DeadValue = false;
};

