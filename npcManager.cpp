#include "stdafx.h"
#include "npcManager.h"
#include "mapManager.h"
#include "playerManager.h"

npcManager::npcManager()
{
}


npcManager::~npcManager()
{
}

HRESULT npcManager::init(void)
{
	//·Îºñ¸Ê npc Ãß°¡
	npcClass* assHun = new assistantHunter;
	assHun->init();
	_npcVec[0].push_back(assHun);

	npcClass* offRob = new officerRobert;
	offRob->init();
	_npcVec[0].push_back(offRob);

	npcClass* hunYu = new hunterYuri;
	hunYu->init();
	_npcVec[0].push_back(hunYu);

	npcClass* hunYuna = new hunterYuna;
	hunYuna->init();
	_npcVec[0].push_back(hunYuna);

	npcClass* port = new portina;
	port->init();
	_npcVec[0].push_back(port);

	npcClass* and = new andrew;
	and->init();
	_npcVec[0].push_back(and);

	//»ç³É¸Ê npc Ãß°¡
	npcClass* lou = new louis;
	lou->init();
	_npcVec[1].push_back(lou);

	//º¸½º¸Ê npc Ãß°¡
	npcClass* dev = new developer;
	dev->init();
	_npcVec[2].push_back(dev);


	return S_OK;
}

void npcManager::release(void)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < _npcVec[i].size(); j++)
		{
			_npcVec[i][j]->release();
			SAFE_DELETE(_npcVec[i][j]);
		}
	}
}

void npcManager::update(void)
{
	switch (_mapManagerLink->getWhatMap())
	{
	case 0:
		for (int i = 0; i < _npcVec[0].size(); i++)
		{
			_npcVec[0][i]->update();
		}
		break;
	case 1:
		for (int i = 0; i < _npcVec[1].size(); i++)
		{
			_npcVec[1][i]->update();
		}
		break;
	case 2:
		for (int i = 0; i < _npcVec[2].size(); i++)
		{
			_npcVec[2][i]->update();
		}
		break;
	}
}

void npcManager::render(void)
{
	RECT temp;
	switch (_mapManagerLink->getWhatMap())
	{
	case 0:
		for (int i = 0; i < _npcVec[0].size(); i++)
		{
			_npcVec[0][i]->render();

			_npcIcon->render(getTempDC(), _npcVec[0][i]->getX() + _npcVec[0][i]->getImage()
				->getFrameWidth() / 2, _npcVec[0][i]->getY() + _npcVec[0][i]->getImage()->getFrameHeight() / 2);
		}
		break;
	case 1:
		for (int i = 0; i < _npcVec[1].size(); i++)
		{
			_npcVec[1][i]->render();

			_npcIcon->render(getTempDC(), _npcVec[1][i]->getX() + _npcVec[1][i]->getImage()
				->getFrameWidth() / 2, _npcVec[1][i]->getY() + _npcVec[1][i]->getImage()->getFrameHeight() / 2);
		}
		break;
	case 2:
		for (int i = 0; i < _npcVec[2].size(); i++)
		{
			_npcVec[2][i]->render();

			_npcIcon->render(getTempDC(), _npcVec[2][i]->getX() + _npcVec[2][i]->getImage()
				->getFrameWidth() / 2, _npcVec[2][i]->getY() + _npcVec[2][i]->getImage()->getFrameHeight() / 2);
		}
		break;
	}
}