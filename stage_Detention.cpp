#include "stdafx.h"
#include "stage_Detention.h"

HRESULT stage_Detention::init()
{
	// �̹��� �ʱ�ȭ ���߿� ��� �ε����� �ű���
	IMAGEMANAGER->addImage("Detention_Pixel", "img/stage/stage1/Detention_PixelBG2.bmp", 2016, WINSIZEY, true, RGB(255, 0, 255));
	_background = IMAGEMANAGER->findImage("Detention_Pixel");
	IMAGEMANAGER->addImage("BackGround2", "img/stage/stage1/Detention_BG.bmp", 2016, 672, true, RGB(255, 0, 255));
	_background2 = IMAGEMANAGER->findImage("BackGround2");
	_background3 = IMAGEMANAGER->findImage("BackGround3");
	IMAGEMANAGER->addImage("Desk1", "img/stage/stage1/Detention_OBJ_Desks_01.bmp", 189, 171, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Desk2", "img/stage/stage1/Detention_OBJ_Desks_02.bmp", 186, 171, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Desk3", "img/stage/stage1/Detention_OBJ_Desks_03.bmp", 186, 171, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Desk4", "img/stage/stage1/Detention_OBJ_Desks_04.bmp", 186, 171, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Desk5", "img/stage/stage1/Detention_OBJ_Desks_05.bmp", 189, 144, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Desk6", "img/stage/stage1/Detention_OBJ_Desks_06.bmp", 186, 144, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Desk7", "img/stage/stage1/Detention_OBJ_Desks_07.bmp", 186, 144, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Desk8", "img/stage/stage1/Detention_OBJ_Desks_08.bmp", 183, 144, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("TeacherDesk", "img/stage/stage1/Detention_OBJ_TeacherDesk.bmp", 261, 102, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("school_girl_Idle", "img/enemy/school_girl/school_girl_Idle.bmp", 1170, 354, 10, 2, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("Chair1", "img/stage/stage1/Detention_Chair_2.bmp", 129, 120, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Chair2", "img/stage/stage1/Detention_Chair_3.bmp", 153, 132, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SB_sit_idle", "img/stage/stage1/SB_sit_idle.bmp", 732, 180, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("SG_sit_idle", "img/stage/stage1/SG_sit_idle.bmp", 408, 216, 2, 1, true, RGB(255, 0, 255));	
	IMAGEMANAGER->addFrameImage("MrRudis_idle", "img/stage/stage1/MrRudis_idle.bmp", 396, 237, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI_UNLOCKED_DOOR", "img/ui/UI_UNLOCKED_DOOR.bmp", 78, 114, true, RGB(255, 0, 255), true);
	_school_girl = IMAGEMANAGER->findImage("school_girl_Idle");
	doorAlpha = 0;

	// ������Ʈ �ִϸ��̼�
	int boy_sleep[] = { 0, 1, 2, 3 };
	KEYANIMANAGER->addArrayFrameAnimation("SIT_BOY_SLEEP", "SB_sit_idle", boy_sleep, 4, 1, true);
	int girl_sit[] = { 0, 1 };
	KEYANIMANAGER->addArrayFrameAnimation("SIT_GIRL_SIT", "SG_sit_idle", girl_sit, 2, 2, true);
	_sit_boy_ani = KEYANIMANAGER->findAnimation("SIT_BOY_SLEEP");
	KEYANIMANAGER->findAnimation("SIT_GIRL_SIT")->start();
	KEYANIMANAGER->addArrayFrameAnimation("MRRUDIS_IDLE_LEFT", "MrRudis_idle", girl_sit, 2, 14, true);
	int _MrRudis_Right[] = { 2, 3 };
	KEYANIMANAGER->addArrayFrameAnimation("MRRUDIS_IDLE_RIGHT", "MrRudis_idle", _MrRudis_Right, 2, 14, true);
	_MrRudis_idle_ani = KEYANIMANAGER->findAnimation("MRRUDIS_IDLE_RIGHT");

	// �ִϸ��̼��� ��������� ������ �ؾ���?
	_MrRudis_idle_ani->start();
	_sit_boy_ani->start();

	// ����� ��Ʈ����
	_rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, _school_girl->getFrameWidth(), _school_girl->getFrameHeight());

	// door ��Ʈ ����
	_door = RectMakeCenter(1438, 500, 300, 20);
	// �÷��̾� ���� �� �ʱ�ȭ
	DATAMANAGER->setStageKey("Detention_Pixel");
	DATAMANAGER->setBgmKey("River City Girls OST - 4 - Detention");
	stage::init();
	//_em->setting_Unit_school_girl(1375, 650);
	/*_em->setting_Unit_school_girl(1375, 650);
	_em->setting_Unit_school_girl(1375, 650);
	_em->setting_Unit_school_girl(1375, 650);
	_em->setting_Unit_school_girl(1375, 650);*/
	return S_OK;
}


void stage_Detention::release()
{
}

void stage_Detention::update()
{

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		cout << _ptMouse.x << ", " << _ptMouse.y << endl;
		//EFFECTMANAGER->play("����Ʈ1", _ptMouse.x, _ptMouse.y, true, 150);
	}

	


	// ����� ������ ������
	if (_count % 5 == 0)
	{
		if (_school_girl->getFrameX() >= _school_girl->getMaxFrameX()) _school_girl->setFrameX(0);
		_school_girl->setFrameX(_school_girl->getFrameX() + 1);

	}
	_count++;


	// �׽�Ʈ �л� rc
	_rc = RectMake(WINSIZEX / 2, WINSIZEY / 2 + 90, _school_girl->getFrameWidth(), _school_girl->getFrameHeight() - 70);
	EFFECTMANAGER->update();
	cameraWork();
	stage::update();
	doorWork();

	// �̰� �ּ��� �ִϸ��̼��� ������ �ȵǴ� ���� �츮�� Ȯ���� �� ���� �̴ϴ� ^^
	KEYANIMANAGER->update();
}

void stage_Detention::render()
{
	// �׽�Ʈ�� ����� ���̵�
	RENDERMANAGER->push_BackFrameRenderInfo(_rc.bottom, "school_girl_Idle", WINSIZEX / 2, WINSIZEY / 2,
		_school_girl->getFrameX(),
		_school_girl->getFrameY(), true);

	// ����

	RENDERMANAGER->push_BackRenderInfo(-1000, "Chair2", 1570, 520, true);
	RENDERMANAGER->push_BackRenderInfo(-1000, "Chair1", 1760, 650, true);
	// ���ȭ��
	RENDERMANAGER->push_BackRenderInfo(-1000, "BackGround2", 0, (WINSIZEY - _background2->getHeight()) / 2, true);

	// ������ 
	RENDERMANAGER->push_BackAniRenderInfo(450 + 237, "MrRudis_idle", _MrRudis_idle_ani, 1650, 450, true);


	// �ȼ� ���� �ѱ� ó�� 
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		RENDERMANAGER->push_BackRenderInfo(-999, "Detention_Pixel", 0, 0, true);
		_background->render(getMemDC(), 0, 0);
	}

	// �÷��̾� ��ġ�� ���� å�� �׷����� ������ �ٲ���
	if (_tagPlayer->rc.top > 550 && _tagPlayer->rc.left > 1200)
	{
		RENDERMANAGER->push_BackAniRenderInfo(442, "SG_sit_idle", KEYANIMANAGER->findAnimation("SIT_GIRL_SIT"), 1080, 442, true);
		RENDERMANAGER->push_BackRenderInfo(442, "Desk4", 1098, 487, true);
		
	}
	else
	{
		RENDERMANAGER->push_BackAniRenderInfo(442 + 228, "SG_sit_idle", KEYANIMANAGER->findAnimation("SIT_GIRL_SIT"), 1080, 442, true);
		RENDERMANAGER->push_BackRenderInfo(442 + 228, "Desk4", 1098, 487, true);
	}

	if (_tagPlayer->rc.top > 550 && _tagPlayer->rc.left > 940)
		RENDERMANAGER->push_BackRenderInfo(442, "Desk3", 838, 487, true);
	else
	RENDERMANAGER->push_BackRenderInfo(442 + 208, "Desk3", 838, 487, true);

	if (_tagPlayer->rc.top > 550 && _tagPlayer->rc.left > 670)
		RENDERMANAGER->push_BackRenderInfo(442, "Desk2", 572, 487, true);
	else
		RENDERMANAGER->push_BackRenderInfo(442 + 208, "Desk2", 572, 487, true);

	if (_tagPlayer->rc.top > 550 && _tagPlayer->rc.left > 430)
		RENDERMANAGER->push_BackRenderInfo(442, "Desk1", 328, 487, true);
	else
		RENDERMANAGER->push_BackRenderInfo(442 + 208, "Desk1", 328, 487, true);

	_player->render();
	RENDERMANAGER->push_BackAniRenderInfo(3000, "SB_sit_idle", _sit_boy_ani, 425, 632, true);
	RENDERMANAGER->push_BackRenderInfo(3000, "Desk5", 175, 642, true);
	RENDERMANAGER->push_BackRenderInfo(3000, "Desk6", 425, 638, true);
	RENDERMANAGER->push_BackRenderInfo(3000, "Desk7", 685, 642, true);
	RENDERMANAGER->push_BackRenderInfo(3000, "Desk8", 940, 642, true);
	RENDERMANAGER->push_BackRenderInfo(3000, "TeacherDesk", 1400, 684, true);
	EFFECTMANAGER->render();
	RENDERMANAGER->push_BackRenderInfo(3000, "UI_UNLOCKED_DOOR", 1400, 300, true, true, doorAlpha);

	RENDERMANAGER->render(getMemDC());
	_background3->render(getMemDC());
	stage::render();
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _tagPlayer->rc);
		Rectangle(getMemDC(), _tagPlayer->attackRect);
		for (int i = 0; i < _em->getEnemyVector().size(); i++)
		{
			Rectangle(getMemDC(), _em->getEnemyVector()[i]->getEnemyInfo()->rc);
		}
	}
}

void stage_Detention::cameraWork()
{

	// ī�޶� ó��
	if (_tagPlayer->x > WINSIZEX / 2)
	{
		RENDERMANAGER->setCameraX(-(_tagPlayer->x - WINSIZEX / 2));
	}

	if (RENDERMANAGER->getCameraX() < -_background2->getWidth() + WINSIZEX)
	{
		RENDERMANAGER->setCameraX(-_background2->getWidth() + WINSIZEX);
	}
}

void stage_Detention::doorWork()
{
	// �� UI blend �� ����
	if (IntersectRect(&_temp, &_tagPlayer->rc, &_door))
	{
		if (doorAlpha < 200)
			doorAlpha += 5;
		if (KEYMANAGER->isOnceKeyDown('Y'))
		{
			DATAMANAGER->setPlayerData(2624, 610, 0, DATAMANAGER->getPlayerData().hp);
			DATAMANAGER->setCamera(0, 0);
			_fade = false;
			_targetStageKey = "3������";
		}
	}
	else if (doorAlpha > 0)
	{
		doorAlpha -= 5;
	}
}


