#include "stdafx.h"
#include "loading.h"

loading::loading()
	: _loading(nullptr), _count(0)
{
}

loading::~loading()
{
}

HRESULT loading::init()
{
	_loading = IMAGEMANAGER->addFrameImage("로딩", "img/ui/loading.bmp", 1100, 217, 4, 1, true, RGB(23, 23, 23));
	_loading->setFrameX(0);
	_loading->setFrameY(0);
	CreateThread(
		NULL,			//스레드의 보안속성(자신윈도우가 존재할때)
		NULL,			//스레드의 스택크기(NULL로 두면 메인쓰레드)
		threadFunction,	//사용할 함수
		this,			//스레드 매개변수(this로 뒀으니 본 클래스)
		NULL,			//스레드 특성(기다릴지 바로실행할지(NULL))
		NULL			//스레드 생성 후 스레드의 ID 넘겨줌
	);
	return S_OK;
	
}

void loading::release()
{
}
    
void loading::update()
{
	_count++;
	if (_count % 15 == 0) 
	{
		if (_loading->getFrameX() >= _loading->getMaxFrameX()) _loading->setFrameX(0);
		else
		_loading->setFrameX(_loading->getFrameX() + 1);
	}
}

void loading::render()
{
	_loading->frameRender(getMemDC(), WINSIZEX - 300, WINSIZEY - 300);
}

DWORD threadFunction(LPVOID lpParameter)
{
	IMAGEMANAGER->addImage("그림자", "img/shadow.bmp", 120, 45, true, RGB(255, 0, 255), true);
	SOUNDMANAGER->addSound("River City Girls OST - 4 - Detention", "sound/bgm/River City Girls OST - 4 - Detention.mp3", true, true);
	SOUNDMANAGER->addSound("intro", "sound/bgm/intro.mp3", true, true);
	SOUNDMANAGER->addSound("River City Girls OST - 3 - Bully", "sound/bgm/River City Girls OST - 3 - Bully.mp3", true, true);
	SOUNDMANAGER->addSound("River City Girls OST - 5 - Knock Out", "sound/bgm/River City Girls OST - 5 - Knock Out.mp3", true, true);
	SOUNDMANAGER->addSound("River City Girls OST - 6 - Lunch Money", "sound/bgm/River City Girls OST - 6 - Lunch Money.mp3", true, true);
	SOUNDMANAGER->addSound("River City Girls OST - 7 - Misuzu Intro", "River City Girls OST - 7 - Misuzu Intro.mp3", true, true);
	SOUNDMANAGER->addSound("River City Girls OST - 8 - Boss_ Misuzu", "sound/bgm/River City Girls OST - 8 - Boss_ Misuzu.mp3", true, true);


	IMAGEMANAGER->addImage("검은배경", "img/ui/bgblack.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("BackGround3", "img/stage/stage1/BackBg3.bmp", 2016, WINSIZEY, true, RGB(255, 0, 255));
	SCENEMANAGER->addScene("3층복도", new stage_3rdFloor_Corridor);
	SCENEMANAGER->addScene("테스트씬", new testScene);
	SCENEMANAGER->addScene("반성실", new stage_Detention);
	SCENEMANAGER->addScene("2층홀A", new stage_2ndFloor_HallA);
	SCENEMANAGER->addScene("2층방", new stage_2ndFloor_room);
	SCENEMANAGER->addScene("2층홀B", new stage_2ndFloor_HallB);
	SCENEMANAGER->addScene("1층홀A", new stage_1stFloor_HallA);
	SCENEMANAGER->addScene("1층홀B", new stage_1stFloor_HallB);
	SCENEMANAGER->addScene("1층방", new stage_1stFloor_room);
	SCENEMANAGER->addScene("식당", new stage_cafeteria);
	SCENEMANAGER->addScene("로비", new stage_lobby);
	IMAGEMANAGER->addImage("UI_UNLOCKED_DOOR", "img/ui/UI_UNLOCKED_DOOR.bmp", 78, 114, true, RGB(255, 0, 255), true);

	IMAGEMANAGER->addImage("그림자", "img/Shedow.bmp", 120, 45, true, RGB(255, 0, 255), true);

	//IDLE 이미지
	IMAGEMANAGER->addFrameImage("Enemy_Image_Idle_School_Girl", "img/enemy/school_girl/school_girl_Idle.bmp", 1170, 354, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_Image_Move_School_Girl", "img/enemy/school_girl/school_girl_Walk.bmp", 1296, 372, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_Image_Run_School_Girl", "img/enemy/school_girl/school_girl_Run.bmp", 1530, 336, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_Image_Jump_School_Girl", "img/enemy/school_girl/school_girl_Jump.bmp", 351, 372, 3, 2, true, RGB(255, 0, 255));




	//공격 이미지
	IMAGEMANAGER->addFrameImage("Enemy_Image_Attack_1_School_Girl", "img/enemy/school_girl/school_girl_Attack_1.bmp", 825, 354, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_Image_Attack_2_School_Girl", "img/enemy/school_girl/school_girl_Attack_2.bmp", 1260, 354, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_Image_Attack_3_School_Girl", "img/enemy/school_girl/school_girl_Attack_3.bmp", 1632, 354, 8, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("Enemy_Image_Dash_Attack_School_Girl", "img/enemy/school_girl/school_girl_Dash_Attack.bmp", 3312, 414, 12, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("Enemy_Image_Jump_Attack_School_Girl", "img/enemy/school_girl/school_girl_Jump_Attack.bmp", 1239, 354, 7, 2, true, RGB(255, 0, 255));


	//피격 이미지
	IMAGEMANAGER->addFrameImage("Enemy_Image_Attacked_1_School_Girl", "img/enemy/school_girl/school_girl_getHit_1.bmp", 477, 360, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_Image_Attacked_2_School_Girl", "img/enemy/school_girl/school_girl_getHit_2.bmp", 477, 360, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_Image_Attacked_3_School_Girl", "img/enemy/school_girl/school_girl_getHit_3.bmp", 477, 360, 3, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("Enemy_Image_Ground_Hitted_School_Girl", "img/enemy/school_girl/school_girl_Ground_Hitted.bmp", 675, 360, 3, 2, true, RGB(255, 0, 255));

	//넉다운 이미지
	IMAGEMANAGER->addFrameImage("Enemy_Image_KnockDown_1_School_Girl", "img/enemy/school_girl/school_girl_KnockDown_1.bmp", 4050, 360, 18, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_Image_KnockDown_2_School_Girl", "img/enemy/school_girl/school_girl_KnockDown_2.bmp", 675, 360, 3, 2, true, RGB(255, 0, 255));
	//기상 이미지 
	IMAGEMANAGER->addFrameImage("Enemy_Image_Wake_up_School_Girl", "img/enemy/school_girl/school_girl_Wake_up.bmp", 2025, 360, 9, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("Enemy_Image_Wake_up_School_Boy", "img/enemy/school_boy/schoo_boy_wake_up.bmp", 2160, 420, 8, 2, true, RGB(255, 0, 255));


	IMAGEMANAGER->addFrameImage("Enemy_Image_Idle_School_Boy", "img/enemy/school_boy/school_boy_idle.bmp", 1224, 432, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_Image_Jump_School_Boy", "img/enemy/school_boy/school_boy_jump.bmp", 423, 486, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_Image_Move_School_Boy", "img/enemy/school_boy/school_boy_walk.bmp", 1620, 444, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_Image_Run_School_Boy", "img/enemy/school_boy/school_boy_run.bmp", 1920, 390, 10, 2, true, RGB(255, 0, 255));


	IMAGEMANAGER->addFrameImage("Enemy_Image_Attack_1_School_Boy", "img/enemy/school_boy/school_boy_attack_1.bmp", 1764, 426, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_Image_Attack_2_School_Boy", "img/enemy/school_boy/school_boy_attack_2.bmp", 1386, 510, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_Image_Attack_3_School_Boy", "img/enemy/school_boy/school_boy_attack_3.bmp", 1863, 558, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_Image_Dash_Attack_School_Boy", "img/enemy/school_boy/school_boy_dash_attack.bmp", 1764, 444, 7, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_Image_Jump_Attack_School_Boy", "img/enemy/school_boy/school_boy_jump_attack.bmp", 1188, 456, 6, 2, true, RGB(255, 0, 255));


	IMAGEMANAGER->addFrameImage("Enemy_Image_Attacked_1_School_Boy", "img/enemy/school_boy/school_boy_attacked_1.bmp", 576, 450, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_Image_Attacked_2_School_Boy", "img/enemy/school_boy/school_boy_attacked_2.bmp", 576, 450, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Enemy_Image_Attacked_3_School_Boy", "img/enemy/school_boy/school_boy_attacked_3.bmp", 576, 450, 3, 2, true, RGB(255, 0, 255));



	IMAGEMANAGER->addFrameImage("Enemy_Image_KnockDown_1_School_Boy", "img/enemy/school_boy/school_boy_knockdown_1.bmp", 5400, 420, 20, 2, true, RGB(255, 0, 255));//23
	IMAGEMANAGER->addFrameImage("Enemy_Image_KnockDown_2_School_Boy", "img/enemy/school_boy/school_boy_knockdown_3.bmp", 540, 420, 2, 2, true, RGB(255, 0, 255));




	IMAGEMANAGER->addFrameImage("Misuzu_IDLE", "img/enemy/misuzu/misuzu_idle.bmp", 2844, 582, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Misuzu_Move", "img/enemy/misuzu/misuzu_walk.bmp", 1770, 540, 10, 2, true, RGB(255, 0, 255));


	IMAGEMANAGER->addFrameImage("Misuzu_Attack_1", "img/enemy/misuzu/misuzu_Attack_1.bmp", 2574, 600, 11, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Misuzu_Attack_2", "img/enemy/misuzu/misuzu_Attack_2.bmp", 5040, 534, 14, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("Misuzu_PowerAttack", "img/enemy/misuzu/misuzu_power_Attack.bmp", 10854, 546, 27, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("Misuzu_Tount", "img/enemy/misuzu/misuzu_tount.bmp", 5037, 690, 23, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Misuzu_PowerUp", "img/enemy/misuzu/misuzu_powerUp.bmp", 2592, 534, 12, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("Misuzu_Wake_Up", "img/enemy/misuzu/misuzu_wake_up.bmp", 3330, 528, 15, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("Misuzu_Takkle_Ready", "img/enemy/misuzu/misuzu_takkle_ready.bmp", 990, 528, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Misuzu_Takkle", "img/enemy/misuzu/misuzu_takkle.bmp", 2574, 510, 11, 2, true, RGB(255, 0, 255));


	IMAGEMANAGER->addFrameImage("Misuzu_Attacked_1", "img/enemy/misuzu/misuzu_Attacked_1.bmp", 657, 546, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Misuzu_Attacked_2", "img/enemy/misuzu/misuzu_Attacked_2.bmp", 657, 546, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Misuzu_Attacked_3", "img/enemy/misuzu/misuzu_Attacked_3.bmp", 657, 546, 3, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("Misuzu_KnockDown_1", "img/enemy/misuzu/misuzu_knockdown_1.bmp", 2580, 534, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Misuzu_KnockDown_2", "img/enemy/misuzu/misuzu_knockdown_2.bmp", 948, 426, 4, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("Misuzu_Ground_Hitted", "img/enemy/misuzu/misuzu_ground_hitted.bmp", 924, 420, 3, 2, true, RGB(255, 0, 255));


	IMAGEMANAGER->addFrameImage("Misuzu_Die", "img/enemey/misuzu/misuzu_die.bmp", 4134, 528, 13, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("Misuzu_Jump_Up_Ready", "img/enemy/misuzu/misuzu_meteor_jump_attack_ready.bmp", 1584, 612, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Misuzu_Jump_Up", "img/enemy/misuzu/misuzu_meteor_jump_start.bmp", 360, 612, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Misuzu_Jump_Down", "img/enemy/misuzu/misuzu_meteor_jump_attack.bmp", 426, 420, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Misuzu_Jump_after_not_groggy", "img/enemy/misuzu/misuzu_meteor_jump_not_groggy.bmp", 2628, 528, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Misuzu_Jump_after_groggy", "img/enemy/misuzu/misuzu_meteor_jump_groggy.bmp", 4161, 528, 19, 2, true, RGB(255, 0, 255));

	int i = 0;
	while (100 > i)
	{
		i++;


		Sleep(1);



	}
	DATAMANAGER->setPlayerData(800,800,0,25);
	SCENEMANAGER->changeScene("로비");
	return 0;
}
