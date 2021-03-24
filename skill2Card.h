#pragma once
#include "item.h"
class skill2Card : public item
{
public:
	HRESULT init(int x, int y);
	void release(void);
	void update(void);
	void render(void);

	skill2Card();
	~skill2Card();
};

