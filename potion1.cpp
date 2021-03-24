#include "stdafx.h"
#include "potion1.h"


potion1::potion1()
{
}


potion1::~potion1()
{
}

HRESULT potion1::init(int x, int y)
{
	_iconImg = IMAGEMANAGER->findImage("포션1");
	_iconX = x;
	_iconY = y;
	_iconRc = RectMake(_iconX, _iconY, _iconImg->getWidth(), _iconImg->getHeight());

	_desCripImg = IMAGEMANAGER->findImage("포션1확대");
	_desX = _iconX;
	_desY = _iconY - _desCripImg->getHeight();
	_desRC = RectMake(_desX, _desY, _desCripImg->getWidth(), _desCripImg->getHeight());

	sprintf(_itemName, "빨간 포션");
	sprintf(_description, "빨간색 포션. 마시면 체력이 찬다.");

	this->setInitValue();

	_weight = 1;

	_hpUp = 150;

	_boughtPrice = 100;
	_sellPrice = _boughtPrice / 2;

	_itemkind = ITEM_SPEND;
	_itemlist = ITEM_SPEND_1;

	_itemInfoShow = IMAGEMANAGER->findImage("아이템정보표시");

	_requiredLv = 1;

	return S_OK;
}

void potion1::release(void)
{

}

void potion1::update(void)
{
	this->setItemWhere();
}

void potion1::render(void)
{

}