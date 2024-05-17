#include "PreCompile.h"
#include "BombBase.h"

#include "MainPlayLevel.h"
#include "MapConstant.h"
#include "MapBase.h"
#include "Player.h"
#include "Wave.h"

#include "BlockBase.h"
#include "MoveBox.h"
#include "Wall.h"
#include "Box.h"

ABombBase::ABombBase()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");

	Body = CreateDefaultSubObject<USpriteRenderer>("Bomb");
	Body->SetupAttachment(Root);	

	SetRoot(Root);
}

ABombBase::~ABombBase()
{
}

void ABombBase::BeginPlay()
{
	Super::BeginPlay();

	SetImgCutting();
	RendererInit();
	StateInit();

	PlayLevel = dynamic_cast<AMainPlayLevel*>(GetWorld()->GetGameMode().get());	
	State.ChangeState(BombState::idle);
}

void ABombBase::SetImgCutting()
{
	UEngineSprite::CreateCutting(MapImgRes::bomb, 3, 1);
	UEngineSprite::CreateCutting(MapImgRes::bomb_effect_center, 3, 1);
}

void ABombBase::RendererInit()
{
	float BlockSize = AMapBase::GetBlockSize();

	Body->CreateAnimation(MapAnim::bomb, MapImgRes::bomb, 0.25f, true);
	Body->CreateAnimation(MapAnim::bomb_effect_center, MapImgRes::bomb_effect_center, 0.01f, true);
	Body->SetAutoSize(1.0f, true);
	Body->SetActive(false);
}

void ABombBase::StateInit()
{
	// State Create
	State.CreateState(BombState::idle);
	State.CreateState(BombState::explosion);

	// State Start
	State.SetStartFunction(BombState::idle, [=] 
		{
			int BombOrder = AMapBase::GetRenderOrder(GetActorLocation());
			Body->ChangeAnimation(MapAnim::bomb);
			Body->SetOrder(BombOrder);
			Body->SetActive(true);

			ExplosionTimeCount = ExplosionTime;
		}
	);

	State.SetStartFunction(BombState::explosion, [=] 
		{
			CreateLeftWave();
			CreateRightWave();
			CreateUpWave();
			CreateDownWave();

			AddActorLocation({ 0.0f, -AMapBase::BombAdjustPosY, 0.0f });
			Body->ChangeAnimation(MapAnim::bomb_effect_center);
			DelayCallBack(0.66f, [=] 
				{
					PlayLevel->GetMap()->GetTileInfo(CurPoint).Bomb = nullptr;
					Destroy();
				}
			);
		}
	);

	// State Update
	State.SetUpdateFunction(BombState::idle, [=](float _DeltaTime) 
		{
			ExplosionTimeCount -= _DeltaTime;
			if (0.0f > ExplosionTimeCount)
			{
				PlayerBombCountUpdate();
				State.ChangeState(BombState::explosion);
				return;
			}
		}
	);

	State.SetUpdateFunction(BombState::explosion, [=](float _DeltaTime)	{});

}

void ABombBase::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void ABombBase::PlayerBombCountUpdate()
{
	if (nullptr != Player)
	{
		Player->IncreaseBombCount();
	}
}

void ABombBase::SetPlayer(APlayer* _Player)
{
	Player = _Player;
}

void ABombBase::SetCurPoint(FPoint _Point)
{
	CurPoint = _Point;
}

void ABombBase::CreateLeftWave()
{
	// Left
	for (int i = 1; i <= Power; i++)
	{
		FPoint WavePoint = { CurPoint.X - i, CurPoint.Y };
		FVector WavePos = AMapBase::ConvertPointToLocation(WavePoint);
		
		if (false == AMapBase::MapRangeCheckByPoint(WavePoint))
		{
			break;
		}

		ABlockBase* Block = PlayLevel->GetMap()->GetTileInfo(WavePoint).Block;
		if (nullptr != dynamic_cast<AWall*>(Block))
		{
			break;
		}
		
		if (nullptr != dynamic_cast<ABox*>(Block) || nullptr != dynamic_cast<AMoveBox*>(Block))
		{
			AWave* LeftWave = GetWorld()->SpawnActor<AWave>("Wave").get();
			LeftWave->SetActorLocation(WavePos);
			LeftWave->SetWaveType(EWaveType::UnderBlock);
			break;
		}

		ABombBase* Bomb = PlayLevel->GetMap()->GetTileInfo(WavePoint).Bomb;
		if (nullptr != Bomb && BombState::explosion != Bomb->State.GetCurStateName())
		{
			Bomb->PlayerBombCountUpdate();
			Bomb->State.ChangeState(BombState::explosion);
		}

		if (i == Power)
		{
			AWave* LeftWave = GetWorld()->SpawnActor<AWave>("Wave").get();
			LeftWave->SetActorLocation(WavePos);
			LeftWave->SetWaveType(EWaveType::LeftEnd);
			continue;
		}
	
		AWave* LeftWave = GetWorld()->SpawnActor<AWave>("Wave").get();
		LeftWave->SetActorLocation(WavePos);
		LeftWave->SetWaveType(EWaveType::Left);
	}
}

void ABombBase::CreateRightWave()
{
	// Right
	for (int i = 1; i <= Power; i++)
	{
		FPoint WavePoint = { CurPoint.X + i, CurPoint.Y };
		FVector WavePos = AMapBase::ConvertPointToLocation(WavePoint);

		if (false == AMapBase::MapRangeCheckByPoint(WavePoint))
		{
			break;
		}

		ABlockBase* Block = PlayLevel->GetMap()->GetTileInfo(WavePoint).Block;
		if (nullptr != dynamic_cast<AWall*>(Block))
		{
			break;
		}

		if (nullptr != dynamic_cast<ABox*>(Block) || nullptr != dynamic_cast<AMoveBox*>(Block))
		{
			AWave* LeftWave = GetWorld()->SpawnActor<AWave>("Wave").get();
			LeftWave->SetActorLocation(WavePos);
			LeftWave->SetWaveType(EWaveType::UnderBlock);
			break;
		}

		ABombBase* Bomb = PlayLevel->GetMap()->GetTileInfo(WavePoint).Bomb;
		if (nullptr != Bomb && BombState::explosion != Bomb->State.GetCurStateName())
		{
			Bomb->PlayerBombCountUpdate();
			Bomb->State.ChangeState(BombState::explosion);
		}

		if (i == Power)
		{
			AWave* LeftWave = GetWorld()->SpawnActor<AWave>("Wave").get();
			LeftWave->SetActorLocation(WavePos);
			LeftWave->SetWaveType(EWaveType::RightEnd);
			continue;
		}

		AWave* LeftWave = GetWorld()->SpawnActor<AWave>("Wave").get();
		LeftWave->SetActorLocation(WavePos);
		LeftWave->SetWaveType(EWaveType::Right);
	}
}

void ABombBase::CreateUpWave()
{
	// Up
	for (int i = 1; i <= Power; i++)
	{
		FPoint WavePoint = { CurPoint.X, CurPoint.Y + i };
		FVector WavePos = AMapBase::ConvertPointToLocation(WavePoint);

		if (false == AMapBase::MapRangeCheckByPoint(WavePoint))
		{
			break;
		}

		ABlockBase* Block = PlayLevel->GetMap()->GetTileInfo(WavePoint).Block;
		if (nullptr != dynamic_cast<AWall*>(Block))
		{
			break;
		}

		if (nullptr != dynamic_cast<ABox*>(Block) || nullptr != dynamic_cast<AMoveBox*>(Block))
		{
			AWave* LeftWave = GetWorld()->SpawnActor<AWave>("Wave").get();
			LeftWave->SetActorLocation(WavePos);
			LeftWave->SetWaveType(EWaveType::UnderBlock);
			break;
		}

		ABombBase* Bomb = PlayLevel->GetMap()->GetTileInfo(WavePoint).Bomb;
		if (nullptr != Bomb && BombState::explosion != Bomb->State.GetCurStateName())
		{
			Bomb->PlayerBombCountUpdate();
			Bomb->State.ChangeState(BombState::explosion);
		}

		if (i == Power)
		{
			AWave* LeftWave = GetWorld()->SpawnActor<AWave>("Wave").get();
			LeftWave->SetActorLocation(WavePos);
			LeftWave->SetWaveType(EWaveType::UpEnd);
			continue;
		}

		AWave* LeftWave = GetWorld()->SpawnActor<AWave>("Wave").get();
		LeftWave->SetActorLocation(WavePos);
		LeftWave->SetWaveType(EWaveType::Up);
	}
}

void ABombBase::CreateDownWave()
{
	// Down
	for (int i = 1; i <= Power; i++)
	{
		FPoint WavePoint = { CurPoint.X, CurPoint.Y - i };
		FVector WavePos = AMapBase::ConvertPointToLocation(WavePoint);

		if (false == AMapBase::MapRangeCheckByPoint(WavePoint))
		{
			break;
		}

		ABlockBase* Block = PlayLevel->GetMap()->GetTileInfo(WavePoint).Block;
		if (nullptr != dynamic_cast<AWall*>(Block))
		{
			break;
		}

		if (nullptr != dynamic_cast<ABox*>(Block) || nullptr != dynamic_cast<AMoveBox*>(Block))
		{
			AWave* LeftWave = GetWorld()->SpawnActor<AWave>("Wave").get();
			LeftWave->SetActorLocation(WavePos);
			LeftWave->SetWaveType(EWaveType::UnderBlock);
			break;
		}

		ABombBase* Bomb = PlayLevel->GetMap()->GetTileInfo(WavePoint).Bomb;
		if (nullptr != Bomb && BombState::explosion != Bomb->State.GetCurStateName())
		{
			Bomb->PlayerBombCountUpdate();
			Bomb->State.ChangeState(BombState::explosion);
		}

		if (i == Power)
		{
			AWave* LeftWave = GetWorld()->SpawnActor<AWave>("Wave").get();
			LeftWave->SetActorLocation(WavePos);
			LeftWave->SetWaveType(EWaveType::DownEnd);
			continue;
		}

		AWave* LeftWave = GetWorld()->SpawnActor<AWave>("Wave").get();
		LeftWave->SetActorLocation(WavePos);
		LeftWave->SetWaveType(EWaveType::Down);
	}
}
