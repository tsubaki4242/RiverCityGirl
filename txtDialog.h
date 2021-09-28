#pragma once
#include "gameNode.h"
#include <vector>

#define TEXTSIZE	60

class txtDialog : public gameNode
{
private:
	vector<string>	_vText;


	image* _front;
	int _frontloofX, _frontloofY;

	int i;
	int _index;
	int _count;
	int _row;

	bool _nextRow;
	int _printRow;

	image* _test;

	bool _change;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


};