#include "stdafx.h"
#include "Enemy_Wake_Up.h"


#include "Enemy_Idle.h"
#include "Enemy_Move.h"

#include "Enemy_Basic.h"

Enemy_State * Enemy_Wake_Up::input_state(Enemy_Basic * _Enemy, bool reverse, int targetX, int targetY)
{
	return nullptr;
}

void Enemy_Wake_Up::update(Enemy_Basic * _Enemy, int targetX, int targetY)
{
	ImageUpdateFunc(_Enemy);

	switch (_Enemy->getEnemyKind())
	{
	case SCHOOL_BOY:
		if (_Enemy->getEnemyInfo()->CurrentframeX == _Enemy->getEnemyInfo()->_image->getMaxFrameX())
		{
			_Enemy->setEnemyImageError(-10);
		}

		break;
	default:
		break;
	}
}

void Enemy_Wake_Up::release(Enemy_Basic * _Enemy)
{
}


void Enemy_Wake_Up::enter_this_state(Enemy_Basic * _Enemy)
{
	//Enemy_Image_Wake_up_School_Girl

	_Enemy->setEnemyTestText("KNOCK_DOWN_1");
	_Enemy->set_Enemy_State_Enum(KNOCK_DOWN_2);



	char str[128] = "Enemy_Image_Wake_up_";

	strcat_s(str, _Enemy->getEnemyInfo()->imageName);

	string Idle_Image = str;

	_Enemy->setEnemyImage(IMAGEMANAGER->findImage(Idle_Image));
	_Enemy->setEnemyImageError_Y(10);
	_Enemy->setEnemyImageError(10);
	_Enemy->setEnemyFrameX(0);
	frameCount = 0;
	frameUpdateCount = 8;
}

void Enemy_Wake_Up::ImageUpdateFunc(Enemy_Basic * _Enemy)
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
				Enemy_State* _t;
				_t = new Enemy_Move();

				_Enemy->set_Enemy_State(_t);
			}
		}
		else
		{
			_Enemy->setEnemyFrameY(1);
			_Enemy->setEnemyFrameX(_Enemy->getEnemyInfo()->CurrentframeX + 1);

			if (_Enemy->getEnemyInfo()->CurrentframeX > _Enemy->getEnemyInfo()->_image->getMaxFrameX())
			{
				Enemy_State* _t;
				_t = new Enemy_Move();

				_Enemy->set_Enemy_State(_t);
			}
		}
	}
}
