#include "PreCompile.h"
#include "EngineNetWindow.h"
#include <EngineBase/EngineServer.h>


UEngineNetWindow::UEngineNetWindow() 
{
	IP.resize(100);
}

UEngineNetWindow::~UEngineNetWindow() 
{
}

void UEngineNetWindow::ServerOpen()
{
	if (nullptr != ServerOpenFunction)
	{
		NetType = ENetType::Server;
		ServerOpenFunction();
	}
}

void UEngineNetWindow::ClientOpen(std::string_view _Ip, int _Port)
{
	if (nullptr != ServerOpenFunction)
	{
		NetType = ENetType::Client;
		ClientConnectFunction("127.0.0.1", 30000);
	}
}
void UEngineNetWindow::OnGui(ULevel* Level, float _Delta)
{
	if (NetType != ENetType::None)
	{
		switch (NetType)
		{
		case ENetType::Server:
		{
			ImGui::Text("Server");
			break;
		}
		case ENetType::Client:
		{
			ImGui::Text("Client");
			break;
		}
		default:
			break;
		}

		return;
	}

	if (true == ImGui::Button("ServerOpen"))
	{
		if (nullptr != ServerOpenFunction)
		{
			NetType = ENetType::Server;
			ServerOpenFunction();
		}
	}

	ImGui::InputText("IP", &IP[0], IP.size());
	ImGui::SameLine();
	ImGui::InputInt("PORT", &PORT);
	if (true == ImGui::Button("Connect"))
	{
		if (nullptr != ServerOpenFunction)
		{
			NetType = ENetType::Client;
			ClientConnectFunction(IP, PORT);
		}
	}
}
