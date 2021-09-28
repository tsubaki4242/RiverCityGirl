#include "stdafx.h"
#include "deadState.h"
#include "player.h"

state * deadState::inputHandle(player * player)
{
	return nullptr;
}

void deadState::enter(player * player)
{
	PLAYERDATA->image = IMAGEMANAGER->findImage("Ä³¸¯ÅÍ»ç¸Á");
	PLAYERDATA->frameX = 0;
	PLAYERDATA->time = 0;
	PLAYERDATA->speed = 0.f;
	PLAYERDATA->stateEnum = STATE_DEAD;
	PLAYERDATA->imageErrorX = 24;
}

void deadState::update(player * player)
{
	if (PLAYERDATA->time % 5 == 4)
	{
		PLAYERDATA->x += 1;
		if (PLAYERDATA->frameX >= PLAYERDATA->image->getMaxFrameX())
			PLAYERDATA->frameX = PLAYERDATA->image->getMaxFrameX();
	}
}

void deadState::exit(player * player)
{

}
