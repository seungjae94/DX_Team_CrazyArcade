#pragma once
#include "CrazyArcadeEnum.h"

struct ConnectUserInfo 
{
public:
	std::string MyName;

public:
	
	void SetMyCharacterType(ECharacterType _Type)
	{
		MyCharacterType = static_cast<int>(_Type);
	}
	ECharacterType GetMyCharacterType()
	{
		return static_cast<ECharacterType>(MyCharacterType);
	}

	void SetMyColorType(ECharacterColor _Type)
	{
		MyColorType = static_cast<int>(_Type);
	}
	ECharacterColor GetMyColorType()
	{
		return static_cast<ECharacterColor>(MyColorType);
	}

	void SetIsDead(bool _IsDead)
	{
		IsDead = _IsDead;
	}
	bool GetIsDead()
	{
		return IsDead;
	}

	void SetIsExist(bool _IsExist)
	{
		IsExist = _IsExist;
	}
	bool GetIsExist()
	{
		return IsExist;
	}

	void SetIsReady(bool _IsReady)
	{
		IsReady = _IsReady;
	}
	bool GetIsReady()
	{
		return IsReady;
	}

private:
	int MyCharacterType = 0;
	int MyColorType = 0;
	bool IsDead = false;
	bool IsExist = false;
	bool IsReady = false;
};


class ConnectionInfo
{
public:

	ConnectionInfo(const ConnectionInfo& _Other) = delete;
	ConnectionInfo(ConnectionInfo&& _Other) noexcept = delete;
	ConnectionInfo& operator=(const ConnectionInfo& _Other) = delete;
	ConnectionInfo& operator=(ConnectionInfo&& _Other) noexcept = delete;

	static ConnectionInfo& GetInst()
	{
		// Áö¿ªstatic ½Ì±ÛÅæ
		static ConnectionInfo Inst = ConnectionInfo();
		return Inst;
	}

	void SetOrder(int _Order)
	{
		MyOrder = _Order;
	}
	int GetOrder()
	{
		return MyOrder;
	}
	
	void SetMyName(std::string_view _Name) {
		UserInfos[MyOrder].MyName = _Name;
	}
	std::string_view GetMyName() {
		return UserInfos[MyOrder].MyName;
	}

	void SetCharacterType(ECharacterType _CharacterType)
	{
		UserInfos[MyOrder].SetMyCharacterType(_CharacterType);
	}
	ECharacterType GetCharacterType() 
	{
		return UserInfos[MyOrder].GetMyCharacterType();
	}

	
	void SetCharacterColor(ECharacterColor _CharacterColor)
	{
		UserInfos[MyOrder].SetMyColorType(_CharacterColor);
	}
	ECharacterColor GetCharacterColor()
	{
		return UserInfos[MyOrder].GetMyColorType();
	}

	void SetMyIsReady(bool _IsReady)
	{
		UserInfos[MyOrder].SetIsReady(_IsReady);
	}
	bool GetMyIsReady()
	{
		return UserInfos[MyOrder].GetIsReady();
	}

	void SetEmpty(int _Order) 
	{
		UserInfos.erase(_Order);
	}

	void SetUserInfos(std::map<int, ConnectUserInfo> _Infos)
	{
		UserInfos = _Infos;
	}
	void PushUserInfos(int _Order, std::string _Name)
	{
		UserInfos[_Order].MyName = _Name;
		UserInfos[_Order].SetMyCharacterType(ECharacterType::Random);
		UserInfos[_Order].SetMyColorType(ECharacterColor::Red);
		UserInfos[_Order].SetIsExist(true);
	}
	std::map<int, ConnectUserInfo>& GetUserInfos()
	{
		return UserInfos;
	}

	int GetInfoSize() const
	{
		return static_cast<int>(UserInfos.size());
	}

	int GetBlueCount()
	{
		return BlueCount;
	}
	int GetRedCount()
	{
		return RedCount;
	}

	void TeamCount()
	{
		int BCount = 0;
		int RCount = 0;
		for (std::pair<int, ConnectUserInfo> Iterator : UserInfos)
		{
			if (true == Iterator.second.GetIsDead())
			{
				continue;
			}
			else
			{
				if (ECharacterColor::Blue == Iterator.second.GetMyColorType())
				{
					BCount++;
				}
				if (ECharacterColor::Red == Iterator.second.GetMyColorType())
				{
					RCount++;
				}
			}
		}

		BlueCount = BCount;
		RedCount = RCount;
	}

	ECharacterColor WinCheck()
	{
		if (RedCount == 0 && BlueCount == 0)
		{
			return ECharacterColor::Green;
		}
		else if (RedCount == 0 && BlueCount >= 1)
		{
			return ECharacterColor::Blue;
		}
		else if (BlueCount == 0 && RedCount >= 1)
		{
			return ECharacterColor::Red;
		}
		else
		{
			return ECharacterColor::None;
		}
	}

	void SetWins(ECharacterColor _Wins)
	{
		Wins = _Wins;
	}
	ECharacterColor GetWins()
	{
		return Wins;
	}

	void SetTempName(std::string _TempName)
	{
		TempName = _TempName;
	}
	std::string GetTempName()
	{
		return TempName;
	}

	void SetMapType(EMapType _MapType)
	{
		CurMapType = _MapType;
	}
	EMapType GetCurMapType()
	{
		return CurMapType;
	}

	void SetIsFadeOut(bool _IsFadeOut)
	{
		IsFadeOut = _IsFadeOut;
	}
	bool GetIsFadeOut()
	{
		return IsFadeOut;
	}


protected:

private:
	ConnectionInfo();
	~ConnectionInfo();

	bool IsFadeOut = false;

	int MyOrder = 0;
	int RedCount = 0;
	int BlueCount = 0;

	std::string TempName;
	ECharacterColor Wins = ECharacterColor::None;
	std::map<int, ConnectUserInfo> UserInfos;
	EMapType CurMapType = EMapType::Village;
};