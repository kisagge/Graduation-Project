#include "stdafx.h"
#include "helmet1.h"


helmet1::helmet1()
{
}


helmet1::~helmet1()
{
}

HRESULT helmet1::init(int x, int y)
{
	_iconImg = IMAGEMANAGER->findImage("모자1");
	_iconX = x;
	_iconY = y;
	_iconRc = RectMake(_iconX, _iconY, _iconImg->getWidth(), _iconImg->getHeight());

	_desCripImg = IMAGEMANAGER->findImage("모자1확대");
	_desX = _iconX;
	_desY = _iconY - _desCripImg->getHeight();
	_desRC = RectMake(_desX, _desY, _desCripImg->getWidth(), _desCripImg->getHeight());

	sprintf(_itemName, "나무 투구");
	sprintf(_description, "나무로 만든 투구. 불편하다.");

	this->setInitValue();

	_weight = 5;

	_dxUp = 5;
	_dpUp = 10;
	_hvUp = 5;

	_boughtPrice = 100;
	_sellPrice = _boughtPrice / 2;

	_itemkind = ITEM_HAT;
	_itemlist = ITEM_HAT_1;

	_itemInfoShow = IMAGEMANAGER->findImage("아이템정보표시");

	_requiredLv = 1;

	return S_OK;
}

void helmet1::release(void)
{

}

void helmet1::update(void)
{
	this->setItemWhere();
}

void helmet1::render(void)
{

}
