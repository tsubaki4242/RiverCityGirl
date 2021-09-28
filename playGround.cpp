#include "stdafx.h"
#include "playGround.h"

#include <iostream>
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
using namespace std;

playGround::playGround()
{
}


playGround::~playGround()
{
}

//�ʱ�ȭ�� ����� �ϼ��� ����
HRESULT playGround::init()
{
	// ���͹ڽ�
	if (!_isOnce) {
		gameNode::init(true);
	}
	DATAMANAGER->setPlayerData(350, 570, 0, 25);
	SCENEMANAGER->addScene("�ΰ�", new logo);
	SCENEMANAGER->addScene("��Ʈ��", new intro);
	SCENEMANAGER->addScene("Ÿ��Ʋ", new title);
	SCENEMANAGER->addScene("���̺�ε�", new saveLode);
	SCENEMANAGER->addScene("��ȭ", new manga);
	SCENEMANAGER->addScene("�ε�", new loading);
	SCENEMANAGER->addScene("������Ʈ��", new bossIntro);

	SCENEMANAGER->changeScene("Ÿ��Ʋ");
	_isOnce = true;
	return S_OK;
}

//�޸� ������ ����� �ϼ��� ����
void playGround::release()
{
	gameNode::release();


}


void playGround::update()
{
	gameNode::update();
	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		init();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		cout << _ptMouse.x - RENDERMANAGER->getCameraX() << ", " << _ptMouse.y - RENDERMANAGER->getCameraY() << endl;
	}
		SCENEMANAGER->update();
}


void playGround::render()
{
	if (SCENEMANAGER->getSeanName() == "�ΰ�" || SCENEMANAGER->getSeanName() == "��Ʈ��" || SCENEMANAGER->getSeanName() == "��ȭ" || SCENEMANAGER->getSeanName() == "������Ʈ��")
	{
		SCENEMANAGER->render();
	}
	else
	{
		PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);

		SCENEMANAGER->render();
		//		TIMEMANAGER->render(getMemDC());
		this->getBackBuffer()->render(getHDC(), 0, 0);
	}
}
