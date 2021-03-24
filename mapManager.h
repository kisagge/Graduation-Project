#pragma once
#include "gameNode.h"
#include "lobbyMap.h"
#include "firstMap.h"
#include "secondMap.h"

class playerManager;

class mapManager : public gameNode
{
private:
	vector<mapClass*> _mapVec;

	mapClass* _lb;
	mapClass* _ftM;
	mapClass* _bsM;
	playerManager* _playerManagerLink;

	int _whatMap;

	float _changeSceneCount;
	bool _isChangeScene;
	image* _changeSceneList[3];
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	mapClass* getMap(int i){ return _mapVec[i]; }
	mapClass* getLobbyMap(){ return _lb; }
	mapClass* getFirstMap(){ return _ftM; }
	mapClass* getBossMap(){ return _bsM; }
	int getWhatMap(){ return _whatMap; }

	void changeMap(int k);
	void collisionPortal(void);

	void setPlayerManagerLink(playerManager* pl){ _playerManagerLink = pl; }

	float getChangeSceneCount(){ return _changeSceneCount; }
	void setChangeSceneCount(float k){ _changeSceneCount = k; }
	bool getIsChangeScene(){ return _isChangeScene; }
	image* getChangeSceneList(int i){ return _changeSceneList[i]; }

	mapManager();
	~mapManager();
};

