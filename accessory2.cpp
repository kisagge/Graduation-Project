#include "stdafx.h"
#include "accessory2.h"


accessory2::accessory2()
{
}


accessory2::~accessory2()
{
}

HRESULT accessory2::init(int x, int y)
{
	_iconImg = IMAGEMANAGER->findImage("악세2");
	_iconX = x;
	_iconY = y;
	_iconRc = RectMake(_iconX, _iconY, _iconImg->getWidth(), _iconImg->getHeight());

	_desCripImg = IMAGEMANAGER->findImage("악세2확대");
	_desX = _iconX;
	_desY = _iconY - _desCripImg->getHeight();
	_desRC = RectMake(_desX, _desY, _desCripImg->getWidth(), _desCripImg->getHeight());

	sprintf(_itemName, "붉은 보석");
	sprintf(_description, "붉은색 하트모양 보석. 매우 찬란하게 빛난다.");

	this->setInitValue();

	_weight = 10;

	_wtUp = 7;
	_lkUp = 10;
	_mpUp = 70;
	_hvUp = 10;

	_boughtPrice = 1000;
	_sellPrice = _boughtPrice / 2;

	_itemkind = ITEM_ACCESSORY;
	_itemlist = ITEM_ACCESSORY_2;

	_itemInfoShow = IMAGEMANAGER->findImage("아이템정보표시");

	_requiredLv = 5;

	return S_OK;
}

void accessory2::release(void)
{

}

void accessory2::update(void)
{
	this->setItemWhere();
}

void accessory2::render(void)
{

}