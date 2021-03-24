#include "stdafx.h"
#include "playerManager.h"
#include "mapManager.h"
#include "uiManager.h"
#include "enemyManager.h"

playerManager::playerManager()
{
}


playerManager::~playerManager()
{
}

HRESULT playerManager::init(void)
{
	_player = new player;
	_player->init(500, 300);

	return S_OK;
}

void playerManager::release(void)
{
	_player->release();
	SAFE_DELETE(_player);
}

void playerManager::update(void)
{
	_player->update();
}

void playerManager::render(void)
{
	_player->render();

	_playerIcon->render(getTempDC(), _player->getX(), _player->getY());
}
