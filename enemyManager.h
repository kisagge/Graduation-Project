#pragma once
#include "gameNode.h"
#include "fantaSlime.h"
#include "addax.h"
#include "pochi.h"
#include "requi.h"
#include "sphinx.h"

#define ADDAXMAX 2
#define POCHIMAX 2
#define REQUIMAX 2
#define SPHINXMAX 1

class mapManager;
class playerManager; 

class enemyManager : public gameNode
{
private:
	vector<enemy*>::iterator _viEnemy;

	vector<enemy*> _vEnemyMap[3];
	mapManager* _mapManagerLink;
	playerManager* _playerManagerLink;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void setMapManagerLink(mapManager* k){ _mapManagerLink = k; }
	void setPlayerManagerLink(playerManager* k){ _playerManagerLink = k; }

	void pushFantaSlime(void);
	void pushAddax(void);
	void pushPochi(void);
	void pushRequi(void);
	void pushSphinx(void);

	vector<enemy*> getEnemyVec(int i){ return _vEnemyMap[i]; }
	void releaseMon(void);

	void calculateMonSize(void);
	item* dropItem(int k);

	enemyManager();
	~enemyManager();
};

