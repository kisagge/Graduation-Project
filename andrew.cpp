#include "stdafx.h"
#include "andrew.h"


andrew::andrew()
{
}


andrew::~andrew()
{
}

HRESULT andrew::init(void)
{
	_img = IMAGEMANAGER->findImage("�ص��");

	_x = 280;
	_y = 770;

	_rc = RectMake(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

	_frameWorldCount = 0.0f;
	_frameWaitTime = 3.0f;

	sprintf(name, "�ص��");

	return S_OK;
}

