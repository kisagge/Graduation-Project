#include "stdafx.h"
#include "weapon3.h"


weapon3::weapon3()
{
}


weapon3::~weapon3()
{
}

HRESULT weapon3::init(int x, int y)
{
	_iconImg = IMAGEMANAGER->findImage("����3");
	_iconX = x;
	_iconY = y;
	_iconRc = RectMake(_iconX, _iconY, _iconImg->getWidth(), _iconImg->getHeight());

	_desCripImg = IMAGEMANAGER->findImage("����3Ȯ��");
	_desX = _iconX;
	_desY = _iconY - _desCripImg->getHeight();
	_desRC = RectMake(_desX, _desY, _desCripImg->getWidth(), _desCripImg->getHeight());

	sprintf(_itemName, "������");
	sprintf(_description, "���־� ���̴� ������.");

	this->setInitValue();

	_weight = 15;

	_apUp = 20;
	_acUp = 4.0f;
	_dxUp = 8;

	_boughtPrice = 5000;
	_sellPrice = _boughtPrice / 2;

	_itemkind = ITEM_WEAPON;
	_itemlist = ITEM_WEAPON_3;

	_itemInfoShow = IMAGEMANAGER->findImage("����������ǥ��");

	_requiredLv = 10;

	return S_OK;
}

void weapon3::release(void)
{

}

void weapon3::update(void)
{
	this->setItemWhere();
}

void weapon3::render(void)
{

}