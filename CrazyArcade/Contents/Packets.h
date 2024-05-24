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
	Reject = -4,
	EndSession = -3,
	ActorUpdatePacket = 99,
	SpawnUpdatePacket,
	ConnectUpdatePacket,
	ConnectInitPacket,
	ChangeLevelPacket,
	CharacterTypePacket,
	ColorTypePacket,
	DeadUpdatePacket,
	CheatingPacket,
	ReadyUpdatePacket,
	StageUpdatePacket,
	FadeOutUpdatePacket,
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
		_Ser << IsNeedleUse;
	}

	void DeSerialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::DeSerialize(_Ser);
		_Ser >> Pos;
		_Ser >> SpriteName;
		_Ser >> SpawnSelect;
		_Ser >> IsNeedleUse;
	}

public:
	float4 Pos = float4::Zero;
	std::string SpriteName; // ?? 랜덤
	int SpawnSelect = 0;
	bool IsNeedleUse = false;
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

		_Ser << static_cast<int>(Infos.size());

		for (std::pair<const int, ConnectUserInfo>& Pair : Infos)
		{
			int Key = Pair.first;
			ConnectUserInfo& Info = Pair.second;
			_Ser << Key;
			_Ser << Info.MyName;
			_Ser << static_cast<int>(Info.GetMyCharacterType());
			_Ser << static_cast<int>(Info.GetMyColorType());
			_Ser << Info.GetIsDead();
			_Ser << Info.GetIsExist();
			_Ser << Info.GetIsReady();
		}
		
	}

	void DeSerialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::DeSerialize(_Ser);

		Infos.clear();

		int Count;
		_Ser >> Count;

		for (int i = 0; i < Count; ++i)
		{
			int Key;
			std::string MyName;
			int MyCharacterType;
			int MyColorType;
			bool IsDead;
			bool IsExist;
			bool IsReady;

			_Ser >> Key;
			_Ser >> MyName;
			_Ser >> MyCharacterType;
			_Ser >> MyColorType;
			_Ser >> IsDead;
			_Ser >> IsExist;
			_Ser >> IsReady;

			Infos[Key].MyName = MyName;
			Infos[Key].SetMyCharacterType(static_cast<ECharacterType>(MyCharacterType));
			Infos[Key].SetMyColorType(static_cast<ECharacterColor>(MyColorType));
			Infos[Key].SetIsDead(IsDead);
			Infos[Key].SetIsExist(IsExist);
			Infos[Key].SetIsReady(IsReady);
		}
	}

	void SetMyCharacterType(int _Key, ECharacterType _Type)
	{
		Infos[_Key].SetMyCharacterType(_Type);
	}
	ECharacterType GetMyCharacterType(int _Key)
	{
		return Infos[_Key].GetMyCharacterType();
	}

	void SetMyColorType(int _Key, ECharacterColor _Color)
	{
		Infos[_Key].SetMyColorType(_Color);
	}
	ECharacterColor GetMyColorType(int _Key)
	{
		return Infos[_Key].GetMyColorType();
	}

	void SetExist(int _Key, bool _IsExist)
	{
		Infos[_Key].SetIsExist(_IsExist);
	}
	bool GetExist(int _Key)
	{
		return Infos[_Key].GetIsExist();
	}

	void SetReady(int _Key, bool _IsReady)
	{
		Infos[_Key].SetIsReady(_IsReady);
	}
	bool GetReady(int _Key)
	{
		return Infos[_Key].GetIsReady();
	}

public:
	std::map<int, ConnectUserInfo> Infos;
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
		_Ser << Pos;
		_Ser << IsDestroy;
	}

	void DeSerialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::DeSerialize(_Ser);
		_Ser >> IsMoveValue;
		_Ser >> MoveDir;
		_Ser >> Pos;
		_Ser >> IsDestroy;
	}

public:
	bool IsMoveValue = false;
	FVector MoveDir = {};
	FVector Pos = {};
	bool IsDestroy = false;
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

class UReadyUpdatePacket : public UEngineProtocol {
public:
	static const EContentPacket Type = EContentPacket::ReadyUpdatePacket;
public:
	UReadyUpdatePacket()
	{
		SetType(EContentPacket::ReadyUpdatePacket);
	}

	void Serialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::Serialize(_Ser);
		_Ser << Order;
		_Ser << ReadyValue;
	}

	void DeSerialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::DeSerialize(_Ser);
		_Ser >> Order;
		_Ser >> ReadyValue;
	}

public:
	int Order = 0;
	bool ReadyValue = false;
};

class UCheatingPacket : public UEngineProtocol {
public:
	static const EContentPacket Type = EContentPacket::CheatingPacket;
public:
	UCheatingPacket()
	{
		SetType(EContentPacket::CheatingPacket);
	}

	void Serialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::Serialize(_Ser);
		_Ser << Cheating;
	}

	void DeSerialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::DeSerialize(_Ser);
		_Ser >> Cheating;
	}

public:
	std::string Cheating;
};

class UServerRejectPacket : public UEngineProtocol {
public:
	static const EContentPacket Type = EContentPacket::Reject;
public:
	UServerRejectPacket()
	{
		SetType(EContentPacket::Reject);
	}

	void Serialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::Serialize(_Ser);
		_Ser << WhichSession;
	}

	void DeSerialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::DeSerialize(_Ser);
		_Ser >> WhichSession;
	}

public:
	int WhichSession;
};

class UStageUpdatePacket : public UEngineProtocol {
public:
	static const EContentPacket Type = EContentPacket::StageUpdatePacket;
public:
	UStageUpdatePacket()
	{
		SetType(EContentPacket::StageUpdatePacket);
	}

	void Serialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::Serialize(_Ser);
		_Ser << static_cast<int>(MapType);
	}

	void DeSerialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::DeSerialize(_Ser);
		int Temp;
		_Ser >> Temp;
		MapType = static_cast<EMapType>(Temp);
	}

public:
	EMapType MapType;
};

class UFadeOutUpdatePacket : public UEngineProtocol {
public:
	static const EContentPacket Type = EContentPacket::FadeOutUpdatePacket;
public:
	UFadeOutUpdatePacket()
	{
		SetType(EContentPacket::FadeOutUpdatePacket);
	}

	void Serialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::Serialize(_Ser);
		_Ser << IsFadeOut;
	}

	void DeSerialize(UEngineSerializer& _Ser) override
	{
		UEngineProtocol::DeSerialize(_Ser);
		_Ser >> IsFadeOut;
	}

public:
	bool IsFadeOut = false;
};