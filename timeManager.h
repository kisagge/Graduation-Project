#pragma once
#include "singletonBase.h"
#include "timer.h"
//==================================================================
//		## timeManager ## (Ÿ�ӸŴ���)
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

	//�������Ӵ� ����ð�(1 / 60) ��������
	float getElapsedTime(void) const { return _timer->getElapsedTime(); }
	//��ü ����ð� ��������(����Ÿ��)
	float getWorldTime(void) const { return _timer->getWorldTime(); }

	timeManager();
	~timeManager();
};

