#include "PreCompile.h"
#include "Player.h"

#include "MainPlayLevel.h"
#include "MapBase.h"

#include "BombBase.h"
#include "ConnectionInfo.h"

void APlayer::StateInit()
{
	// 스테이트 생성
	State.CreateState("Ready");
	State.CreateState("Idle");
	State.CreateState("Run");
	State.CreateState("RidingIdle");
	State.CreateState("RidingRun");
	State.CreateState("RidingDown");
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

	State.SetUpdateFunction("RidingIdle", std::bind(&APlayer::RidingIdle, this, std::placeholders::_1));
	State.SetStartFunction("RidingIdle", [=]
		{
			std::string RidingType = "";
			switch (Riding)
			{
			case ERiding::None:
				State.ChangeState("Idle");
				return;
			case ERiding::Owl:
				RidingType = "Owl";
				break;
			case ERiding::Turtle:
				RidingType = "Turtle";
				break;
			case ERiding::UFO:
				RidingType = "UFO";
				break;
			default:
				break;
			}

			switch (PlayerDir)
			{
			case EPlayerDir::Left:
				Renderer->ChangeAnimation(Type + PlayerColorText + "_Idle" + RidingType + "_Left");
				break;
			case EPlayerDir::Right:
				Renderer->ChangeAnimation(Type + PlayerColorText + "_Idle" + RidingType + "_Right");
				break;
			case EPlayerDir::Up:
				Renderer->ChangeAnimation(Type + PlayerColorText + "_Idle" + RidingType + "_Up");
				break;
			case EPlayerDir::Down:
				Renderer->ChangeAnimation(Type + PlayerColorText + "_Idle" + RidingType + "_Down");
				break;
			default:
				break;
			}
		}
	);

	State.SetUpdateFunction("RidingRun", std::bind(&APlayer::RidingRun, this, std::placeholders::_1));
	State.SetStartFunction("RidingRun", [=]()
		{
		});

	State.SetUpdateFunction("RidingDown", std::bind(&APlayer::RidingDown, this, std::placeholders::_1));
	State.SetStartFunction("RidingDown", [=]()
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
		});

	State.SetUpdateFunction("TrapStart", std::bind(&APlayer::TrapStart, this, std::placeholders::_1));
	State.SetStartFunction("TrapStart", [=]()
		{
			NoHit = true;
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
			Renderer->SetPosition(FVector::Zero);
			Renderer->ChangeAnimation(Type + PlayerColorText + "_Die");
			SetPlayerDead();
		});

	State.SetUpdateFunction("Revival", std::bind(&APlayer::Revival, this, std::placeholders::_1));
	State.SetStartFunction("Revival", [=]()
		{
			NeedleCount--;
			CurSpeed = BaseSpeed + Speed;
			Renderer->ChangeAnimation(Type + PlayerColorText + "_Revival");
			NoHit = false;
		});

	State.ChangeState("Ready");
}

void APlayer::Ready(float _DeltaTime)
{
	if (Renderer->IsCurAnimationEnd())
	{
		State.ChangeState("Idle");
		return;
	}
}

void APlayer::Idle(float _Update)
{
	// 탈 것 탑승
	if (ERiding::None != Riding)
	{
		State.ChangeState("RidingIdle");
		return;
	}

	// 부쉬 Hide
	if (true == PlayLevel->GetMap()->IsBushPos(GetActorLocation()))
	{
		Renderer->SetActive(false);
	}
	else
	{
		Renderer->SetActive(true);
	}

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
		SpawnBombCheckSend();
	}

	//Devil 효과로 물풍선 제어 불가
	if (true == IsDevil && false == MoveDevil)
	{
		SpawnBombCheckSend();
	}

	if (true == IsPress(VK_LEFT) || true == IsPress(VK_RIGHT) || true == IsPress(VK_UP) || true == IsPress(VK_DOWN))
	{
		State.ChangeState("Run");
		return;
	}
}

void APlayer::Run(float _DeltaTime)
{
	if (ERiding::None != Riding)
	{
		State.ChangeState("RidingRun");
		return;
	}

	// 부쉬 Hide
	if (true == PlayLevel->GetMap()->IsBushPos(GetActorLocation()))
	{
		Renderer->SetActive(false);
	}
	else
	{
		Renderer->SetActive(true);
	}

	// Bomb 설치
	if (true == IsDown(VK_SPACE))
	{
		SpawnBombCheckSend();
	}

	//Devil 효과로 물풍선 제어 불가
	if (true == IsDevil && false == MoveDevil)
	{
		SpawnBombCheckSend();
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

void APlayer::RidingIdle(float _Update)
{
	// 부쉬 Hide
	if (true == PlayLevel->GetMap()->IsBushPos(GetActorLocation()))
	{
		Renderer->SetActive(false);
	}
	else
	{
		Renderer->SetActive(true);
	}

	// Bomb 설치
	if (true == IsDown(VK_SPACE))
	{
		SpawnBombCheckSend();
	}

	//Devil 효과로 물풍선 제어 불가
	if (true == IsDevil && false == MoveDevil)
	{
		SpawnBombCheckSend();
	}

	if (true == IsPress(VK_LEFT) || true == IsPress(VK_RIGHT) || true == IsPress(VK_UP) || true == IsPress(VK_DOWN))
	{
		State.ChangeState("RidingRun");
		return;
	}
}

void APlayer::RidingRun(float _DeltaTime)
{
	std::string RidingType = "";
	float RidingSpeed = 0.0f;
	switch (Riding)
	{
	case ERiding::None:
		State.ChangeState("Run");
		return;
	case ERiding::Owl:
		RidingType = "Owl";
		RidingSpeed = 200.0f;
		break;
	case ERiding::Turtle:
		RidingType = "Turtle";
		RidingSpeed = 40.0f;
		break;
	case ERiding::UFO:
		RidingType = "UFO";
		RidingSpeed = 400.0f;
		break;
	default:
		break;
	}

	// 부쉬 Hide
	if (true == PlayLevel->GetMap()->IsBushPos(GetActorLocation()))
	{
		Renderer->SetActive(false);
	}
	else
	{
		Renderer->SetActive(true);
	}

	// Bomb 설치
	if (true == IsDown(VK_SPACE))
	{
		SpawnBombCheckSend();
	}

	//Devil 효과로 물풍선 제어 불가
	if (true == IsDevil && false == MoveDevil)
	{
		SpawnBombCheckSend();
	}

	if (true == IsPress(VK_LEFT))
	{
		//Devil 효과로 이동 반전되었을 때
		if (true == IsDevil && true == MoveDevil)
		{
			Renderer->ChangeAnimation(Type + PlayerColorText + "_Riding" + RidingType + "_Right");
			KeyMove(_DeltaTime, FVector::Right, RidingSpeed);
			PlayerDir = EPlayerDir::Right;
		}
		else //기본 이동
		{
			Renderer->ChangeAnimation(Type + PlayerColorText + "_Riding" + RidingType + "_Left");
			KeyMove(_DeltaTime, FVector::Left, RidingSpeed);
			PlayerDir = EPlayerDir::Left;
		}
	}
	else if (true == IsPress(VK_RIGHT))
	{
		if (true == IsDevil && true == MoveDevil)
		{
			Renderer->ChangeAnimation(Type + PlayerColorText + "_Riding" + RidingType + "_Left");
			KeyMove(_DeltaTime, FVector::Left, RidingSpeed);
			PlayerDir = EPlayerDir::Left;
		}
		else
		{
			Renderer->ChangeAnimation(Type + PlayerColorText + "_Riding" + RidingType + "_Right");
			KeyMove(_DeltaTime, FVector::Right, RidingSpeed);
			PlayerDir = EPlayerDir::Right;

		}
	}
	else if (true == IsPress(VK_UP))
	{
		if (true == IsDevil && true == MoveDevil)
		{
			Renderer->ChangeAnimation(Type + PlayerColorText + "_Riding" + RidingType + "_Down");
			KeyMove(_DeltaTime, FVector::Down, RidingSpeed);
			PlayerDir = EPlayerDir::Down;
		}
		else
		{
			Renderer->ChangeAnimation(Type + PlayerColorText + "_Riding" + RidingType + "_Up");
			KeyMove(_DeltaTime, FVector::Up, RidingSpeed);
			PlayerDir = EPlayerDir::Up;
		}
	}
	else if (true == IsPress(VK_DOWN))
	{
		if (true == IsDevil && true == MoveDevil)
		{
			Renderer->ChangeAnimation(Type + PlayerColorText + "_Riding" + RidingType + "_Up");
			KeyMove(_DeltaTime, FVector::Up, RidingSpeed);
			PlayerDir = EPlayerDir::Up;
		}
		else
		{
			Renderer->ChangeAnimation(Type + PlayerColorText + "_Riding" + RidingType + "_Down");
			KeyMove(_DeltaTime, FVector::Down, RidingSpeed);
			PlayerDir = EPlayerDir::Down;
		}
	}

	if (true == IsFree(VK_LEFT) && true == IsFree(VK_RIGHT) && true == IsFree(VK_UP) && true == IsFree(VK_DOWN))
	{
		State.ChangeState("RidingIdle");
		return;
	}
}

void APlayer::RidingDown(float _DeltaTime)
{
	Riding = ERiding::None;
	NoHit = true;
	if (0.0f <= JumpTime && JumpTime < 0.35f)
	{
		Renderer->AddPosition(FVector::Up * 100.0f * _DeltaTime);
	}
	else if (0.35f <= JumpTime && JumpTime < 0.7f)
	{
		Renderer->AddPosition(FVector::Down * 100.0f * _DeltaTime);
	}
	else
	{
		Renderer->SetPosition({ 0.0f, BlockSize / 2.0f, 0.0f });
		JumpTime = 0.0f;
		NoHit = false;
		State.ChangeState("Idle");
		return;
	}

	JumpTime += _DeltaTime;
}

void APlayer::TrapStart(float _DeltaTime)
{
	TrapStartTime -= _DeltaTime;
	if (TrapStartTime <= 0.0f)
	{
		State.ChangeState("Traped");
		return;
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

	// 부쉬 Hide
	if (true == PlayLevel->GetMap()->IsBushPos(GetActorLocation()))
	{
		Renderer->SetActive(false);
	}
	else
	{
		Renderer->SetActive(true);
	}
}

void APlayer::Traped(float _DeltaTime)
{
	TrapedTime -= _DeltaTime;
	if (TrapedTime <= 0.0f)
	{
		State.ChangeState("TrapEnd");
		return;
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

	// 부쉬 Hide
	if (true == PlayLevel->GetMap()->IsBushPos(GetActorLocation()))
	{
		Renderer->SetActive(false);
	}
	else
	{
		Renderer->SetActive(true);
	}

	if (true == PlayLevel->GetMap()->IsColOtherPlayer(GetActorLocation(), this))
	{
		State.ChangeState("Die");
		return;
	}

	// 바늘 사용하면
	if (true == IsDown('2') && NeedleCount > 0)
	{
		State.ChangeState("Revival");
		return;
	}
}

void APlayer::TrapEnd(float _DeltaTime)
{
	TrapEndTime -= _DeltaTime;
	if (TrapEndTime <= 0.0f)
	{
		State.ChangeState("Die");
		return;
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

	// 부쉬 Hide
	if (true == PlayLevel->GetMap()->IsBushPos(GetActorLocation()))
	{
		Renderer->SetActive(false);
	}
	else
	{
		Renderer->SetActive(true);
	}

	if (true == PlayLevel->GetMap()->IsColOtherPlayer(GetActorLocation(), this))
	{
		State.ChangeState("Die");
		return;
	}

	// 바늘 사용하면
	if (true == IsDown('2') && NeedleCount > 0)
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
	bool IsBombPos = false;
	if (false == IsBombOn)
	{
		IsBombPos = PlayLevel->GetMap()->IsBombPos(NextPos, _Dir);
	}

	if (true == CanMove && false == IsBombPos)
	{
		AddActorLocation(_Dir * _DeltaTime * _Speed);
		FPoint CurPoint = AMapBase::ConvertLocationToPoint(GetActorLocation());
		if (CurPoint != SpawnBombPoint)
		{
			IsBombOn = false;
		}
	}
}

void APlayer::SetTrapState()
{
	if (true == NoHit)
	{
		return;
	}

	if (true == IsSuperman)
	{
		SetSupermanOff();
		NoHit = true;
		DelayCallBack(0.7f, [=]
			{
				NoHit = false;
			}
		);
		return;
	}

	if (ERiding::None != Riding)
	{
		State.ChangeState("RidingDown");
		return;
	}

	State.ChangeState("TrapStart");
}