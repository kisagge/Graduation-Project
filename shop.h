#pragma once
#include "gameNode.h"
#include "item.h"

#define SHOWITEMNUM 8
#define SHOPINITX 200
#define SHOPINITY 200

class playerManager;

class shop : public gameNode
{
private:
	typedef vector<item*> sellList;
	typedef vector<item*>::iterator sellListIter;

private:
	image* _shopWindow;				//����â ������ �̹���
	image* _sellWindow;				//�Ǹ�â ������ �̹���
	image* _shopExitImage;			//���� ������ ��ư �̹���
	int _shopX, _shopY;				//����â x,y
	RECT _shopRect;					//����â ��ü ��Ʈ
	RECT _shopChangeButton[2];		//���� ���� ��ư
	RECT _shopUpDownButton[2];		//���� ��� ���Ʒ� ��ư
	RECT _buyButton;				//��ǰ ���� ��ư
	RECT _cancelButton;				//��ǰ �����Ǹ� ��� ��ư
	RECT _shopExitButton;			//���� �������ư ��Ʈ
	int _exitFrame;
	RECT _sellButton;				//��ǰ �ǸŹ�ư
	RECT _numDownButton[8];			//����, �Ǹ� ���� ���� ��ư��
	RECT _numUpButton[8];			//����, �Ǹ� ���� ���� ��ư��

	sellList _sellSpendList;			//�Ҹ� ������ �Ǹ� ��� ����Ʈ
	sellList _sellEquipList;			//��� ������ �Ǹ� ���

	sellList _buyList;		//���� ����Ʈ
	int* _buyEquipCheck;
	int* _buySpendCheck;
	sellList _soldList;		//�Ǹ��� ����Ʈ
	int* _soldCheck;

	int _showStart;
	int _showEnd;				//������ �������� ���۰� ��

	int _nowShopPage;			//�Ҹ�ǰ ��������, ����� ��������

	bool _shopOn;				//���� ���ȳ�

	playerManager* _playerManagerLink;

	float _btnDelay = 0.0f;

	float _sellBtnDelay = 0.0f;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//���� OnOff
	void shopOpenAndClose(void);

	//���� ������ ��ġ ����ֱ�
	void shopSettingWindow(void);

	//���� ������ ��ġ ����ֱ�
	void shopSetItemLocation(void);
	void shopEquipUpDoWn(void);
	void purchaseManagement(void);
	int returnMoneyPurchase(void);
	int returnWeightPurchase(void);
	void buyManagement(void);
	void sellManagement(void);
	void sellUpDown(void);

	//���� ���� ���� ó��
	void shopManageMent(void);

	//���� ����
	void shopRender(bool shopOn, int shopPage);
	void shopBuyShopRender(void);
	void shopSellShopRender(void);
	void shopEquipItemRender(void);
	void shopSpendItemRender(void);

	bool getShopOn(){ return _shopOn; }
	void setShopOn(bool k){ _shopOn = k; }
	
	RECT getShopRC(){ return _shopRect; }

	void setPlayerManagerLink(playerManager* k){ _playerManagerLink = k; }

	void clickSound()
	{
		if (SOUNDMANAGER->isPlaySound("âŬ��1"))
		{
			SOUNDMANAGER->stop("âŬ��1");
			SOUNDMANAGER->play("âŬ��1", 0.5f);
		}
		else SOUNDMANAGER->play("âŬ��1", 0.5f);
	}

	shop();
	~shop();
};

