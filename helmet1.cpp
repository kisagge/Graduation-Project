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
	_iconImg = IMAGEMANAGER->findImage("����1");
	_iconX = x;
	_iconY = y;
	_iconRc = RectMake(_iconX, _iconY, _iconImg->getWidth(), _iconImg->getHeight());

	_desCripImg = IMAGEMANAGER->findImage("����1Ȯ��");
	_desX = _iconX;
	_desY = _iconY - _desCripImg->getHeight();
	_desRC = RectMake(_desX, _desY, _desCripImg->getWidth(), _desCripImg->getHeight());

	sprintf(_itemName, "���� ����");
	sprintf(_description, "������ ���� ����. �����ϴ�.");

	this->setInitValue();

	_weight = 5;

	_dxUp = 5;
	_dpUp = 10;
	_hvUp = 5;

	_boughtPrice = 100;
	_sellPrice = _boughtPrice / 2;

	_itemkind = ITEM_HAT;
	_itemlist = ITEM_HAT_1;

	_itemInfoShow = IMAGEMANAGER->findImage("����������ǥ��");

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
