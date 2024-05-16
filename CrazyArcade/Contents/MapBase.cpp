#include "PreCompile.h"
#include "MapBase.h"

#include "MapConstant.h"
#include "BlockBase.h"
#include "MoveBox.h"

float AMapBase::BlockSize = 40.0f;

AMapBase::AMapBase()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Root");

	BackGround = CreateDefaultSubObject<USpriteRenderer>("BackGround");
	BackGround->SetPosition({ -80.0f, 0.0f, 0.0f });
	BackGround->SetAutoSize(1.0f, true);
	BackGround->SetupAttachment(Root);

	PlayUI_BackGround = CreateDefaultSubObject<USpriteRenderer>("PlayUI_BackGround");
	PlayUI_BackGround->SetSprite(MapImgRes::play_ui_background);
	PlayUI_BackGround->SetSamplering(ETextureSampling::LINEAR);
	PlayUI_BackGround->SetAutoSize(1.0f, true);
	PlayUI_BackGround->SetupAttachment(Root);

	SetRoot(Root);
}

AMapBase::~AMapBase()
{
}

void AMapBase::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetMainCamera()->SetActorLocation({ 400.0f, 300.0f, -100.0f });
	SetActorLocation({ 400.0f, 300.0f, 0.0f });
}

void AMapBase::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AMapBase::SetMapInfoSize(int _SizeX, int _SizeY)
{
	SizeY = _SizeY;
	SizeX = _SizeX;
	MapInfo.resize(SizeY);
	for (size_t Y = 0; Y < MapInfo.size(); Y++)
	{
		MapInfo[Y].resize(SizeX);
	}

	BackGround->SetOrder(ERenderOrder::BackGround);
	PlayUI_BackGround->SetOrder(ERenderOrder::BackGround);
}

FPoint AMapBase::CovertLocationToPoint(const FVector& _Pos)
{
	FPoint Result = FPoint();
	FVector Pos = _Pos - StartPos;

	Result.X = static_cast<int>(Pos.X / BlockSize);
	Result.Y = static_cast<int>(Pos.Y / BlockSize);

	return Result;
}

int AMapBase::GetRenderOrder(const FVector& _CurPos)
{
	FVector CurPos = _CurPos;
	CurPos.Y -= StartPos.Y;
	int CurY = static_cast<int>(CurPos.Y / BlockSize);
	return Const::MaxOrder - CurY;
} 

bool AMapBase::CanMovePos(const FVector& _NextPos, const FVector& _Dir)
{
	// MapInfo
	FVector NextPos = _NextPos - StartPos;

	if (0.0f < _Dir.X)
	{
		NextPos.X += 20.0f;
	}
	else if (0.0f > _Dir.X)
	{
		NextPos.X -= 20.0f;
	}
	else if (0.0f < _Dir.Y)
	{
		NextPos.Y += 30.0f;
	}
	else if (0.0f > _Dir.Y)
	{
		NextPos.Y -= 10.0f;
	}

	float NextPlayerFX = NextPos.X / BlockSize;
	float NextPlayerFY = NextPos.Y / BlockSize;

	FPoint NextPoint = FPoint();
	NextPoint.X = static_cast<int>(NextPos.X / BlockSize);
	NextPoint.Y = static_cast<int>(NextPos.Y / BlockSize);
	
	// 맵 범위 밖일때
	if (SizeX <= NextPoint.X || 0 > NextPlayerFX || SizeY <= NextPoint.Y || 0 > NextPlayerFY)
	{
		return false;
	}
	
	// 빈 공간일때
	if (nullptr == MapInfo[NextPoint.Y][NextPoint.X].Block)
	{
		return true;
	}

	// 오브젝트 존재할때
	EBlockType BlockType = MapInfo[NextPoint.Y][NextPoint.X].Block->GetBlockType();
	if (EBlockType::Wall == BlockType || EBlockType::Box == BlockType)
	{
		return false;
	}

	// MoveBox 체크
	if (EBlockType::MoveBox == BlockType)
	{
		std::shared_ptr<AMoveBox> MoveBox = std::dynamic_pointer_cast<AMoveBox>(MapInfo[NextPoint.Y][NextPoint.X].Block);
		MoveBox->SetMoveDir(_Dir);
		FPoint TwoStepPoint = NextPoint;

		if (0.0f < _Dir.X)
		{
			TwoStepPoint.X += 1;
		}
		else if (0.0f > _Dir.X)
		{
			TwoStepPoint.X -= 1;
		}
		else if (0.0f < _Dir.Y)
		{
			TwoStepPoint.Y += 1;
		}
		else if (0.0f > _Dir.Y)
		{
			TwoStepPoint.Y -= 1;
		}

		if (0 > TwoStepPoint.X || SizeX <= TwoStepPoint.X 
		||  0 > TwoStepPoint.Y || SizeY <= TwoStepPoint.Y
		|| nullptr != MapInfo[TwoStepPoint.Y][TwoStepPoint.X].Block)
		{
			return false;
		}
		
		if ("Idle" == MoveBox->GetCurState())
		{
			MoveBox->StateChange("Move");
			return false;
		}
		
		return false;
	}

	return true;
}


