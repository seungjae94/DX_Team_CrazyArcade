#include "PreCompile.h"
#include "BombBase.h"
#include "ServerHelper.h"


std::shared_ptr<ANetActor> ServerHelper::EnumSpawn(ULevel* _Level, int _Enum) {
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