#include "PreCompile.h"
#include "Wave.h"

#include "MapConstant.h"
#include "MapBase.h"

AWave::AWave()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");

	Body = CreateDefaultSubObject<USpriteRenderer>("Wave");
	Body->SetScale({ AMapBase::BlockSize,  AMapBase::BlockSize, 0.0f });
	Body->SetupAttachment(Root);

	SetRoot(Root);
}

AWave::~AWave()
{
}

void AWave::BeginPlay()
{
	Super::BeginPlay();

	SetImgCutting();
	CreateAnimation();
}

void AWave::SetImgCutting()
{
	UEngineSprite::CreateCutting(MapImgRes::bomb_effect_left, 11, 1);
	UEngineSprite::CreateCutting(MapImgRes::bomb_effect_left_end, 11, 1);
	UEngineSprite::CreateCutting(MapImgRes::bomb_effect_right, 11, 1);
	UEngineSprite::CreateCutting(MapImgRes::bomb_effect_right_end, 11, 1);
	UEngineSprite::CreateCutting(MapImgRes::bomb_effect_up, 11, 1);
	UEngineSprite::CreateCutting(MapImgRes::bomb_effect_up_end, 11, 1);
	UEngineSprite::CreateCutting(MapImgRes::bomb_effect_down, 11, 1);
	UEngineSprite::CreateCutting(MapImgRes::bomb_effect_down_end, 11, 1);
}

void AWave::CreateAnimation()
{
	Body->CreateAnimation(MapAnim::bomb_effect_left, MapImgRes::bomb_effect_left, 0.06f, false);
	Body->CreateAnimation(MapAnim::bomb_effect_left_end, MapImgRes::bomb_effect_left_end, 0.06f, false);

	Body->CreateAnimation(MapAnim::bomb_effect_right, MapImgRes::bomb_effect_right, 0.06f, false);
	Body->CreateAnimation(MapAnim::bomb_effect_right_end, MapImgRes::bomb_effect_right_end, 0.06f, false);

	Body->CreateAnimation(MapAnim::bomb_effect_up, MapImgRes::bomb_effect_up, 0.06f, false);
	Body->CreateAnimation(MapAnim::bomb_effect_up_end, MapImgRes::bomb_effect_up_end, 0.06f, false);

	Body->CreateAnimation(MapAnim::bomb_effect_down, MapImgRes::bomb_effect_down, 0.06f, false);
	Body->CreateAnimation(MapAnim::bomb_effect_down_end, MapImgRes::bomb_effect_down_end, 0.06f, false);
}

void AWave::SetWaveType(EWaveType _WaveType)
{
	switch (_WaveType)
	{
	case EWaveType::Left:
		Body->ChangeAnimation(MapAnim::bomb_effect_left);
		break;
	case EWaveType::LeftEnd:
		Body->ChangeAnimation(MapAnim::bomb_effect_left_end);
		break;
	case EWaveType::Right:
		Body->ChangeAnimation(MapAnim::bomb_effect_right);
		break;
	case EWaveType::RightEnd:
		Body->ChangeAnimation(MapAnim::bomb_effect_right_end);
		break;
	case EWaveType::Up:
		Body->ChangeAnimation(MapAnim::bomb_effect_up);
		break;
	case EWaveType::UpEnd:
		Body->ChangeAnimation(MapAnim::bomb_effect_up_end);
		break;
	case EWaveType::Down:
		Body->ChangeAnimation(MapAnim::bomb_effect_down);
		break;
	case EWaveType::DownEnd:
		Body->ChangeAnimation(MapAnim::bomb_effect_down_end);
		break;
	}

	Body->SetOrder(AMapBase::GetRenderOrder(GetActorLocation()));
}

void AWave::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (true == Body->IsCurAnimationEnd())
	{
		Destroy();
	}
}
