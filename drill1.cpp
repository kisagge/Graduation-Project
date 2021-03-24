#include "stdafx.h"
#include "drill1.h"


drill1::drill1()
{
}


drill1::~drill1()
{
}

HRESULT drill1::init(int x, int y)
{
	_iconImg = IMAGEMANAGER->findImage("�帱1");
	_iconX = x;
	_iconY = y;
	_iconRc = RectMake(_iconX, _iconY, _iconImg->getWidth(), _iconImg->getHeight());

	_desCripImg = IMAGEMANAGER->findImage("�帱1Ȯ��");
	_desX = _iconX;
	_desY = _iconY - _desCripImg->getHeight();
	_desRC = RectMake(_desX, _desY, _desCripImg->getWidth(), _desCripImg->getHeight());

	sprintf(_itemName, "�߽��� �帱");
	sprintf(_description, "��ǰ���� �帱�̴�.");

	this->setInitValue();

	_weight = 5;

	_daUp = 20;

	_boughtPrice = 100;
	_sellPrice = _boughtPrice / 2;

	_itemkind = ITEM_DRILL;
	_itemlist = ITEM_DRILL_1;

	_itemInfoShow = IMAGEMANAGER->findImage("����������ǥ��");

	_requiredLv = 1;

	return S_OK;
}

void drill1::release(void)
{

}

void drill1::update(void)
{
	this->setItemWhere();
}

void drill1::render(void)
{

}