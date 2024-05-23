#pragma once
#include "EngineNet.h"
#include "TCPSession.h"
#include "EngineThread.h"

// Ό³Έν :
class UEngineClient : public UEngineNet
{
public:
	// constrcuter destructer
	UEngineClient();
	~UEngineClient();

	// delete Function
	UEngineClient(const UEngineClient& _Other) = delete;
	UEngineClient(UEngineClient&& _Other) noexcept = delete;
	UEngineClient& operator=(const UEngineClient& _Other) = delete;
	UEngineClient& operator=(UEngineClient&& _Other) noexcept = delete;

	void Send(std::shared_ptr<UEngineProtocol> _Protocol) override;

	int GetSessionToken()
	{
		return Session.GetSessionToken();
	}
	void SetSessionToken(int _SessionToken)
	{
		Session.SetSessionToken(_SessionToken);
	}

	void Off() override
	{
		UEngineNet::Off();
		Session.End();
	}

	bool IsNetConnetion() override{
		return	Session.IsServerConnected();
	}

protected:
	void ServerOpen(int _Port, int _BackLog) override;
	void Connect(std::string _Ip, int _Port) override;

private:
	UTCPSession Session;
	UEngineThread RecvThread;
};

