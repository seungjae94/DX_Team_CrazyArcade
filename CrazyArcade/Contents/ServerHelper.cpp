#include "PreCompile.h"
#include "Bomb.h"
#include "ServerHelper.h"
#include <EngineBase/NetObject.h>


std::shared_ptr<UNetObject> ServerHelper::EnumSpawn(ULevel* _Level, int _Enum) {
	switch (_Enum) {
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	case 2001:
		return _Level->SpawnActor<ABomb>("Bomb");
		break;
	default:
		return nullptr;
		break;
	}
	return nullptr;
}