#include "PreCompile.h"
#include "Player.h"

#include "MainPlayLevel.h"
#include "MapBase.h"

#include "BombBase.h"
#include "ConnectionInfo.h"

void APlayer::StateInit()
{
	SetCharacterType(ConnectionInfo::GetInst().GetCharacterType());
	SetPlayerColor(ConnectionInfo::GetInst().GetCharacterColor());

	// 스테이트 생성
	State.CreateState("Ready");
	State.CreateState("Idle");
	State.CreateState("Run");
	State.CreateState("RidingIdle");
	State.CreateState("RidingRun");
	State.CreateState("RidingDown");
	State.CreateState("TrapStart");
	State.CreateState("Trapped");
	State.CreateState("TrapEnd");
	State.CreateState("Die");
	State.CreateState("Revival");
	State.CreateState("Win");
	State.CreateState("Lose");

	// 함수 세팅
	State.SetUpdateFunction("Ready", std::bind(&APlayer::Ready, this, std::placeholders::_1));
	State.SetStartFunction("Ready", [=]
		{
			NoHit = true;
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
			IsTrapped = true;
			NoHit = true;
			CurSpeed = 30.0f;
			Renderer->ChangeAnimation(Type + PlayerColorText + "_TrapStart");

			UEngineSound::SoundPlay("TrapIn.mp3");
		});

	State.SetUpdateFunction("Trapped", std::bind(&APlayer::Trapped, this, std::placeholders::_1));
	State.SetStartFunction("Trapped", [=]()
		{
			Renderer->ChangeAnimation(Type + PlayerColorText + "_Trapped");
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
			DelayCallBack(0.9f, [=]
				{
					StartBlink(3.0f);
				}
			);
			DelayCallBack(3.9f, [=]
				{
					Renderer->SetActive(false);
					ShadowRenderer->SetActive(false);
				}
			);
			SetPlayerDead();

			UEngineSound::SoundPlay("TrapPop.mp3");
		});

	State.SetUpdateFunction("Revival", std::bind(&APlayer::Revival, this, std::placeholders::_1));
	State.SetStartFunction("Revival", [=]()
		{
			IsTrapped = false;
			NoHit = false;
			CurSpeed = BaseSpeed + Speed;
			TrapStartTime = 0.28f;
			TrappedTime = 4.0f;
			TrapEndTime = 1.6f;
			Renderer->ChangeAnimation(Type + PlayerColorText + "_Revival");

			if ("Revival" != State.GetCurStateName())
			{
				UEngineSound::SoundPlay("Revive.mp3");
			}
		});

	State.SetUpdateFunction("Win", std::bind(&APlayer::Win, this, std::placeholders::_1));
	State.SetStartFunction("Win", [=]()
		{
			NoHit = true;
			Renderer->ChangeAnimation(Type + PlayerColorText + "_Win");
		});

	State.SetUpdateFunction("Lose", std::bind(&APlayer::Lose, this, std::placeholders::_1));
	State.SetStartFunction("Lose", [=]()
		{
			NoHit = true;
			Renderer->ChangeAnimation(Type + PlayerColorText + "_Lose");
		});

	// 시작 상태
	State.ChangeState("Ready");
}

void APlayer::Ready(float _DeltaTime)
{
	if (Renderer->IsCurAnimationEnd())
	{
		NoHit = false;
		State.ChangeState("Idle");
		return;
	}
}

void APlayer::Idle(float _DeltaTime)
{
	// 탈 것 탑승
	if (ERiding::None != Riding)
	{
		State.ChangeState("RidingIdle");
		return;
	}

	// 부쉬 Hide
	HideInBush();

	// 아이템 습득
	PickUpItem();

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
	HideInBush();

	// 아이템 습득
	PickUpItem();

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
			PlayerDir = EPlayerDir::Right;
			PlayerDirVector = FVector::Right;
			KeyMove(_DeltaTime, PlayerDirVector, CurSpeed);
		}
		else //기본 이동
		{
			Renderer->ChangeAnimation(Type + PlayerColorText + "_Run_Left");
			PlayerDir = EPlayerDir::Left;
			PlayerDirVector = FVector::Left;
			KeyMove(_DeltaTime, PlayerDirVector, CurSpeed);
		}
	}
	else if (true == IsPress(VK_RIGHT))
	{
		if (true == IsDevil && true == MoveDevil)
		{
			Renderer->ChangeAnimation(Type + PlayerColorText + "_Run_Left");
			PlayerDir = EPlayerDir::Left;
			PlayerDirVector = FVector::Left;
			KeyMove(_DeltaTime, PlayerDirVector, CurSpeed);
		}
		else
		{
			Renderer->ChangeAnimation(Type + PlayerColorText + "_Run_Right");
			PlayerDir = EPlayerDir::Right;
			PlayerDirVector = FVector::Right;
			KeyMove(_DeltaTime, PlayerDirVector, CurSpeed);
		}
	}
	else if (true == IsPress(VK_UP))
	{
		if (true == IsDevil && true == MoveDevil)
		{
			Renderer->ChangeAnimation(Type + PlayerColorText + "_Run_Down");
			PlayerDir = EPlayerDir::Down;
			PlayerDirVector = FVector::Down;
			KeyMove(_DeltaTime, PlayerDirVector, CurSpeed);
		}
		else
		{
			Renderer->ChangeAnimation(Type + PlayerColorText + "_Run_Up");
			PlayerDir = EPlayerDir::Up;
			PlayerDirVector = FVector::Up;
			KeyMove(_DeltaTime, PlayerDirVector, CurSpeed);
		}
	}
	else if (true == IsPress(VK_DOWN))
	{
		if (true == IsDevil && true == MoveDevil)
		{
			Renderer->ChangeAnimation(Type + PlayerColorText + "_Run_Up");
			PlayerDir = EPlayerDir::Up;
			PlayerDirVector = FVector::Up;
			KeyMove(_DeltaTime, PlayerDirVector, CurSpeed);

		}
		else
		{
			Renderer->ChangeAnimation(Type + PlayerColorText + "_Run_Down");
			PlayerDir = EPlayerDir::Down;
			PlayerDirVector = FVector::Down;
			KeyMove(_DeltaTime, PlayerDirVector, CurSpeed);

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
	HideInBush();

	if (ERiding::UFO != Riding)
	{
		// 아이템 습득
		PickUpItem();
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
	HideInBush();

	if (ERiding::UFO != Riding)
	{
		// 아이템 습득
		PickUpItem();
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

			PlayerDir = EPlayerDir::Right;
			PlayerDirVector = FVector::Right;
			KeyMove(_DeltaTime, PlayerDirVector, RidingSpeed);
		}
		else //기본 이동
		{
			Renderer->ChangeAnimation(Type + PlayerColorText + "_Riding" + RidingType + "_Left");
			PlayerDir = EPlayerDir::Left;
			PlayerDirVector = FVector::Left;
			KeyMove(_DeltaTime, PlayerDirVector, RidingSpeed);
		}
	}
	else if (true == IsPress(VK_RIGHT))
	{
		if (true == IsDevil && true == MoveDevil)
		{
			Renderer->ChangeAnimation(Type + PlayerColorText + "_Riding" + RidingType + "_Left");
			PlayerDir = EPlayerDir::Left;
			PlayerDirVector = FVector::Left;
			KeyMove(_DeltaTime, PlayerDirVector, RidingSpeed);
		}
		else
		{
			Renderer->ChangeAnimation(Type + PlayerColorText + "_Riding" + RidingType + "_Right");
			PlayerDir = EPlayerDir::Right;
			PlayerDirVector = FVector::Right;
			KeyMove(_DeltaTime, PlayerDirVector, RidingSpeed);
		}
	}
	else if (true == IsPress(VK_UP))
	{
		if (true == IsDevil && true == MoveDevil)
		{
			Renderer->ChangeAnimation(Type + PlayerColorText + "_Riding" + RidingType + "_Down");
			PlayerDir = EPlayerDir::Down;
			PlayerDirVector = FVector::Down;
			KeyMove(_DeltaTime, PlayerDirVector, RidingSpeed);
		}
		else
		{
			Renderer->ChangeAnimation(Type + PlayerColorText + "_Riding" + RidingType + "_Up");
			PlayerDir = EPlayerDir::Up;
			PlayerDirVector = FVector::Up;
			KeyMove(_DeltaTime, PlayerDirVector, RidingSpeed);
		}
	}
	else if (true == IsPress(VK_DOWN))
	{
		if (true == IsDevil && true == MoveDevil)
		{
			Renderer->ChangeAnimation(Type + PlayerColorText + "_Riding" + RidingType + "_Up");
			PlayerDir = EPlayerDir::Up;
			PlayerDirVector = FVector::Up;
			KeyMove(_DeltaTime, PlayerDirVector, RidingSpeed);
		}
		else
		{
			Renderer->ChangeAnimation(Type + PlayerColorText + "_Riding" + RidingType + "_Down");
			PlayerDir = EPlayerDir::Down;
			PlayerDirVector = FVector::Down;
			KeyMove(_DeltaTime, PlayerDirVector, RidingSpeed);
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
		State.ChangeState("Trapped");
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
		PlayerDirVector = FVector::Left;
		KeyMove(_DeltaTime, PlayerDirVector, CurSpeed);
	}
	else if (true == IsPress(VK_RIGHT))
	{
		PlayerDirVector = FVector::Right;
		KeyMove(_DeltaTime, PlayerDirVector, CurSpeed);
	}
	else if (true == IsPress(VK_UP))
	{
		PlayerDirVector = FVector::Up;
		KeyMove(_DeltaTime, PlayerDirVector, CurSpeed);
	}
	else if (true == IsPress(VK_DOWN))
	{
		PlayerDirVector = FVector::Down;
		KeyMove(_DeltaTime, PlayerDirVector, CurSpeed);
	}

	// 부쉬 Hide
	HideInBush();

	// 사운드
	//UEngineSound::SoundPlay("TrapIn.mp3");
}

void APlayer::Trapped(float _DeltaTime)
{
	TrappedTime -= _DeltaTime;
	if (TrappedTime <= 0.0f)
	{
		State.ChangeState("TrapEnd");
		return;
	}
	if (true == IsPress(VK_LEFT))
	{
		PlayerDirVector = FVector::Left;
		KeyMove(_DeltaTime, PlayerDirVector, CurSpeed);
	}
	else if (true == IsPress(VK_RIGHT))
	{
		PlayerDirVector = FVector::Right;
		KeyMove(_DeltaTime, PlayerDirVector, CurSpeed);
	}
	else if (true == IsPress(VK_UP))
	{
		PlayerDirVector = FVector::Up;
		KeyMove(_DeltaTime, PlayerDirVector, CurSpeed);
	}
	else if (true == IsPress(VK_DOWN))
	{
		PlayerDirVector = FVector::Down;
		KeyMove(_DeltaTime, PlayerDirVector, CurSpeed);
	}

	// 부쉬 Hide
	HideInBush();

	ECharacterColor ColPlayerColor = PlayLevel->GetMap()->IsColOtherPlayer(GetActorLocation(), this);
	if (ECharacterColor::None != ColPlayerColor && PlayerColor != ColPlayerColor)
	{
		//UEngineSound::SoundPlay("TrapPop.mp3");
		State.ChangeState("Die");
		return;
	}

	if (ECharacterColor::None != ColPlayerColor && PlayerColor == ColPlayerColor)
	{
		//UEngineSound::SoundPlay("Revive.mp3");
		State.ChangeState("Revival");
		return;
	}

	// 바늘 사용하면
	if (true == IsDown(VK_CONTROL) && NeedleCount > 0 && false == IsNeedleUse)
	{
		//UEngineSound::SoundPlay("Revive.mp3");

		IsNeedleUse = true;
		NeedleUpdate();
		NeedleCount--;
		if (NeedleCount <= 0)
		{
			NeedleCount = 0;
		}
		return;
	}
}

void APlayer::TrapEnd(float _DeltaTime)
{
	TrapEndTime -= _DeltaTime;
	if (TrapEndTime <= 0.0f)
	{
		//UEngineSound::SoundPlay("TrapPop.mp3");
		State.ChangeState("Die");
		return;
	}
	if (true == IsPress(VK_LEFT))
	{
		PlayerDirVector = FVector::Left;
		KeyMove(_DeltaTime, PlayerDirVector, CurSpeed);
	}
	else if (true == IsPress(VK_RIGHT))
	{
		PlayerDirVector = FVector::Right;
		KeyMove(_DeltaTime, PlayerDirVector, CurSpeed);
	}
	else if (true == IsPress(VK_UP))
	{
		PlayerDirVector = FVector::Up;
		KeyMove(_DeltaTime, PlayerDirVector, CurSpeed);
	}
	else if (true == IsPress(VK_DOWN))
	{
		PlayerDirVector = FVector::Down;
		KeyMove(_DeltaTime, PlayerDirVector, CurSpeed);
	}

	// 부쉬 Hide
	HideInBush();

	ECharacterColor ColPlayerColor = PlayLevel->GetMap()->IsColOtherPlayer(GetActorLocation(), this);
	if (ECharacterColor::None != ColPlayerColor && PlayerColor != ColPlayerColor)
	{
		State.ChangeState("Die");
		return;
	}

	if (ECharacterColor::None != ColPlayerColor && PlayerColor == ColPlayerColor)
	{
		State.ChangeState("Revival");
		return;
	}

	// 바늘 사용하면
	if (true == IsDown(VK_CONTROL) && NeedleCount > 0 && false == IsNeedleUse)
	{
		IsNeedleUse = true;
		NeedleCount--;
		if (NeedleCount <= 0)
		{
			NeedleCount = 0;
		}
		return;
	}
}

void APlayer::Die(float _DeltaTime)
{
	BlinkRenderer(_DeltaTime);
}

void APlayer::Revival(float _DeltaTime)
{
	if (Renderer->IsCurAnimationEnd())
	{
		State.ChangeState("Idle");
		IsNeedleUse = false;
		return;
	}
	if (PlayerColor == ConnectionInfo::GetInst().GetWins())
	{
		State.ChangeState("Win");
		IsNeedleUse = false;
		return;
	}
}

void APlayer::Win(float _DeltaTime)
{
}

void APlayer::Lose(float _DeltaTime)
{
}

void APlayer::KeyMove(float _DeltaTime, FVector _Dir, float _Speed)
{
	FVector NextPos = GetActorLocation() + FVector(_DeltaTime * _Speed * _Dir.X, _DeltaTime * _Speed * _Dir.Y, 0.0f);

	bool CanMove = false;

	if (false == IsTrapped)
	{
		CanMove = PlayLevel->GetMap()->CanMovePos(NextPos, _Dir);
	}
	else
	{
		CanMove = PlayLevel->GetMap()->CanMovePosInTraped(NextPos, _Dir);
	}

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

void APlayer::HideInBush()
{
	if (true == PlayLevel->GetMap()->IsBushPos(GetActorLocation(), IsInBush))
	{
		IsInBush = true;
		Renderer->SetActive(false);
		ShadowRenderer->SetActive(false);
	}
	else
	{
		IsInBush = false;
		Renderer->SetActive(true);
		ShadowRenderer->SetActive(true);
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
