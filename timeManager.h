#pragma once
#include "singletonBase.h"
#include "timer.h"
//==================================================================
//		## timeManager ## (타임매니져)
//==================================================================

class timeManager : public singletonBase <timeManager>
{
private:
	timer* _timer;

public:
	HRESULT init(void);
	void release(void);
	void update(float lock);
	void render(HDC hdc);

	//한프레임당 경과시간(1 / 60) 가져오기
	float getElapsedTime(void) const { return _timer->getElapsedTime(); }
	//전체 경과시간 가져오기(월드타임)
	float getWorldTime(void) const { return _timer->getWorldTime(); }

	timeManager();
	~timeManager();
};

