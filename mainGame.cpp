#include "stdafx.h"
#include "mainGame.h"
mainGame::mainGame()
{
}
mainGame::~mainGame()
{
}

//==================================================================
//		## 초기화 ## init(void)
//==================================================================
HRESULT mainGame::init(void)
{
	SCENEMANAGER->addScene("트릭스터", new trickster);
	SCENEMANAGER->changeScene("트릭스터");

	return S_OK;
}

//==================================================================
//		## 해제 ## release(void)
//==================================================================
void mainGame::release(void)
{
	gameNode::release();
}

//==================================================================
//		## 업데이트 ## update(void)
//==================================================================
void mainGame::update(void)
{
	gameNode::update();

	//씬매니져 업데이트
	SCENEMANAGER->update();

	//사운드매니져 업데이트
	SOUNDMANAGER->update();
}

//==================================================================
//		## 렌더 ## render(void)
//==================================================================
void mainGame::render(void)
{
	//흰색 빈 비트맵(이건 렌더에 그냥 그대로 둘것)
	PatBlt(getCameraDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//씬매니져 렌더
	SCENEMANAGER->render();
}
