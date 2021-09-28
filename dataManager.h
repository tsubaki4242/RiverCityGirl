#pragma once
#include "stdafx.h"
// 돈과 관련된 정	보 빼고 모두 이곳을 통해 상호작용 할 수 있도록
struct playerData
{
	float x;
	float y;
	float z;
	int hp;
};
class dataManager : public singletonBase<dataManager>
{
private:
	string _stageKey;
	string _bgmKey;
	playerData _playerData;
	
	float _cameraX;
	float _cameraY;
public:
	dataManager();
	~dataManager();

	HRESULT init();
	void release();

	void setPlayerData(float x, float y, float z, int hp) { _playerData.x = x;  _playerData.y = y;  _playerData.z = z;  _playerData.hp = hp; }
	playerData getPlayerData() { return _playerData; }
	void setStageKey(string stykey) { _stageKey = stykey; }
	void setBgmKey(string stykey) { _bgmKey = stykey; }
	string getStageKey() { return _stageKey; }
	string getBgmKey() { return _bgmKey; }

	void setHp(int hp) { _playerData.hp = hp; }
	void setCamera(float x, float y) { _cameraX = x; _cameraY = y; }
	float getCameraX() { return _cameraX; }
	float getCameraY() { return _cameraY; }
};

