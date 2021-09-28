#include "stdafx.h"
#include "Enemy_Basic.h"

#include "Enemy_Power_Up_Boss.h"
#include "Enemy_Idle_Boss.h"

Enemy_State * Enemy_Power_Up_Boss::input_state(Enemy_Basic * _Enemy, bool reverse, int targetX, int targetY)
{
	return nullptr;
}

void Enemy_Power_Up_Boss::update(Enemy_Basic * _Enemy, int targetX, int targetY)
{
	if (frameCount == 0)
	{
		if (_Enemy->getEnemyInfo()->x < targetX) _Enemy->setEnemyReverse(true);
		else _Enemy->setEnemyReverse(false);
	}

	ImageUpdateFunc(_Enemy);


}

void Enemy_Power_Up_Boss::release(Enemy_Basic * _Enemy)
{
}

void Enemy_Power_Up_Boss::enter_this_state(Enemy_Basic * _Enemy)
{
	_Enemy->setEnemyTestText("IDLE");
	//_Enemy->set_Enemy_State_Enum();

	char str[128] = "Misuzu_PowerUp";

	_Enemy->setEnemyImage(IMAGEMANAGER->findImage(str));

	frameCount = 0;
	frameUpdateCount = 7;

	_Enemy->setEnemyFrameX(0);

	if (_Enemy->getEnemyInfo()->isRight) _Enemy->setEnemyFrameY(0);
	else _Enemy->setEnemyFrameY(1);

	PowerUpCount = 0;
	PowerUpCountUpdate = 100;
}

void Enemy_Power_Up_Boss::call_Idle_function(Enemy_Basic * _Enemy)
{
}

void Enemy_Power_Up_Boss::ImageUpdateFunc(Enemy_Basic * _Enemy)
{
	frameCount++;

	if (frameCount % frameUpdateCount == 0)
	{
		if (_Enemy->getEnemyInfo()->isRight)
		{
			_Enemy->setEnemyFrameY(0);
			_Enemy->setEnemyFrameX(_Enemy->getEnemyInfo()->CurrentframeX + 1);


			if (PowerUpCount < 20)
			{
				PowerUpCount++;
				frameUpdateCount = 5;

				if (_Enemy->getEnemyInfo()->CurrentframeX > 4)
					_Enemy->setEnemyFrameX(2);
			}
			else
			{
				if (_Enemy->getEnemyInfo()->CurrentframeX > _Enemy->getEnemyInfo()->_image->getMaxFrameX())
				{
					frameUpdateCount = 8;

					Enemy_State* IDLE;
					IDLE = new Enemy_Idle_Boss();

					_Enemy->setEnemyAiTrigger_Boss(OBSERVE_STATE_TRIGGER_BOSS);


					_Enemy->set_Enemy_State(IDLE);

				}
			}
		}
		else
		{
			_Enemy->setEnemyFrameY(1);
			_Enemy->setBossSpecialCount_Zero();
			_Enemy->setEnemyFrameX(_Enemy->getEnemyInfo()->CurrentframeX + 1);


			if (PowerUpCount < 20)
			{
				PowerUpCount++;
				frameUpdateCount = 5;

				if (_Enemy->getEnemyInfo()->CurrentframeX > 4)
					_Enemy->setEnemyFrameX(2);
			}
			else
			{
				if (_Enemy->getEnemyInfo()->CurrentframeX > _Enemy->getEnemyInfo()->_image->getMaxFrameX())
				{
					frameUpdateCount = 8;

					Enemy_State* IDLE;
					IDLE = new Enemy_Idle_Boss();

					_Enemy->setEnemyAiTrigger_Boss(OBSERVE_STATE_TRIGGER_BOSS);
					_Enemy->setBossSpecialCount_Zero();
					_Enemy->set_Enemy_State(IDLE);
				}
			}
		}
	}
}
