#include "stdafx.h"
#include "helmet3.h"


helmet3::helmet3()
{
}


helmet3::~helmet3()
{
}

HRESULT helmet3::init(int x, int y)
{
	_iconImg = IMAGEMANAGER->findImage("����3");
	_iconX = x;
	_iconY = y;
	_iconRc = RectMake(_iconX, _iconY, _iconImg->getWidth(), _iconImg->getHeight());

	_desCripImg = IMAGEMANAGER->findImage("����3Ȯ��");
	_desX = _iconX;
	_desY = _iconY - _desCripImg->getHeight();
	_desRC = RectMake(_desX, _desY, _desCripImg->getWidth(), _desCripImg->getHeight());

	sprintf(_itemName, "��Ÿ ����");
	sprintf(_description, "�Ϳ��� ��Ÿ����. �ſ� �Ϳ���.");

	this->setInitValue();

	_weight = 15;

	_dxUp = 20;
	_dpUp = 50;
	_hvUp = 13;

	_boughtPrice = 5000;
	_sellPrice = _boughtPrice / 2;

	_itemkind = ITEM_HAT;
	_itemlist = ITEM_HAT_3;

	_itemInfoShow = IMAGEMANAGER->findImage("����������ǥ��");

	_requiredLv = 10;

	return S_OK;
}

void helmet3::release(void)
{

}

void helmet3::update(void)
{
	this->setItemWhere();
}

void helmet3::render(void)
{

}