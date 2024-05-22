#include "PreCompile.h"
#include "ServerTestPlayer.h"
#include "Packets.h"
#include "CrazyArcadeCore.h"
#include "ServerTestOtherPlayer.h"
#include "BombBase.h"

#include "MainPlayLevel.h"
#include "MapBase.h"
#include "CrazyArcadeEnum.h"

ServerTestPlayer::ServerTestPlayer()
	:APlayer()
{
}

ServerTestPlayer::~ServerTestPlayer()
{
}


void ServerTestPlayer::BeginPlay()
{
	Super::BeginPlay();

	PlayLevel->GetMap()->PushAllPlayer(this);
}

void ServerTestPlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);


	if (false == IsNetInit())
	{
		// 네트워크 통신준비가 아직 안된 오브젝트다.
		if (nullptr != UCrazyArcadeCore::Net)
		{
			InitNet(UCrazyArcadeCore::Net);
		}
	}

	static float FrameTime = 1.0f / 60.0f;
	static float CurTime = FrameTime;

	CurTime -= _DeltaTime;

	if (true == IsDown(VK_SPACE) && false == IsSpawn)
	{
		IsSpawn = true;
	}

	if (0.0f >= CurTime && true == IsNetInit())
	{
		std::shared_ptr<UActorUpdatePacket> Packet = std::make_shared<UActorUpdatePacket>();

		Packet->Pos = GetActorLocation();
		Packet->SpriteName = Renderer->GetCurAnimationName();
		Packet->SpawnSelect = static_cast<int>(ECharacterType::Random);
		Send(Packet);
		CurTime += FrameTime;
		if (true == IsSpawn) {
			SpawnBomb();
		}
	}
}




void ServerTestPlayer::SpawnBomb()
{
	if (Bomb == nullptr) {
		return;
	}
	FEngineTimeStamp Stamp = UEngineTime::GetCurTime();
	float FloatResult = Stamp.TimeToFloat();
	std::shared_ptr<USpawnUpdatePacket> SpawnPacket = std::make_shared<USpawnUpdatePacket>();
	SpawnPacket->SpawnSelect = static_cast<int>(EItemType::Bubble);
	SpawnPacket->SpawnTime = FloatResult;
	Bomb->SetObjectToken(GetToken);
	SpawnPacket->Pos = /*Bomb->*/GetActorLocation();
	SpawnPacket->Power = BombPower;
	Send(SpawnPacket, Bomb->GetObjectToken());
	IsSpawn = false;
	Bomb = nullptr;
}