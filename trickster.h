#pragma once
#include "gameNode.h"
#include "mapManager.h"
#include "playerManager.h"
#include "npcManager.h"
#include "enemyManager.h"
#include "uiManager.h"

#include "loadingScene.h"
#include "openingScene.h"
#include "selectScene.h"


class trickster : 	public gameNode
{
private:
	mapManager* _mapManager;
	playerManager* _playerManager;
	npcManager* _npcManager;
	enemyManager* _enemyManager;
	uiManager* _uiManager;

	RECT _cllipingRc = RectMake(0, 0, WINSIZEX, WINSIZEY);

	openingScene* _openingScene;
	selectScene* _selectScene;
	loadingScene* _loadingScene;

	float _frameCount;
	int _mouseFrame = 6;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	template <typename T>
	void swap(T& k1, T& k2);

	//미니맵 함수
	void minimap(void);

	//z오더 퀵소트
	void zorderQuickSort(int left, int right);
	//z오더 렌더
	void zorderRender();

	//미니맵 관련변수들 호출
	HDC getMinimapDC(){ return _backBuffer3->getMemDC(); }
	image* getMinimap(){ return _backBuffer3; }

	void setCamera(int a, int b, int width, int height);


	//마우스 커서
	void uiMouseCursor(void);

	trickster();
	~trickster();
};

