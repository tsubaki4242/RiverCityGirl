#include "stdafx.h"
#include "Enemy_Basic.h"
#include "Enemy_Idle.h"
#include "Enemy_Move.h"
#include "Enemy_Attack.h"
#include "Enemy_Die.h"

#include "Enemy_Idle_Boss.h"

void Enemy_Basic::input_state_data(int targetX, int targetY)
{
	Enemy_State* _newState = _state->input_state(this, _EnemyInfo.isRight, targetX, targetY); //���� �־��� state Ŭ���� �ӽú���



	if (_newState != nullptr)//���� ���� �����Ͱ� ������ ���� �����͸� ���� ��, nullptr�� �������
	{
		SAFE_DELETE(_state);
		_state = _newState;
		_state->enter_this_state(this);
	}
}

HRESULT Enemy_Basic::init(int _x, int _y, const char * _imageName, int _Hp, EnemyKind _kind)
{
	_EnemyInfo.x = _x;
	_EnemyInfo.y = _y;
	_EnemyInfo.z = 0.0f;

	_EnemyInfo.imageName = _imageName;
	_EnemyInfo.imageName_RenderManager = _EnemyInfo.imageName;

	Kind = _kind;

	if (Kind != BOSS) _state = new Enemy_Idle();
	else  _state = new Enemy_Idle_Boss();
	_state->enter_this_state(this);

	_EnemyInfo.rc= RectMakeCenter(_EnemyInfo.x, _EnemyInfo.y, 100, 30);
	_EnemyInfo.gravity = 0;
	_EnemyInfo.JumpPower = 0;
	_EnemyInfo.range = 9999;

	_EnemyInfo.Hp = _EnemyInfo.maxHp = _Hp;
	_EnemyInfo.isRight = true;

	_EnemyInfo.CurrentframeX = _EnemyInfo.CurrentframeY = 0;



	_AI = OBSERVE_STATE_TRIGGER;

	triggerCount = 0;//�ش� Ʈ���� ������Ʈ������ ī����

	//���������� �����ϰ� triggercount���� �������� 0�� �� ��� Ʈ���Ÿ� �ٲ��ֱ�.
	if (Kind == BOSS) updateTriggerCount = 3;
	else updateTriggerCount = RND->getFromIntTo(200, 300);



	//������
	_AI_BOSS = NORMAL_ATTACK_TRIGGER_BOSS;
	currentPhase = PHASE_3;
	_EnemyInfo.Special_Attack_Count = 2;
	_EnemyInfo.DashAttack_Limit_Count = 100;

	EnemyImageError = 0;


	//������
	testText = "NON";

	AttackRect.AttackRect = _EnemyInfo.rc;
	AttackRect.isAttackCollision = false;

	recoveryCount = 0;

	return S_OK;
}

void Enemy_Basic::update(int targetX, int targetY)
{

	input_state_data(targetX, targetY);

	_state->update(this, targetX, targetY);

	//	_EnemyInfo._rc = RectMakeCenter(_EnemyInfo.x, _EnemyInfo.y, _EnemyInfo._image->getFrameWidth(), _EnemyInfo._image->getFrameHeight());
	//_EnemyInfo.rc = RectMakeCenter(_EnemyInfo.x + RENDERMANAGER->getCameraX(), _EnemyInfo.y + RENDERMANAGER->getCameraY(),
	//	100, 30);
	_EnemyInfo.rc = RectMakeCenter(_EnemyInfo.x, _EnemyInfo.y ,
		100, 30);


	//- _EnemyInfo.JumpPower + _EnemyInfo.gravity

	switch (Kind)
	{
	case BOSS:

		if (_AI_BOSS == OBSERVE_STATE_TRIGGER_BOSS)
		{
			triggerCount++;

			if (triggerCount % updateTriggerCount == 0)
			{
				int randomPattern;


				//����� ���� ���� ���� 
				switch (currentPhase)
				{
				case PHASE_1:
					randomPattern = RND->getFromIntTo(1, 3);
					break;
				case PHASE_2:
					//�����Ÿ� �̻��̸� ���Ÿ����ϵ� ���, �ƴϸ� �������ϵ� ���.
					if (getDistance(_EnemyInfo.x, _EnemyInfo.y, targetX, targetY) > 900) randomPattern = RND->getFromIntTo(4, 6);
					else randomPattern = RND->getFromIntTo(1, 6);

					break;
				case PHASE_3:

					if (getDistance(_EnemyInfo.x, _EnemyInfo.y, targetX, targetY) > 900) randomPattern = RND->getFromIntTo(4, 7);
					else randomPattern = RND->getFromIntTo(1, 7);

					break;
				}

				//randomPattern = 5;

				//���� ���� ����
				switch (randomPattern)
				{
				case 1:
					_AI_BOSS = NORMAL_ATTACK_TRIGGER_BOSS;
					break;
				case 2:
					_AI_BOSS = POWER_ATTACK_TRIGGER_BOSS;
					break;
				case 3:
					_AI_BOSS = POWER_ATTACK_2_TRIGGER_BOSS;
					break;
				case 4:
					_EnemyInfo.Special_Attack_Count = 2;
					_AI_BOSS = METEOR_JUMP_TRIGGER_BOSS;
					break;
				case 5:
					_EnemyInfo.Special_Attack_Count = 2;
					_AI_BOSS = TAKKLE_TRIGGER_BOSS;

					break;
				}
			}
		}


		break;
	default:

		//Ž�� ���� Ʈ�����ϰ��, �����ð����� Ž�� �� ������ ������Ʈ�� �ٲ���
		if (_AI == OBSERVE_STATE_TRIGGER)
		{
			triggerCount++;

			if (triggerCount % updateTriggerCount == 0)
			{
				int RandomPattern = RND->getFromIntTo(2, 5);
				//int RandomPattern = 4;
				switch (RandomPattern)
				{
				case 2:		//�Ϲݰ���
					_AI = NORMAL_ATTACK_TRIGGER;
					break;
				case 3:		//�뽬����
					_AI = DASH_ATTACK_TRIGGER;
					break;
				case 4:		//��������
					_AI = JUMP_ATTACK_TRIGGER;
					break;
				}
				//_AI.TriggerName = (EnemyTrigger)RandomPattern;
			}
		}



		break;
	}


	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		_EnemyInfo.Hp = _EnemyInfo.Hp*0.5f;
	}

	

}


void Enemy_Basic::release()
{
}

void Enemy_Basic::render()
{

         	RENDERMANAGER->push_BackFrameImageRenderInfo(_EnemyInfo.rc.bottom,
		_EnemyInfo._image,
		_EnemyInfo.x + EnemyImageError, _EnemyInfo.y + EnemyImageError_Y - _EnemyInfo._image->getFrameHeight() / 2 + _EnemyInfo.z,
		_EnemyInfo.CurrentframeX, _EnemyInfo.CurrentframeY);
			
			if (Kind != SCHOOL_BOY)
			{
				RENDERMANAGER->push_BackRenderInfo(_EnemyInfo.rc.bottom - 1, "�׸���", _EnemyInfo.x - 60, _EnemyInfo.y - 22, true, true, 155);
			}
			else
			{
				if(_EnemyInfo.isRight) RENDERMANAGER->push_BackRenderInfo(_EnemyInfo.rc.bottom - 1, "�׸���", _EnemyInfo.x - 60 -15, _EnemyInfo.y - 22, true);
				else RENDERMANAGER->push_BackRenderInfo(_EnemyInfo.rc.bottom - 1, "�׸���", _EnemyInfo.x - 60+15, _EnemyInfo.y - 22, true);
			}



	char str[128];


}


void Enemy_Basic::set_Enemy_State(Enemy_State * _new_State)
{
	_state = _new_State;

	_state->enter_this_state(this);


}

