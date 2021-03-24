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
	image* _shopWindow;				//구매창 윈도우 이미지
	image* _sellWindow;				//판매창 윈도우 이미지
	image* _shopExitImage;			//상점 나가기 버튼 이미지
	int _shopX, _shopY;				//상점창 x,y
	RECT _shopRect;					//상점창 전체 렉트
	RECT _shopChangeButton[2];		//상점 구분 버튼
	RECT _shopUpDownButton[2];		//상점 목록 위아래 버튼
	RECT _buyButton;				//물품 구매 버튼
	RECT _cancelButton;				//물품 구매판매 취소 버튼
	RECT _shopExitButton;			//상점 나가기버튼 렉트
	int _exitFrame;
	RECT _sellButton;				//물품 판매버튼
	RECT _numDownButton[8];			//구매, 판매 수량 감소 버튼들
	RECT _numUpButton[8];			//구매, 판매 수량 증가 버튼들

	sellList _sellSpendList;			//소모 아이템 판매 목록 리스트
	sellList _sellEquipList;			//장비 아이템 판매 목록

	sellList _buyList;		//구매 리스트
	int* _buyEquipCheck;
	int* _buySpendCheck;
	sellList _soldList;		//판매할 리스트
	int* _soldCheck;

	int _showStart;
	int _showEnd;				//아이템 보여지는 시작과 끝

	int _nowShopPage;			//소모품 페이지냐, 장비템 페이지냐

	bool _shopOn;				//상점 열렸냐

	playerManager* _playerManagerLink;

	float _btnDelay = 0.0f;

	float _sellBtnDelay = 0.0f;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//상점 OnOff
	void shopOpenAndClose(void);

	//상점 윈도우 위치 잡아주기
	void shopSettingWindow(void);

	//상점 아이템 위치 잡아주기
	void shopSetItemLocation(void);
	void shopEquipUpDoWn(void);
	void purchaseManagement(void);
	int returnMoneyPurchase(void);
	int returnWeightPurchase(void);
	void buyManagement(void);
	void sellManagement(void);
	void sellUpDown(void);

	//상점 구입 관련 처리
	void shopManageMent(void);

	//상점 렌더
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
		if (SOUNDMANAGER->isPlaySound("창클릭1"))
		{
			SOUNDMANAGER->stop("창클릭1");
			SOUNDMANAGER->play("창클릭1", 0.5f);
		}
		else SOUNDMANAGER->play("창클릭1", 0.5f);
	}

	shop();
	~shop();
};

