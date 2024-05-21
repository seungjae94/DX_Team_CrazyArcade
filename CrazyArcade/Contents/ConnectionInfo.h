#pragma once
#include "CrazyArcadeEnum.h"

struct ConnectUserInfo 
{
public:
	std::string MyName = "Anonymous";

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

private:
	int MyCharacterType = 0;
	int MyColorType = 0;

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


	void SetUserInfos(std::map<int, ConnectUserInfo> _Infos)
	{
		UserInfos = _Infos;
	}
	void PushUserInfos(int _Order, std::string _Name)
	{
		UserInfos[_Order].MyName = _Name;
	}
	std::map<int, ConnectUserInfo>& GetUserInfos()
	{
		return UserInfos;
	}

	int GetInfoSize() const
	{
		return static_cast<int>(UserInfos.size());
	}

protected:

private:
	ConnectionInfo();
	~ConnectionInfo();

	int MyOrder = 0;

	std::map<int, ConnectUserInfo> UserInfos;

};