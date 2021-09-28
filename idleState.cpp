#include "stdafx.h"
#include "idleState.h"
#include "walkState.h"
#include "skillState.h"
#include "runState.h"
#include "comboState.h"
#include "strongAttackState.h"
#include "jumpState.h"
#include "player.h"

state * idleState::inputHandle(player * player)
{

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		if (PLAYERDATA->moveCommandInput == 0)
		{
			PLAYERDATA->frameY = 1;
			return new walkState;
		}
		else
		{
			PLAYERDATA->frameY = 1;
			return new runState;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		if (PLAYERDATA->moveCommandInput == 0)
		{
			PLAYERDATA->frameY = 0;
			return new walkState;
		}
		else
		{
			PLAYERDATA->frameY = 0;
			return new runState;
		}
			
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		return new walkState;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		return new walkState;
	}
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		return new skillState;
	}
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		return new comboState;
	}
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		return new strongAttackState;
	}
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		return new jumpState;
	}
	return nullptr;
}

void idleState::enter(player * player)
{
	PLAYERDATA->image = IMAGEMANAGER->findImage("캐릭터기본");
	PLAYERDATA->frameX = 0;
	PLAYERDATA->time = 0;
	PLAYERDATA->comboCount = 0;
	PLAYERDATA->isHit = false;
	PLAYERDATA->isAttack = false;
	PLAYERDATA->isAttackHitted = false;
	PLAYERDATA->imageErrorX = 0;
	PLAYERDATA->imageErrorY = 0;
	PLAYERDATA->stateEnum = STATE_IDLE;
}

void idleState::update(player * player)
{
	if (PLAYERDATA->time % 5 == 4)
	{
		PLAYERDATA->frameX += 1;
		if (PLAYERDATA->frameX > PLAYERDATA->image->getMaxFrameX())
			PLAYERDATA->frameX = 0;
	}
}

void idleState::exit(player * player)
{

}
