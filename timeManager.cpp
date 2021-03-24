#include "stdafx.h"
#include "timeManager.h"
timeManager::timeManager()
{
}
timeManager::~timeManager()
{
}
//==================================================================
//		## 더이상 생성자, 소멸자는 사용하지 않는다 ##
//==================================================================

HRESULT timeManager::init(void)
{
	_timer = new timer;
	_timer->init();

	return S_OK;
}

void timeManager::release(void)
{
	SAFE_DELETE(_timer);
}

void timeManager::update(float lock)
{
	if (_timer != NULL)
	{
		_timer->tick(lock);
	}
}

void timeManager::render(HDC hdc)
{
	char str[256];
	string strFrame;

	//글자배경모드
	SetBkMode(hdc, TRANSPARENT);
	//글자색상
	SetTextColor(hdc, RGB(0, 0, 255));

#ifdef _DEBUG
	if(_timer != NULL)
	{
		//FPS
		sprintf(str, "FPS : %d", _timer->getFrameRate());
		TextOut(hdc, 0, 0, str, strlen(str));
		//wolrdTime
		sprintf(str, "WorldTime : %f", _timer->getWorldTime());
		TextOut(hdc, 0, 20, str, strlen(str));
		//elapsedTime
		sprintf(str, "ElapsedTime : %f", _timer->getElapsedTime());
		TextOut(hdc, 0, 40, str, strlen(str));
	}
#else
	if(_timer != NULL)
	{
		sprintf(str, "FPS : %d", _timer->getFrameRate());
		TextOut(hdc, 0, 0, str, strlen(str));
	}
#endif
}