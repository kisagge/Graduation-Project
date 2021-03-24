#pragma once
#include "mapClass.h"
#include "tile.h"

class secondMap : public mapClass
{
public:
	HRESULT init(void);
	void release(void);
	void render(void);

	secondMap();
	~secondMap();
};

