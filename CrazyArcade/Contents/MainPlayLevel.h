#pragma once
#include "NetGameMode.h"

class AVillageMap;

class AMapBase;
class APlayer;

//UI
class ATimerUI;
class AInGameUI;
class AMouse;

// 설명 : Map 테스트 레벨
class AMainPlayLevel : public ANetGameMode
{
	GENERATED_BODY(ANetGameMode)
public:
	// constrcuter destructer
	AMainPlayLevel();
	~AMainPlayLevel();

	// delete Function
	AMainPlayLevel(const AMainPlayLevel& _Other) = delete;
	AMainPlayLevel(AMainPlayLevel&& _Other) noexcept = delete;
	AMainPlayLevel& operator=(const AMainPlayLevel& _Other) = delete;
	AMainPlayLevel& operator=(AMainPlayLevel&& _Other) noexcept = delete;
		
	inline std::shared_ptr<AMapBase> GetMap() const
	{
		return TileMap;
	}

	inline std::shared_ptr<APlayer> GetPlayer() const
	{
		return Player;
	}

	inline void SetMapType(EMapType _MapType)
	{
		MapType = _MapType;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelEnd(ULevel* _NextLevel) override;
	void LevelStart(ULevel* _PrevLevel) override;

protected:
	void CreateMap();

protected:
	std::shared_ptr<AMapBase> TileMap = nullptr;
	EMapType MapType = EMapType::None;

	std::shared_ptr<APlayer> Player = nullptr;
	std::shared_ptr<ATimerUI> Timer = nullptr;
	std::shared_ptr<AInGameUI> InGameUI = nullptr;


	std::shared_ptr<AMouse> MouseUI = nullptr;

	//// Chat
	//UImage* VoidBox = nullptr;
	//UImage* ChatBox = nullptr;
	//UTextWidget* ChatInputText = nullptr;
	//std::vector<UTextWidget*> ChatTexts;
	//bool Chat_IsActive = false;
	//int Chat_Size = 0;
	//std::string ChatInput = "";
	//std::string Chat = "";
	//std::string Chat_Prev = "";
	//void ChatUpdate();

	// 사운드
	UEngineSoundPlayer BgmPlayer;
	UEngineSoundPlayer StartSound;
};

