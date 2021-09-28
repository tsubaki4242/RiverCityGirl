#include "stdafx.h"
#include "hitState.h"
#include "hitAndDownState.h"
#include "player.h"

HRESULT player::init()
{
	IMAGEMANAGER->addFrameImage("ĳ���ͱ⺻", "img/player/KyokoIdle.bmp", 1404, 414, 12, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("ĳ���͹���", "img/player/KyokoMove.bmp", 1476, 402, 12, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("���ڹ�����", "img/player/KyokoKick.bmp", 6402, 432, 22, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("ĳ���ʹ޸���", "img/player/KyokoRun.bmp", 2736, 384, 16, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("ĳ�����޺�1", "img/player/KyokoCombo1.bmp", 1062, 390, 6, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("ĳ�����޺�2", "img/player/KyokoCombo2.bmp", 1470, 402, 7, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("ĳ�����޺�3", "img/player/KyokoCombo3.bmp", 2952, 414, 12, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("ĳ���Ͱ�����", "img/player/KyokoStrongAttack.bmp", 2508, 414, 11, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("ĳ��������", "img/player/KyokoJump.bmp", 405, 420, 3, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("ĳ������������", "img/player/KyokoJumpAttack.bmp", 1500, 432, 10, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("ĳ��������������", "img/player/KyokoJumpStrongAttack.bmp", 1551, 522, 11, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("ĳ���ʹ�ð���", "img/player/KyokoDashAttack.bmp", 1728, 378, 8, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("ĳ�����ǰ��ı��", "img/player/KyokoHitandStand.bmp", 6732, 372, 33, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("ĳ�����ǰ�", "img/player/KyokoHitCombo.bmp", 2268, 396, 12, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("ĳ���͸ָ����ư�", "img/player/KyokoFarhit.bmp", 4896, 366, 24, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addFrameImage("ĳ���ͻ��", "img/player/KyokoDie.bmp", 7020, 282, 26, 2, true, RGB(255, 0, 255), true);

	_player.state = new idleState;
	_player.state->enter(this);
	_player.frameY = 0;

	_player.x = WINSIZEX / 2;
	_player.y = WINSIZEY / 2 + 200;
	_player.z = 0.f;
	_player.frameX = 0;
	_player.gravity = 0.7f;
	_player.jumpPower = 0.f;
	_player.time = 0;
	_player.speed = 0.0f;
	_player.moveCommandInput = 0;
	_player.attackCommandInput = 0;
	_player.comboCount = 0;
	_player.collsionRcWidth = 70;
	_player.collsionRcHeight = 40;
	_player.imageErrorX = 0.f;
	_player.imageErrorY = 0.f;
	_player.isHit = false;
	_player.isRide = false;
	_player.isAttack = false;
	_player.isDead = false;
	_player.isAttackHitted = false;
	_player.hp = 100;
	_player.hitRecovery = 100;
	_player.shadowZ = 0.f;
	_player.rc = RectMakeCenter(_player.x,
		_player.y - 105,
		_player.collsionRcWidth,
		_player.collsionRcHeight);
	return S_OK;
}

void player::release()
{

}

void player::update()
{
	inputHandle();
	if (_player.hp <= 0)
	{
		if (!_player.isDead)
		{
			_player.isDead = true;
			changeState(new hitAndDownState);
		}
	}
	else if (_player.isHit && _player.stateEnum != STATE_HIT && _player.stateEnum != STATE_DOWN)
	{
		if (_player.stateEnum == STATE_JUMP)
		{
			_player.isHit = false;
			changeState(new hitAndDownState);
		}
		else
		{
			_player.isHit = false;
			changeState(new hitState);
		}

	}

	_player.state->update(this);

	//Ÿ���� ��� �ö󰡰� Ŀ�ǵ� �Է½ð��� ����
	_player.time++;
	if (_player.moveCommandInput > 0)
		_player.moveCommandInput--;
	if (_player.attackCommandInput > 0)
		_player.attackCommandInput--;

	//�ϴ� ���� �ݸ��� ��Ʈ


	_player.rc = RectMakeCenter(
		_player.x,
		_player.y - _player.collsionRcHeight * 0.5,
		_player.collsionRcWidth,
		_player.collsionRcHeight);

	if (_player.time == 120)
		_player.time = 1;

}

void player::render()
{
	switch (_player.frameY)
	{
	case 0:
		RENDERMANAGER->push_BackFrameImageRenderInfo(_player.rc.bottom + _player.z, _player.image,
			_player.x - _player.image->getFrameWidth() * 0.5 + _player.imageErrorX,
			_player.y - _player.image->getFrameHeight() - _player.z + _player.imageErrorY,
			_player.frameX,
			_player.frameY, true);
		break;
	case 1:
		RENDERMANAGER->push_BackFrameImageRenderInfo(_player.rc.bottom + _player.z, _player.image,
			_player.x - _player.image->getFrameWidth() * 0.5 - _player.imageErrorX,
			_player.y - _player.image->getFrameHeight() - _player.z + _player.imageErrorY,
			_player.frameX,
			_player.frameY, true);
		break;
	}
	RENDERMANAGER->push_BackRenderInfo(_player.rc.bottom + _player.shadowZ, "�׸���",
		_player.x, _player.y - _player.shadowZ, false, true, 120);
}



void player::changeState(state * state)
{
	SAFE_DELETE(_player.state);
	_player.state = state;
	_player.state->enter(this);
}

void player::setAttackRc(float width, float height)
{
	switch (_player.frameY)
	{
	case 0:
		_player.attackRect = RectMake(_player.rc.right - width * 0.3, (_player.rc.top + _player.rc.bottom)*0.5 - height * 0.5, width, height);
		break;
	case 1:
		_player.attackRect = RectMake(_player.rc.left - width * 0.7, (_player.rc.top + _player.rc.bottom)*0.5 - height * 0.5, width, height);
		break;
	default:
		break;
	}
}

void player::setAttackRcCenter(float width, float height)
{
	_player.attackRect = RectMakeCenter(_player.x, _player.y, width, height);
}

//������Ʈ���� ���°� �ٲ���� üũ
void player::inputHandle()
{
	state* tmpstate = _player.state->inputHandle(this);
	if (tmpstate != nullptr)
	{
		SAFE_DELETE(_player.state);
		_player.state = tmpstate;
		_player.state->enter(this);
	}
}
