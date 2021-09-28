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
		SCENEMANAGER->changeScene("��Ʈ��");

	}
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		std::ifstream file("saveplayer.txt");
		if (file.peek() == std::ifstream::traits_type::eof())
		{
			SOUNDMANAGER->stop("menuSound");
			SCENEMANAGER->changeScene("��ȭ");

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
	IMAGEMANAGER->findImage("���̺�ε���")->loopRender(getMemDC(), &_LOOP, _loopX, _loopY);
	IMAGEMANAGER->findImage("���̺�ε���2")->render(getMemDC());
	IMAGEMANAGER->findImage("���̺�ε���3")->alphaRender(getMemDC(),100);
	IMAGEMANAGER->findImage("����")->render(getMemDC(),750,0);
	IMAGEMANAGER->findImage("�׵θ�")->render(getMemDC());
	
	IMAGEMANAGER->findImage("���ڹ̻��ڱ׸���")->alphaRender(getMemDC(),100);
	IMAGEMANAGER->findImage("���ڹ̻���")->render(getMemDC());
	IMAGEMANAGER->findImage("���ϼ���")->render(getMemDC());
	
	_slot1->render(getMemDC(), 800, 300);
	_slot1_2->render(getMemDC(), 1000, 250);

	IMAGEMANAGER->findImage("���ھ�")->render(getMemDC(), 1250 , 420);
	IMAGEMANAGER->findImage("�̽����")->render(getMemDC(),1350, 410);
	textPrint();
}

void saveLode::imglist()
{
	IMAGEMANAGER->addImage("���̺�ε���", "UI/�����׶���.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���̺�ε���2", "UI/����ȭ���׶���2.bmp", WINSIZEX, WINSIZEY, true, RGB(70, 109, 252));
	IMAGEMANAGER->addImage("���ڹ̻���", "UI/���ڹ̻���.bmp", 794, 1332, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("���ڹ̻��ڱ׸���", "UI/���ڹ̻���2.bmp", 794, 1332, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("���̺�ε���3", "UI/���ļ����.bmp", WINSIZEX, WINSIZEY, true, RGB(70, 109, 252),true);
	IMAGEMANAGER->addImage("���ϼ���", "UI/���ϼ���.bmp", 442, 157, true, RGB(23, 23, 23));
	IMAGEMANAGER->addImage("����", "UI/����.bmp", 774, 894, true, RGB(23, 23, 23));

	IMAGEMANAGER->addImage("�����÷�_1", "UI/���̺�_1.bmp", 457, 246, true, RGB(23, 23, 23));
	IMAGEMANAGER->addImage("�����÷�", "UI/���̺�.bmp", 193, 214, true, RGB(23, 23, 23));

	IMAGEMANAGER->addImage("���ھ�", "UI/����.bmp", 77, 75, true, RGB(23, 23, 23));
	IMAGEMANAGER->addImage("�̽����", "UI/�̽���.bmp", 77, 75, true, RGB(23, 23, 23));

	IMAGEMANAGER->addImage("������", "UI/������.bmp", 371, 115, true, RGB(250, 250, 251), true);
	IMAGEMANAGER->addImage("�ҷ��������", "UI/�ҷ��������.bmp", 371, 115, true, RGB(250, 250, 251), true);

	_slot1 = IMAGEMANAGER->findImage("�����÷�");
	_slot1_2 = IMAGEMANAGER->findImage("�����÷�_1");
	_front = IMAGEMANAGER->findImage("������");
	_LOOP = RectMake(0, 0, WINSIZEX, WINSIZEY);
	_loopX = 0;
	_loopY = 0;
}

void saveLode::textPrint()
{
	std::ifstream file("saveplayer.txt");
	if (file.peek() == std::ifstream::traits_type::eof())
	{
		_front = IMAGEMANAGER->findImage("������");
		_front->render(getMemDC(), 1015, 300);

	}
	else
	{
		_front = IMAGEMANAGER->findImage("�ҷ��������");
		_front->render(getMemDC(), 1015, 300);
	}



}

void saveLode::load()
{
	HANDLE file;
	DWORD read;

	//���ڿ� �о���̴� ���ۼ���ŭ �׶��׶� �����Ҵ� �ϸ�
	//�� ����ϰ� �������ϴ�
	char str[128];

	file = CreateFile("savePlayer.txt", GENERIC_READ, FALSE,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	
	ReadFile(file, str, strlen(str), &read, NULL);

	CloseHandle(file);
	_vplayerDATA = TXTDATA->charArraySeparation(str);
}
