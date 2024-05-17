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


protected:

private:
	ServerNumber();
	~ServerNumber();

	int CurSessionCount = 0;

};