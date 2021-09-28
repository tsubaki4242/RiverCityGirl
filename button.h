#pragma once
#include "gameNode.h"

//�Լ������� ���¸� ���� �ݹ��Լ� 
typedef void(*CALLBACK_FUNCTION2)(void);

//<Functional> 
//std::Function, std::move, std::bind ����� �Լ��� �ִµ�
//�ݹ��Լ��� ������ ����Ǿ� �־ �Ű������� ����Ҽ����µ�
//���� �͵��� �� �̿��ϸ� �Ϲ����� �Ű������� �־ ����Ҽ� ����.

//����) �ǿܷ� ���, �̰� ��¥ �����ΰ�? ����ǥ ���� ���� ���� ����
//Lambda expression
//Lambda�� �� ��� ���� �ӵ��� ������ ����! ���ٽ��̶� ��� ������
//�� ����!


enum BUTTONDIRECTION
{
	BUTTONDIRECTION_NULL,
	BUTTONDIRECTION_UP,
	BUTTONDIRECTION_DOWN
};

class button : public gameNode
{
private:
	BUTTONDIRECTION _direction;

	const char* _imageName;
	image* _image;
	RECT _rc;
	float _x, _y;

	POINT _btnDownFramePoint;
	POINT _btnUpFramePoint;

	//�ݹ��Լ� typedef �� �ָ� ������ ��
	CALLBACK_FUNCTION2 _callbackFunction;

public:
	button();
	~button();

	HRESULT init(const char* imageName, int x, int y,
		POINT btnDownFramePoint, POINT btnUpFramePoint,
		CALLBACK_FUNCTION2 cbFunction);
	void release();
	void update();
	void render();
};

