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
	OBSERVE_STATE_TRIGGER, //관찰하는 행동. 다음 공격 스테이트 입장 전까지 해당 스테이트로 만들어줌.
	CANT_JESTURE, //다운, 피격 등에 의해 행동 못받을 경우
	NORMAL_ATTACK_TRIGGER, //기본공격을 행하게 하는 트리거
	DASH_ATTACK_TRIGGER,	//대쉬공격을 하기 위한 트리거 
	JUMP_ATTACK_TRIGGER		//점프공격을 하기 위한 트리거.
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
//열거형으로 switch문 써서 상태전환 하기 위해서 만들어줌.
//사용처 : EnemyManager에서 에너미 피격 당할때마다 피격 state 바꿔주기

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
	RECT imageRect;	//충돌판정용 몸
	float x, y;	//rc의 중점
	float z; //z축. 나중에 공격 피격 타격 관련으로 쓸 변수. 


	image* _image; //이미지 클래스 변수
	const char* imageName; //해당 IMAGEMANAGER에서 해당 이미지를 찾기 위한 key값
	const char* imageName_RenderManager;//렌더매니저에서 이미지 키값을 넣어주기 위한 변수 
	int CurrentframeX, CurrentframeY;

	bool isRight;		//오른쪽인지 판단여부

	int range; //에너미의 판단범위. 일단 임시로 설정해놓음 
	int AttackRange = 70;//공격 사거리. 임시로 설정.

	int Hp;//체력
	int maxHp;

	int stiffness; //경직도 관련 변수 

	RECT rc;
	POINT EnemyShedowMiddle;

	float JumpPower;
	float gravity;

	//=========================================
	//보스용
	//=========================================

	int Special_Attack_Count; //어깨빵or내려찍기 반복해줄 횟수
	int DashAttack_Limit_Count; //해당 시간동안 플레이어랑 충돌 하지 않을시, 취소하기


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

	int triggerCount;//해당 트리거 업데이트까지의 카운터
	int updateTriggerCount;//랜덤값으로 설정하고 triggercount와의 나머지가 0이 될 경우 트리거를 바꿔주기.

	EnemyKind Kind;

	int EnemyImageError;//이미지 위치 오류나는거 보정용 
	int EnemyImageError_Y;

	tagAttackRect AttackRect;

	int recoveryCount;

public:

	//==========================================================================

	//void input_state_data(Enemy_State* getNewstate);//스테이트 상태를 갱신해줄 함수
	void input_state_data(int targetX, int targetY);//스테이트 상태를 갱신해줄 함수


	virtual HRESULT init(int _x, int _y, const char* _imageName, int _Hp, EnemyKind _kind); //init
	virtual void update(int targetX, int targetY);	//아직 플레이어 x,y값은 안넣엇고, 이미지 판단 
	virtual void release();
	virtual void render();

	//==========================================================================

	/*
	state에서 해당하는 값을 가져오고
	EnemyBasic에 지정시켜주려고함.
	*/

	//==========================================================================

	//에너미 구조체 정보 가져오기(getter)
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

	//에너미 정보 수정용(setter)
	void setEnemyImage(image* _image) { _EnemyInfo._image = _image; }//이미지 수정
	void setEnemyImageError(int num) { EnemyImageError = num; }
	void setEnemyImageError_Y(int num) { EnemyImageError_Y = num; }

	void setEnemyPointX(float _x) { _EnemyInfo.x = _x; }
	void setEnemyPointY(float _y) { _EnemyInfo.y = _y; }
	void setEnemyPointZ(float _z) { _EnemyInfo.z = _z; }


	void setEnemyFrameX(int frameX) { _EnemyInfo.CurrentframeX = frameX; }
	void setEnemyFrameY(int frameY) { _EnemyInfo.CurrentframeY = frameY; }


	void setEnemyTestText(const char* _TT) { testText = _TT; }

	void set_Enemy_State(Enemy_State* _new_State);//에너미 스테이트 변경용.공격당하거나 죽었을때 쓸듯?
	void set_Enemy_State_Enum(Enemy_State_enum _new_Enum_state) { _enum_state = _new_Enum_state; }

	void set_Enum_State_Boss(Enemy_State_Boss_Enum _new) { _boss_state = _new; }

	void set_Enemy_Hp(int _Hp) { _EnemyInfo.Hp -= _Hp; }//기본적으로 - 설정.

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

	//공격렉트 RectMake
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

	//공격렉트 RectMakeCenter
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

