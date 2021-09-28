#pragma once
#include "stdafx.h"
#include "gameNode.h"
#include "Enemy_State.h"


#define MOVESPEED_RUN  10.0f
#define MOVESPEED_LEFT_RIGHT 5.0f
#define MOVESPEED_UP_DOWN 2.0f


#define BOSS_SPEED 3.0f
#define BOSS_JUMP_SPEED 25.0f
#define BOSS_GRAVITY 0.2f



#define GRAVITY_POWER 0.7f
#define JUMP_POWER 17.0f




enum EnemyKind
{
	SCHOOL_GIRL,
	SCHOOL_BOY,
	CHEER_LEADER,
	BOSS
};


enum EnemyTrigger
{
	OBSERVE_STATE_TRIGGER, //�����ϴ� �ൿ. ���� ���� ������Ʈ ���� ������ �ش� ������Ʈ�� �������.
	CANT_JESTURE, //�ٿ�, �ǰ� � ���� �ൿ ������ ���
	NORMAL_ATTACK_TRIGGER, //�⺻������ ���ϰ� �ϴ� Ʈ����
	DASH_ATTACK_TRIGGER,	//�뽬������ �ϱ� ���� Ʈ���� 
	JUMP_ATTACK_TRIGGER		//���������� �ϱ� ���� Ʈ����.
};


enum EnemyTrigger_Boss
{
	OBSERVE_STATE_TRIGGER_BOSS,
	NORMAL_ATTACK_TRIGGER_BOSS,
	POWER_ATTACK_TRIGGER_BOSS,
	POWER_ATTACK_2_TRIGGER_BOSS,
	TAKKLE_TRIGGER_BOSS,
	METEOR_JUMP_TRIGGER_BOSS,
};

enum Boss_Phase
{
	PHASE_1,
	PHASE_2,
	PHASE_3
};

enum Enemy_State_enum
{
	IDLE,
	WALK,
	MOVE,
	RUN,
	DASH_ATTACK,
	ATTACK_1,
	//ATTACK_2,
	//ATTACK_3,
	DAMAGED_1,
	DAMAGED_2,
	DAMAGED_3,
	KNOCK_DOWN,
	KNOCK_DOWN_2,
	WAKE_UP,
	DIE
};
//���������� switch�� �Ἥ ������ȯ �ϱ� ���ؼ� �������.
//���ó : EnemyManager���� ���ʹ� �ǰ� ���Ҷ����� �ǰ� state �ٲ��ֱ�

enum Enemy_State_Boss_Enum
{
	IDLE_BOSS,
	MOVE_BOSS,
	DASH_ATTACK_BOSS,
	ATTACK_1_BOSS,
	ATTACK_3_BOSS,
	POWER_ATTACK_BOSS,
	DAMAGED_1_BOSS,
	DAMAGED_2_BOSS,
	DAMAGED_3_BOSS,
	KNOCK_DOWN_1_BOSS,
	KNOCK_DOWN_2_BOSS,
	WAKE_UP_BOSS,
	DIE_BOSS
};

struct tagEnemyInfo
{
	RECT imageRect;	//�浹������ ��
	float x, y;	//rc�� ����
	float z; //z��. ���߿� ���� �ǰ� Ÿ�� �������� �� ����. 


	image* _image; //�̹��� Ŭ���� ����
	const char* imageName; //�ش� IMAGEMANAGER���� �ش� �̹����� ã�� ���� key��
	const char* imageName_RenderManager;//�����Ŵ������� �̹��� Ű���� �־��ֱ� ���� ���� 
	int CurrentframeX, CurrentframeY;

	bool isRight;		//���������� �Ǵܿ���

	int range; //���ʹ��� �Ǵܹ���. �ϴ� �ӽ÷� �����س��� 
	int AttackRange = 70;//���� ��Ÿ�. �ӽ÷� ����.

	int Hp;//ü��
	int maxHp;

	int stiffness; //������ ���� ���� 

	RECT rc;
	POINT EnemyShedowMiddle;

	float JumpPower;
	float gravity;

	//=========================================
	//������
	//=========================================

	int Special_Attack_Count; //�����or������� �ݺ����� Ƚ��
	int DashAttack_Limit_Count; //�ش� �ð����� �÷��̾�� �浹 ���� ������, ����ϱ�


};

struct tagAttackRect
{
	RECT AttackRect;
	bool isAttackCollision;
};


class Enemy_Basic :
	public gameNode
{
protected:

	tagEnemyInfo _EnemyInfo;

	Enemy_State* _state;
	Enemy_State_enum  _enum_state;

	Enemy_State_Boss_Enum _boss_state;

	const char* testText;

	EnemyTrigger _AI;
	EnemyTrigger_Boss _AI_BOSS;
	Boss_Phase currentPhase;

	int triggerCount;//�ش� Ʈ���� ������Ʈ������ ī����
	int updateTriggerCount;//���������� �����ϰ� triggercount���� �������� 0�� �� ��� Ʈ���Ÿ� �ٲ��ֱ�.

	EnemyKind Kind;

	int EnemyImageError;//�̹��� ��ġ �������°� ������ 
	int EnemyImageError_Y;

	tagAttackRect AttackRect;

	int recoveryCount;

public:

	//==========================================================================

	//void input_state_data(Enemy_State* getNewstate);//������Ʈ ���¸� �������� �Լ�
	void input_state_data(int targetX, int targetY);//������Ʈ ���¸� �������� �Լ�


	virtual HRESULT init(int _x, int _y, const char* _imageName, int _Hp, EnemyKind _kind); //init
	virtual void update(int targetX, int targetY);	//���� �÷��̾� x,y���� �ȳ־���, �̹��� �Ǵ� 
	virtual void release();
	virtual void render();

	//==========================================================================

	/*
	state���� �ش��ϴ� ���� ��������
	EnemyBasic�� ���������ַ�����.
	*/

	//==========================================================================

	//���ʹ� ����ü ���� ��������(getter)
	tagEnemyInfo* getEnemyInfo() { return &_EnemyInfo; }
	EnemyTrigger getAITRIGGER() { return _AI; }
	Enemy_State* getEnemyStateInfo() { return _state; }
	Enemy_State_enum getEnemyStateEnumInfo() { return _enum_state; }
	Enemy_State_Boss_Enum getBossStateEnumInfo() { return _boss_state; }
	EnemyKind getEnemyKind() { return Kind; }
	EnemyTrigger_Boss getBOSS_AI_TRIGGER() { return _AI_BOSS; }
	Boss_Phase getcurrentPhase() { return currentPhase; }

	tagAttackRect* getAttackRect() { return &AttackRect; }

	int getRecoveryCount() { return recoveryCount; }
	void setRecoveryCount() { recoveryCount++; }
	void setRecoveryCountZero() { recoveryCount = 0; }
	//==========================================================================

	//���ʹ� ���� ������(setter)
	void setEnemyImage(image* _image) { _EnemyInfo._image = _image; }//�̹��� ����
	void setEnemyImageError(int num) { EnemyImageError = num; }
	void setEnemyImageError_Y(int num) { EnemyImageError_Y = num; }

	void setEnemyPointX(float _x) { _EnemyInfo.x = _x; }
	void setEnemyPointY(float _y) { _EnemyInfo.y = _y; }
	void setEnemyPointZ(float _z) { _EnemyInfo.z = _z; }


	void setEnemyFrameX(int frameX) { _EnemyInfo.CurrentframeX = frameX; }
	void setEnemyFrameY(int frameY) { _EnemyInfo.CurrentframeY = frameY; }


	void setEnemyTestText(const char* _TT) { testText = _TT; }

	void set_Enemy_State(Enemy_State* _new_State);//���ʹ� ������Ʈ �����.���ݴ��ϰų� �׾����� ����?
	void set_Enemy_State_Enum(Enemy_State_enum _new_Enum_state) { _enum_state = _new_Enum_state; }

	void set_Enum_State_Boss(Enemy_State_Boss_Enum _new) { _boss_state = _new; }

	void set_Enemy_Hp(int _Hp) { _EnemyInfo.Hp -= _Hp; }//�⺻������ - ����.

	void setEnemyImageKey(const char* this_imageName) { _EnemyInfo.imageName_RenderManager = this_imageName; }


	void setEnemyGravity(float G) { _EnemyInfo.gravity = G; }
	void setEnemyJumpSpeed(float JumpSpeed) { _EnemyInfo.JumpPower = JumpSpeed; }

	void setEnemyReverse(bool isRight_) { _EnemyInfo.isRight = isRight_; }

	void setEnemyAiTrigger(EnemyTrigger new_AI) { _AI = new_AI; }
	void setEnemyAiTrigger_Boss(EnemyTrigger_Boss new_AI) { _AI_BOSS = new_AI; }

	void setEnemyRandomCountReset() { updateTriggerCount = RND->getFromIntTo(200, 300); }
	void setEnemyRandomCountReset_more() { updateTriggerCount = RND->getFromIntTo(150, 220); }

	void setBossSpecialCount() { _EnemyInfo.Special_Attack_Count--; }
	void setBossSpecialCount_Zero() { _EnemyInfo.Special_Attack_Count = -1; }
	void setChangePhase(Boss_Phase nextPhase) { currentPhase = nextPhase; }

	void setAttackRectBool(bool off) { AttackRect.isAttackCollision = off; }

	void setAttackRect_x(int x)
	{
		AttackRect.AttackRect.left += x;
		AttackRect.AttackRect.right += x;
	}
	void setAttackRect_y(int y)
	{
		AttackRect.AttackRect.top += y;
		AttackRect.AttackRect.bottom += y;
	}


	//==========================================================================

	//���ݷ�Ʈ RectMake
	void Setting_AttackRect_LeftRight(EnemyKind Enemy_kind ,int x, int y, int width, int height ,int beforeFrameX, int count,int updateCount)
	{
		if (_boss_state== DASH_ATTACK_BOSS)
		{ 
			AttackRect.AttackRect = RectMakeCenter(x, y, width, height);

			if (!(AttackRect.isAttackCollision) &&
				_EnemyInfo.CurrentframeX == beforeFrameX &&
				count % updateCount == 0)
			{
				AttackRect.isAttackCollision = true;
			}
			if (AttackRect.isAttackCollision &&
				_EnemyInfo.CurrentframeX == beforeFrameX &&
				count % updateCount == 7)
			{
				AttackRect.isAttackCollision = false;
			}
		}
		else
		{
			if (Kind == Enemy_kind)
			{
				//AttackRect.AttackRect = RectMakeCenter(x - RENDERMANAGER->getCameraX(), y - RENDERMANAGER->getCameraY(), width, height);
				AttackRect.AttackRect = RectMakeCenter(x, y, width, height);

				if (!(AttackRect.isAttackCollision) &&
					_EnemyInfo.CurrentframeX == beforeFrameX &&
					count % updateCount == 0)
				{
					AttackRect.isAttackCollision = true;
				}
				if (AttackRect.isAttackCollision &&
					_EnemyInfo.CurrentframeX == beforeFrameX &&
					count % updateCount == 1)
				{
					AttackRect.isAttackCollision = false;
				}
			}
		}
		
	}

	//���ݷ�Ʈ RectMakeCenter
	void Setting_AttackRect_Center(EnemyKind Enemy_kind ,int x, int y, int width, int height, int beforeFrameX, int count, int updateCount)
	{
		if (Kind == Enemy_kind)
		{
			AttackRect.AttackRect = RectMakeCenter(x , y , width, height);

			if (!(AttackRect.isAttackCollision) &&
				_EnemyInfo.CurrentframeX == beforeFrameX &&
				count%updateCount == 0)
			{
				AttackRect.isAttackCollision = true;
			}
			if (AttackRect.isAttackCollision &&
				_EnemyInfo.CurrentframeX == beforeFrameX &&
				count%updateCount == 1)
			{
				AttackRect.isAttackCollision = false;
			}
		}
	}

	//==========================================================================



	//==========================================================================
};

