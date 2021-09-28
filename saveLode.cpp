#include "stdafx.h"
#include "saveLode.h"
#include <fstream>
#include <type_traits>
HRESULT saveLode::init()
{
	SOUNDMANAGER->stop("intro");
	SOUNDMANAGER->addSound("menuSound", "sound/menu.mp3", true, true);
	SOUNDMANAGER->play("menuSound");
	imglist();

	load();
	
	return S_OK;
}

void saveLode::release()
{
	
}

void saveLode::update()
{
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		SOUNDMANAGER->stop("menuSound");
		SCENEMANAGER->changeScene("인트로");

	}
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		std::ifstream file("saveplayer.txt");
		if (file.peek() == std::ifstream::traits_type::eof())
		{
			SOUNDMANAGER->stop("menuSound");
			SCENEMANAGER->changeScene("만화");

		}
		else
		{

		}



	}
	_loopX++;
	_loopY++;


}

void saveLode::render()
{
	IMAGEMANAGER->findImage("세이브로드배경")->loopRender(getMemDC(), &_LOOP, _loopX, _loopY);
	IMAGEMANAGER->findImage("세이브로드배경2")->render(getMemDC());
	IMAGEMANAGER->findImage("세이브로드배경3")->alphaRender(getMemDC(),100);
	IMAGEMANAGER->findImage("판지")->render(getMemDC(),750,0);
	IMAGEMANAGER->findImage("테두리")->render(getMemDC());
	
	IMAGEMANAGER->findImage("쿄코미사코그림자")->alphaRender(getMemDC(),100);
	IMAGEMANAGER->findImage("쿄코미사코")->render(getMemDC());
	IMAGEMANAGER->findImage("파일선택")->render(getMemDC());
	
	_slot1->render(getMemDC(), 800, 300);
	_slot1_2->render(getMemDC(), 1000, 250);

	IMAGEMANAGER->findImage("쿄코얼굴")->render(getMemDC(), 1250 , 420);
	IMAGEMANAGER->findImage("미스즈얼굴")->render(getMemDC(),1350, 410);
	textPrint();
}

void saveLode::imglist()
{
	IMAGEMANAGER->addImage("세이브로드배경", "UI/저장백그라운드.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("세이브로드배경2", "UI/저장화면백그라운드2.bmp", WINSIZEX, WINSIZEY, true, RGB(70, 109, 252));
	IMAGEMANAGER->addImage("쿄코미사코", "UI/쿄코미사코.bmp", 794, 1332, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("쿄코미사코그림자", "UI/쿄코미사코2.bmp", 794, 1332, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("세이브로드배경3", "UI/알파선배경.bmp", WINSIZEX, WINSIZEY, true, RGB(70, 109, 252),true);
	IMAGEMANAGER->addImage("파일선택", "UI/파일선택.bmp", 442, 157, true, RGB(23, 23, 23));
	IMAGEMANAGER->addImage("판지", "UI/판지.bmp", 774, 894, true, RGB(23, 23, 23));

	IMAGEMANAGER->addImage("슬롯컬러_1", "UI/세이브_1.bmp", 457, 246, true, RGB(23, 23, 23));
	IMAGEMANAGER->addImage("슬롯컬러", "UI/세이브.bmp", 193, 214, true, RGB(23, 23, 23));

	IMAGEMANAGER->addImage("쿄코얼굴", "UI/쿄코.bmp", 77, 75, true, RGB(23, 23, 23));
	IMAGEMANAGER->addImage("미스즈얼굴", "UI/미스즈.bmp", 77, 75, true, RGB(23, 23, 23));

	IMAGEMANAGER->addImage("뉴게임", "UI/뉴게임.bmp", 371, 115, true, RGB(250, 250, 251), true);
	IMAGEMANAGER->addImage("불러오기게임", "UI/불러오기게임.bmp", 371, 115, true, RGB(250, 250, 251), true);

	_slot1 = IMAGEMANAGER->findImage("슬롯컬러");
	_slot1_2 = IMAGEMANAGER->findImage("슬롯컬러_1");
	_front = IMAGEMANAGER->findImage("뉴게임");
	_LOOP = RectMake(0, 0, WINSIZEX, WINSIZEY);
	_loopX = 0;
	_loopY = 0;
}

void saveLode::textPrint()
{
	std::ifstream file("saveplayer.txt");
	if (file.peek() == std::ifstream::traits_type::eof())
	{
		_front = IMAGEMANAGER->findImage("뉴게임");
		_front->render(getMemDC(), 1015, 300);

	}
	else
	{
		_front = IMAGEMANAGER->findImage("불러오기게임");
		_front->render(getMemDC(), 1015, 300);
	}



}

void saveLode::load()
{
	HANDLE file;
	DWORD read;

	//문자열 읽어들이는 버퍼수만큼 그때그때 동적할당 하면
	//더 깔끔하고 조옿습니다
	char str[128];

	file = CreateFile("savePlayer.txt", GENERIC_READ, FALSE,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	
	ReadFile(file, str, strlen(str), &read, NULL);

	CloseHandle(file);
	_vplayerDATA = TXTDATA->charArraySeparation(str);
}
