#include "stdafx.h"
#include "hunterYuri.h"


hunterYuri::hunterYuri()
{
}


hunterYuri::~hunterYuri()
{
}

HRESULT hunterYuri::init(void)
{
	_img = IMAGEMANAGER->findImage("���� ����");

	_x = 1520;
	_y = 300;

	_rc = RectMake(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

	_frameWorldCount = 0.0f;
	_frameWaitTime = 3.0f;

	sprintf(name, "���� ����");


	return S_OK;
}
