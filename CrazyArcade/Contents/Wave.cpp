#include "PreCompile.h"
#include "Wave.h"

#include "MapConstant.h"

AWave::AWave()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");

	Body = CreateDefaultSubObject<USpriteRenderer>("Wave");
	Body->SetAutoSize(1.0f, true);
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
	Body->CreateAnimation(MapAnim::bomb_effect_left, MapImgRes::bomb_effect_left, 0.05f, false);
	Body->CreateAnimation(MapAnim::bomb_effect_left_end, MapImgRes::bomb_effect_left_end, 0.05f, false);

	Body->CreateAnimation(MapAnim::bomb_effect_right, MapImgRes::bomb_effect_right, 0.05f, false);
	Body->CreateAnimation(MapAnim::bomb_effect_right_end, MapImgRes::bomb_effect_right_end, 0.05f, false);

	Body->CreateAnimation(MapAnim::bomb_effect_up, MapImgRes::bomb_effect_up, 0.05f, false);
	Body->CreateAnimation(MapAnim::bomb_effect_up_end, MapImgRes::bomb_effect_up_end, 0.05f, false);

	Body->CreateAnimation(MapAnim::bomb_effect_down, MapImgRes::bomb_effect_down, 0.05f, false);
	Body->CreateAnimation(MapAnim::bomb_effect_down_end, MapImgRes::bomb_effect_down_end, 0.05f, false);
}

void AWave::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);


}
