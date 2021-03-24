#include "stdafx.h"
#include "drill2.h"


drill2::drill2()
{
}


drill2::~drill2()
{
}

HRESULT drill2::init(int x, int y)
{
	_iconImg = IMAGEMANAGER->findImage("드릴2");
	_iconX = x;
	_iconY = y;
	_iconRc = RectMake(_iconX, _iconY, _iconImg->getWidth(), _iconImg->getHeight());

	_desCripImg = IMAGEMANAGER->findImage("드릴2확대");
	_desX = _iconX;
	_desY = _iconY - _desCripImg->getHeight();
	_desRC = RectMake(_desX, _desY, _desCripImg->getWidth(), _desCripImg->getHeight());

	sprintf(_itemName, "숙련자용 드릴");
	sprintf(_description, "드릴링 숙련자들이 사용하는 드릴이다.");

	this->setInitValue();

	_weight = 10;

	_daUp = 40;

	_boughtPrice = 1000;
	_sellPrice = _boughtPrice / 2;

	_itemkind = ITEM_DRILL;
	_itemlist = ITEM_DRILL_2;

	_itemInfoShow = IMAGEMANAGER->findImage("아이템정보표시");

	_requiredLv = 5;

	return S_OK;
}

void drill2::release(void)
{

}

void drill2::update(void)
{
	this->setItemWhere();
}

void drill2::render(void)
{

}