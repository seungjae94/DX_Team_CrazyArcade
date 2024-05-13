#pragma once
#include "EngineDefines.h"
#include "EngineEditorWindow.h"
#include <vector>

enum class ENetType
{
	None,
	Server,
	Client
};

// Ό³Έν :
class UEngineNet;
class UEngineNetWindow : public UEngineEditorWindow
{
public:
	// constrcuter destructer
	UEngineNetWindow();
	~UEngineNetWindow();

	// delete Function
	UEngineNetWindow(const UEngineNetWindow& _Other) = delete;
	UEngineNetWindow(UEngineNetWindow&& _Other) noexcept = delete;
	UEngineNetWindow& operator=(const UEngineNetWindow& _Other) = delete;
	UEngineNetWindow& operator=(UEngineNetWindow&& _Other) noexcept = delete;

	void SetServerOpenFunction(std::function<void()> _Function)
	{
		ServerOpenFunction = _Function;
	}

	void SetClientConnectFunction(std::function<void(std::string, short)> _Function)
	{
		ClientConnectFunction = _Function;
	}

protected:
	void OnGui(ULevel* Level, float _Delta) override;

private:
	std::function<void()> ServerOpenFunction = nullptr;
	std::function<void(std::string, short)> ClientConnectFunction = nullptr;

	std::string IP = "127.0.0.1";
	int PORT = 30000;

	ENetType NetType = ENetType::None;
};

