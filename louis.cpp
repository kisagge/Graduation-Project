#include "stdafx.h"
#include "louis.h"


louis::louis()
{
}


louis::~louis()
{
}

HRESULT louis::init(void)
{
	_img = IMAGEMANAGER->findImage("���̽�");

	_x = 1580;
	_y = 400;

	_rc = RectMake(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

	_frameWorldCount = 0.0f;
	_frameWaitTime = 3.0f;

	sprintf(name, "���û� ���̽�");

	return S_OK;
}