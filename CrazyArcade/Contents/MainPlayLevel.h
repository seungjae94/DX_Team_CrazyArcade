#pragma once

class AVillageMap;

class AMapBase;
class ServerTestPlayer;

//UI
class ATimerUI;

// 설명 : Map 테스트 레벨
class AMainPlayLevel : public AGameMode
{
	GENERATED_BODY(AGameMode)
public:
	// constrcuter destructer
	AMainPlayLevel();
	~AMainPlayLevel();

	// delete Function
	AMainPlayLevel(const AMainPlayLevel& _Other) = delete;
	AMainPlayLevel(AMainPlayLevel&& _Other) noexcept = delete;
	AMainPlayLevel& operator=(const AMainPlayLevel& _Other) = delete;
	AMainPlayLevel& operator=(AMainPlayLevel&& _Other) noexcept = delete;
		
	std::shared_ptr<AMapBase> GetMap() const
	{
		return TileMap;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	std::shared_ptr<AMapBase> TileMap = nullptr;
	std::shared_ptr<ServerTestPlayer> Player = nullptr;
	std::shared_ptr<ATimerUI> Timer = nullptr;
};

