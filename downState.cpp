#include "stdafx.h"
#include "downState.h"
#include "player.h"
#include "idleState.h"
#include "deadState.h"

state * downState::inputHandle(player * player)
{
	if (PLAYERDATA->hp <= 0)
		return new deadState;
	if (PLAYERDATA->frameX >= PLAYERDATA->image->getMaxFrameX())
	{
		PLAYERDATA->hitRecovery = 100;
		return new idleState;
	}
	return nullptr;
}

void downState::enter(player * player)
{
	PLAYERDATA->image = IMAGEMANAGER->findImage("캐릭터피격후기상");
	PLAYERDATA->frameX = 23;
	PLAYERDATA->time = 0;
	PLAYERDATA->speed = 0.f;
}
void downState::update(player * player)
{
	if (PLAYERDATA->frameX == 23)
	{
		if (PLAYERDATA->time % 80 == 79)
			PLAYERDATA->frameX += 1;
	}
	else if (PLAYERDATA->time % 5 == 4)
	{
		PLAYERDATA->frameX += 1;
	}
}

void downState::exit(player * player)
{

}
