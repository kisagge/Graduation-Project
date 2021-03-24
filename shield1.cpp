#include "stdafx.h"
#include "shield1.h"


shield1::shield1()
{
}


shield1::~shield1()
{
}

HRESULT shield1::init(int x, int y)
{
	_iconImg = IMAGEMANAGER->findImage("����1");
	_iconX = x;
	_iconY = y;
	_iconRc = RectMake(_iconX, _iconY, _iconImg->getWidth(), _iconImg->getHeight());

	_desCripImg = IMAGEMANAGER->findImage("����1Ȯ��");
	_desX = _iconX;
	_desY = _iconY - _desCripImg->getHeight();
	_desRC = RectMake(_desX, _desY, _desCripImg->getWidth(), _desCripImg->getHeight());

	sprintf(_itemName, "���� ����");
	sprintf(_description, "������ ���� ����. �μ��� �� ����.");

	this->setInitValue();

	_weight = 10;

	_hpUp = 20;
	_dpUp = 5;

	_boughtPrice = 100;
	_sellPrice = _boughtPrice / 2;

	_itemkind = ITEM_SHIELD;
	_itemlist = ITEM_SHIELD_1;

	_itemInfoShow = IMAGEMANAGER->findImage("����������ǥ��");

	_requiredLv = 1;

	return S_OK;
}

void shield1::release(void)
{

}

void shield1::update(void)
{
	this->setItemWhere();
}

void shield1::render(void)
{

}