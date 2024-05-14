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
		if (0 < BombCount)
		{
			std::shared_ptr<ABomb> Bomb = GetWorld()->SpawnActor<ABomb>("Bomb");
			Bomb->SetActorLocation(GetActorLocation());
			--BombCount;
		}
	}

	if (true == IsPress(VK_LEFT) || true == IsPress(VK_RIGHT) || true == IsPress(VK_UP) || true == IsPress(VK_DOWN))
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
		if (0 < BombCount)
		{
			std::shared_ptr<ABomb> Bomb = GetWorld()->SpawnActor<ABomb>("Bomb");
			Bomb->SetActorLocation(GetActorLocation());
			--BombCount;
		}
	}

	if (true == IsPress(VK_LEFT))
	{
		Renderer->ChangeAnimation("Run_Left");
		//Renderer->SetDir(EEngineDir::Left);
		KeyMove(_DeltaTime, FVector::Left, CurSpeed);
		PlayerDir = EPlayerDir::Left;
	}
	else if (true == IsPress(VK_RIGHT))
	{
		Renderer->ChangeAnimation("Run_Right");
		//Renderer->SetDir(EEngineDir::Right);
		KeyMove(_DeltaTime, FVector::Right, CurSpeed);
		PlayerDir = EPlayerDir::Right;
	}
	else if (true == IsPress(VK_UP))
	{
		Renderer->ChangeAnimation("Run_Up");
		//Renderer->SetDir(EEngineDir::Right);
		KeyMove(_DeltaTime, FVector::Up, CurSpeed);
		PlayerDir = EPlayerDir::Up;
	}
	else if (true == IsPress(VK_DOWN))
	{
		Renderer->ChangeAnimation("Run_Down");
		//Renderer->SetDir(EEngineDir::Right);
		KeyMove(_DeltaTime, FVector::Down, CurSpeed);
		PlayerDir = EPlayerDir::Down;
	}

	if (true == IsFree(VK_LEFT) && true == IsFree(VK_RIGHT) && true == IsFree(VK_UP) && true == IsFree(VK_DOWN))
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
