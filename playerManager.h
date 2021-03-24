#pragma once
#include "gameNode.h"
#include "player.h"

class mapManager;
class uiManager;
class playerManager;

class playerManager : public gameNode
{
private:
	player* _player;
	image* _playerIcon = IMAGEMANAGER->findImage("플레이어표시");

	mapManager* _mapManagerLink;
	uiManager* _uiManagerLink;
	enemyManager* _enemyManagerLink;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void setMapManagerLink(mapManager* mm){ _mapManagerLink = mm; }
	void setUiManagerLink(uiManager* ui){ _uiManagerLink = ui; }
	void setEnemyManagerLink(enemyManager* en){ _enemyManagerLink = en; }

	player* getPlayer(){ return _player; }

	playerManager();
	~playerManager();
};

