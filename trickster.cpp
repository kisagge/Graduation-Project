#include "stdafx.h"
#include "trickster.h"


trickster::trickster()
{
}


trickster::~trickster()
{
}

HRESULT trickster::init(void)
{
	gameNode::init(true);

	_loadingScene = new loadingScene;
	_loadingScene->init();

	_openingScene = new openingScene;
	_openingScene->init();
	_sceneType = LOADING;

	//이곳에서 초기화를 한다
	//엔트리브_시사체, NtreevSoft, 나눔손글씨 펜

	_mapManager = new mapManager;
	_mapManager->init();

	_playerManager = new playerManager;
	_playerManager->init();

	_npcManager = new npcManager;
	_npcManager->init();

	_enemyManager = new enemyManager;
	_enemyManager->init();

	_uiManager = new uiManager;
	_uiManager->init();

	_selectScene = new selectScene;
	_selectScene->init();
	
	_mapManager->setPlayerManagerLink(_playerManager);
	_playerManager->setMapManagerLink(_mapManager);
	_playerManager->setUiManagerLink(_uiManager);
	_playerManager->setEnemyManagerLink(_enemyManager);
	_playerManager->getPlayer()->setUiManagerLink(_uiManager);
	_npcManager->setMapManagerLink(_mapManager);
	_npcManager->setPlayerManagerLink(_playerManager);
	_enemyManager->setMapManagerLink(_mapManager);
	_enemyManager->setPlayerManagerLink(_playerManager);
	_uiManager->setPlayerManagerLink(_playerManager);
	_uiManager->setNpcManagerLink(_npcManager);
	_uiManager->setMapManagerLink(_mapManager);

	_playerManager->getPlayer()->setMapManagerLink(_mapManager);
	_playerManager->getPlayer()->setEnemyManagerLink(_enemyManager);

	_mapManager->getLobbyMap()->setPlayerManagerLink(_playerManager);
	_mapManager->getFirstMap()->setPlayerManagerLink(_playerManager);
	_mapManager->getBossMap()->setPlayerManagerLink(_playerManager);

	_uiManager->getShop()->setPlayerManagerLink(_playerManager);

	_selectScene->setPlayerManagerLink(_playerManager);

	_frameCount = 0.0f;

	IMAGEMANAGER->findImage("마우스커서")->setFrameY(6);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < _enemyManager->getEnemyVec(i).size(); j++)
		{
			_enemyManager->getEnemyVec(i)[j]->setPlayerManagerLink(_playerManager);
		}
	}

	ShowCursor(FALSE);

	return S_OK;
}

void trickster::release(void)
{
	_loadingScene->release();
	SAFE_DELETE(_loadingScene);

	_mapManager->release();
	SAFE_DELETE(_mapManager);

	_playerManager->release();
	SAFE_DELETE(_playerManager);

	_npcManager->release();
	SAFE_DELETE(_npcManager);

	_enemyManager->release();
	SAFE_DELETE(_enemyManager);

	_uiManager->release();
	SAFE_DELETE(_uiManager);

	_openingScene->release();
	SAFE_DELETE(_openingScene);

	_selectScene->release();
	SAFE_DELETE(_selectScene);

	gameNode::release();
}

void trickster::update(void)
{
	switch (_sceneType)
	{
	case LOADING:
		_loadingScene->update();
		break;
	case TITLE:
		_openingScene->update();
		break;
	case SELECT:
		_selectScene->update();
		break;
	case MAIN:
		_mapManager->update();
		_playerManager->update();
		EFFECTMANAGER->update();
		_npcManager->update();
		_enemyManager->update();

		_uiManager->update();
		break;
	}
}

void trickster::render(void)
{	
	switch (_sceneType)
	{
	case LOADING:
		_loadingScene->render();
		setCamera(0, 0, WINSIZEX, WINSIZEY);
		uiMouseCursor();
		break;
	case TITLE:
		_openingScene->render();
		setCamera(0, 0, WINSIZEX, WINSIZEY);

		//마우스
		uiMouseCursor();
		break;
	case SELECT:
		_selectScene->render();
		setCamera(0, 0, WINSIZEX, WINSIZEY);
		uiMouseCursor();
		break;
	case MAIN:
		_mapManager->render();
		_npcManager->render();
		_playerManager->render();
		_enemyManager->render();

		EFFECTMANAGER->render();
		this->zorderRender();

		//카메라 설정
		setCamera(_playerManager->getPlayer()->getX(), _playerManager->getPlayer()->getY(),
			_mapManager->getMap(0)->getBg()->getWidth(), _mapManager->getMap(0)->getBg()->getHeight());

		_uiManager->render();

		//마우스
		if (PtInRect(&_uiManager->getMenuRect(0), _ptMouse)
			|| PtInRect(&_uiManager->getMenuRect(1), _ptMouse)
			|| PtInRect(&_uiManager->getMenuRect(2), _ptMouse)
			|| PtInRect(&_uiManager->getMenuRect(3), _ptMouse)
			|| PtInRect(&_uiManager->getMenuRect(4), _ptMouse)
			|| PtInRect(&_uiManager->getMenuRect(5), _ptMouse)
			|| PtInRect(&_uiManager->getMenuRect(6), _ptMouse)
			|| PtInRect(&_uiManager->getMenuRect(7), _ptMouse))
		{
			uiMouseCursor();
		}
		else if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			IMAGEMANAGER->findImage("마우스커서")->setFrameY(1);
			_mouseFrame = 1;
		}
		else
		{
			IMAGEMANAGER->findImage("마우스커서")->setFrameY(0);
			_mouseFrame = 0;
		}
		//미니맵 렌더
		/*this->minimap();*/

		if (_mapManager->getChangeSceneCount() > 0)
			_mapManager->getChangeSceneList(_mapManager->getWhatMap())
				->alphaRender(getCameraDC(), 0, 0, (int)_mapManager->getChangeSceneCount());

		/*TIMEMANAGER->render(getCameraDC());*/

		break;
	}

	IMAGEMANAGER->findImage("마우스커서")->frameRender(getCameraDC(), _ptMouse.x - 6, _ptMouse.y - 4,
		0, _mouseFrame);

	this->getCameraBuffer()->render(getHDC());
}

template <typename T>
void trickster::swap(T& k1, T& k2)
{
	T temp = k1;
	k1 = k2;
	k2 = temp;
}

void trickster::minimap(void)
{
	StretchBlt(getMinimapDC(), 0, 0, 200, 150, getTempDC(), 0, 0, _mapManager->getMap(0)->getBg()->getWidth(), _mapManager->getMap(0)->getBg()->getHeight(), SRCCOPY);
	this->getMinimap()->alphaRender(getCameraDC(), WINSIZEX - 200, 0, 180);
}

//z오더 퀵소트
void trickster::zorderQuickSort(int left, int right)
{
	int i = left, j = right, h;
	int x = _zorderVec[(left + right) / 2].zorder;

	//partion
	do
	{
		while (_zorderVec[i].zorder < x) i++;
		while (_zorderVec[j].zorder > x) j--;

		if (i <= j)
		{
			swap(_zorderVec[i], _zorderVec[j]);
			i++;
			j--;
		}
	} while (i <= j);

	//recursion
	if (left < j) zorderQuickSort(left, j);
	if (i < right) zorderQuickSort(i, right);
}

//z오더 렌더
void trickster::zorderRender()
{
	RECT temp;
	zorderQuickSort(0, _zorderVec.size() - 1);
	for (int i = 0; i < _zorderVec.size(); i++)
	{
		if (IntersectRect(&temp, &_cllipingRc, &_zorderVec[i].rc))
		{
			if (_zorderVec[i].isFrameImage)
			{
				if (!_zorderVec[i].isAlpha)
					_zorderVec[i].img->frameRender(getMemDC(), _zorderVec[i].x, _zorderVec[i].y,
					_zorderVec[i].frameX, _zorderVec[i].frameY);
				else
					_zorderVec[i].img->frameAlphaRender(getMemDC(), _zorderVec[i].x, _zorderVec[i].y,
					_zorderVec[i].frameX, _zorderVec[i].frameY, _zorderVec[i].alpha);
			}
			else
			{
				if (!_zorderVec[i].isAlpha)
					_zorderVec[i].img->render(getMemDC(), _zorderVec[i].x, _zorderVec[i].y);
				else
					_zorderVec[i].img->alphaRender(getMemDC(), _zorderVec[i].x, _zorderVec[i].y, _zorderVec[i].alpha);
			}
		}
	}
	_zorderVec.clear();
}

void trickster::setCamera(int a, int b, int width, int height)
{
	if (a < WINSIZEX / 2) cameraX = 0;
	else if (a + WINSIZEX / 2 > width)
		cameraX = width - WINSIZEX;
	else cameraX = a - WINSIZEX / 2;

	if (b < WINSIZEY / 2) cameraY = 0;
	else if (b + WINSIZEY / 2 > height)
		cameraY = height - WINSIZEY;
	else cameraY = b - WINSIZEY / 2;

	_cllipingRc = RectMake(cameraX, cameraY, WINSIZEX, WINSIZEY);
	BitBlt(getCameraDC(), 0, 0, width, height, getMemDC(), cameraX, cameraY, SRCCOPY);
}

void trickster::uiMouseCursor(void)
{
	if (0.1f + _frameCount <= TIMEMANAGER->getWorldTime())
	{
		if (IMAGEMANAGER->findImage("마우스커서")->getFrameY() <= 6)
		{
			IMAGEMANAGER->findImage("마우스커서")->setFrameY(6);
			_mouseFrame = 6;
		}
		_frameCount = TIMEMANAGER->getWorldTime();
		if (IMAGEMANAGER->findImage("마우스커서")->getFrameY() >= 10)
		{
			IMAGEMANAGER->findImage("마우스커서")->setFrameY(6);
			_mouseFrame = 6;
			return;
		}
		IMAGEMANAGER->findImage("마우스커서")->setFrameY(
			IMAGEMANAGER->findImage("마우스커서")->getFrameY() + 1);
		_mouseFrame++;
	}
}