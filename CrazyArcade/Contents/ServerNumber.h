#pragma once

class ServerNumber
{
public:
	ServerNumber();
	~ServerNumber();

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

	int CurSessionCount = 0;

protected:

private:

};