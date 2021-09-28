#include "stdafx.h"

#include "Enemy_Basic.h"

#include "Enemy_Move.h"
#include "Enemy_Idle.h"
#include "Enemy_Attack.h"
#include "Enemy_Run.h"
#include "Enemy_Jump.h"

Enemy_State * Enemy_Move::input_state(Enemy_Basic * _Enemy, bool reverse, int targetX, int targetY)
{

	switch (_Enemy->getAITRIGGER())
	{
	case NORMAL_ATTACK_TRIGGER: //�Ϲ� �����ϰ��, distance�� �ް� ���ݹ��� ������ �̵� ��Ű��.

		if ((_Enemy->getEnemyInfo()->y >= targetY - 25 && _Enemy->getEnemyInfo()->y <= targetY + 25) &&
			getDistance(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, targetX, targetY) <= NORMAL_ATTACK_RANGE)
		
			return new Enemy_Attack();
		
		break;
	case DASH_ATTACK_TRIGGER:

		if ((_Enemy->getEnemyInfo()->y >= targetY - 30 && _Enemy->getEnemyInfo()->y <= targetY + 30) &&
			(getDistance(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, targetX, targetY) <= DASH_ATTACK_RANGE &&
			getDistance(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, targetX, targetY) >= DASH_ATTACK_RANGE-40))  
			return new Enemy_Run();
		
		break;
	case JUMP_ATTACK_TRIGGER:
		if ((_Enemy->getEnemyInfo()->y >= targetY - 20 && _Enemy->getEnemyInfo()->y <= targetY + 20) &&
			(getDistance(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, targetX, targetY) <= JUMP_ATTACK_RANGE &&
				getDistance(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, targetX, targetY) >= JUMP_ATTACK_RANGE-30)) 
			return new Enemy_Jump();
		
		break;
	}


	return nullptr;
	//�ش� �Ÿ� ����� IDLE�� .
	/*
	�ϴ� �ӽ÷� �����س�����. ���� �����ؾ���.
	*/


}

void Enemy_Move::update(Enemy_Basic* _Enemy, int targetX, int targetY)
{

	float angle = getAngle(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, targetX, targetY);



	//���� �Ÿ��ȿ� ������ �����̰� 
	switch (_Enemy->getAITRIGGER())
	{
	case OBSERVE_STATE_TRIGGER:

		if (!isObserve)
		{
			if (getDistance(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, targetX, targetY) > OBSERVE_RANGE)
			{
				_Enemy->setEnemyPointX(_Enemy->getEnemyInfo()->x + cosf(angle)*MOVESPEED_LEFT_RIGHT);
				_Enemy->setEnemyPointY(_Enemy->getEnemyInfo()->y - sinf(angle)*MOVESPEED_UP_DOWN);
			}
			else isObserve = true;
		}
		else
		{
			ObserveCount++;

			if (ObserveCount%RandomObserveUpdateCount == 0)
			{
				RandomAngle = RND->getFromFloatTo(0, PI2);			  //������ �ޱ۷� �̵��ϰ� ������.
				RandomObserveUpdateCount = RND->getFromIntTo(70, 120); //���� ���� �������� ���� ���ֱ�
			}

			
			_Enemy->setEnemyPointX(_Enemy->getEnemyInfo()->x + cosf(RandomAngle)*MOVESPEED_LEFT_RIGHT*0.7f);
			_Enemy->setEnemyPointY(_Enemy->getEnemyInfo()->y - sinf(RandomAngle)*MOVESPEED_UP_DOWN*0.7f);
		}



		break;
	
	case NORMAL_ATTACK_TRIGGER: //�Ϲ� �����ϰ��, distance�� �ް� ���ݹ��� ������ �̵� ��Ű��.

		//if (getDistance(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, targetX, targetY) > NORMAL_ATTACK_RANGE
		//	&& (_Enemy->getEnemyInfo()->y < targetY - 3|| _Enemy->getEnemyInfo()->y > targetY + 3))
		//{
		//	//float angle = getAngle(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, targetX, targetY);

		//	_Enemy->setEnemyPointX(_Enemy->getEnemyInfo()->x + cosf(angle)*MOVESPEED_LEFT_RIGHT*0.7f);
		//	_Enemy->setEnemyPointY(_Enemy->getEnemyInfo()->y - sinf(angle)*MOVESPEED_UP_DOWN*0.7f);

		//}

		//�÷��̾�� y�� ���̰� ���� ���Ұ��, y�� �������ֱ�	
		if ((_Enemy->getEnemyInfo()->y <= targetY - 25 || _Enemy->getEnemyInfo()->y >= targetY + 25))
		{
			_Enemy->setEnemyPointY(_Enemy->getEnemyInfo()->y - sinf(angle)*MOVESPEED_UP_DOWN);
		}
		//���� �뽬���� ��Ÿ����� �� ��� �����ϰ�
		if (getDistance(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, targetX, targetY) > NORMAL_ATTACK_RANGE)
		{
			_Enemy->setEnemyPointX(_Enemy->getEnemyInfo()->x + cosf(angle)*MOVESPEED_LEFT_RIGHT);
		}
		

		break;

	case DASH_ATTACK_TRIGGER:

		
		//�÷��̾�� y�� ���̰� ���� ���Ұ��, y�� �������ֱ�	
		if ((_Enemy->getEnemyInfo()->y < targetY - 25 || _Enemy->getEnemyInfo()->y > targetY + 25))
		{
			_Enemy->setEnemyPointY(_Enemy->getEnemyInfo()->y - sinf(angle)*MOVESPEED_LEFT_RIGHT*1.5f);
		}
		//���� �뽬���� ��Ÿ����� �� ��� �����ϰ�
		if (getDistance(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, targetX, targetY) > DASH_ATTACK_RANGE)
		{
			_Enemy->setEnemyPointX(_Enemy->getEnemyInfo()->x + cosf(angle)*MOVESPEED_LEFT_RIGHT);
		}
		//���� �뽬���� ��Ÿ����� �� ��� �����ϰ�
		else if (getDistance(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, targetX, targetY) < DASH_ATTACK_RANGE - 40)
		{
			_Enemy->setEnemyPointX(_Enemy->getEnemyInfo()->x - cosf(angle)*MOVESPEED_LEFT_RIGHT);
		}

		break;
	case JUMP_ATTACK_TRIGGER:

		//�÷��̾�� y�� ���̰� ���� ���Ұ��, y�� �������ֱ�	
		if((_Enemy->getEnemyInfo()->y < targetY - 20 || _Enemy->getEnemyInfo()->y > targetY + 20))
		{
			_Enemy->setEnemyPointY(_Enemy->getEnemyInfo()->y - sinf(angle)*MOVESPEED_LEFT_RIGHT);
		}
		//���� �������� ��Ÿ����� �� ��� �����ϰ�
		if (getDistance(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, targetX, targetY) > JUMP_ATTACK_RANGE)
		{
			_Enemy->setEnemyPointX(_Enemy->getEnemyInfo()->x + cosf(angle)*MOVESPEED_LEFT_RIGHT);
		}
		//���� ���� ���� ��Ÿ����� ����� ��� �����ϰ�
		else if (getDistance(_Enemy->getEnemyInfo()->x, _Enemy->getEnemyInfo()->y, targetX, targetY) < JUMP_ATTACK_RANGE - 30)
		{
			_Enemy->setEnemyPointX(_Enemy->getEnemyInfo()->x - cosf(angle)*MOVESPEED_LEFT_RIGHT);
		}

		break;
	}



	

	//������ �̹��� ������ �Լ�
	ImageUpdateFunc(_Enemy);


	if (_Enemy->getEnemyInfo()->x > targetX)
	{
		_Enemy->setEnemyReverse(false);
	}
	else _Enemy->setEnemyReverse(true);

}

void Enemy_Move::release(Enemy_Basic* _Enemy)
{
}

void Enemy_Move::render()
{
}

void Enemy_Move::enter_this_state(Enemy_Basic * _Enemy)
{
	_Enemy->setEnemyTestText("MOVE");
	_Enemy->set_Enemy_State_Enum(MOVE);



	char str[128] = "Enemy_Image_Move_";

	strcat_s(str, _Enemy->getEnemyInfo()->imageName);

	_Enemy->setEnemyImageKey(str);

	string Idle_Image = str;
	_Enemy->setEnemyImage(IMAGEMANAGER->findImage(Idle_Image));

	frameCount = 0;
	frameUpdateCount = 5;
	

	_Enemy->setEnemyFrameX(0);

	if (_Enemy->getEnemyInfo()->isRight) _Enemy->setEnemyFrameY(0);
	else _Enemy->setEnemyFrameY(1);

	isObserve = false; //Ž��������
	ObserveCount = 0;									  //�������� ������Ʈ ī��Ʈ
	RandomAngle = RND->getFromFloatTo(0,PI2);			  //������ �ޱ۷� �̵��ϰ� ������.
	RandomObserveUpdateCount = RND->getFromIntTo(70, 120); //���� ���� �������� ���� ���ֱ�

}

void Enemy_Move::ImageUpdateFunc(Enemy_Basic * _Enemy)
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

