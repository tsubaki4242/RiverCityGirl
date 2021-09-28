#pragma once

#include <Vfw.h>	// ���� ��� ���� ���̺귯��
#pragma comment(lib, "vfw32.lib")

class video
{
private:

	const char* _fileName; //���� �̸�
	HWND _hWndAVI;
	HINSTANCE _hWndInstance;
public:

	video();
	~video();


	HRESULT init();
	void release();

	HRESULT setVideo(const char* fileName);
	void playVideo();
	void closeVideo(void);
	void deletVideo();
	void langsVideo(const char* fileName);
	void startVideo(const char* fileName);


	long getLnagStart() { return MCIWndGetPosition(_hWndAVI); }
	long getLangEnd() {return MCIWndGetLength(_hWndAVI); }


};

