#include "stdafx.h"
#include "dashAttackState.h"
#include "idleState.h"
#include "fallState.h"
#include "player.h"

state * dashAttackState::inputHandle(player * player)
{
	if (PLAYERDATA->frameX >= PLAYERDATA->image->getMaxFrameX())
	{
		PLAYERDATA->speed = 0.0f;
		return new idleState;
	}
	if (_onGround && !PLAYERDATA->isRide)
	{
		return new fallState;
	}
	return nullptr;
}

void dashAttackState::enter(player * player)
{
	PLAYERDATA->image = IMAGEMANAGER->findImage("캐릭터대시공격");
	PLAYERDATA->frameX = 0;
	PLAYERDATA->time = 0;
	PLAYERDATA->speed = 14.0f;
	PLAYERDATA->imageErrorX = 55;
	PLAYERDATA->imageErrorY = 5;
	PLAYERDATA->stateEnum = STATE_DASHATTACK;
	_onGround = PLAYERDATA->isRide;
}

void dashAttackState::update(player * player)
{
	if (PLAYERDATA->time % 5 == 4)
	{
		PLAYERDATA->frameX += 1;
	}
	if (PLAYERDATA->speed > 0.f)
	{
		PLAYERDATA->speed -= 0.3f;
		switch (PLAYERDATA->frameY)
		{
		case 0:
			PLAYERDATA->x += PLAYERDATA->speed;
			break;
		case 1:
			PLAYERDATA->x -= PLAYERDATA->speed;
			break;
		default:
			break;
		}
	}
	if (PLAYERDATA->frameX > 2)
	{
		if (PLAYERDATA->time % 5 == 1)
		{
			PLAYERDATA->isAttack = true;
			player->setAttackRc(140, 50);
		}
		if (PLAYERDATA->time % 5 == 2)
			PLAYERDATA->isAttack = false;
	}
}

void dashAttackState::exit(player * player)
{
}
