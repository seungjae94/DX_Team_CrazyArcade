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

	void SetUserInfos(int _Order, std::string _Name)
	{
		UserInfos[_Order] = _Name;
	}
	std::map<int, std::string> GetUserInfos() const
	{
		return UserInfos;
	}
	
	void SetMyName(std::string _Name)
	{
		MyName = _Name;
	}
	std::string GetMyName() const
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
	std::map<int, std::string> UserInfos;
};