#include "stdafx.h"
#include "enemyManager.h"
#include "mapManager.h"
#include "playerManager.h"

enemyManager::enemyManager()
{
}


enemyManager::~enemyManager()
{
}

HRESULT enemyManager::init(void)
{
	pushAddax();
	pushPochi();
	pushAddax();
	pushPochi();

	pushRequi();
	pushRequi();
	pushSphinx();

	return S_OK;
}

void enemyManager::release(void)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < _vEnemyMap[i].size(); j++)
		{
			_vEnemyMap[i].at(j)->release();
			SAFE_DELETE(_vEnemyMap[i].at(j));
		}
	}
}

void enemyManager::update(void)
{
	for (int i = 0; i < _vEnemyMap[(int)_mapManagerLink->getWhatMap()].size(); i++)
	{
		_vEnemyMap[_mapManagerLink->getWhatMap()][i]->update();
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < _vEnemyMap[i].size(); j++)
		{
			if (i == _mapManagerLink->getWhatMap()) continue;

			_vEnemyMap[i].at(j)->setIsFightOrNot(false);
			_vEnemyMap[i].at(j)->setState(IDLE);
		}
	}
	releaseMon();
	calculateMonSize();
}

void enemyManager::render(void)
{
	for (int i = 0; i < _vEnemyMap[(int)_mapManagerLink->getWhatMap()].size(); i++)
	{
		_vEnemyMap[(int)_mapManagerLink->getWhatMap()][i]->render();
	}
}

void enemyManager::pushFantaSlime(void)
{	
	enemy* _fts = new fantaSlime;
	_fts->init(RND->getFromIntTo(100, 1200),
		RND->getFromIntTo(100, 500));

	_vEnemyMap[0].push_back(_fts);
}

void enemyManager::pushAddax(void)
{
	enemy* add = new addax;
	add->init(RND->getFromIntTo(100, 1200),
		RND->getFromIntTo(100, 600));
	add->setPlayerManagerLink(_playerManagerLink);
	add->setWhatMap(1);

	_vEnemyMap[1].push_back(add);
}

void enemyManager::pushPochi(void)
{
	enemy* poc = new pochi;
	poc->init(RND->getFromIntTo(100, 1200),
		RND->getFromIntTo(100, 600));
	poc->setPlayerManagerLink(_playerManagerLink);
	poc->setWhatMap(1);

	_vEnemyMap[1].push_back(poc);
}

void enemyManager::pushRequi(void)
{
	enemy* req = new requi;
	req->init(RND->getFromIntTo(100, 1200),
		RND->getFromIntTo(100, 600));
	req->setPlayerManagerLink(_playerManagerLink);
	req->setWhatMap(2);

	_vEnemyMap[2].push_back(req);
}

void enemyManager::pushSphinx(void)
{
	enemy* sph = new sphinx;
	sph->init(RND->getFromIntTo(100, 1200),
		RND->getFromIntTo(100, 600));
	sph->setPlayerManagerLink(_playerManagerLink);
	sph->setWhatMap(2);

	_vEnemyMap[2].push_back(sph);
}

void enemyManager::releaseMon(void)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < _vEnemyMap[i].size(); j++)
		{
			if (_vEnemyMap[i].at(j)->getIsDead())
			{
				/*_playerManagerLink->getPlayer()->setLvExp(_playerManagerLink->getPlayer()->getLvExp()
					+ _vEnemyMap[i].at(j)->getExp());*/
				if (_playerManagerLink->getPlayer()->getInventorySize() < _playerManagerLink->getPlayer()->getInvenMaxSize())
				{
					item* temp = dropItem(99);
					if (temp != NULL)
						_playerManagerLink->getPlayer()->pushBackItem(temp);
				}
				_vEnemyMap[i].at(j)->release();
				_vEnemyMap[i].erase(_vEnemyMap[i].begin() + j);
				return;
			}
		}
	}
}

void enemyManager::calculateMonSize(void)
{
	int _addaxSize = 0;
	int _pochiSize = 0;
	int _requiSize = 0;
	int _sphinxSize = 0;
	for (int i = 1; i < 3; i++)
	{
		switch (i)
		{
		case 1:
			for (int j = 0; j < _vEnemyMap[1].size(); j++)
			{
				if (_vEnemyMap[1].at(j)->getEnemyList() == ENEMY_POCHI)
				{
					_pochiSize++;
				}
			}

			if (_pochiSize < POCHIMAX)
			{
				pushPochi();
				return;
			}

			for (int j = 0; j < _vEnemyMap[1].size(); j++)
			{
				if (_vEnemyMap[1].at(j)->getEnemyList() == ENEMY_ADDAX)
				{
					_addaxSize++;
				}
			}

			if (_addaxSize < ADDAXMAX)
			{
				pushAddax();
				return;
			}
			break;
		case 2:
			for (int j = 0; j < _vEnemyMap[2].size(); j++)
			{
				if (_vEnemyMap[2].at(j)->getEnemyList() == ENEMY_REQUI)
				{
					_requiSize++;
				}
			}

			if (_requiSize < REQUIMAX)
			{
				pushRequi();
				return;
			}

			for (int j = 0; j < _vEnemyMap[2].size(); j++)
			{
				if (_vEnemyMap[2].at(j)->getEnemyList() == ENEMY_SPHINX)
				{
					_sphinxSize++;
				}
			}

			if (_sphinxSize < SPHINXMAX)
			{
				pushSphinx();
				return;
			}
			break;
		}
	}
}

item* enemyManager::dropItem(int k)
{
	int l = RND->getFromIntTo(1, 100);

	if (k >= l)
	{
		int u = RND->getFromIntTo(1, 100);
		if (u <= 12) return ITEMDB->findItem("무기_1");
		else if (u <= 24) return ITEMDB->findItem("방패_1");
		else if (u <= 36) return ITEMDB->findItem("모자_1");
		else if (u <= 48) return ITEMDB->findItem("악세_1");
		else if (u <= 60) return ITEMDB->findItem("드릴_1");
		else if (u <= 67) return ITEMDB->findItem("무기_2");
		else if (u <= 74) return ITEMDB->findItem("방패_2");
		else if (u <= 81) return ITEMDB->findItem("모자_2");
		else if (u <= 88) return ITEMDB->findItem("악세_2");
		else if (u <= 95) return ITEMDB->findItem("드릴_2");
		else if (u <= 96) return ITEMDB->findItem("무기_3");
		else if (u <= 97) return ITEMDB->findItem("방패_3");
		else if (u <= 98) return ITEMDB->findItem("모자_3");
		else if (u <= 99) return ITEMDB->findItem("악세_3");
		else return ITEMDB->findItem("도릴_3");
	}
	else return NULL;
}
