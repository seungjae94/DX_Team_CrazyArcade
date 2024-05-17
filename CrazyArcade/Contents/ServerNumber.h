#pragma once

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

	int GetCurSessionCount()
	{
		return CurSessionCount;
	}

	void SetSessionCount(int _Count)
	{
		CurSessionCount = _Count;
	}

	void AddSession()
	{
		CurSessionCount += 1;
	}

	void MinSession()
	{
		CurSessionCount -= 1;
	}

	void SetOrder(int _Order)
	{
		MyOrder = _Order;
	}
	int GetOrder()
	{
		return MyOrder;
	}

	void SetInfo(int _Order, std::string _Name)
	{
		UserInfo[_Order] = _Name;
	}
	std::string GetName(int _Order)
	{
		return UserInfo[_Order];
	}
	
	void SetMyName(std::string _Name)
	{
		MyName = _Name;
	}
	std::string GetMyName()
	{
		return MyName;
	}


protected:

private:
	ServerNumber();
	~ServerNumber();

	int CurSessionCount = 0;
	int MyOrder = 0;
	std::string MyName = "";
	std::map<int, std::string> UserInfo;
};