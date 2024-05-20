#pragma once
#include <EngineCore/EngineNetWindow.h>
#include <EngineBase/NetObject.h>
// Ό³Έν :
class UServerManager : public UNetObject
{
public:
	// constructor destructor
	UServerManager();
	~UServerManager() override;

	// delete Function
	UServerManager(const UServerManager& _Other) = delete;
	UServerManager(UServerManager&& _Other) noexcept = delete;
	UServerManager& operator=(const UServerManager& _Other) = delete;
	UServerManager& operator=(UServerManager&& _Other) noexcept = delete;


	void ServerOpen();

	void ClientOpen(std::string_view _Ip, int _Port);


	void AddHandlerFunction();

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

	void ReserveHandler(std::function<void()> _Handler);

protected:
	std::mutex SessinInitMutex;
	std::vector<bool> SessionInitVec = { true, false, false, false, false, false, false, false };
	ENetType ManagerType = ENetType::None;
private:
	std::list<std::function<void()>> ReservedHandlers;
};


