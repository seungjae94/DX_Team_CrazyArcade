#pragma once
#include <EngineCore/EngineCore.h>

class UCrazyArcadeCore : public UserCore
{
public:
	UCrazyArcadeCore();
	~UCrazyArcadeCore();

	UCrazyArcadeCore(const UCrazyArcadeCore& _Other) = delete;
	UCrazyArcadeCore(UCrazyArcadeCore&& _Other) noexcept = delete;
	UCrazyArcadeCore& operator=(const UCrazyArcadeCore& _Other) = delete;
	UCrazyArcadeCore& operator=(UCrazyArcadeCore&& _Other) noexcept = delete;

protected:
	void Initialize() override;

private:
	void ResLoad();

};

