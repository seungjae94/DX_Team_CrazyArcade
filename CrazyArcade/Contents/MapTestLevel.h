#pragma once

class AVillageMap;
class ATestPlayer;
class AMapBase;

//UI
class ATimerUI;

// 설명 : Map 테스트 레벨
class AMapTestLevel : public AGameMode
{
	GENERATED_BODY(AGameMode)
public:
	// constrcuter destructer
	AMapTestLevel();
	~AMapTestLevel();

	// delete Function
	AMapTestLevel(const AMapTestLevel& _Other) = delete;
	AMapTestLevel(AMapTestLevel&& _Other) noexcept = delete;
	AMapTestLevel& operator=(const AMapTestLevel& _Other) = delete;
	AMapTestLevel& operator=(AMapTestLevel&& _Other) noexcept = delete;
		
	std::shared_ptr<AMapBase> GetMap() const
	{
		return TileMap;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<AMapBase> TileMap = nullptr;
	std::shared_ptr<ATestPlayer> Player = nullptr;
	std::shared_ptr<ATimerUI> Timer = nullptr;
};

