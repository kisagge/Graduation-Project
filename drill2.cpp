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
	_iconImg = IMAGEMANAGER->findImage("�帱2");
	_iconX = x;
	_iconY = y;
	_iconRc = RectMake(_iconX, _iconY, _iconImg->getWidth(), _iconImg->getHeight());

	_desCripImg = IMAGEMANAGER->findImage("�帱2Ȯ��");
	_desX = _iconX;
	_desY = _iconY - _desCripImg->getHeight();
	_desRC = RectMake(_desX, _desY, _desCripImg->getWidth(), _desCripImg->getHeight());

	sprintf(_itemName, "�����ڿ� �帱");
	sprintf(_description, "�帱�� �����ڵ��� ����ϴ� �帱�̴�.");

	this->setInitValue();

	_weight = 10;

	_daUp = 40;

	_boughtPrice = 1000;
	_sellPrice = _boughtPrice / 2;

	_itemkind = ITEM_DRILL;
	_itemlist = ITEM_DRILL_2;

	_itemInfoShow = IMAGEMANAGER->findImage("����������ǥ��");

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