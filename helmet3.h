#pragma once
#include "item.h"
class helmet3 : public item
{
public:
	HRESULT init(int x, int y);
	void release(void);
	void update(void);
	void render(void);

	helmet3();
	~helmet3();
};

