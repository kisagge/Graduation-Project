#include "stdafx.h"
#include "secondMap.h"
#include "playerManager.h"

secondMap::secondMap()
{
}


secondMap::~secondMap()
{
}

HRESULT secondMap::init(void)
{
	_bg = IMAGEMANAGER->findImage("º¸½º¸Ê");

	for (int i = 0; i < TILEX; i++)
	{
		for (int j = 0; j < TILEY; j++)
		{
			_lobbyTile[i][j] = new tile;
			_lobbyTile[i][j]->init(i, j);
		}
	}

	this->addObj("¹ÚÁã¼º", 26, 2, 26, 9, 6, 3, 1);

	tagPortal _map1Portal;
	_map1Portal.img = IMAGEMANAGER->findImage("Æ÷Å»");
	_map1Portal.x = 850;
	_map1Portal.y = 50;
	_map1Portal.rc = RectMake(_map1Portal.x, _map1Portal.y, 200, 100);
	_map1Portal.gotoMap = 1;
	_portalVec.push_back(_map1Portal);

	return S_OK;
}

void secondMap::release(void)
{
	for (int i = 0; i < TILEX; i++)
	{
		for (int j = 0; j < TILEY; j++)
		{
			SAFE_DELETE(_lobbyTile[i][j]);
		}
	}
}

void secondMap::render(void)
{
	_backBuffer = IMAGEMANAGER->addImage("backbuffer", _bg->getWidth(), _bg->getHeight());

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