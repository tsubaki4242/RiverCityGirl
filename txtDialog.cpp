#include "stdafx.h"
#include "txtDialog.h"

HRESULT txtDialog::init()
{
	_vText = TXTDATA->txtLoad("��ȭ.txt");

	return S_OK;
}

void txtDialog::release()
{
}

void txtDialog::update()
{
}

void txtDialog::render()
{
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(255, 255, 255));

	HFONT font, oldFont;

	font = CreateFont(TEXTSIZE - 20, 0, 0, 0, 100, false, false, false, HANGUL_CHARSET,
		0, 0, 0, 0, TEXT("a��������"));
	oldFont = (HFONT)SelectObject(getMemDC(), font);
	if (!TIMEMANAGER->clock()) {
		if (_nextRow) {
			_printRow += 2;
			if (_printRow % TEXTSIZE == 0) {
				_printRow = 0;
				_nextRow = false;
			}
		}

		if (i < _vText.size() && !_nextRow) {
			//�ٽ�
			TextOut(getMemDC(), WINSIZEX / 16 + TEXTSIZE - 20, WINSIZEY - 40 * _row, _vText[i].c_str(), _index);

			//�ѱ��ھ� ���
			if (_vText[i][_index] != '@') {
				_count++;
				if (_count > 2) 
				{
					_index += 2;
					_count = 0;
				}
			}

			//���� ��
			else {
				_index = 0;
				_count = 0;
				i++;
				_row++;
				_nextRow = true;

				if (_row % 3 == 0)
					TIMEMANAGER->setTimer();
			}
		}
	}
	else if (TIMEMANAGER->clock() > 3) TIMEMANAGER->endTimer();


	DeleteObject(font);

}
