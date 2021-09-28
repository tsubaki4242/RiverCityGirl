#include "stdafx.h"
#include "Enemy_Basic.h"

#include "Enemy_Dash_Attack_Boss.h"
#include "Enemy_Tount_Boss.h"
#include "Enemy_Idle.h"

Enemy_State * Enemy_Dash_Attack_Boss::input_state(Enemy_Basic * _Enemy, bool reverse, int targetX, int targetY)
{
	return nullptr;
}

void Enemy_Dash_Attack_Boss::update(Enemy_Basic * _Enemy, int targetX, int targetY)
{
	ImageUpdateFunc(_Enemy);

	if (DashAttackCount == 0)
	{
		targetAngle = getAngle(_Enemy->getEnemyInfo()->x,
			_Enemy->getEnemyInfo()->y, targetX, targetY);

		if (_Enemy->getEnemyInfo()->x > targetX) _Enemy->setEnemyReverse(true);
		else _Enemy->setEnemyReverse(false);
	}

	DashAttackCount++;

	if (DashAttackCount%MaxDashAttackCount != 0)
	{

		//이동 
		float angle = getAngle(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, targetX, targetY);

		_Enemy->setEnemyPointX(_Enemy->getEnemyInfo()->x + cosf(targetAngle)*MOVESPEED_LEFT_RIGHT*1.5f);
		_Enemy->setEnemyPointY(_Enemy->getEnemyInfo()->y - sinf(targetAngle)*MOVESPEED_UP_DOWN*1.5f);

		/*
		y축은 완전히 전환하지 않고, 일정 거리만큼만 내려감.
		적에게 명중, 혹은 일정시간동안 맞지않으면 tount로 돌아감.
		*/

		if (_Enemy->getEnemyInfo()->isRight)
		{
			_Enemy->Setting_AttackRect_LeftRight(BOSS,
				_Enemy->getEnemyInfo()->rc.left - 30, _Enemy->getEnemyInfo()->rc.top - 10,
				20, 50, 6, frameCount, frameUpdateCount);

		}
		else
		{
			_Enemy->Setting_AttackRect_LeftRight(BOSS,
				_Enemy->getEnemyInfo()->rc.right + 10, _Enemy->getEnemyInfo()->rc.top - 10,
				20, 50, 6, frameCount, frameUpdateCount);
		}
		_Enemy->getAttackRect()->isAttackCollision = true;
	}
	else
	{
		_Enemy->getAttackRect()->isAttackCollision = false;
		_Enemy->set_Enemy_State(new Enemy_Tount_Boss);
	}
}

void Enemy_Dash_Attack_Boss::release(Enemy_Basic * _Enemy)
{
}

void Enemy_Dash_Attack_Boss::enter_this_state(Enemy_Basic * _Enemy)
{
	_Enemy->set_Enum_State_Boss(DASH_ATTACK_BOSS);


	char str[128] = "Misuzu_Takkle";

	_Enemy->setEnemyImage(IMAGEMANAGER->findImage(str));

	frameCount = 0;
	frameUpdateCount = 5;

	_Enemy->setEnemyFrameX(0);

	if (_Enemy->getEnemyInfo()->isRight) _Enemy->setEnemyFrameY(0);
	else _Enemy->setEnemyFrameY(1);

	DashAttackCount = 0;
	MaxDashAttackCount = 100;
}



void Enemy_Dash_Attack_Boss::ImageUpdateFunc(Enemy_Basic * _Enemy)
{
	frameCount++;

	if (frameCount % frameUpdateCount == 0)
	{
		if (_Enemy->getEnemyInfo()->isRight)
		{
			_Enemy->setEnemyFrameY(1);
			_Enemy->setEnemyFrameX(_Enemy->getEnemyInfo()->CurrentframeX + 1);

			if (_Enemy->getEnemyInfo()->CurrentframeX > _Enemy->getEnemyInfo()->_image->getMaxFrameX() - 3)
				_Enemy->setEnemyFrameX(0);
		}
		else
		{
			_Enemy->setEnemyFrameY(0);
			_Enemy->setEnemyFrameX(_Enemy->getEnemyInfo()->CurrentframeX + 1);

			if (_Enemy->getEnemyInfo()->CurrentframeX > _Enemy->getEnemyInfo()->_image->getMaxFrameX() - 3)
				_Enemy->setEnemyFrameX(0);
		}
	}
}
