#include "stdafx.h"
#include "lobbyMap.h"
#include "playerManager.h"

lobbyMap::lobbyMap()
{
}


lobbyMap::~lobbyMap()
{
}

HRESULT lobbyMap::init(void)
{
	_bg = IMAGEMANAGER->findImage("로비맵");

	for (int i = 0; i < TILEX; i++)
	{
		for (int j = 0; j < TILEY; j++)
		{
			_lobbyTile[i][j] = new tile;
			_lobbyTile[i][j]->init(i, j);
		}
	}

	this->addObj("소라집", 4, 1, 4, 3, 5, 2, 0);
	this->addObj("캠프1", 32, 3, 32, 6, 4, 2, 0);
	this->addObj("피라미드", 2, 13, 2, 16, 6, 2, 0);
	this->addObj("잠수함", 30, 13, 30, 15, 4, 1, 0);
	this->addObj("캔디집", 1, 7, 1, 10, 5, 2, 0);
	this->addObj("캠프파이어", 18, 9, 18, 10, 3, 2, 1);
	this->addObj("소라집2", 28, 7, 28, 10, 4, 2, 0);

	_map1Portal.img = IMAGEMANAGER->findImage("포탈");
	_map1Portal.x = 800;
	_map1Portal.y = 850;
	_map1Portal.rc = RectMake(_map1Portal.x, _map1Portal.y, 200, 100);
	_map1Portal.gotoMap = 1;

	_portalVec.push_back(_map1Portal);

	_backBuffer = IMAGEMANAGER->findImage("backbuffer");

	return S_OK;
}

void lobbyMap::release(void)
{
	for (int i = 0; i < TILEX; i++)
	{
		for (int j = 0; j < TILEY; j++)
		{
			SAFE_DELETE(_lobbyTile[i][j]);
		}
	}
}

void lobbyMap::render(void)
{

	_bg->render(getMemDC(), cameraX, cameraY, cameraX, cameraY, WINSIZEX, WINSIZEY);

	for (int i = 0; i < TILEX; i++)
	{
		for (int j = 0; j < TILEY; j++)
		{
			_lobbyTile[i][j]->render();
		}
	}


	for (_iobjVec = _objVec.begin(); _iobjVec != _objVec.end(); ++_iobjVec)
	{
		if (_iobjVec->isFrameImage)
			putZorderVec(_iobjVec->image, _iobjVec->imageX, _iobjVec->imageY, _iobjVec->imageRc.bottom, _iobjVec->image->getFrameX(),
			_iobjVec->image->getFrameY());
		else putZorderVec(_iobjVec->image, _iobjVec->imageX, _iobjVec->imageY, _iobjVec->imageRc.bottom);
	}

	for (int i = 0; i < _portalVec.size(); i++)
	{
		putZorderVec(_portalVec[i].img, _portalVec[i].x, _portalVec[i].y, _portalVec[i].y);
		_portalIcon->render(getTempDC(), _portalVec[i].x + _portalIcon->getWidth() / 4,
			_portalVec[i].y + _portalIcon->getHeight() / 4);
	}
}