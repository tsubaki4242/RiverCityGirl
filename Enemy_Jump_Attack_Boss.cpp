#include "stdafx.h"
#include "Enemy_Basic.h"

#include "Enemy_Jump_Attack_Boss.h"
#include "Enemy_Jump_Attack_stun_Boss.h"
#include "Enemy_Jump_Attack_not_stun.h"

#include "Enemy_Jump_Attack_Ready.h"

#include "Enemy_Idle_Boss.h"

Enemy_State * Enemy_Jump_Attack_Boss::input_state(Enemy_Basic * _Enemy, bool reverse, int targetX, int targetY)
{
	if (_Enemy->getEnemyInfo()->y - _Enemy->getEnemyInfo()->z < _Enemy->getEnemyInfo()->y)
	{
		_Enemy->setEnemyGravity(0);
		_Enemy->setEnemyJumpSpeed(0);

		_Enemy->setEnemyPointZ(0);
		_Enemy->setBossSpecialCount();

		moveCount = 0;
		SaveTargetX = 0;
		SaveTargetY = 0;

		_Enemy->getAttackRect()->isAttackCollision = false;

		if (_Enemy->getEnemyInfo()->Special_Attack_Count <= 0) return new Enemy_Jump_Attack_stun_Boss();
		else return new Enemy_Jump_Attack_Ready();
	}

	return nullptr;
}

void Enemy_Jump_Attack_Boss::update(Enemy_Basic * _Enemy, int targetX, int targetY)
{

	ImageUpdateFunc(_Enemy);


	/*if (!isDown)
	{
		if (_Enemy->getEnemyInfo()->y - _Enemy->getEnemyInfo()->z < 1100)
		{
			_Enemy->setEnemyGravity(_Enemy->getEnemyInfo()->gravity + BOSS_GRAVITY);
			_Enemy->setEnemyPointZ(_Enemy->getEnemyInfo()->z + _Enemy->getEnemyInfo()->gravity - _Enemy->getEnemyInfo()->JumpPower);
		}
		else
		{
			_Enemy->setEnemyImage(IMAGEMANAGER->findImage("Misuzu_Jump_Down"));
			_Enemy->setEnemyPointZ(_Enemy->getEnemyInfo()->y -1100);

			isDown = true;
		}

	}
	else
	{
		moveCount++;


		if (moveCount < 50)
		{
			SaveTargetX = targetX;
			SaveTargetY = targetY;

			float angle = getAngle(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, SaveTargetX, SaveTargetY);

			_Enemy->setEnemyPointX(_Enemy->getEnemyInfo()->x + cosf(angle)*MOVESPEED_LEFT_RIGHT*15.0f);
			_Enemy->setEnemyPointY(_Enemy->getEnemyInfo()->y - sinf(angle)*MOVESPEED_UP_DOWN*20.0f);

			if (_Enemy->getEnemyInfo()->x < targetX) _Enemy->setEnemyReverse(true);
			else _Enemy->setEnemyReverse(false);
		}

		_Enemy->setEnemyGravity(_Enemy->getEnemyInfo()->gravity + BOSS_GRAVITY * 1.4f);
		_Enemy->setEnemyPointZ(_Enemy->getEnemyInfo()->z + _Enemy->getEnemyInfo()->gravity - _Enemy->getEnemyInfo()->JumpPower);

	}*/

	if (!isDown)
	{
		_Enemy->setEnemyGravity(_Enemy->getEnemyInfo()->gravity + BOSS_GRAVITY);
		_Enemy->setEnemyPointZ(_Enemy->getEnemyInfo()->z + _Enemy->getEnemyInfo()->gravity - _Enemy->getEnemyInfo()->JumpPower);

		if ((_Enemy->getEnemyInfo()->y - RENDERMANAGER->getCameraY()) < (- _Enemy->getEnemyInfo()->z))
		{

			_Enemy->setEnemyImage(IMAGEMANAGER->findImage("Misuzu_Jump_Down"));
			isDown = true;
			_Enemy->setEnemyJumpSpeed(0);
		}
		
	}
	else
	{
		moveCount++;

		if (moveCount <30)
		{
			SaveTargetX = targetX;
			SaveTargetY = targetY;

			float angle = getAngle(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, SaveTargetX, SaveTargetY);

			_Enemy->setEnemyPointX(_Enemy->getEnemyInfo()->x + cosf(angle)*MOVESPEED_LEFT_RIGHT*20.0f);
			_Enemy->setEnemyPointY(_Enemy->getEnemyInfo()->y - sinf(angle)*MOVESPEED_UP_DOWN*20.0f);

			if (_Enemy->getEnemyInfo()->x < targetX) _Enemy->setEnemyReverse(true);
			else _Enemy->setEnemyReverse(false);

		
		}
		else
		{
			_Enemy->setEnemyGravity(_Enemy->getEnemyInfo()->gravity + BOSS_GRAVITY * 5);
			_Enemy->setEnemyPointZ(_Enemy->getEnemyInfo()->z + _Enemy->getEnemyInfo()->gravity - _Enemy->getEnemyInfo()->JumpPower);


			if (_Enemy->getEnemyInfo()->y - _Enemy->getEnemyInfo()->z < _Enemy->getEnemyInfo()->y - 10)
			{
				/*_Enemy->Setting_AttackRect_Center(BOSS,
					SaveTargetX,
					SaveTargetY,
					400, 200, 1, frameCount, frameUpdateCount
				);*/

				_Enemy->getAttackRect()->AttackRect = RectMakeCenter(SaveTargetX, SaveTargetY, 400, 200);

				_Enemy->getAttackRect()->isAttackCollision = true;
			}
		}
	}


}

void Enemy_Jump_Attack_Boss::release(Enemy_Basic * _Enemy)
{
}

void Enemy_Jump_Attack_Boss::enter_this_state(Enemy_Basic * _Enemy)
{
	_Enemy->setEnemyTestText("IDLE");
	//_Enemy->set_Enemy_State_Enum();

	char str[128] = "Misuzu_Jump_Up";

	_Enemy->setEnemyImage(IMAGEMANAGER->findImage(str));

	_Enemy->setEnemyJumpSpeed(BOSS_JUMP_SPEED);

	frameCount = 0;
	frameUpdateCount = 100;

	_Enemy->setEnemyFrameX(0);

	if (_Enemy->getEnemyInfo()->isRight) _Enemy->setEnemyFrameY(0);
	else _Enemy->setEnemyFrameY(1);

	isDown = false;

	moveCount = 0;

	SaveTargetX = 0;
	SaveTargetY = 0;
}


void Enemy_Jump_Attack_Boss::ImageUpdateFunc(Enemy_Basic * _Enemy)
{
	frameCount++;
	
	if (frameCount % frameUpdateCount == 0)
	{
		if (_Enemy->getEnemyInfo()->isRight)
		{
			_Enemy->setEnemyFrameY(0);
			_Enemy->setEnemyFrameX(_Enemy->getEnemyInfo()->CurrentframeX + 1);

			if (_Enemy->getEnemyInfo()->CurrentframeX > _Enemy->getEnemyInfo()->_image->getMaxFrameX()) _Enemy->setEnemyFrameX(0);
		}
		else
		{
			_Enemy->setEnemyFrameY(1);
			_Enemy->setEnemyFrameX(_Enemy->getEnemyInfo()->CurrentframeX + 1);

			if (_Enemy->getEnemyInfo()->CurrentframeX > _Enemy->getEnemyInfo()->_image->getMaxFrameX()) _Enemy->setEnemyFrameX(0);
		}
	}
}
