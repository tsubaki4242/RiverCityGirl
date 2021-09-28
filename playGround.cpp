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

//초기화는 여기다 하세요 제발
HRESULT playGround::init()
{
	// 레터박스
	if (!_isOnce) {
		gameNode::init(true);
	}
	DATAMANAGER->setPlayerData(350, 570, 0, 25);
	SCENEMANAGER->addScene("로고", new logo);
	SCENEMANAGER->addScene("인트로", new intro);
	SCENEMANAGER->addScene("타이틀", new title);
	SCENEMANAGER->addScene("세이브로드", new saveLode);
	SCENEMANAGER->addScene("만화", new manga);
	SCENEMANAGER->addScene("로딩", new loading);
	SCENEMANAGER->addScene("보스인트로", new bossIntro);

	SCENEMANAGER->changeScene("타이틀");
	_isOnce = true;
	return S_OK;
}

//메모리 해제는 여기다 하세요 제발
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
	if (SCENEMANAGER->getSeanName() == "로고" || SCENEMANAGER->getSeanName() == "인트로" || SCENEMANAGER->getSeanName() == "만화" || SCENEMANAGER->getSeanName() == "보스인트로")
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
