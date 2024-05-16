#pragma once

class ServerNumber
{
public:


	ServerNumber(const ServerNumber& _Other) = delete;
	ServerNumber(ServerNumber&& _Other) noexcept = delete;
	ServerNumber& operator=(const ServerNumber& _Other) = delete;
	ServerNumber& operator=(ServerNumber&& _Other) noexcept = delete;

	// Singleton
	static ServerNumber& GetInst()
	{
		// Áö¿ªstatic ½Ì±ÛÅæ
		static ServerNumber Inst = ServerNumber();
		return Inst;
	}

	void Connected()
	{
		Count++;
	}

	void DisConnected(int _MyNum)
	{
		Count--;
	}

	int GetCount()
	{
		return Count;
	}

protected:

private:
	ServerNumber();
	~ServerNumber();

	int Count = 0;
};