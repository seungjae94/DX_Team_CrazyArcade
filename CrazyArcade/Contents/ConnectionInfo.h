#pragma once
#include "CrazyArcadeEnum.h"

struct ConnectUserInfo 
{
public:
	std::string MyName = "Anonymous";

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

private:
	int MyCharacterType = 0;
	int MyColorType = 0;
	bool IsDead = false;
	bool IsExist = true;
	//ECharacterType MyCharacterType = ECharacterType::None;
	//ECharacterColor MyColorType = ECharacterColor::None;
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

	void SetEmpty(int _Order) {
		UserInfos[_Order].SetMyColorType(ECharacterColor::None);
		UserInfos[_Order].SetMyCharacterType(ECharacterType::None);
		UserInfos[_Order].MyName = "";
		UserInfos[_Order].SetIsExist(false);
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
		if (RedCount == 0 && BlueCount >= 1)
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

protected:

private:
	ConnectionInfo();
	~ConnectionInfo();

	int MyOrder = 0;

	int RedCount = 0;
	int BlueCount = 0;

	ECharacterColor Wins = ECharacterColor::None;

	std::map<int, ConnectUserInfo> UserInfos;

};