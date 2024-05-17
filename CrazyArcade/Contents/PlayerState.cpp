#include "PreCompile.h"
#include "Player.h"

#include "MainPlayLevel.h"
#include "MapBase.h"

#include "BombBase.h"

void APlayer::StateInit()
{
	// 스테이트 생성
	State.CreateState("Idle");
	State.CreateState("Run");
	State.CreateState("TrapStart");
	State.CreateState("Traped");
	State.CreateState("TrapEnd");
	State.CreateState("Die");
	State.CreateState("Revival");

	// 함수 세팅
	State.SetUpdateFunction("Idle", std::bind(&APlayer::Idle, this, std::placeholders::_1));
	State.SetStartFunction("Idle", [=]
		{
			switch (PlayerDir)
			{
			case EPlayerDir::Left:
				Renderer->ChangeAnimation(Type + PlayerColorText + "_Idle_Left");
				break;
			case EPlayerDir::Right:
				Renderer->ChangeAnimation(Type + PlayerColorText + "_Idle_Right");
				break;
			case EPlayerDir::Up:
				Renderer->ChangeAnimation(Type + PlayerColorText + "_Idle_Up");
				break;
			case EPlayerDir::Down:
				Renderer->ChangeAnimation(Type + PlayerColorText + "_Idle_Down");
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

	State.SetUpdateFunction("TrapStart", std::bind(&APlayer::TrapStart, this, std::placeholders::_1));
	State.SetStartFunction("TrapStart", [=]()
		{
			Renderer->ChangeAnimation(Type + PlayerColorText + "_TrapStart");
		});

	State.SetUpdateFunction("Traped", std::bind(&APlayer::Traped, this, std::placeholders::_1));
	State.SetStartFunction("Traped", [=]()
		{
			Renderer->ChangeAnimation(Type + PlayerColorText + "_Traped");
		});

	State.SetUpdateFunction("TrapEnd", std::bind(&APlayer::TrapEnd, this, std::placeholders::_1));
	State.SetStartFunction("TrapEnd", [=]()
		{
			Renderer->ChangeAnimation(Type + PlayerColorText + "_TrapEnd");
		});

	State.SetUpdateFunction("Die", std::bind(&APlayer::Die, this, std::placeholders::_1));
	State.SetStartFunction("Die", [=]()
		{
			Renderer->ChangeAnimation(Type + PlayerColorText + "_Die");
			SetPlayerDead();
		});

	State.SetUpdateFunction("Revival", std::bind(&APlayer::Revival, this, std::placeholders::_1));
	State.SetStartFunction("Revival", [=]()
		{
		});

	State.ChangeState("Idle");
}

void APlayer::Idle(float _Update)
{
	// Bomb 피격
	//if (/*피격 당했으면*/)
	if (true == IsDown('1'))
	{
		State.ChangeState("TrapStart");
		return;
	}

	// Bomb 설치
	if (true == IsDown(VK_SPACE))
	{
		if (0 < BombCount)
		{
			Bomb = PlayLevel->GetMap()->SpawnBomb(GetActorLocation(), this);
			if (nullptr != Bomb)
			{
				--BombCount;
			}
		}
		else
		{
			Bomb = nullptr;
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
			Bomb = PlayLevel->GetMap()->SpawnBomb(GetActorLocation(), this);
			if (nullptr != Bomb)
			{
				--BombCount;
			}
		}
		else
		{
			Bomb = nullptr;
		}
	}

	if (true == IsPress(VK_LEFT))
	{
		Renderer->ChangeAnimation(Type + PlayerColorText + "_Run_Left");
		KeyMove(_DeltaTime, FVector::Left, CurSpeed);
		PlayerDir = EPlayerDir::Left;
	}
	else if (true == IsPress(VK_RIGHT))
	{
		Renderer->ChangeAnimation(Type + PlayerColorText + "_Run_Right");
		KeyMove(_DeltaTime, FVector::Right, CurSpeed);
		PlayerDir = EPlayerDir::Right;
	}
	else if (true == IsPress(VK_UP))
	{
		Renderer->ChangeAnimation(Type + PlayerColorText + "_Run_Up");
		KeyMove(_DeltaTime, FVector::Up, CurSpeed);
		PlayerDir = EPlayerDir::Up;
	}
	else if (true == IsPress(VK_DOWN))
	{
		Renderer->ChangeAnimation(Type + PlayerColorText + "_Run_Down");
		KeyMove(_DeltaTime, FVector::Down, CurSpeed);
		PlayerDir = EPlayerDir::Down;
	}

	if (true == IsFree(VK_LEFT) && true == IsFree(VK_RIGHT) && true == IsFree(VK_UP) && true == IsFree(VK_DOWN))
	{
		State.ChangeState("Idle");
		return;
	}
}

void APlayer::TrapStart(float _DeltaTime)
{
	if (Renderer->IsCurAnimationEnd())
	{
		State.ChangeState("Traped");
	}
}

void APlayer::Traped(float _DeltaTime)
{
	if (Renderer->IsCurAnimationEnd())
	{
		State.ChangeState("TrapEnd");
	}
}

void APlayer::TrapEnd(float _DeltaTime)
{
	if (Renderer->IsCurAnimationEnd())
	{
		State.ChangeState("Die");
	}
}

void APlayer::Die(float _Update)
{
}

void APlayer::Revival(float _DeltaTime)
{
}

void APlayer::KeyMove(float _DeltaTime, FVector _Dir, float _Speed)
{
	FVector NextPos = GetActorLocation() + FVector(_DeltaTime * _Speed * _Dir.X, _DeltaTime * _Speed * _Dir.Y, 0.0f);
	bool CanMove = PlayLevel->GetMap()->CanMovePos(NextPos, _Dir);
	if (true == CanMove)
	{
		AddActorLocation(_Dir * _DeltaTime * _Speed);
	}
}

void APlayer::SetTrapState()
{
	State.ChangeState("TrapStart");
}