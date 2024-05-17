#pragma once
#include "CrazyArcadeEnum.h"

class ServerNumber
{
public:

	ServerNumber(const ServerNumber& _Other) = delete;
	ServerNumber(ServerNumber&& _Other) noexcept = delete;
	ServerNumber& operator=(const ServerNumber& _Other) = delete;
	ServerNumber& operator=(ServerNumber&& _Other) noexcept = delete;

	static ServerNumber& GetInst()
	{
		// Áö¿ªstatic ½Ì±ÛÅæ
		static ServerNumber Inst = ServerNumber();
		return Inst;
	}

	void SetSessionCount(int _Count)
	{
		CurSessionCount = _Count;
	}
	int GetCurSessionCount() const
	{
		return CurSessionCount;
	}

	void SetOrder(int _Order)
	{
		MyOrder = _Order;
	}
	int GetOrder() const
	{
		return MyOrder;
	}
	
	void SetMyName(std::string _Name)
	{
		MyName = _Name;
	}
	std::string GetMyName() const
	{
		return MyName;
	}

	void SetCharacterType(ECharacterType _CharacterType)
	{
		MyCharacterType = _CharacterType;
	}
	ECharacterType GetCharacterType() const
	{
		return MyCharacterType;
	}

	
	void SetCharacterColor(ECharacterColor _CharacterColor)
	{
		MyColorType = _CharacterColor;
	}
	ECharacterColor GetCharacterColor() const
	{
		return MyColorType;
	}

	void SetUserInfos(std::map<int, std::string> _Infos)
	{
		UserInfos = _Infos;
	}
	void PushUserInfos(int _Order, std::string _Name)
	{
		UserInfos[_Order] = _Name;
	}
	std::map<int, std::string>& GetUserInfos()
	{
		return UserInfos;
	}

	void SetCharacterColor(std::map<int, ECharacterColor> _ColorInfos)
	{
		CharacterColorInfos = _ColorInfos;
	}
	void PushCharacterColor(int _Order, ECharacterColor _ColorType)
	{
		CharacterColorInfos[_Order] = _ColorType;
	}
	std::map<int, ECharacterColor>& GetCharacterColorInfos()
	{
		return CharacterColorInfos;
	}

	void SetCharacterType(std::map<int, ECharacterType> _TypeInfos)
	{
		CharacterTypeInfos = _TypeInfos;
	}
	void PushCharacterType(int _Order, ECharacterType _CharacterType)
	{
		CharacterTypeInfos[_Order] = _CharacterType;
	}
	std::map<int, ECharacterType>& GetCharacterTypeInfos()
	{
		return CharacterTypeInfos;
	}


protected:

private:
	ServerNumber();
	~ServerNumber();

	int CurSessionCount = 0;

	int MyOrder = 0;
	std::string MyName = "";

	ECharacterType MyCharacterType = ECharacterType::None;
	ECharacterColor MyColorType = ECharacterColor::None;

	std::map<int, std::string> UserInfos;
	std::map<int, ECharacterType> CharacterTypeInfos;
	std::map<int, ECharacterColor> CharacterColorInfos;

};