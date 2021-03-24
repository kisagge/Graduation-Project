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
	_img = IMAGEMANAGER->findImage("포티나");

	_x = 1460;
	_y = 720;

	_rc = RectMake(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

	_frameWorldCount = 0.0f;
	_frameWaitTime = 3.0f;

	sprintf(name, "포티나");

	return S_OK;
}
