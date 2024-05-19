#pragma once
#include "CrazyArcadeEnum.h"
#include <EngineCore/Actor.h>
#include <EngineCore/Level.h>
#include "ServerTestOtherPlayer.h"
#include "BombBase.h"

class UNetObject;

class ServerHelper {
public:
	void static EnumSpawn(ULevel* _Level, int _Enum, int _Token) {
		switch (_Enum) {
		case 0:
		{
			std::shared_ptr<ServerTestOtherPlayer> Player = _Level->SpawnActor<ServerTestOtherPlayer>("Player");
			Player->SetObjectToken(_Token);
		}
		break;
		case 1:
			break;
		case 2:
			break;
		case 2001:
		{
			std::shared_ptr<ABombBase> Bomb = _Level->SpawnActor<ABombBase>("Bomb");
			Bomb->SetObjectToken(_Token);
		}
		break;
		default:
			break;
		}
	}

	template <typename Enum>
	static Enum EnumReturn(int _EnumNum) {
		if (_EnumNum < 1000) {
			return static_cast<ECharacterType>(_EnumNum);
		}
		else if (_EnumNum < 2000) {
			return static_cast<EBlockType>(_EnumNum);
		}
		else if (_EnumNum < 3000) {
			return static_cast<EItemType>(_EnumNum);
		}
		return static_cast<EItemType>(_EnumNum);
	}
};