#pragma once
#include <EngineCore/EngineCore.h>
#include <EngineBase/EngineNet.h>
#include <EngineBase/NetObject.h>

#define GetToken UCrazyArcadeCore::GetNewNetObjectTokenSet() 

class UEngineNet;
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
	static int GetNewNetObjectTokenSet() {
		return UCrazyArcadeCore::Net->GetSessionToken() * 1000 + UNetObject::GetNewObjectToken();
	}
protected:
	void Initialize() override;
	void Tick(float _DeltaTime) override;
private:
	void ResLoad();

};

