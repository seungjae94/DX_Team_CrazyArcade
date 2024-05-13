#include "PreCompile.h"
#include "StateManager.h"

UStateManager::UStateManager()
{
}

UStateManager::~UStateManager()
{
}

void UStateManager::ChangeState(std::string_view _Name)
{
	if (nullptr != CurState && nullptr != CurState->End)
	{
		CurState->End();
	}

	CurState = FindState(_Name);

	if (nullptr != CurState && nullptr != CurState->Start)
	{
		CurState->Start();
	}

	if (nullptr == CurState)
	{
		MsgBoxAssert("존재하지 않는 스테이트로 체인지 하려고 했습니다." + std::string(_Name));
	}
}

void UStateManager::Update(float _Time)
{
	if (nullptr == CurState)
	{
		MsgBoxAssert("스테이트를 설정하지 않고 스테이트 매니저를 사용하려고 했습니다..");
	}

	CurState->Update(_Time);
}

void UStateManager::CreateState(std::string_view _Name)
{
	std::string UpperName = UEngineString::ToUpper(_Name);
	States[UpperName] = std::make_shared<UState>();
	States[UpperName]->SetName(_Name);
}

void UStateManager::SetFunction(std::string_view _Name,
	std::function<void()> _Start /*= nullptr*/,
	std::function<void(float)> _Update /*= nullptr*/,
	std::function<void()> _End /*= nullptr*/
)
{
	std::shared_ptr<UState> State = FindState(_Name);

	if (nullptr == State)
	{
		MsgBoxAssert("존재하지 않는 스테이트 입니다");
	}

	State->Start = _Start;
	State->Update = _Update;
	State->End = _End;
}

std::shared_ptr<UState> UStateManager::FindState(std::string_view _Name)
{
	std::string UpperName = UEngineString::ToUpper(_Name);

	if (false == States.contains(UpperName))
	{
		return nullptr;
	}

	return States[UpperName];
}

void UStateManager::SetStartFunction(std::string_view _Name, std::function<void()> _Function /*= nullptr*/)
{
	std::shared_ptr<UState> State = FindState(_Name);

	if (nullptr == State)
	{
		MsgBoxAssert("존재하지 않는 스테이트 입니다");
	}

	State->Start = _Function;
}

void UStateManager::SetUpdateFunction(std::string_view _Name, std::function<void(float)> _Function /*= nullptr*/)
{
	std::shared_ptr<UState> State = FindState(_Name);

	if (nullptr == State)
	{
		MsgBoxAssert("존재하지 않는 스테이트 입니다");
	}

	State->Update = _Function;
}

void UStateManager::SetEndFunction(std::string_view _Name, std::function<void()> _Function /*= nullptr*/)
{
	std::shared_ptr<UState> State = FindState(_Name);

	if (nullptr == State)
	{
		MsgBoxAssert("존재하지 않는 스테이트 입니다");
	}

	State->End = _Function;
}