#include "PreCompile.h"
#include "Wave.h"

#include "MainPlayLevel.h"
#include "MapConstant.h"
#include "MapBase.h"
#include "BlockBase.h"
#include "ItemBase.h"
#include "BushBase.h"

#include "ServerTestPlayer.h"

AWave::AWave()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");

	Body = CreateDefaultSubObject<USpriteRenderer>("Wave");
	Body->SetScale({ AMapBase::BlockSize, AMapBase::BlockSize, 0.0f });
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
	CreateAnim();

	PlayLevel = dynamic_cast<AMainPlayLevel*>(GetWorld()->GetGameMode().get());
}

void AWave::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);

	Destroy();
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

void AWave::CreateAnim()
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
	WaveType = _WaveType;

	switch (WaveType)
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
	case EWaveType::UnderBlock:
		Body->SetActive(false);
		break;
	}

	Body->SetOrder(AMapBase::GetRenderOrder(GetActorLocation()));
	CurPoint = AMapBase::ConvertLocationToPoint(GetActorLocation());
}

void AWave::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	switch (WaveType)
	{
	case EWaveType::UnderBlock:
	{
		if (nullptr != PlayLevel->GetMap()->GetTileInfo(CurPoint).Block)
		{
			PlayLevel->GetMap()->GetTileInfo(CurPoint).Block->StateChange(BlockState::destroy);
		}
		
		Destroy();
	}
		break;
	default:
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

		if (nullptr != PlayLevel->GetMap()->GetTileInfo(CurPoint).Item)
		{
			PlayLevel->GetMap()->GetTileInfo(CurPoint).Item->Destroy();
			PlayLevel->GetMap()->GetTileInfo(CurPoint).Item = nullptr;
		}

		if (nullptr != PlayLevel->GetMap()->GetTileInfo(CurPoint).Bush)
		{
			PlayLevel->GetMap()->GetTileInfo(CurPoint).Bush->Destroy();
			PlayLevel->GetMap()->GetTileInfo(CurPoint).Bush = nullptr;
		}

		if (true == Body->IsCurAnimationEnd())
		{
			Destroy();
		}
	}
		break;
	}
}

