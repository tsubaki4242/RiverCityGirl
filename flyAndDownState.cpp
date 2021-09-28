#include "stdafx.h"
#include "flyAndDownState.h"
#include "downState.h"
#include "player.h"

state * flyAndDownState::inputHandle(player * player)
{
	if (PLAYERDATA->frameX >= PLAYERDATA->image->getMaxFrameX())
	{
		return new downState;
	}
	return nullptr;
}

void flyAndDownState::enter(player * player)
{
	PLAYERDATA->image = IMAGEMANAGER->findImage("캐릭터멀리날아감");
	PLAYERDATA->frameX = 0;
	PLAYERDATA->time = 0;
	PLAYERDATA->speed = 9.0f;
	PLAYERDATA->stateEnum = STATE_DOWN;
}

void flyAndDownState::update(player * player)
{
	if (PLAYERDATA->time % 4 == 3)
	{
		PLAYERDATA->frameX += 1;
		switch (PLAYERDATA->frameY)
		{
		case 0:
			PLAYERDATA->frameX -= PLAYERDATA->speed;
			break;
		case 1:
			PLAYERDATA->frameX += PLAYERDATA->speed;
			break;
		default:
			break;
		}
	}
}

void flyAndDownState::exit(player * player)
{
}
