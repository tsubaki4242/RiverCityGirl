#include "stdafx.h"
#include "comboState.h"
#include "player.h"
#include "idleState.h"
#include "fallState.h"
#include "strongAttackState.h"

state * comboState::inputHandle(player * player)
{
	if (PLAYERDATA->frameX >= PLAYERDATA->image->getMaxFrameX())
	{
		return new idleState;
	}
	if (PLAYERDATA->comboCount == 2 &&
		PLAYERDATA->time > 26 &&
		PLAYERDATA->time < 30 &&
		KEYMANAGER->isOnceKeyDown('S'))
	{
		return new strongAttackState;
	}
	if (_onGround && !PLAYERDATA->isRide)
	{
		return new fallState;
	}
	return nullptr;
}

void comboState::enter(player * player)
{
	PLAYERDATA->image = IMAGEMANAGER->findImage("캐릭터콤보1");
	PLAYERDATA->frameX = 0;
	PLAYERDATA->time = 0;
	PLAYERDATA->speed = 14.0f;
	PLAYERDATA->imageErrorX = 35;
	PLAYERDATA->imageErrorY = 0;
	PLAYERDATA->stateEnum = STATE_COMBO;
	_onGround = PLAYERDATA->isRide;
	_comboOn = false;
}

void comboState::update(player * player)
{
	if (PLAYERDATA->time % 4 == 3)
	{
		PLAYERDATA->frameX += 1;
	}

	/*커맨드 입력 타이밍을 좀 널널하게 잡고 그 타이밍 안에 눌렀으면
	마지막 동작 후에 자동으로 다음 콤보로 연결*/
	switch (PLAYERDATA->comboCount)
	{
	case 0:
		if (PLAYERDATA->time > 4 &&
			PLAYERDATA->time < 19 &&
			KEYMANAGER->isOnceKeyDown('A'))
		{
			_comboOn = true;
		}
		if (PLAYERDATA->time == 12)
		{
			PLAYERDATA->isAttack = true;
			player->setAttackRc(130, 70);
		}
		if (PLAYERDATA->time == 13)
		{
			PLAYERDATA->isAttack = false;
		}
		if (PLAYERDATA->time == 19 &&
			_comboOn)
		{
			_comboOn = false;
			PLAYERDATA->image = IMAGEMANAGER->findImage("캐릭터콤보2");
			PLAYERDATA->frameX = 0;
			PLAYERDATA->time = 0;
			PLAYERDATA->comboCount = 1;
		}
		break;
	case 1:
		if (PLAYERDATA->time < 11)
		{
			switch (PLAYERDATA->frameY)
			{
			case 0:
				PLAYERDATA->x += 1.5f;
				break;
			case 1:
				PLAYERDATA->x -= 1.5f;
				break;
			default:
				break;
			}
		}
		if (PLAYERDATA->time > 11 &&
			PLAYERDATA->time < 23 &&
			KEYMANAGER->isOnceKeyDown('A'))
		{
			_comboOn = true;
		}
		if (PLAYERDATA->time == 13)
		{
			PLAYERDATA->isAttack = true;
			player->setAttackRc(160, 70);
		}
		if (PLAYERDATA->time == 14)
		{
			PLAYERDATA->isAttack = false;
		}
		if (PLAYERDATA->time == 23 &&
			_comboOn)
		{
			_comboOn = false;
			PLAYERDATA->image = IMAGEMANAGER->findImage("캐릭터콤보3");
			PLAYERDATA->frameX = 0;
			PLAYERDATA->time = 0;
			PLAYERDATA->comboCount = 2;
			PLAYERDATA->imageErrorX = 20;
		}
		break;
	case 2:
		if (PLAYERDATA->time < 14)
		{
			switch (PLAYERDATA->frameY)
			{
			case 0:
				PLAYERDATA->x += 1.8f;
				break;
			case 1:
				PLAYERDATA->x -= 1.8f;
				break;
			default:
				break;
			}
		}
		if (PLAYERDATA->time == 16)
		{
			PLAYERDATA->isAttack = true;
			player->setAttackRc(180, 70);
		}
		if (PLAYERDATA->time == 17)
		{
			PLAYERDATA->isAttack = false;
		}
		break;
	default:
		break;
	}

}

void comboState::exit(player * player)
{

}
