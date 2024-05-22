#include"PreCompile.h"
#include "InGameUI.h"
#include "Player.h"
#include "CrazyArcadeCore.h"
#include "ConnectionInfo.h"
#include "ServerManager.h"
#include "Packets.h"

AInGameUI::AInGameUI()
{
}

AInGameUI::~AInGameUI()
{
}

void AInGameUI::BeginPlay()
{


	UEngineSprite::CreateCutting("Play_ExitButtonHover.png", 1, 2);


	//베찌
	UEngineSprite::CreateCutting("Play_Portrait_Bazzi_Lose_R.png", 1, 4);
	UEngineSprite::CreateCutting("Play_Portrait_Bazzi_Normal_R.png", 1, 2);
	UEngineSprite::CreateCutting("Play_Portrait_Bazzi_Lose_B.png", 1, 4);
	UEngineSprite::CreateCutting("Play_Portrait_Bazzi_Normal_B.png", 1, 2);

	//다오
	UEngineSprite::CreateCutting("Play_Portrait_Dao_Normal_R.png", 1, 2);
	UEngineSprite::CreateCutting("Play_Portrait_Dao_Lose_R.png", 1, 4);
	UEngineSprite::CreateCutting("Play_Portrait_Dao_Lose_B.png", 1, 4);
	UEngineSprite::CreateCutting("Play_Portrait_Dao_Normal_B.png", 1, 2);

	//마리드
	UEngineSprite::CreateCutting("Play_Portrait_Marid_Lose_B.png", 1, 4);
	UEngineSprite::CreateCutting("Play_Portrait_Marid_Lose_R.png", 1, 4);
	UEngineSprite::CreateCutting("Play_Portrait_Marid_Normal_B.png", 1, 2);
	UEngineSprite::CreateCutting("Play_Portrait_Marid_Normal_R.png", 1, 2);



	Super::BeginPlay();
	CancelBtn = CreateWidget<UImage>(GetWorld(), "CancelButton");
	CancelBtn->CreateAnimation("CancelButtonUnHoverAni", "Play_ExitButtonUnHover.png", 0.1f, false, 0, 0);
	CancelBtn->CreateAnimation("CancelButtonHoverAni", "Play_ExitButtonHover.png", 0.1f, false, 0, 1);
	CancelBtn->CreateAnimation("CancelButtonIsDownAni", "Play_ExitButtonIsDown.png", 0.1f, false, 0, 0);

	CancelBtn->SetAutoSize(1.0f, true);
	CancelBtn->ChangeAnimation("CancelButtonUnHoverAni");
	CancelBtn->SetWidgetLocation({ 316.0f, -276.0f });
	CancelBtn->AddToViewPort(3);


	ResultBackGround = CreateWidget<UImage>(GetWorld(), "ResultBackGroundUI");
	ResultBackGround->SetSprite("ResultWindow.png");
	ResultBackGround->SetMulColor({ 1.0f,1.0f,1.0f,0.7f });
	ResultBackGround->AddWidgetLocation(FVector{ -80.0,-30.0f });
	ResultBackGround->AddToViewPort(3);
	ResultBackGround->SetScale({ 550,400 });


	ResultSummary = CreateWidget<UImage>(GetWorld(), "ResultBackGroundUI");
	ResultSummary->SetSprite("Result_Summary.png");

	ResultSummary->AddWidgetLocation(FVector{ -90.0f,140.0f });
	ResultSummary->SetScale({ 350,20 });
	ResultSummary->AddToViewPort(4);



	CancelBtn->SetUnHover([=] {



		CancelBtn->ChangeAnimation("CancelButtonUnHoverAni");

		});
	CancelBtn->SetHover([=] {

		CancelBtn->ChangeAnimation("CancelButtonHoverAni");


		});
	CancelBtn->SetDown([=] {

		if (ENetType::Server == UCrazyArcadeCore::NetManager.GetNetType()) {
			std::shared_ptr<UChangeLevelPacket> LevelChangePacket = std::make_shared<UChangeLevelPacket>();
			LevelChangePacket->LevelName = "LobbyTitleTestLevel";
			UCrazyArcadeCore::Net->Send(LevelChangePacket);

		CancelBtn->ChangeAnimation("CancelButtonUnHoverAni");
		CancelBtn->SetUp([=] {

			GEngine->ChangeLevel("LobbyTitleTestLevel");
			});
		}

		});


	//게임 실행 하면 유저 정보 가져와서 표시해주기 

	for (int i = 0; i < 8; i++)
	{

		UImage* Render = CreateWidget<UImage>(GetWorld(), "PlayerRender" + i);
		//Render->SetSprite();
		Render->CreateAnimation("BazziRedNormal", "Play_Portrait_Bazzi_Normal_R.png", 0.8f, true, 0, 1);
		Render->CreateAnimation("BazziRedDead", "Play_Portrait_Bazzi_Lose_R.png", 0.4f, true, 0, 3);
		Render->CreateAnimation("BazziBlueNormal", "Play_Portrait_Bazzi_Normal_B.png", 0.8f, true, 0, 1);
		Render->CreateAnimation("BazziBlueDead", "Play_Portrait_Bazzi_Lose_B.png", 0.4f, true, 0, 3);

		Render->CreateAnimation("DaoRedNormal", "Play_Portrait_Dao_Normal_R.png", 0.8f, true, 0, 1);
		Render->CreateAnimation("DaoRedDead", "Play_Portrait_Dao_Lose_R.png", 0.4f, true, 0, 3);
		Render->CreateAnimation("DaoBlueNormal", "Play_Portrait_Dao_Normal_B.png", 0.8f, true, 0, 1);
		Render->CreateAnimation("DaoBlueDead", "Play_Portrait_Dao_Lose_B.png", 0.4f, true, 0, 3);

		Render->CreateAnimation("MaridRedNormal", "Play_Portrait_Marid_Normal_R.png", 0.8f, true, 0, 1);
		Render->CreateAnimation("MaridRedDead", "Play_Portrait_Marid_Lose_R.png", 0.4f, true, 0, 3);
		Render->CreateAnimation("MaridBlueNormal", "Play_Portrait_Marid_Normal_B.png", 0.8f, true, 0, 1);
		Render->CreateAnimation("MaridBlueDead", "Play_Portrait_Marid_Lose_B.png", 0.4f, true, 0, 3);




		Render->SetAutoSize(1.0f, true);
		//Render->ChangeAnimation("BazziRedAniNormal");
		// 랜더러 추가로 CreatAnimation만들고 추가하기 
		Render->AddToViewPort(40);
		PlayerUI.push_back(Render);

		UTextWidget* Name = CreateWidget<UTextWidget>(GetWorld(), "PlayerNameUI" + i);
		Name->SetFont("굴림");
		Name->SetScale(12.0f);
		Name->SetColor(Color8Bit::White);
		Name->AddToViewPort(30);
		Name->SetFlag(FW1_LEFT);
		Name->SetPosition({ 0 * (i + 20),0 });

		PlayerNameUI.push_back(Name);

		PlayerState State;
		State.Order = i;
		State.PlayerName = "";
		State.PlayerColor = ECharacterColor::Red;
		State.PlayerType = ECharacterType::Random;
		State.IsDead = false;
		PlayerInfo.push_back(State);
	}

	InitPlayerInfo();
	//DataToRender();

	ResultBackGround->SetActive(false);
	ResultSummary->SetActive(false);
	std::vector<UImage*> PlayerUI; //플레이어
	std::vector<UTextWidget*> PlayerNameUI;
	std::vector<PlayerState> PlayerInfo;


}

void AInGameUI::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);
	InitPlayerInfo();
	DataToRender();
}

void AInGameUI::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}

void AInGameUI::Tick(float _DeltaTIme)
{
	Super::Tick(_DeltaTIme);

	for (std::pair<const int, bool>& Pair : FPlayerInfo::IsDeads)
	{
		//if (Pair.first == true)
		//{
		//	// 죽은 플레이어가 해야할 코드
		//	//PlayerUI[Pair.first]->ChangeAnimation();
		//	
		//}
	}
	//죽었는지 살았는지 확인하는 예제 코드(승재형)

	if (this->IsActive() == true)
	{
		//InitPlayerInfo();
		//DataToRender();
		//PlayerStateCheck();

	}

	DeadCheck(); //죽었으면 상태를 바꿔준다 


	for (int i = 0; i < PlayerInfo.size(); i++)
	{
		if (PlayerInfo[i].IsDead == true && PlayerInfo[i].IsChange == false)
		{
			std::string AnimName = StateToAnimName(PlayerInfo[i].PlayerType, PlayerInfo[i].PlayerColor, PlayerInfo[i].IsDead);
			PlayerUI[i]->ChangeAnimation(AnimName);
			PlayerInfo[i].IsChange = true;
		}	//
	}

}



void AInGameUI::PlayerUpdate()
{
	std::map<int, ConnectUserInfo> UserInfos = ConnectionInfo::GetInst().GetUserInfos();

	for (std::pair<int, ConnectUserInfo> Iterator : UserInfos)
	{
		//	PlayerInfo[Iterator.first].IsDead = FPlayerInfo::IsDeads;
	}


	for (int i = 0; i < UCrazyArcadeCore::Net->GetSessionToken(); i++)
	{
		//PlayerInfo[i].IsDead() = FPlayerInfo::IsDeads();
	}
}



void AInGameUI::InitPlayerInfo()
{
	//
	std::map<int, ConnectUserInfo> UserInfos = ConnectionInfo::GetInst().GetUserInfos();
	std::map<int, bool>UserDeadCheck = FPlayerInfo::IsDeads;

	//오더랑 이름 가져오기
	for (std::pair<int, ConnectUserInfo> Iterator : UserInfos)
	{ //이터레이터로 돌리기 
		PlayerInfo[Iterator.first].Order = Iterator.first;
		//PlayerInfo[Iterator.first].IsDead = UserDeadCheck[Iterator.first];
		//임시 작업용 코드 	

		PlayerInfo[Iterator.first].PlayerName = Iterator.second.MyName;
		PlayerInfo[Iterator.first].PlayerType = Iterator.second.GetMyCharacterType();
		PlayerInfo[Iterator.first].PlayerColor = Iterator.second.GetMyColorType();

	}

	for (std::pair<int, bool> Iterattor : UserDeadCheck)
	{
		PlayerInfo[Iterattor.first].IsDead = Iterattor.second;
	}
}


void AInGameUI::DataToRender()
{


	//PlayerInfo.size()
	for (int i = 0; i < PlayerInfo.size(); i++)
	{
		PlayerNameUI[i]->SetPosition({ 305, 179 - (i * 43) });
		PlayerNameUI[i]->SetText(PlayerInfo[i].PlayerName);
		PlayerUI[i]->SetPosition({ 281, 181 - (i * 43) });
		PlayerStateCheck();
	}



	//사진 

	//ChangeAnmation()

}

std::string AInGameUI::StateToAnimName(ECharacterType _Type, ECharacterColor _Color, bool _IsDead)
{
	return TypeToName(_Type) + ColorToName(_Color) + (_IsDead ? "Dead" : "Normal");

	//애니메이션 이름은 만들고 
	//return TypeToName[_Type] + ColorToName[_Color] + (_IsDead ? "Dead" : "Normal");
}


void AInGameUI::PlayerStateCheck()
{
	//유저 들어오면 들어올수록 증가해주고 
	//처음에 셋팅할때 디폴트로 셋팅을 해주기 때문에 전부 껐다가 켜는 기능을 추가하였다. 
	std::map<int, ConnectUserInfo> UserInfos = ConnectionInfo::GetInst().GetUserInfos();

	int UserCount = static_cast<int>(UserInfos.size());

	for (int i = 0; i < UserCount; ++i)
	{
		PlayerUI[i]->SetActive(true);

		std::string AnimName = StateToAnimName(PlayerInfo[i].PlayerType, PlayerInfo[i].PlayerColor, PlayerInfo[i].IsDead);
		PlayerUI[i]->ChangeAnimation(AnimName);
	}

	for (int i = UserCount; i < 8; ++i)
	{
		PlayerUI[i]->SetActive(false);
	}


	//for (int i = 0; i < PlayerInfo.size(); i++)
	//{
	//	/*PlayerInfo[i].PlayerType*/
	////ECharacterType TypeToName = ECharacterType::Bazzi;
	////ECharacterColor ColorToName = PlayerInfo[i].PlayerColor;

	////std::string name = StateToAnimName(TypeToName, ColorToName, PlayerInfo[i].IsDead);
	////PlayerUI[i]->ChangeAnimation(StateToAnimName(TypeToName, ColorToName, PlayerInfo[i].IsDead));
	////어떤 상태를 한번에 채크하는 방식으로 사용할 것ㅇ이다.

	//	std::string AnimName = StateToAnimName(PlayerInfo[i].PlayerType,PlayerInfo[i].PlayerColor,PlayerInfo[i].IsDead);
	//	PlayerUI[i]->ChangeAnimation(AnimName);
	//}
}

std::string AInGameUI::TypeToName(ECharacterType _Type)
{

	switch (_Type)
	{
	case ECharacterType::Bazzi:
		return "Bazzi";

	case ECharacterType::Dao:
		return "Dao";

	case ECharacterType::Marid:
		return "Marid";

	default:
		return "Dao";
		break;
	}
}

std::string AInGameUI::ColorToName(ECharacterColor _Color)
{
	switch (_Color)
	{
	case ECharacterColor::Red:
		return "Red";

	case ECharacterColor::Blue:
		return "Blue";
	default:
		return "Red";
		break;
	}
}

void AInGameUI::DeadCheck()
{
	std::map<int, bool>UserDeadCheck = FPlayerInfo::IsDeads;
	
	for (std::pair<int, bool> Iterattor : UserDeadCheck)
	{
		PlayerInfo[Iterattor.first].IsDead = Iterattor.second;

	}
}


