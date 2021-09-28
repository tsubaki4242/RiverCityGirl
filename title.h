#pragma once
#include "gameNode.h"

enum FIRE
{
	FIRE_1,
	FIRE_2,
	FIRE_3,
	FIRE_4,
	FIRE_5,
	FIRE_6
};
class title : public gameNode
{
private:
	image* _backGroundTile;
	image* _flashGround;
	int _flash;
	image* _Line;
	image* _fire;
	image* _title;
	image* _river;
	image* _city;
	image* _girls;
	image* _girls2;
	image* _P1;
	image* _P2;
	int _P1X, _P2X;

	RECT _start;
	RECT _exit;
	RECT _arrow;
	image* _startImg;
	image* _exitImg;
	image* _arrowImg;
	int _arrowY, _arrowStat;

	FIRE _fireAni;
	int _count, _index, _index2;

public:
	title() {}
	~title() {}

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


	void imglist();
	void Twinkle();
	void imgFrame();
};

