#include "stdafx.h"
#include "officerRobert.h"


officerRobert::officerRobert()
{
}


officerRobert::~officerRobert()
{
}

HRESULT officerRobert::init(void)
{
	_img = IMAGEMANAGER->findImage("오피서 로버트");

	_x = 1340;
	_y = 510;

	_rc = RectMake(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

	_frameWorldCount = 0.0f;
	_frameWaitTime = 3.0f;

	sprintf(name, "관리원 로버트");

	return S_OK;
}

void officerRobert::update(void)
{
	_rc = RectMake(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

	if (_frameWaitTime > 0) _frameWaitTime -= TIMEMANAGER->getElapsedTime();
	else
	{
		if (0.15f + _frameWorldCount <= TIMEMANAGER->getWorldTime())
		{
			_frameWorldCount = TIMEMANAGER->getWorldTime();
			if (_img->getFrameX() >= _img->getMaxFrameX())
			{
				_img->setFrameX(0);
				_frameWaitTime = 3.0f;
				return;
			}
			_img->setFrameX(_img->getFrameX() + 1);
		}
	}
}