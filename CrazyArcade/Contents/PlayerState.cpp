#include "PreCompile.h"
#include "Player.h"

#include "MainPlayLevel.h"
#include "MapBase.h"

#include "BombBase.h"

void APlayer::StateInit()
{
	// 스테이트 생성
	State.CreateState("Ready");
	State.CreateState("Idle");
	State.CreateState("Run");
	State.CreateState("TrapStart");
	State.CreateState("Traped");
	State.CreateState("TrapEnd");
	State.CreateState("Die");
	State.CreateState("Revival");

	// 함수 세팅
	State.SetUpdateFunction("Ready", std::bind(&APlayer::Ready, this, std::placeholders::_1));
	State.SetStartFunction("Ready", [=]
		{
			Renderer->ChangeAnimation(Type + PlayerColorText + "_Ready");
		}
	);

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
			IsTraped = true;
			CurSpeed = 30.0f;
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
			if (IsTraped == false)
			{
				State.ChangeState("Idle");
				return;
			}

			CurSpeed = BaseSpeed + Speed;
			Renderer->ChangeAnimation(Type + PlayerColorText + "_Revival");
			IsTraped = false;
		});

	State.ChangeState("Ready");
}

void APlayer::Ready(float _DeltaTime)
{
	if (Renderer->IsCurAnimationEnd())
	{
		State.ChangeState("Idle");
	}
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
			Bomb = PlayLevel->GetMap()->SpawnBomb(GetActorLocation(), this).get();
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
	//Devil 효과로 물풍선 제어 불가
	if (true == IsDevil && false == MoveDevil)
	{
		if (0 < BombCount)
		{
			Bomb = PlayLevel->GetMap()->SpawnBomb(GetActorLocation(), this).get();
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
			Bomb = PlayLevel->GetMap()->SpawnBomb(GetActorLocation(), this).get();
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
	//Devil 효과로 물풍선 제어 불가
	if (true == IsDevil && false == MoveDevil)
	{
		if (0 < BombCount)
		{
			Bomb = PlayLevel->GetMap()->SpawnBomb(GetActorLocation(), this).get();
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
		//Devil 효과로 이동 반전되었을 때
		if (true == IsDevil && true == MoveDevil)
		{
			Renderer->ChangeAnimation(Type + PlayerColorText + "_Run_Right");
			KeyMove(_DeltaTime, FVector::Right, CurSpeed);
			PlayerDir = EPlayerDir::Right;
		}
		else //기본 이동
		{
			Renderer->ChangeAnimation(Type + PlayerColorText + "_Run_Left");
			KeyMove(_DeltaTime, FVector::Left, CurSpeed);
			PlayerDir = EPlayerDir::Left;
		}
	}
	else if (true == IsPress(VK_RIGHT))
	{
		if (true == IsDevil && true == MoveDevil)
		{
			Renderer->ChangeAnimation(Type + PlayerColorText + "_Run_Left");
			KeyMove(_DeltaTime, FVector::Left, CurSpeed);
			PlayerDir = EPlayerDir::Left;
		}
		else
		{
			Renderer->ChangeAnimation(Type + PlayerColorText + "_Run_Right");
			KeyMove(_DeltaTime, FVector::Right, CurSpeed);
			PlayerDir = EPlayerDir::Right;

		}
	}
	else if (true == IsPress(VK_UP))
	{
		if (true == IsDevil && true == MoveDevil)
		{
			Renderer->ChangeAnimation(Type + PlayerColorText + "_Run_Down");
			KeyMove(_DeltaTime, FVector::Down, CurSpeed);
			PlayerDir = EPlayerDir::Down;
		}
		else
		{
			Renderer->ChangeAnimation(Type + PlayerColorText + "_Run_Up");
			KeyMove(_DeltaTime, FVector::Up, CurSpeed);
			PlayerDir = EPlayerDir::Up;
		}
	}
	else if (true == IsPress(VK_DOWN))
	{
		if (true == IsDevil && true == MoveDevil)
		{
			Renderer->ChangeAnimation(Type + PlayerColorText + "_Run_Up");
			KeyMove(_DeltaTime, FVector::Up, CurSpeed);
			PlayerDir = EPlayerDir::Up;
		}
		else
		{
			Renderer->ChangeAnimation(Type + PlayerColorText + "_Run_Down");
			KeyMove(_DeltaTime, FVector::Down, CurSpeed);
			PlayerDir = EPlayerDir::Down;
		}
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

	if (true == IsDevil)
	{
		IsDevil = false;
		Renderer->SetMulColor(FVector::One);
		DevilTime = 10.0f;
	}

	// 이동
	
	if (true == IsPress(VK_LEFT))
	{
		KeyMove(_DeltaTime, FVector::Left, CurSpeed);
	}
	else if (true == IsPress(VK_RIGHT))
	{
		KeyMove(_DeltaTime, FVector::Right, CurSpeed);
	}
	else if (true == IsPress(VK_UP))
	{
		KeyMove(_DeltaTime, FVector::Up, CurSpeed);
	}
	else if (true == IsPress(VK_DOWN))
	{
		KeyMove(_DeltaTime, FVector::Down, CurSpeed);
	}
}

void APlayer::Traped(float _DeltaTime)
{
	if (Renderer->IsCurAnimationEnd())
	{
		State.ChangeState("TrapEnd");
	}
	if (true == IsPress(VK_LEFT))
	{
		KeyMove(_DeltaTime, FVector::Left, CurSpeed);
	}
	else if (true == IsPress(VK_RIGHT))
	{
		KeyMove(_DeltaTime, FVector::Right, CurSpeed);
	}
	else if (true == IsPress(VK_UP))
	{
		KeyMove(_DeltaTime, FVector::Up, CurSpeed);
	}
	else if (true == IsPress(VK_DOWN))
	{
		KeyMove(_DeltaTime, FVector::Down, CurSpeed);
	}

	// 바늘 사용하면
	if (true == IsDown('2'))
	{
		State.ChangeState("Revival");
		return;
	}
}

void APlayer::TrapEnd(float _DeltaTime)
{
	if (Renderer->IsCurAnimationEnd())
	{
		State.ChangeState("Die");
	}
	if (true == IsPress(VK_LEFT))
	{
		KeyMove(_DeltaTime, FVector::Left, CurSpeed);
	}
	else if (true == IsPress(VK_RIGHT))
	{
		KeyMove(_DeltaTime, FVector::Right, CurSpeed);
	}
	else if (true == IsPress(VK_UP))
	{
		KeyMove(_DeltaTime, FVector::Up, CurSpeed);
	}
	else if (true == IsPress(VK_DOWN))
	{
		KeyMove(_DeltaTime, FVector::Down, CurSpeed);
	}

	// 바늘 사용하면
	if (true == IsDown('2'))
	{
		State.ChangeState("Revival");
		return;
	}
}

void APlayer::Die(float _Update)
{
}

void APlayer::Revival(float _DeltaTime)
{
	if (Renderer->IsCurAnimationEnd())
	{
		State.ChangeState("Idle");
		return;
	}
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
	if (false == IsTraped)
	{
		State.ChangeState("TrapStart");
	}
	else
	{
		return;
	}
}