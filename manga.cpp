#include "stdafx.h"
#include "manga.h"

HRESULT manga::init()
{
	STREAMMANAGER->addVideo("movi/manga.wmv", "manga");
	STREAMMANAGER->findVideo("manga")->playVideo();
	return S_OK;
}

void manga::release()
{
}

void manga::update()
{
	if (STREAMMANAGER->getPosition("manga") >= STREAMMANAGER->getLenthEnd("manga"))
	{

		STREAMMANAGER->closeVideo("manga");
		SCENEMANAGER->changeScene("로딩");

	}
	if (KEYMANAGER->isOnceKeyDown('A'))
	{

		STREAMMANAGER->closeVideo("manga");
		SCENEMANAGER->changeScene("로딩");


	}
}

void manga::render()
{
}
