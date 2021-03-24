#include "stdafx.h"
#include "firstMap.h"
#include "playerManager.h"

firstMap::firstMap()
{
}


firstMap::~firstMap()
{
}

HRESULT firstMap::init(void)
{
	_bg = IMAGEMANAGER->findImage("사냥맵");

	for (int i = 0; i < TILEX; i++)
	{
		for (int j = 0; j < TILEY; j++)
		{
			_lobbyTile[i][j] = new tile;
			_lobbyTile[i][j]->init(i, j);
		}
	}

	this->addObj("나무집", 32, 5, 32, 8, 4, 2, 0);
	this->addObj("캐슬", 5, 6, 5, 9, 3, 2, 0);
	this->addObj("나무1", -1, -1, 1, 3, 2, 2, 1);
	this->addObj("나무1", -1, 2, 1, 6, 2, 2, 1);
	this->addObj("나무1", -1, 5, 1, 9, 2, 2, 1);
	this->addObj("나무1", -1, 12, 1, 16, 2, 2, 1);
	this->addObj("나무1", -1, 15, 1, 19, 2, 2, 1);
	this->addObj("나무1", 3, -1, 5, 3, 2, 2, 1);
	this->addObj("나무1", 7, -1, 9, 3, 2, 2, 1);
	this->addObj("나무1", 11, -1, 13, 3, 2, 2, 1);
	this->addObj("나무1", 23, -1, 25, 3, 2, 2, 1);
	this->addObj("나무1", 27, -1, 29, 3, 2, 2, 1);
	this->addObj("나무1", 31, -1, 33, 3, 2, 2, 1);
	this->addObj("나무1", 35, -1, 37, 3, 2, 2, 1);
	this->addObj("나뭇잎더미", 25, 15, 25, 15, 6, 4, 0);

	tagPortal _map1Portal;
	_map1Portal.img = IMAGEMANAGER->findImage("포탈");
	_map1Portal.x = 850;
	_map1Portal.y = 50;
	_map1Portal.rc = RectMake(_map1Portal.x, _map1Portal.y, 200, 100);
	_map1Portal.gotoMap = 0;
	_portalVec.push_back(_map1Portal);

	_map1Portal.x = 850;
	_map1Portal.y = 850;
	_map1Portal.rc = RectMake(_map1Portal.x, _map1Portal.y, 200, 100);
	_map1Portal.gotoMap = 2;
	_portalVec.push_back(_map1Portal);

	return S_OK;
}

void firstMap::release(void)
{
	for (int i = 0; i < TILEX; i++)
	{
		for (int j = 0; j < TILEY; j++)
		{
			SAFE_DELETE(_lobbyTile[i][j]);
		}
	}
}


void firstMap::render(void)
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