#include "stdafx.h"
#include "accessory1.h"


accessory1::accessory1()
{
}


accessory1::~accessory1()
{
}

HRESULT accessory1::init(int x, int y)
{
	_iconImg = IMAGEMANAGER->findImage("¾Ç¼¼1");
	_iconX = x;
	_iconY = y;
	_iconRc = RectMake(_iconX, _iconY, _iconImg->getWidth(), _iconImg->getHeight());

	_desCripImg = IMAGEMANAGER->findImage("¾Ç¼¼1È®´ë");
	_desX = _iconX;
	_desY = _iconY - _desCripImg->getHeight();
	_desRC = RectMake(_desX, _desY, _desCripImg->getWidth(), _desCripImg->getHeight());

	sprintf(_itemName, "ÆÈÂî");
	sprintf(_description, "ÆÈÂî. µµ±Ý ÆÈÂî´Ù");

	this->setInitValue();

	_weight = 5;

	_wtUp = 5;
	_lkUp = 5;
	_mpUp = 30;
	_hvUp = 5;

	_boughtPrice = 100;
	_sellPrice = _boughtPrice / 2;

	_itemkind = ITEM_ACCESSORY;
	_itemlist = ITEM_ACCESSORY_1;

	_itemInfoShow = IMAGEMANAGER->findImage("¾ÆÀÌÅÛÁ¤º¸Ç¥½Ã");

	_requiredLv = 1;

	return S_OK;
}

void accessory1::release(void)
{

}

void accessory1::update(void)
{
	this->setItemWhere();
}

void accessory1::render(void)
{

}