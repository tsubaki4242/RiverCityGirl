#include "stdafx.h"
#include "Enemy_Basic.h"


#include "Enemy_Knock_Down_1_Boss.h"
#include "Enemy_Knock_Down_2_Boss.h"

Enemy_State * Enemy_Knock_Down_1_Boss::input_state(Enemy_Basic * _Enemy, bool reverse, int targetX, int targetY)
{
	return nullptr;
}

void Enemy_Knock_Down_1_Boss::update(Enemy_Basic * _Enemy, int targetX, int targetY)
{
	ImageUpdateFunc(_Enemy);

	count++;


	if (_Enemy->getEnemyInfo()->CurrentframeX < 3)
	{
		if (_Enemy->getEnemyInfo()->isRight) _Enemy->setEnemyPointX(_Enemy->getEnemyInfo()->x - 3);
		else _Enemy->setEnemyPointX(_Enemy->getEnemyInfo()->x + 3);

		_Enemy->setEnemyPointZ(_Enemy->getEnemyInfo()->z - 3);
	}
	if (count < 10)
	{
		_Enemy->setEnemyPointZ(_Enemy->getEnemyInfo()->z - 11);

	}
	else
	{
		if (_Enemy->getEnemyInfo()->z < 0)
		{
			_Enemy->setEnemyPointZ(_Enemy->getEnemyInfo()->z + 6);
		}
		else
		{
			_Enemy->setEnemyPointZ(0);
		}
	}

}

void Enemy_Knock_Down_1_Boss::release(Enemy_Basic * _Enemy)
{
}

void Enemy_Knock_Down_1_Boss::enter_this_state(Enemy_Basic * _Enemy)
{

	_Enemy->set_Enum_State_Boss(KNOCK_DOWN_1_BOSS);

	char str[128] = "Misuzu_KnockDown_1";

	_Enemy->setEnemyImage(IMAGEMANAGER->findImage(str));

	frameCount = 0;
	frameUpdateCount = 3;

	count = 0;
	_Enemy->setEnemyFrameX(0);

	if (_Enemy->getEnemyInfo()->isRight) _Enemy->setEnemyFrameY(0);
	else _Enemy->setEnemyFrameY(1);
}

void Enemy_Knock_Down_1_Boss::ImageUpdateFunc(Enemy_Basic * _Enemy)
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
				_ST = new Enemy_Knock_Down_2_Boss();

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
				_ST = new Enemy_Knock_Down_2_Boss();

				_Enemy->set_Enemy_State(_ST);

			}
		}
	}
}
