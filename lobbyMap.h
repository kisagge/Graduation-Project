#pragma once
#include "mapClass.h"
#include "tile.h"

class lobbyMap : public mapClass
{
private:
	tagPortal _map1Portal;
public:
	HRESULT init(void);
	void release(void);
	void render(void);

	lobbyMap();
	~lobbyMap();
};
