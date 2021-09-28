#include "stdafx.h"
#include "stage_3rdFloor_Corridor.h"

HRESULT stage_3rdFloor_Corridor::init()
{
	
	IMAGEMANAGER->addImage("3rdFloor_BackGround", "img/stage/stage2/3rdFloor.bmp", 4224, 864, true, RGB(255, 0, 255));
	_background1 = IMAGEMANAGER->findImage("3rdFloor_BackGround");
	IMAGEMANAGER->addImage("3rdFloorPixel", "img/stage/stage2/3rdFloorPixel.bmp", 4224, 1112, true, RGB(255, 0, 255));
	_background2 = IMAGEMANAGER->findImage("3rdFloorPixel");
	IMAGEMANAGER->addImage("L3_lockers1", "img/stage/stage2/L3_lockers1.bmp", 558, 291, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("L3_lockers2", "img/stage/stage2/L3_lockers2.bmp", 555, 273, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("L3_pillar1", "img/stage/stage2/L3_pillar1.bmp", 207, 864, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("L3_pillar2", "img/stage/stage2/L3_pillar2.bmp", 198, 543, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("L3_pillar3", "img/stage/stage2/L3_pillar3.bmp", 198, 543, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("L3_pillar4", "img/stage/stage2/L3_pillar4.bmp", 207, 864, true, RGB(255, 0, 255), true);
	_background3 = IMAGEMANAGER->findImage("BackGround3");

	DATAMANAGER->setBgmKey("River City Girls OST - 5 - Knock Out");
	DATAMANAGER->setStageKey("3rdFloorPixel");
	// �÷��̾� ���� �� �ʱ�ȭ
	stage::init();

	// ����Ʈ �ʱ�ȭ
	
	_door1 = RectMakeCenter(1400, 600, 260, 40);
	_door1Alpha = 0;
	_door2 = RectMakeCenter(2623, 600, 260, 40);
	_door2Alpha = 0;
	cameraWork();
	_em->setting_Unit_school_girl(500, 926);
	_em->setting_Unit_school_boy(500, 850);
	_em->setting_Unit_school_girl(2500, 850);
	_em->setting_Unit_school_boy(2500, 926);


	return S_OK;
}

void stage_3rdFloor_Corridor::release()
{
}

void stage_3rdFloor_Corridor::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_F7)) 
	{
		RENDERMANAGER->setCameraX(0);
		RENDERMANAGER->setCameraY(0);
		SCENEMANAGER->changeScene("�׽�Ʈ��");
	}
	
	
	KEYANIMANAGER->update();
	// ī�޶� ó��
	cameraWork();
	stage::update();
	doorWork();
}

void stage_3rdFloor_Corridor::render()
{
	//���͹ڽ��� ũ��� ���Ʒ� ���� 114;
	RENDERMANAGER->push_BackRenderInfo(-1000, "3rdFloor_BackGround", 0, 114, true);
	_player->render();
	// �ȼ�
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		RENDERMANAGER->push_BackRenderInfo(-999, "3rdFloorPixel", 0, 0, true);
		_background2->render(getMemDC(), 0, 0);
	}
	// ��Ŀ
	RENDERMANAGER->push_BackRenderInfo(380, "L3_lockers1", 3345, 380, true);
	RENDERMANAGER->push_BackRenderInfo(390 + 273, "L3_lockers2", 1920, 390, true);
	// ���
	RENDERMANAGER->push_BackRenderInfo(3000, "L3_pillar1", 492, 114, true, true, 155);
	RENDERMANAGER->push_BackRenderInfo(3000, "L3_pillar4", 3141, 114, true, true, 155);
	RENDERMANAGER->push_BackRenderInfo(-10, "L3_pillar3", 830, 114, true);
	RENDERMANAGER->push_BackRenderInfo(-10, "L3_pillar2", 2770, 114, true);
	// �� ui
	RENDERMANAGER->push_BackRenderInfo(3000, "UI_UNLOCKED_DOOR", 1400, 450, false, true, _door1Alpha);
	RENDERMANAGER->push_BackRenderInfo(3000, "UI_UNLOCKED_DOOR", 2623, 450, false, true, _door2Alpha);

	// ���� �Ŵ���
	RENDERMANAGER->render(getMemDC());
	// ���� �ڽ�
	_background3->render(getMemDC());
	

	// ĳ���� ��Ʈ
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		RECT rc = RectMake(_door1.left + RENDERMANAGER->getCameraX(), _door1.top + RENDERMANAGER->getCameraY(),
			_door1.right - _door1.left, _door1.bottom - _door1.top);
		Rectangle(getMemDC(), rc);
		rc = RectMake(_door2.left + RENDERMANAGER->getCameraX(), _door2.top + RENDERMANAGER->getCameraY(),
			_door2.right - _door2.left, _door2.bottom - _door2.top);
		Rectangle(getMemDC(), rc);
		rc = RectMake(_tagPlayer->rc.left + RENDERMANAGER->getCameraX(), _tagPlayer->rc.top + RENDERMANAGER->getCameraY(), _tagPlayer->rc.right - _tagPlayer->rc.left, _tagPlayer->rc.bottom - _tagPlayer->rc.top);
		Rectangle(getMemDC(), rc);
	}
	stage::render();
}

void stage_3rdFloor_Corridor::cameraWork()
{
	if (_tagPlayer->x > WINSIZEX / 2)
	{
		RENDERMANAGER->setCameraX(-(_tagPlayer->x - WINSIZEX / 2));
	}
	if (RENDERMANAGER->getCameraX() < -_background1->getWidth() + WINSIZEX)
	{
		RENDERMANAGER->setCameraX(-_background1->getWidth() + WINSIZEX);
	}
	if (_tagPlayer->y - 200 - _tagPlayer->z < _background1->getHeight() - WINSIZEY / 2 + 114)
	{
		RENDERMANAGER->setCameraY(-(_tagPlayer->y - WINSIZEY / 2 + 114 - 200 - _tagPlayer->z));
	}

	if (_tagPlayer->y - _tagPlayer->z < WINSIZEY / 2 - 114 + 200)
	{
		RENDERMANAGER->setCameraY(0);
	}
}

void stage_3rdFloor_Corridor::doorWork()
{
	if (IntersectRect(&_temp, &_tagPlayer->rc, &_door1))
	{
		if (_door1Alpha < 200)
			_door1Alpha += 5;
		if (KEYMANAGER->isOnceKeyDown('Y'))
		{
			DATAMANAGER->setPlayerData(1300, 620, 0, DATAMANAGER->getPlayerData().hp);
			DATAMANAGER->setCamera(0, 0);
			_fade = false;
			_targetStageKey = "2��ȦA";
		}
	}
	else if (_door1Alpha > 0)
	{
		_door1Alpha -= 5;
	}

	if (IntersectRect(&_temp, &_tagPlayer->rc, &_door2))
	{
		if (_door2Alpha < 200)
			_door2Alpha += 5;
		if (KEYMANAGER->isOnceKeyDown('Y'))
		{
			DATAMANAGER->setPlayerData(1435, 510, 0, DATAMANAGER->getPlayerData().hp);
			DATAMANAGER->setCamera(0, 0);
			_fade = false;
			_targetStageKey = "�ݼ���";
		}
	}
	else if (_door2Alpha > 0)
	{
		_door2Alpha -= 5;
	}
}