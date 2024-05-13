#include "PreCompile.h"
#include "ServerTestPlayer.h"
#include "Packets.h"
#include "CrazyArcadeCore.h"
#include "ServerTestOtherPlayer.h"

ServerTestPlayer::ServerTestPlayer()
{
	UDefaultSceneComponent* DefaultComponent = CreateDefaultSubObject<UDefaultSceneComponent>("DefaultComponent");
	SetRoot(DefaultComponent);
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(DefaultComponent);
	Renderer->SetPivot(EPivot::BOT);

	ShadowRenderer = CreateDefaultSubObject<USpriteRenderer>("ShadowRenderer");
	ShadowRenderer->SetupAttachment(DefaultComponent);
	ShadowRenderer->SetPivot(EPivot::BOT);

	InputOn();
}

ServerTestPlayer::~ServerTestPlayer()
{
}

void ServerTestPlayer::BeginPlay()
{
	Super::BeginPlay();

	UEngineSprite::CreateCutting("down.png", 8, 1);
	UEngineSprite::CreateCutting("up.png", 8, 1);
	UEngineSprite::CreateCutting("right.png", 6, 1);

	Renderer->CreateAnimation("Idle_Down", "down.png", 0.1f, false, 0, 0);
	Renderer->CreateAnimation("Idle_Up", "up.png", 0.1f, false, 0, 0);
	Renderer->CreateAnimation("Idle_Right", "right.png", 0.1f, false, 0, 0);
	Renderer->CreateAnimation("Run_Down", "down.png", 0.1f, true, 0, 7);
	Renderer->CreateAnimation("Run_Up", "up.png", 0.1f, true, 0, 7);
	Renderer->CreateAnimation("Run_Right", "right.png", 0.1f, true, 0, 5);

	Renderer->ChangeAnimation("Idle_Down");
	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(1);

	ShadowRenderer->SetSprite("shadow.png");
	ShadowRenderer->SetAutoSize(1.0f, true);
	ShadowRenderer->SetOrder(0);

	StateInit();
}

void ServerTestPlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);

	PlayerPos = GetActorLocation();

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


	if (0.0f >= CurTime && true == IsNetInit())
	{
		std::shared_ptr<UActorUpdatePacket> Packet = std::make_shared<UActorUpdatePacket>();

		Packet->Pos = GetActorLocation();
		Packet->SpriteName = Renderer->GetCurAnimationName();
		Send(Packet);
		CurTime += FrameTime;
		if (IsPress(VK_SPACE)) {
			std::shared_ptr<USpawnUpdatePacket> SpawnPacket = std::make_shared<USpawnUpdatePacket>();
			SpawnPacket->Pos = GetActorLocation();
			SpawnPacket->SpawnSelect = ServerObjectType::Player;
			ServerTestOtherPlayer* Test = GetWorld()->SpawnActor<ServerTestOtherPlayer>("Test").get();
			Test->SetActorLocation(GetActorLocation());
			Send(SpawnPacket);
		}
	}
}