#include "PreCompile.h"
#include "Player.h"

void APlayer::StateInit()
{
	// 스테이트 생성
	State.CreateState("Idle");
	State.CreateState("Run");
	State.CreateState("Die");

	// 함수 세팅
	State.SetUpdateFunction("Idle", std::bind(&APlayer::Idle, this, std::placeholders::_1));
	State.SetStartFunction("Idle", [=]
		{
			switch (PlayerDir)
			{
			case EPlayerDir::Left:
				Renderer->ChangeAnimation("Idle_Right");
				break;
			case EPlayerDir::Right:
				Renderer->ChangeAnimation("Idle_Right");
				break;
			case EPlayerDir::Up:
				Renderer->ChangeAnimation("Idle_Up");
				break;
			case EPlayerDir::Down:
				Renderer->ChangeAnimation("Idle_Down");
				break;
			default:
				break;
			}
		}
	);

	State.SetUpdateFunction("Run", std::bind(&APlayer::Run, this, std::placeholders::_1));
	State.SetStartFunction("Run", [=]()
		{
		});

	State.SetUpdateFunction("Die", std::bind(&APlayer::Die, this, std::placeholders::_1));
	State.SetStartFunction("Die", [=]()
		{
		});

	State.ChangeState("Idle");
}

void APlayer::Idle(float _Update)
{
	if (true == IsPress('A') || true == IsPress('D') || true == IsPress('W') || true == IsPress('S'))
	{
		State.ChangeState("Run");
		return;
	}
}

void APlayer::Run(float _DeltaTime)
{
	if (true == IsPress('A'))
	{
		Renderer->ChangeAnimation("Run_Right");
		Renderer->SetDir(EEngineDir::Left);
		KeyMove(_DeltaTime, FVector::Left, CalSpeed);
		PlayerDir = EPlayerDir::Left;
	}
	else if (true == IsPress('D'))
	{
		Renderer->ChangeAnimation("Run_Right");
		Renderer->SetDir(EEngineDir::Right);
		KeyMove(_DeltaTime, FVector::Right, CalSpeed);
		PlayerDir = EPlayerDir::Right;
	}
	else if (true == IsPress('W'))
	{
		Renderer->ChangeAnimation("Run_Up");
		Renderer->SetDir(EEngineDir::Right);
		KeyMove(_DeltaTime, FVector::Up, CalSpeed);
		PlayerDir = EPlayerDir::Up;
	}
	else if (true == IsPress('S'))
	{
		Renderer->ChangeAnimation("Run_Down");
		Renderer->SetDir(EEngineDir::Right);
		KeyMove(_DeltaTime, FVector::Down, CalSpeed);
		PlayerDir = EPlayerDir::Down;
	}

	if (true == IsUp('A') || true == IsUp('D') || true == IsUp('W') || true == IsUp('S'))
	{
		State.ChangeState("Idle");
	}
}

void APlayer::Die(float _Update)
{

}

void APlayer::KeyMove(float _DeltaTime, float4 _Dir, float _Speed)
{
	AddActorLocation(_Dir * _DeltaTime * _Speed);
}
