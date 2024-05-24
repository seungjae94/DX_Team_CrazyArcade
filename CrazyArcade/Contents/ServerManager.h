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

	int GetServerSize() {
		return ServerSize;
	}

	void ServerOpen();

	void ClientOpen(std::string_view _Ip, int _Port);


	void AddHandlerFunction();

	void Update(float _DeltaTime);

	void ServerUpdate(float _DeltaTime);
	void ClientUpdate(float _DeltaTime);

	void BoxTokenInit();

	void ServerInit();
	bool ServerBool = false;
	void ClientInit();
	bool ClientBool = false;

	void SManagerInit();
	void CManagerInit();
	void CFailInit();

	ENetType GetNetType() {
		return ManagerType;
	}

	void ReserveHandler(std::function<void()> _Handler);

	void PushUpdate(std::function<void()> _Update) {
		std::lock_guard<std::mutex> Lock(UpdateLock);
		UpdateTick.push_back(_Update);
	}
	
	template<typename Type>
	void SetCommonToken(Type _Object) {
		_Object->SetObjectToken(CommonObjectValue++);
	}

protected:

	static int CommonObjectValue;
	std::mutex UpdateLock;
	std::list<std::function<void()>> UpdateTick;

	std::mutex SessinInitMutex;
	//std::vector<bool> SessionInitVec = { true, false, false, false, false, false, false, false };
	ENetType ManagerType = ENetType::None;
private:
	std::list<std::function<void()>> ReservedHandlers;
	int ServerSize = 8;
};


