#include "stdafx.h"
#include "mapManager.h"
#include "playerManager.h"

mapManager::mapManager()
{
}


mapManager::~mapManager()
{
}

HRESULT mapManager::init(void)
{
	_lb = new lobbyMap;
	_lb->init();

	_ftM = new firstMap;
	_ftM->init();

	_bsM = new secondMap;
	_bsM->init();

	_mapVec.push_back(_lb);
	_whatMap = 0;

	_changeSceneList[0] = IMAGEMANAGER->findImage("½ÃÀÛ");
	_changeSceneList[1] = IMAGEMANAGER->findImage("·Îµù2");
	_changeSceneList[2] = IMAGEMANAGER->findImage("·Îµù3");

	_changeSceneCount = 255.0f;
	_isChangeScene = false;

	return S_OK;
}

void mapManager::release(void)
{
	_lb->release();
	SAFE_DELETE(_lb);

	_ftM->release();
	SAFE_DELETE(_ftM);

	_bsM->release();
	SAFE_DELETE(_bsM);

	_mapVec.clear();
}

void mapManager::update(void)
{
	_mapVec[0]->update();
	collisionPortal();

	if (_changeSceneCount > 0)
	{
		_changeSceneCount -= 3.0f;
	}
	else _changeSceneCount = 0.0f;
}

void mapManager::render(void)
{
	_mapVec[0]->render();
}

void mapManager::changeMap(int k)
{
	_mapVec.clear();

	switch (k)
	{
	case 0:
		_mapVec.push_back(_lb);
		_whatMap = 0;

		_changeSceneCount = 255.0f;
		SOUNDMANAGER->stop("»ç³É¸Ê");
		SOUNDMANAGER->stop("º¸½º¸Ê");
		SOUNDMANAGER->soundFadeIn("·Îºñ¸Ê", 0.5f);
		break;
	case 1:
		_mapVec.push_back(_ftM);
		_whatMap = 1;

		_changeSceneCount = 255.0f;
		SOUNDMANAGER->stop("·Îºñ¸Ê");
		SOUNDMANAGER->stop("º¸½º¸Ê");
		SOUNDMANAGER->soundFadeIn("»ç³É¸Ê", 0.5f);
		break;
	case 2:
		_mapVec.push_back(_bsM);
		_whatMap = 2;

		_changeSceneCount = 255.0f;
		SOUNDMANAGER->stop("·Îºñ¸Ê");
		SOUNDMANAGER->stop("»ç³É¸Ê");
		SOUNDMANAGER->soundFadeIn("º¸½º¸Ê", 0.5f);
		break;
	default:
		break;
	}
}

void mapManager::collisionPortal(void)
{
	RECT temp;
	for (int i = 0; i < _mapVec[0]->getPortalVec().size(); i++)
	{
		if (IntersectRect(&temp, &_mapVec[0]->getPortalVec()[i].rc, &_playerManagerLink->getPlayer()->getMoveRc()))
		{
			if (_whatMap == 0 && _mapVec[0]->getPortalVec()[i].gotoMap == 1)
			{
				_playerManagerLink->getPlayer()->setX(950);
				_playerManagerLink->getPlayer()->setY(200);
				_playerManagerLink->getPlayer()->setState(UNMOVING);
				this->changeMap(1);
			}
			else if (_whatMap == 1 && _mapVec[0]->getPortalVec()[i].gotoMap == 0)
			{
				_playerManagerLink->getPlayer()->setX(900);
				_playerManagerLink->getPlayer()->setY(800);
				_playerManagerLink->getPlayer()->setState(UNMOVING);
				this->changeMap(0);
			}
			else if (_whatMap == 1 && _playerManagerLink->getPlayer()->getX() > 850 && _playerManagerLink->getPlayer()->getX() < 1050
				&& _playerManagerLink->getPlayer()->getY() > 850 && _playerManagerLink->getPlayer()->getY() < 950)
			{
				_playerManagerLink->getPlayer()->setX(900);
				_playerManagerLink->getPlayer()->setY(200);
				_playerManagerLink->getPlayer()->setState(UNMOVING);
				this->changeMap(2);
			}
			else if (_whatMap == 2 && _mapVec[0]->getPortalVec()[i].gotoMap == 1)
			{
				_playerManagerLink->getPlayer()->setX(950);
				_playerManagerLink->getPlayer()->setY(800);
				_playerManagerLink->getPlayer()->setState(UNMOVING);
				this->changeMap(1);
			}
		}
	}
}