#pragma once
#include "gameNode.h"
#include "testScene.h"
#include "stage_3rdFloor_Corridor.h"
#include "stage_2ndFloor_HallA.h"
#include "stage_2ndFloor_room.h"
#include "stage_2ndFloor_HallB.h"
#include "stage_1stFloor_HallA.h"
#include "stage_1stFloor_HallB.h"
#include "stage_1stFloor_room.h"
#include "stage_cafeteria.h"
#include "stage_lobby.h"
#include "stage_Detention.h"

class loading :
	public gameNode
{
private:
	image* _loading;
	int _count;
public:
	loading();
	~loading();    

	
	HRESULT init();
	void release();
	void update();
	void render();
};

static DWORD CALLBACK threadFunction(LPVOID lpParameter);