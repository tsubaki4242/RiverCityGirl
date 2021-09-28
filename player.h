#pragma once
#include "gameNode.h"
#include "idleState.h"

#define DASHSPEED 10.0f
#define WALKSPEED 5.0f
#define PLAYERDATA player->getPlayerData()


enum playerStateEnum
{
	STATE_IDLE,
	STATE_WALK,
	STATE_RUN,
	STATE_DASHATTACK,
	STATE_JUMP,
	STATE_JUMPATTACK,
	STATE_JUMPSTRONGATTACK,
	STATE_COMBO,
	STATE_STRONGATTACK,
	STATE_SKILL,
	STATE_HIT,
	STATE_DOWN,
	STATE_DEAD
};

struct tagPlayer
{
	image* image;				//ĳ�� �̹���
	state* state;				//����
	playerStateEnum	stateEnum;	//���¸� �ܺο��� �� �� �ֵ��� �̳�����
	RECT rc;			//�浹�� ��Ʈ
	RECT attackRect;			//���ݿ� ��Ʈ
	float x, y, z;				//��ǥ
	float hp;					//����
	float gravity;				//���� �� �߷°�
	float jumpPower;			//������
	int time;					//������ �� ��������
	int frameX;					//������X
	int frameY;					//������Y
	float speed;				//���ǵ�
	int moveCommandInput;		//��ð����� �Ҷ� n�ʾȿ� �Է��ؾ� ������
	int attackCommandInput;		//�޺������� �Ҷ� n�ʾȿ� �Է��ؾ� ������
	int comboCount;				//���Ŀ�ǵ� �����
	float collsionRcWidth;		//�̹������� ��Ʈ ũ�� �ٸ��� �Ϸ��� �ϴ� ������
	float collsionRcHeight;		//�̹������� ��Ʈ ũ�� �ٸ��� �Ϸ��� �ϴ� ������
	float imageErrorX;			//�̹��� ������ �� ������X
	float imageErrorY;			//�̹��� ������ �� ������Y
	bool isHit;					//�¾Ҵ°�
	bool isAttack;				//������ �ߴ°�
	bool isAttackHitted;		//���� ������ �¾Ҵ°�
	bool isRide;				//������Ʈ ���� �ִ°�(�ȼ��浹 ����)
	bool isDead;				//�÷��̾ �׾��°�
	int hitRecovery;			//������(�ǰݽ� �پ��)
	float shadowZ;				
};
class player : public gameNode
{
private:
	tagPlayer _player;

public:
	HRESULT init();
	void release();
	void update();
	void render();
	void setX(float x) { _player.x = x; }
	void setY(float y) { _player.y = y; }
	void setZ(float z) { _player.z = z; }
	void setImage(image * image) { _player.image = image; }
	void setFrameX(int x) { _player.frameX = x; }
	void setFrameY(int y) { _player.frameY = y; }
	void setJumpPower(float power) { _player.jumpPower = power; }
	void setTime(int time) { _player.time = time; }
	void setSpeed(float speed) { _player.speed = speed; }
	void setMoveCommandInput(int input) { _player.moveCommandInput = input; }
	void setAttackCommandInput(int input) { _player.attackCommandInput = input; }
	void setComboCount(int input) { _player.comboCount = input; }
	void changeState(state * state);
	void setAttackRc(float width, float height);
	void setAttackRcCenter(float width, float height);
	tagPlayer getPlayer() { return _player; }			//���� �� ��
	tagPlayer* getPlayerData() { return &_player; }		//���;��� ������ ��
	void inputHandle();
};

