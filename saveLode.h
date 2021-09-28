#pragma once
#include "gameNode.h"

#define TEXTSIZE	60


class saveLode : public gameNode
{
private:
	RECT _LOOP;
	int _loopX, _loopY;

	image* _slot1;
	image* _slot1_2;

	//ÆùÆ®
	image* _front;

	vector<string>	_vplayerDATA;
public:
	saveLode() {}
	~saveLode() {}

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void imglist();
	void textPrint();
	void load();
};