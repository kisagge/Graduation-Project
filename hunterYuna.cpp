#include "stdafx.h"
#include "hunterYuna.h"


hunterYuna::hunterYuna()
{
}


hunterYuna::~hunterYuna()
{
}

HRESULT hunterYuna::init(void)
{
	_img = IMAGEMANAGER->findImage("헌터 유나");

	_x = 200;
	_y = 490;

	_rc = RectMake(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

	_frameWorldCount = 0.0f;
	_frameWaitTime = 3.0f;

	sprintf(name, "헌터 유나");

	return S_OK;
}
