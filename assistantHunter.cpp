#include "stdafx.h"
#include "assistantHunter.h"


assistantHunter::assistantHunter()
{
}


assistantHunter::~assistantHunter()
{
}

HRESULT assistantHunter::init(void)
{
	_img = IMAGEMANAGER->findImage("어시스트헌터");

	_x = 320;
	_y = 200;

	_rc = RectMake(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

	_frameWorldCount = 0.0f;
	_frameWaitTime = 3.0f;

	sprintf(name, "헌터 조력자");


	return S_OK;
}
