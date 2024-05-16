#pragma once
#include "CrazyArcadeEnum.h"
#include <EngineCore/Actor.h>
#include <EngineCore/Level.h>

class UNetObject;

class ServerHelper {
public:
	static std::shared_ptr<ANetActor> EnumSpawn(ULevel* _Level, int _Enum);

	template <typename Enum>
	static Enum EnumReturn(int _EnumNum) {
		if (_EnumNum < 1000) {
		return static_cast<ECharacterType>(_EnumNum);
		}
		else if (_EnumNum < 2000) {
			return static_cast<EBlockType>(_EnumNum);
		}
		else if (_EnumNum < 3000) {
			return static_cast<EPlayerItem>(_EnumNum);
		}
		return static_cast<EPlayerItem>(_EnumNum);
	}
};