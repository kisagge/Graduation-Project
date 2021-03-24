#pragma once
#include "gameNode.h"
#include "trickster.h"
#include "loadingScene.h"
#include "openingScene.h"

class mainGame : public gameNode
{
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	mainGame();
	~mainGame();
};