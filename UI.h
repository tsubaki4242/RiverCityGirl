#pragma once
#include "gameNode.h"
#define LIFE 25


class UI : public gameNode
{
private:
	image* _prograssBar;
	image* _prograssBar2;
	image* _face;
	image* _lifeImg[LIFE];
	int _life;


public:
	UI() {};
	~UI() {};



	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();



};