#pragma once
#include "singletonBase.h"

#include "accessory1.h"
#include "accessory2.h"
#include "accessory3.h"
#include "weapon1.h"
#include "weapon2.h"
#include "weapon3.h"
#include "shield1.h"
#include "shield2.h"
#include "shield3.h"
#include "drill1.h"
#include "drill2.h"
#include "drill3.h"
#include "helmet1.h"
#include "helmet2.h"
#include "helmet3.h"
#include "potion1.h"
#include "potion2.h"
#include "skill1Card.h"
#include "skill2Card.h"
#include "skill3Card.h"

class itemDb : public singletonBase <itemDb>
{
private:
	typedef map<string, ITEMLIST> itemList;
	typedef map<string, ITEMLIST>::iterator itemListIter;

private:
	itemList _itemList;			//������ ������ ������ ����Ʈ

public:
	//������DB �ʱ�ȭ
	HRESULT init(void);
	//������DB ����
	void release(void);

	//Ű������ ������ �߰�
	item* addItem(string strkey, ITEMLIST itemlist);

	//Ű������ ������ ã��
	item* findItem(string strkey);

	item* returnItemUsingEnum(ITEMLIST itemlist);

	//��ü ����
	BOOL deleteAll(void);

	itemDb();
	~itemDb();
};
