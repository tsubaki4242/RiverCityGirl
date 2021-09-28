#include "stdafx.h"
#include "strongAttackState.h"
#include "idleState.h"
#include "player.h"

state * strongAttackState::inputHandle(player * player)
{
	if (PLAYERDATA->frameX >= PLAYERDATA->image->getMaxFrameX())
	{
		return new idleState;
	}
	return nullptr;
}

void strongAttackState::enter(player * player)
{
	PLAYERDATA->image = IMAGEMANAGER->findImage("캐릭터강공격");
	PLAYERDATA->frameX = 0;
	PLAYERDATA->time = 0;
	PLAYERDATA->comboCount = 0;
	PLAYERDATA->imageErrorX = 8;
	PLAYERDATA->stateEnum = STATE_STRONGATTACK;
}

void strongAttackState::update(player * player)
{
	if (PLAYERDATA->time < 15)
		switch (PLAYERDATA->frameY)
		{
		case 0:
			PLAYERDATA->x += 2.5f;
			break;
		case 1:
			PLAYERDATA->x -= 2.5f;
			break;
		default:
			break;
		}
	if (PLAYERDATA->time % 5 == 4)
		PLAYERDATA->frameX += 1;
	
	if (PLAYERDATA->frameX == 5)
	{
		if (PLAYERDATA->time % 5 == 2)
		{
			PLAYERDATA->isAttack = true;
			player->setAttackRc(160.f, 70.f);
		}
		if (PLAYERDATA->time % 5 == 3)
		{
			PLAYERDATA->isAttack = false;
		}
	}
	
}

void strongAttackState::exit(player * player)
{


}
