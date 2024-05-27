#include "PreCompile.h"
#include "BombBase.h"

#include "MainPlayLevel.h"
#include "MapConstant.h"
#include "BlockBase.h"
#include "MoveBox.h"
#include "BushBase.h"
#include "MapBase.h"
#include "Wave.h"
#include "Wall.h"
#include "Box.h"

#include "ServerTestPlayer.h"

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
}

void ABombBase::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	State.CreateState(BombState::idle);
}

void ABombBase::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);

	Destroy();
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
			Body->SetOrder(BombOrder);

			if (nullptr != Player)
			{
				SetBombPower(Player->GetBombPower());
			}

			CurPoint = AMapBase::ConvertLocationToPoint(GetActorLocation());
			if (true == AMapBase::MapRangeCheckByPoint(CurPoint) && nullptr == PlayLevel->GetMap()->GetTileInfo(CurPoint).Bush)
			{
				Body->ChangeAnimation(MapAnim::bomb);
				Body->SetActive(true);
			}

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
			Body->SetActive(true);

			if (true == AMapBase::MapRangeCheckByPoint(CurPoint) && nullptr != PlayLevel->GetMap()->GetTileInfo(CurPoint).Bush)
			{
				PlayLevel->GetMap()->GetTileInfo(CurPoint).Bush->Destroy();
				PlayLevel->GetMap()->GetTileInfo(CurPoint).Bush = nullptr;
			}

			DelayCallBack(0.66f, [=] 
				{
					if (true == AMapBase::MapRangeCheckByPoint(CurPoint))
					{
						PlayLevel->GetMap()->GetTileInfo(CurPoint).AllBomb.clear();
					}

					Destroy();
				}
			);

			UEngineSound::SoundPlay("Boom.mp3");
			UEngineSound::SoundPlay("Water.mp3").SetVolume(0.5f);
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

	State.SetUpdateFunction(BombState::explosion, [=](float _DeltaTime)	
		{
			for (size_t i = 0; i < PlayLevel->GetMap()->AllPlayer.size(); i++)
			{
				if (nullptr == PlayLevel->GetMap()->AllPlayer[i])
				{
					continue;
				}

				FVector PlayerPos = PlayLevel->GetMap()->AllPlayer[i]->GetActorLocation();
				FPoint PlayerPoint = AMapBase::ConvertLocationToPoint(PlayerPos);
				if (8 > Body->GetCurAnimationFrame() && PlayerPoint == CurPoint)
				{
					PlayLevel->GetMap()->AllPlayer[i]->SetTrapState();
				}
			}
		}
	);
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
	if (nullptr == _Player)
	{
		return;
	}

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

		for (std::shared_ptr<ABombBase> Bomb : PlayLevel->GetMap()->GetTileInfo(WavePoint).AllBomb)
		{
			if (nullptr != Bomb && BombState::explosion != Bomb->State.GetCurStateName())
			{
				Bomb->PlayerBombCountUpdate();
				Bomb->State.ChangeState(BombState::explosion);
			}
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

		for (std::shared_ptr<ABombBase> Bomb : PlayLevel->GetMap()->GetTileInfo(WavePoint).AllBomb)
		{
			if (nullptr != Bomb && BombState::explosion != Bomb->State.GetCurStateName())
			{
				Bomb->PlayerBombCountUpdate();
				Bomb->State.ChangeState(BombState::explosion);
			}
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

		for (std::shared_ptr<ABombBase> Bomb : PlayLevel->GetMap()->GetTileInfo(WavePoint).AllBomb)
		{
			if (nullptr != Bomb && BombState::explosion != Bomb->State.GetCurStateName())
			{
				Bomb->PlayerBombCountUpdate();
				Bomb->State.ChangeState(BombState::explosion);
			}
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

		for (std::shared_ptr<ABombBase> Bomb : PlayLevel->GetMap()->GetTileInfo(WavePoint).AllBomb)
		{
			if (nullptr != Bomb && BombState::explosion != Bomb->State.GetCurStateName())
			{
				Bomb->PlayerBombCountUpdate();
				Bomb->State.ChangeState(BombState::explosion);
			}
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
