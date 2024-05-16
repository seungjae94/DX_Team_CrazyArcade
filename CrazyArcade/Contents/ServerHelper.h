#pragma once
#include "CrazyArcadeEnum.h"
#include <EngineCore/Actor.h>
#include <EngineCore/Level.h>

class ABombBase;
class UNetObject;

class ServerHelper {
public:
	template <typename Type>
	static std::shared_ptr<Type> EnumSpawn(ULevel* _Level, int _Enum) {
		switch (_Enum) {
		case 0:
			break;
		case 1:
			break;
		case 2:
			break;
		case 2001:
			return _Level->SpawnActor<ABombBase>("Bomb");
			break;
		default:
			return nullptr;
			break;
		}
		return nullptr;
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