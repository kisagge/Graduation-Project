#pragma once
#include "gameNode.h"
#include "assistantHunter.h"
#include "officerRobert.h"
#include "hunterYuri.h"
#include "hunterYuna.h"
#include "portina.h"
#include "andrew.h"
#include "louis.h"
#include "developer.h"

class mapManager;
class playerManager;

class npcManager : public gameNode
{
private:
	vector<npcClass*> _npcVec[3];
	image* _npcIcon = IMAGEMANAGER->findImage("npc«•Ω√");

	playerManager* _playerManagerLink;
	mapManager* _mapManagerLink;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	
	vector<npcClass*> getNpcVec(int i){ return _npcVec[i]; }

	void setMapManagerLink(mapManager* mm){ _mapManagerLink = mm; }
	void setPlayerManagerLink(playerManager* pl){ _playerManagerLink = pl; }

	npcManager();
	~npcManager();
};

