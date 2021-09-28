#include "stdafx.h"
#include "Enemy_Basic.h"

#include "Enemy_Idle_Boss.h"
#include "Enemy_Attacked_2_Boss.h"

Enemy_State * Enemy_Attacked_2_Boss::input_state(Enemy_Basic * _Enemy, bool reverse, int targetX, int targetY)
{
	return nullptr;
}

void Enemy_Attacked_2_Boss::update(Enemy_Basic * _Enemy, int targetX, int targetY)
{
	ImageUpdateFunc(_Enemy);
}

void Enemy_Attacked_2_Boss::release(Enemy_Basic * _Enemy)
{
}

void Enemy_Attacked_2_Boss::enter_this_state(Enemy_Basic * _Enemy)
{
	_Enemy->set_Enum_State_Boss(DAMAGED_2_BOSS);

	char str[128] = "Misuzu_Attacked_2";

	_Enemy->setEnemyImage(IMAGEMANAGER->findImage(str));

	frameCount = 0;
	frameUpdateCount = 15;

	_Enemy->setEnemyFrameX(0);

	if (_Enemy->getEnemyInfo()->isRight) _Enemy->setEnemyFrameY(0);
	else _Enemy->setEnemyFrameY(1);
}

void Enemy_Attacked_2_Boss::ImageUpdateFunc(Enemy_Basic * _Enemy)
{
	frameCount++;

	if (frameCount % frameUpdateCount == 0)
	{
		if (_Enemy->getEnemyInfo()->isRight)
		{
			_Enemy->setEnemyFrameY(0);
			_Enemy->setEnemyFrameX(_Enemy->getEnemyInfo()->CurrentframeX + 1);

			if (_Enemy->getEnemyInfo()->CurrentframeX > _Enemy->getEnemyInfo()->_image->getMaxFrameX())
			{
				Enemy_State* _ST;
				_ST = new Enemy_Idle_Boss();

				_Enemy->set_Enemy_State(_ST);

			}
		}
		else
		{
			_Enemy->setEnemyFrameY(1);
			_Enemy->setEnemyFrameX(_Enemy->getEnemyInfo()->CurrentframeX + 1);

			if (_Enemy->getEnemyInfo()->CurrentframeX > _Enemy->getEnemyInfo()->_image->getMaxFrameX())
			{
				Enemy_State* _ST;
				_ST = new Enemy_Idle_Boss();

				_Enemy->set_Enemy_State(_ST);

			}
		}
	}
}
