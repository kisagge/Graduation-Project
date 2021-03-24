#include "stdafx.h"
#include "weapon2.h"


weapon2::weapon2()
{
}


weapon2::~weapon2()
{
}

HRESULT weapon2::init(int x, int y)
{
	_iconImg = IMAGEMANAGER->findImage("����2");
	_iconX = x;
	_iconY = y;
	_iconRc = RectMake(_iconX, _iconY, _iconImg->getWidth(), _iconImg->getHeight());

	_desCripImg = IMAGEMANAGER->findImage("����2Ȯ��");
	_desX = _iconX;
	_desY = _iconY - _desCripImg->getHeight();
	_desRC = RectMake(_desX, _desY, _desCripImg->getWidth(), _desCripImg->getHeight());

	sprintf(_itemName, "�и�ġ");
	sprintf(_description, "�ո��� ���� �и�ġ��");

	this->setInitValue();

	_weight = 13;

	_apUp = 10;
	_acUp = 1.2;
	_dxUp = 5;

	_boughtPrice = 1000;
	_sellPrice = _boughtPrice / 2;

	_itemkind = ITEM_WEAPON;
	_itemlist = ITEM_WEAPON_2;

	_itemInfoShow = IMAGEMANAGER->findImage("����������ǥ��");

	_requiredLv = 5;

	return S_OK;
}

void weapon2::release(void)
{

}

void weapon2::update(void)
{
	this->setItemWhere();
}

void weapon2::render(void)
{

}