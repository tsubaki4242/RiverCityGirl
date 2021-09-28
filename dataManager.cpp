#include "stdafx.h"
#include "dataManager.h"
dataManager::dataManager()
{
	ZeroMemory(&_playerData, sizeof(playerData));
	_playerData.hp = 0;
	_playerData.z = 0;
	_playerData.y = 0;
	_playerData.x = 0;
	_cameraX = 0;
	_cameraY = 0;
}

dataManager::~dataManager()
{
}

HRESULT dataManager::init()
{
	return S_OK;
}

void dataManager::release()
{
}
