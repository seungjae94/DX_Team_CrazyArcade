#pragma once
#include <EngineCore/EngineCore.h>
#include <EngineBase/EngineNet.h>
#include <EngineBase/NetObject.h>
#include "vector"

#define GetToken UCrazyArcadeCore::GetNewNetObjectTokenSet() 
class UServerManager;
class UEngineNet;
class UEngineNetWindow;
class UCrazyArcadeCore : public UserCore
{
public:
	UCrazyArcadeCore();
	~UCrazyArcadeCore();

	UCrazyArcadeCore(const UCrazyArcadeCore& _Other) = delete;
	UCrazyArcadeCore(UCrazyArcadeCore&& _Other) noexcept = delete;
	UCrazyArcadeCore& operator=(const UCrazyArcadeCore& _Other) = delete;
	UCrazyArcadeCore& operator=(UCrazyArcadeCore&& _Other) noexcept = delete;

	static std::shared_ptr<UEngineNet> Net;
	static UServerManager NetManager;

	static int GetNewNetObjectTokenSet() {
		return UCrazyArcadeCore::Net->GetSessionToken() * 1000 + UNetObject::GetNewObjectToken();
	}
protected:
	void Initialize() override;
	void Tick(float _DeltaTime) override;

	std::vector<bool> SessionInitVec = { true, false, false, false, false, false, false, false};

	void End() override;
private:
	void ResLoad();
	bool IsFunctionInit = false;
	bool ClientInfoInit = false;
	bool ServerInfoInit = false;
};

