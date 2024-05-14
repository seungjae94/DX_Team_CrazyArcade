#include "PreCompile.h"
#include "Player.h"

#include "MainPlayLevel.h"
#include "MapBase.h"

#include "Bomb.h"

void APlayer::StateInit()
{
	// 스테이트 생성
	State.CreateState("Idle");
	State.CreateState("Run");
	State.CreateState("Lock");
	State.CreateState("Escape");
	State.CreateState("Die");

	// 함수 세팅
	State.SetUpdateFunction("Idle", std::bind(&APlayer::Idle, this, std::placeholders::_1));
	State.SetStartFunction("Idle", [=]
		{
			switch (PlayerDir)
			{
			case EPlayerDir::Left:
				Renderer->ChangeAnimation("Idle_Left");
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

	State.SetUpdateFunction("Lock", std::bind(&APlayer::Lock, this, std::placeholders::_1));
	State.SetStartFunction("Lock", [=]()
		{
		});

	State.SetUpdateFunction("Escape", std::bind(&APlayer::Escape, this, std::placeholders::_1));
	State.SetStartFunction("Escape", [=]()
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
	// Bomb 설치
	if (true == IsDown(VK_SPACE))
	{
		std::shared_ptr<ABomb> Bomb = GetWorld()->SpawnActor<ABomb>("Bomb");
		Bomb->SetActorLocation(GetActorLocation());
		Bomb->AddActorLocation({ 0.0f, BlockSize / 2.0f });
	}

	if (true == IsPress('A') || true == IsPress('D') || true == IsPress('W') || true == IsPress('S'))
	{
		State.ChangeState("Run");
		return;
	}
}

void APlayer::Run(float _DeltaTime)
{
	// Bomb 설치
	if (true == IsDown(VK_SPACE))
	{
		std::shared_ptr<ABomb> Bomb = GetWorld()->SpawnActor<ABomb>("Bomb");
		Bomb->SetActorLocation(GetActorLocation());
	}

	if (true == IsPress('A'))
	{
		Renderer->ChangeAnimation("Run_Left");
		//Renderer->SetDir(EEngineDir::Left);
		KeyMove(_DeltaTime, FVector::Left, CalSpeed);
		PlayerDir = EPlayerDir::Left;
	}
	else if (true == IsPress('D'))
	{
		Renderer->ChangeAnimation("Run_Right");
		//Renderer->SetDir(EEngineDir::Right);
		KeyMove(_DeltaTime, FVector::Right, CalSpeed);
		PlayerDir = EPlayerDir::Right;
	}
	else if (true == IsPress('W'))
	{
		Renderer->ChangeAnimation("Run_Up");
		//Renderer->SetDir(EEngineDir::Right);
		KeyMove(_DeltaTime, FVector::Up, CalSpeed);
		PlayerDir = EPlayerDir::Up;
	}
	else if (true == IsPress('S'))
	{
		Renderer->ChangeAnimation("Run_Down");
		//Renderer->SetDir(EEngineDir::Right);
		KeyMove(_DeltaTime, FVector::Down, CalSpeed);
		PlayerDir = EPlayerDir::Down;
	}

	if (true == IsFree('A') && true == IsFree('D') && true == IsFree('W') && true == IsFree('S'))
	{
		State.ChangeState("Idle");
		return;
	}
}

void APlayer::Lock(float _DeltaTime)
{
}

void APlayer::Escape(float _DeltaTime)
{
}

void APlayer::Die(float _Update)
{

}

void APlayer::KeyMove(float _DeltaTime, float4 _Dir, float _Speed)
{
	FVector NextPos = GetActorLocation() + FVector(_DeltaTime * _Speed * _Dir.X, _DeltaTime * _Speed * _Dir.Y, 0.0f);
	bool CanMove = PlayLevel->GetMap()->CanMovePos(NextPos, _Dir);
	if (true == CanMove)
	{
		AddActorLocation(_Dir * _DeltaTime * _Speed);
	}
}
