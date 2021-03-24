#include "stdafx.h"
#include "itemDb.h"


itemDb::itemDb()
{
}


itemDb::~itemDb()
{
}

//아이템DB 초기화
HRESULT itemDb::init(void)
{
	return S_OK;
}

//아이템DB 해제
void itemDb::release(void)
{
	deleteAll();
}

//키값으로 아이템 추가
item* itemDb::addItem(string strkey, ITEMLIST itemlist)
{
	item* it = findItem(strkey);

	if (it) return it;

	it = returnItemUsingEnum(itemlist);

	if (FAILED(it->init(0,0)))
	{
		SAFE_DELETE(it);
		return NULL;
	}

	_itemList.insert(make_pair(strkey, itemlist));

	return it;
}

//키값으로 아이템 찾기
item* itemDb::findItem(string strkey)
{
	itemListIter key = _itemList.find(strkey);

	if (key != _itemList.end())
	{
		return returnItemUsingEnum(key->second);
	}

	return NULL;
}

item* itemDb::returnItemUsingEnum(ITEMLIST itemlist)
{
	item* temp;
	switch (itemlist)
	{
	case ITEM_WEAPON_1:
		temp = new weapon1;
		break;
	case ITEM_WEAPON_2:
		temp = new weapon2;
		break;
	case ITEM_WEAPON_3:
		temp = new weapon3;
		break;
	case ITEM_HAT_1:
		temp = new helmet1;
		break;
	case ITEM_HAT_2:
		temp = new helmet2;
		break;
	case ITEM_HAT_3:
		temp = new helmet3;
		break;
	case ITEM_SHIELD_1:
		temp = new shield1;
		break;
	case ITEM_SHIELD_2:
		temp = new shield2;
		break;
	case ITEM_SHIELD_3:
		temp = new shield3;
		break;
	case ITEM_ACCESSORY_1:
		temp = new accessory1;
		break;
	case ITEM_ACCESSORY_2:
		temp = new accessory2;
		break;
	case ITEM_ACCESSORY_3:
		temp = new accessory3;
		break;
	case ITEM_DRILL_1:
		temp = new drill1;
		break;
	case ITEM_DRILL_2:
		temp = new drill2;
		break;
	case ITEM_DRILL_3:
		temp = new drill3;
		break;
	case ITEM_SPEND_1:
		temp = new potion1;
		break;
	case ITEM_SPEND_2:
		temp = new potion2;
		break;
	case ITEM_SKILLCARD_1:
		temp = new skill1Card;
		break;
	case ITEM_SKILLCARD_2:
		temp = new skill2Card;
		break;
	case ITEM_SKILLCARD_3:
		temp = new skill3Card;
		break;
	}

	temp->init(0, 0);
	
	return temp;
}

BOOL itemDb::deleteAll(void)
{
	_itemList.clear();

	return TRUE;
}