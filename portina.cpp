#include "stdafx.h"
#include "portina.h"


portina::portina()
{
}


portina::~portina()
{
}

HRESULT portina::init(void)
{
	_img = IMAGEMANAGER->findImage("��Ƽ��");

	_x = 1460;
	_y = 720;

	_rc = RectMake(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

	_frameWorldCount = 0.0f;
	_frameWaitTime = 3.0f;

	sprintf(name, "��Ƽ��");

	return S_OK;
}
