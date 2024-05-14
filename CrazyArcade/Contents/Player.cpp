#include "PreCompile.h"
#include "Player.h"

APlayer::APlayer()
{
	UDefaultSceneComponent* DefaultComponent = CreateDefaultSubObject<UDefaultSceneComponent>("DefaultComponent");
	SetRoot(DefaultComponent);

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(DefaultComponent);
	Renderer->AddPosition({ 0.0f, -BlockSize / 2.0f });

	ShadowRenderer = CreateDefaultSubObject<USpriteRenderer>("ShadowRenderer");
	ShadowRenderer->SetupAttachment(DefaultComponent);
	ShadowRenderer->AddPosition({ 0.0f, -BlockSize / 2.0f });

	DebugRenderer = CreateDefaultSubObject<USpriteRenderer>("DebugRenderer");
	DebugRenderer->SetupAttachment(DefaultComponent);

	InputOn();
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
	Super::BeginPlay();

	UEngineSprite::CreateCutting("down.png", 8, 1);
	UEngineSprite::CreateCutting("up.png", 8, 1);
	UEngineSprite::CreateCutting("right.png", 6, 1);
	UEngineSprite::CreateCutting("left.png", 6, 1);

	Renderer->CreateAnimation("Idle_Down", "down.png", 0.1f, false, 0, 0);
	Renderer->CreateAnimation("Idle_Up", "up.png", 0.1f, false, 0, 0);
	Renderer->CreateAnimation("Idle_Right", "right.png", 0.1f, false, 0, 0);
	Renderer->CreateAnimation("Idle_Left", "left.png", 0.1f, false, 0, 0);

	Renderer->CreateAnimation("Run_Down", "down.png", 0.1f, true, 0, 7);
	Renderer->CreateAnimation("Run_Up", "up.png", 0.1f, true, 0, 7);
	Renderer->CreateAnimation("Run_Right", "right.png", 0.1f, true, 0, 5);
	Renderer->CreateAnimation("Run_Left", "left.png", 0.1f, true, 0, 5);

	Renderer->ChangeAnimation("Idle_Down");
	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderOrder::Player);

	ShadowRenderer->SetSprite("Shadow.png");
	ShadowRenderer->SetAutoSize(1.0f, true);
	ShadowRenderer->SetOrder(ERenderOrder::Shadow);

	DebugRenderer->SetScale({ 5,5,5 });
	DebugRenderer->SetOrder(ERenderOrder::Debug);

	StateInit();
}

void APlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);

	PlayerPos = GetActorLocation();
}