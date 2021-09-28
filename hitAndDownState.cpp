#include "stdafx.h"
#include "hitAndDownState.h"
#include "downState.h"
#include "fallState.h"
#include "player.h"

state * hitAndDownState::inputHandle(player * player)
{
	if (PLAYERDATA->frameX == 23)
	{
		return new downState;
	}
	return nullptr;
}

void hitAndDownState::enter(player * player)
{
	PLAYERDATA->image = IMAGEMANAGER->findImage("캐릭터피격후기상");
	PLAYERDATA->frameX = 0;
	PLAYERDATA->time = 0;
	PLAYERDATA->speed = 3.0f;
	PLAYERDATA->jumpPower = 12.0f;
	_onGround = PLAYERDATA->isRide;
	_saveZ = PLAYERDATA->z;
	PLAYERDATA->z = PLAYERDATA->z + PLAYERDATA->jumpPower;
	PLAYERDATA->jumpPower = PLAYERDATA->jumpPower - PLAYERDATA->gravity;
	PLAYERDATA->stateEnum = STATE_DOWN;
}

void hitAndDownState::update(player * player)
{
	if (_onGround && !PLAYERDATA->isRide)
	{
		_onGround = false;
		_saveZ = 0.f;
	}
	else if (!_onGround && PLAYERDATA->isRide)
	{
		_onGround = true;
		_saveZ = PLAYERDATA->z;
	}
	if (!PLAYERDATA->isRide)
	{
		if (PLAYERDATA->z > 0.f)
		{
			PLAYERDATA->z = PLAYERDATA->z + PLAYERDATA->jumpPower;
			PLAYERDATA->jumpPower = PLAYERDATA->jumpPower - PLAYERDATA->gravity;
		}
		if (PLAYERDATA->z < 0.f)
		{
			PLAYERDATA->z = 0.f;
		}
		if (PLAYERDATA->z == 0.f)
		{
			_saveZ = 0.f;
		}
	}
	else
	{
		_saveZ = PLAYERDATA->z;
	}
	if (PLAYERDATA->time % 3 == 2 && PLAYERDATA->frameX < 11)
	{
		PLAYERDATA->frameX = PLAYERDATA->frameX + 1;
	}
	if (PLAYERDATA->frameX > 11 && PLAYERDATA->z != _saveZ)
	{
		PLAYERDATA->frameX = 11;
	}
	if (PLAYERDATA->frameX >= 11 && PLAYERDATA->z == _saveZ)
	{
		if (PLAYERDATA->time % 3 == 2)
			PLAYERDATA->frameX += 1;
	}
	if (PLAYERDATA->time < 55)
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
}

void hitAndDownState::exit(player * player)
{
}
