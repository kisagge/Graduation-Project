#include "stdafx.h"
#include "drill3.h"


drill3::drill3()
{
}


drill3::~drill3()
{
}

HRESULT drill3::init(int x, int y)
{
	_iconImg = IMAGEMANAGER->findImage("드릴3");
	_iconX = x;
	_iconY = y;
	_iconRc = RectMake(_iconX, _iconY, _iconImg->getWidth(), _iconImg->getHeight());

	_desCripImg = IMAGEMANAGER->findImage("드릴3확대");
	_desX = _iconX;
	_desY = _iconY - _desCripImg->getHeight();
	_desRC = RectMake(_desX, _desY, _desCripImg->getWidth(), _desCripImg->getHeight());

	sprintf(_itemName, "고대 유적의 드릴");
	sprintf(_description, "고대 유적에서 발견된 마력이 깃든 드릴");

	this->setInitValue();

	_weight = 15;

	_daUp = 90;

	_boughtPrice = 5000;
	_sellPrice = _boughtPrice / 2;

	_itemkind = ITEM_DRILL;
	_itemlist = ITEM_DRILL_3;

	_itemInfoShow = IMAGEMANAGER->findImage("아이템정보표시");

	_requiredLv = 10;

	return S_OK;
}

void drill3::release(void)
{

}

void drill3::update(void)
{
	this->setItemWhere();
}

void drill3::render(void)
{

}