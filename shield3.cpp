#include "stdafx.h"
#include "shield3.h"


shield3::shield3()
{
}


shield3::~shield3()
{
}

HRESULT shield3::init(int x, int y)
{
	_iconImg = IMAGEMANAGER->findImage("방패3");
	_iconX = x;
	_iconY = y;
	_iconRc = RectMake(_iconX, _iconY, _iconImg->getWidth(), _iconImg->getHeight());

	_desCripImg = IMAGEMANAGER->findImage("방패3확대");
	_desX = _iconX;
	_desY = _iconY - _desCripImg->getHeight();
	_desRC = RectMake(_desX, _desY, _desCripImg->getWidth(), _desCripImg->getHeight());

	sprintf(_itemName, "곰돌이 방패");
	sprintf(_description, "곰돌이 얼굴처럼 생긴 귀여운 방패.");

	this->setInitValue();

	_weight = 30;

	_hpUp = 150;
	_dpUp = 50;

	_boughtPrice = 5000;
	_sellPrice = _boughtPrice / 2;

	_itemkind = ITEM_SHIELD;
	_itemlist = ITEM_SHIELD_3;

	_itemInfoShow = IMAGEMANAGER->findImage("아이템정보표시");

	_requiredLv = 10;

	return S_OK;
}

void shield3::release(void)
{

}

void shield3::update(void)
{
	this->setItemWhere();
}

void shield3::render(void)
{

}