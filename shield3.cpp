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
	_iconImg = IMAGEMANAGER->findImage("����3");
	_iconX = x;
	_iconY = y;
	_iconRc = RectMake(_iconX, _iconY, _iconImg->getWidth(), _iconImg->getHeight());

	_desCripImg = IMAGEMANAGER->findImage("����3Ȯ��");
	_desX = _iconX;
	_desY = _iconY - _desCripImg->getHeight();
	_desRC = RectMake(_desX, _desY, _desCripImg->getWidth(), _desCripImg->getHeight());

	sprintf(_itemName, "������ ����");
	sprintf(_description, "������ ��ó�� ���� �Ϳ��� ����.");

	this->setInitValue();

	_weight = 30;

	_hpUp = 150;
	_dpUp = 50;

	_boughtPrice = 5000;
	_sellPrice = _boughtPrice / 2;

	_itemkind = ITEM_SHIELD;
	_itemlist = ITEM_SHIELD_3;

	_itemInfoShow = IMAGEMANAGER->findImage("����������ǥ��");

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