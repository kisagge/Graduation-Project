#pragma once
#include "item.h"

class drill1 : public item
{
public:
	HRESULT init(int x, int y);
	void release(void);
	void update(void);
	void render(void);

	drill1();
	~drill1();
};

