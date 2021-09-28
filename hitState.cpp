#include "stdafx.h"
#include "hitState.h"
#include "player.h"
#include "idleState.h"
#include "fallState.h"
#include "hitAndDownState.h"

state * hitState::inputHandle(player * player)
{
	if (PLAYERDATA->time % 8 == 7 && PLAYERDATA->frameX >= _hitCount * 4 - 1)
		return new idleState;
	if (PLAYERDATA->isHit && PLAYERDATA->hitRecovery < 20)
		return new hitAndDownState;
	
	return nullptr;
}

void hitState::enter(player * player)
{
	PLAYERDATA->image = IMAGEMANAGER->findImage("캐릭터피격");
	PLAYERDATA->frameX = 0;
	PLAYERDATA->time = 0;
	PLAYERDATA->speed = 3.f;
	PLAYERDATA->jumpPower = 0.f;
	PLAYERDATA->stateEnum = STATE_HIT;
	_hitCount = 1;
	_onGround = PLAYERDATA->isRide;
}

void hitState::update(player * player)
{
	if (!PLAYERDATA->isRide && PLAYERDATA->z > 0.f)
	{
		PLAYERDATA->z += PLAYERDATA->jumpPower;
		PLAYERDATA->jumpPower -= PLAYERDATA->gravity;
	}
	else if (PLAYERDATA->z < 0.f)
		PLAYERDATA->z = 0.f;
	if (PLAYERDATA->time < 7)
	{
		switch (PLAYERDATA->frameY)
		{
		case 0:
			PLAYERDATA->x -= PLAYERDATA->speed;
			break;
		case 1:
			PLAYERDATA->x += PLAYERDATA->speed;
			break;
		default:
			break;
		}
	}

	if (PLAYERDATA->isHit)
	{
		if (PLAYERDATA->hitRecovery > 60)
		{
			PLAYERDATA->frameX = 0;
			PLAYERDATA->time = 0;
		}
		else if (PLAYERDATA->hitRecovery > 30)
		{
			PLAYERDATA->frameX = 4;
			PLAYERDATA->time = 0;
			_hitCount = 2;
		}
		else
		{
			PLAYERDATA->frameX = 8;
			PLAYERDATA->time = 0;
			_hitCount = 3;
		}
		PLAYERDATA->isHit = false;
	}
	if (PLAYERDATA->frameX == (_hitCount -1) * 4)
	{
		if (PLAYERDATA->time % 15 == 14)
		{
			PLAYERDATA->frameX += 1;
		}

	}
	else if (PLAYERDATA->time % 8 == 7)
	{
		PLAYERDATA->frameX += 1;
	}
}

void hitState::exit(player * player)
{

}
