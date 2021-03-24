#include "stdafx.h"
#include "npcClass.h"


npcClass::npcClass()
{
}


npcClass::~npcClass()
{
}

HRESULT npcClass::init(void)
{
	return S_OK;
}

void npcClass::release(void)
{

}

void npcClass::update(void)
{
	_rc = RectMake(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());

	if (_frameWaitTime > 0) _frameWaitTime -= TIMEMANAGER->getElapsedTime();
	else
	{
		if (0.2f + _frameWorldCount <= TIMEMANAGER->getWorldTime())
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

void npcClass::render(void)
{
	putZorderVec(_img, _x, _y, _rc.bottom + 20, _img->getFrameX(), _img->getFrameY());
	fontRender("³ª´®°íµñ", name, 20, 1, _x + 5, _y + _img->getFrameHeight() + 5, RGB(0, 0, 0));
}

void npcClass::alphaRen(void)
{
	putZorderVec(_img, _x, _y, _rc.bottom + 10, _img->getFrameX(), _img->getFrameY(), 190);
	fontRender("³ª´®°íµñ", name, 20, 1, _x + 5, _y + _img->getFrameHeight() + 5, RGB(0, 0, 0));
}