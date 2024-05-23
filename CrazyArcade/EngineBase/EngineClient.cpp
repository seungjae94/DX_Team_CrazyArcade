#include "PreCompile.h"
#include "EngineClient.h"
#include "EngineDebug.h"

UEngineClient::UEngineClient()
{
}

UEngineClient::~UEngineClient()
{
}

void UEngineClient::ServerOpen(int _Port, int _BackLog)
{
	MsgBoxAssert("클라이언트로 구현되어있는 인스턴스가 서버로 다시 오픈하려고 했습니다. 불가능합니다.");
}

void UEngineClient::Connect(std::string _Ip, int _Port)
{
	Session.Create();
	Session.SetAdd(_Ip, _Port);
	if (false == Session.Connect())
	{
		MsgBoxAssert("클라이언트로 서버에 접속에 실패했습니다. 서버가 열었는지 포트는 정확한지 아이피도 정확한지 확인하세요.");
		Session.SetServerConnected(false);
		return;
	}
	Session.SetServerConnected(true);
	RecvThread.SetName("Client Recv Thread");
	RecvThread.Start(std::bind(UEngineNet::RecvThreadFunction, &Session, this));
}

void UEngineClient::Send(std::shared_ptr<UEngineProtocol> _Protocol)
{
	if (false == Session.IsTokenInit())
	{
		return;
	}
	Session.Send(_Protocol);


}