#pragma once
#include <EngineCore/EngineNetWindow.h>
#include <EngineBase/NetObject.h>
// ���� :
class ServerManager : public UEngineNetWindow, public UNetObject
{
public:
	// constructor destructor
	ServerManager();
	~ServerManager() override;

	// delete Function
	ServerManager(const ServerManager& _Other) = delete;
	ServerManager(ServerManager&& _Other) noexcept = delete;
	ServerManager& operator=(const ServerManager& _Other) = delete;
	ServerManager& operator=(ServerManager&& _Other) noexcept = delete;


	void ServerOpen();

	void ClientOpen(std::string_view _Ip, int _Port);

	void SetServerOpenFunction(std::function<void()> _Function)
	{
		UEngineNetWindow::SetServerOpenFunction(_Function);
	}

	void SetClientConnectFunction(std::function<void(std::string, short)> _Function)
	{
		UEngineNetWindow::SetClientConnectFunction(_Function);
	}

	void Update(float _DeltaTime);
	
	void ServerUpdate(float _DeltaTime);
	void ClientUpdate(float _DeltaTime);

	void ServerInit();
	bool ServerBool = false;
	void ClientInit();
	bool ClientBool = false;

	void SManagerInit();
	void CManagerInit();

	ENetType GetNetType() {
		return ManagerType;
	}

protected:
	std::mutex SessinInitMutex;
	std::vector<bool> SessionInitVec = { true, false, false, false, false, false, false, false };
	ENetType ManagerType = ENetType::None;
private:

};


