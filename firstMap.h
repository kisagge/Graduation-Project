#pragma once
#include "mapClass.h"
#include "tile.h"
class firstMap : public mapClass
{
public:
	HRESULT init(void);
	void release(void);
	void render(void);

	firstMap();
	~firstMap();
};

