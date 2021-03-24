#include "stdafx.h"
#include "developer.h"


developer::developer()
{
}


developer::~developer()
{
}

HRESULT developer::init(void)
{
	_img = IMAGEMANAGER->findImage("개발자");

	_x = 1080;
	_y = 400;

	_rc = RectMake(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

	_frameWorldCount = 0.0f;
	_frameWaitTime = 3.0f;

	sprintf(name, "개발자 J");

	return S_OK;
}