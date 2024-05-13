#include "PreCompile.h"
#include "Player.h"

void APlayer::StateInit()
{
	// 스테이트 생성
	State.CreateState("PlayerIdle");
	State.CreateState("PlayerRun");
	State.CreateState("PlayerDie");

	// 함수들 세팅
	State.SetUpdateFunction("PlayerIdle", std::bind(&APlayer::Idle, this, std::placeholders::_1));
	State.SetStartFunction("PlayerIdle", [this]()
		{
		});


	State.SetUpdateFunction("PlayerRun", std::bind(&APlayer::Run, this, std::placeholders::_1));
	State.SetStartFunction("PlayerRun", [this]()
		{
		});

	State.SetUpdateFunction("PlayerDie", std::bind(&APlayer::Die, this, std::placeholders::_1));
	State.SetStartFunction("PlayerDie", [this]()
		{
		});


	State.ChangeState("PlayerIdle");
}

void APlayer::Idle(float _DeltaTime)
{
	// 상태 변화
	if (true == IsPress('A') || true == IsPress('D') || true == IsPress('W') || true == IsPress('S'))
	{
		State.ChangeState("PlayerRun");
		return;
	}
}

void APlayer::Run(float _DeltaTime)
{
	if (true == IsPress('A'))
	{
		AddActorLocation(FVector::Left * Speed * _DeltaTime);
	}
	if (true == IsPress('D'))
	{
		AddActorLocation(FVector::Right * Speed * _DeltaTime);
	}
	if (true == IsPress('W'))
	{
		AddActorLocation(FVector::Up * Speed * _DeltaTime);
	}
	if (true == IsPress('S'))
	{
		AddActorLocation(FVector::Down * Speed * _DeltaTime);
	}
	
	// 상태 변화
	if (true == IsFree('A') && true == IsFree('D') && true == IsFree('W') && true == IsFree('S'))
	{
		State.ChangeState("PlayerIdle");
		return;
	}
}

void APlayer::Die(float _DeltaTime)
{
}
