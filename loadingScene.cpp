#include "stdafx.h"
#include "loadingScene.h"

loadingScene::loadingScene()
{
}

loadingScene::~loadingScene()
{
}

HRESULT loadingScene::init(void)
{
	//로딩 클래스 초기화
	_loading = new loading;
	_loading->init();
	//이미지 로딩하자
	this->loadingImage();
	//사운드 로딩하자
	this->loadingSound();

	return S_OK;
}

void loadingScene::release(void)
{
	SAFE_DELETE(_loading);
}

void loadingScene::update(void)
{
	_loading->update();

	//로딩 완료 후 씬 전환
	if (_loading->loadingDone())
	{
		SOUNDMANAGER->play("기본브금", 0.35f);
		_sceneType = TITLE;
	}
}

void loadingScene::render(void)
{
	_loading->render();
}

//로딩 이미지 함수(이곳에 로딩 이미지를 전부 넣어라!)
void loadingScene::loadingImage()
{
	//_loading->loadImage();

	//배경화면
	IMAGEMANAGER->addImage("시작", "images/로딩.bmp", WINSIZEX, WINSIZEY);
	IMAGEMANAGER->addImage("로비맵", "images/lobbyMap/lobbyMap.bmp", 1920, 960, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("소라집", "images/lobbyMap/shellObj.bmp", 48 * 5, 48 * 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("캠프1", "images/lobbyMap/camp1.bmp", 48 * 4, 48 * 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("피라미드", "images/lobbyMap/phyramid.bmp", 48 * 6, 48 * 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("잠수함", "images/lobbyMap/ship.bmp", 48 * 4, 48 * 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("캔디집", "images/lobbyMap/candyHouse.bmp", 48 * 5, 48 * 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("캠프파이어", "images/lobbyMap/fire.bmp", 48 * 12, 48 * 3, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("소라집2", "images/lobbyMap/shellHouse.bmp", 48 * 4, 48 * 5, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("사냥맵", "images/firstMap/firstMap.bmp", 1920, 960, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("캐슬", "images/firstMap/castle.bmp", 48 * 3, 48 * 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("나무집", "images/firstMap/treeHouse.bmp", 48 * 4, 48 * 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("나무1", "images/firstMap/tree1.bmp", 48 * 6 * 8, 48 * 6, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("나뭇잎더미", "images/firstMap/나뭇잎더미.bmp", 48 * 6, 48 * 4, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("보스맵", "images/secondMap/secondMap.bmp", 1920, 960, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("박쥐성", "images/secondMap/batCastle.bmp", 48 * 18, 48 * 10, 3, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("npc표시", "images/UI/npcDot.bmp", 100, 75, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("플레이어표시", "images/UI/playerDot.bmp", 160, 120, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("포탈표시", "images/UI/portalDot.bmp", 100, 75, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("메세지박스", "images/UI/messageBox.bmp", 250, 200, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("포탈", "images/UI/portal.bmp", 200, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("폰트1", "images/UI/numeric1.bmp", 192, 14, 12, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("폰트2", "images/UI/numeric2.bmp", 180, 24, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("폰트3", "images/ui/numeric3.bmp", 140, 18, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("폰트4", "images/ui/numeric4.bmp", 180, 24, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("폰트5", "images/ui/numeric5.bmp", 160, 20, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("폰트6", "images/ui/numeric6.bmp", 130, 16, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("폰트7", "images/ui/numeric7.bmp", 120, 15, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("메뉴바", "images/UI/menuBar.bmp", 473, 23, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("스킬윗버튼", "images/UI/skillButton.bmp", 40, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("카드윗버튼", "images/UI/cardButton.bmp", 40, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("아이템윗버튼", "images/UI/itemButton.bmp", 40, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("장비윗버튼", "images/UI/equipButton.bmp", 40, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("정보윗버튼", "images/UI/myviewButton.bmp", 40, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("퀘스트윗버튼", "images/UI/questButton.bmp", 40, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("길드윗버튼", "images/UI/guildButton.bmp", 40, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("친구윗버튼", "images/UI/friendButton.bmp", 40, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("스킬아이콘", "images/UI/skillIcon.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("카드아이콘", "images/ui/cardIcon.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("아이템아이콘", "images/ui/itemIcon.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("장비아이콘", "images/ui/equipIcon.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("퀘스트아이콘", "images/ui/questIcon.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("정보아이콘", "images/ui/myviewIcon.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("길드아이콘", "images/ui/guildIcon.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("친구아이콘", "images/ui/friendIcon.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("돈표시", "images/ui/moneySign.bmp", 12, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("무게표시", "images/ui/weightIcon.bmp", 11, 11, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("스킬퀵슬롯", "images/ui/skillQuickUi.bmp", 96, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("스킬1아이콘", "images/ui/skill1Icon.bmp", 26, 26, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("스킬2아이콘", "images/ui/skill2Icon.bmp", 26, 26, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("스킬3아이콘", "images/ui/skill3Icon.bmp", 26, 26, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("미스", "images/ui/miss.bmp", 43, 12, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("치명타뒷배경", "images/ui/crit.bmp", 54, 49, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("메뉴버튼배경", "images/ui/menuButton.bmp", 40, 40);
	IMAGEMANAGER->addFrameImage("마우스커서", "images/ui/cursor.bmp", 45, 374, 1, 11, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("캐릭터OK", "images/ui/selectOK.bmp", 53, 75, 1, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("캐릭터back", "images/ui/selectBack.bmp", 53, 75, 1, 3, true, RGB(255, 0, 255));

	//플레이어
	IMAGEMANAGER->addFrameImage("기본", "images/character/chaIdle.bmp", 412.8, 88, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("걷기0", "images/character/chaWalk0.bmp", 344, 84, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("걷기1", "images/character/chaWalk1.bmp", 353, 89, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("걷기2", "images/character/chaWalk2.bmp", 288, 88, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("걷기3", "images/character/chaWalk3.bmp", 353, 89, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("걷기4", "images/character/chaWalk4.bmp", 344, 84, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("걷기5", "images/character/chaWalk5.bmp", 288, 88, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("걷기6", "images/character/chaWalk6.bmp", 302, 85, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("걷기7", "images/character/chaWalk7.bmp", 288, 88, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("특수", "images/character/chaSpecial.bmp", 994, 86, 12, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("공격대기0", "images/character/chaAttackIdle0.bmp", 480, 85, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("공격대기1", "images/character/chaAttackIdle1.bmp", 480, 85, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("공격대기2", "images/character/chaAttackIdle2.bmp", 456, 85, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("공격대기3", "images/character/chaAttackIdle3.bmp", 456, 85, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("공격0", "images/character/chaAttack0.bmp", 504, 86, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("공격1", "images/character/chaAttack1.bmp", 504, 86, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("공격2", "images/character/chaAttack2.bmp", 504, 86, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("공격3", "images/character/chaAttack3.bmp", 504, 86, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("드릴", "images/character/drill.bmp", 40, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("캐릭드릴", "images/character/chaDrill.bmp", 396, 110, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("피격", "images/character/chaHit.bmp", 144, 348, 2, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("체력미니바", "images/character/hpMiniBar.bmp", 70, 5);
	IMAGEMANAGER->addImage("마나미니바", "images/character/mpMiniBar.bmp", 70, 5);

	//몬스터
	IMAGEMANAGER->addFrameImage("addaxIdle", "images/firstMap/monster/AddaxIdle.bmp", 400, 1200, 5, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("addaxAttack", "images/firstMap/monster/AddaxAttack.bmp", 1190, 680, 7, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("addaxHit", "images/firstMap/monster/AddaxHit.bmp", 180, 600, 2, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("addaxDead", "images/firstMap/monster/AddaxDead.bmp", 160, 70, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("pochiIdle", "images/firstMap/monster/PochiIdle.bmp", 720, 640, 9, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("pochiAttack", "images/firstMap/monster/PochiAttack.bmp", 640, 320, 8, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("pochiHit", "images/firstMap/monster/PochiHit.bmp", 240, 320, 3, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("pochiDead", "images/firstMap/monster/PochiDead.bmp", 640, 80, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("requiIdle", "images/secondMap/monster/RequiIdle.bmp", 630, 800, 7, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("requiAttack", "images/secondMap/monster/RequiAttack.bmp", 840, 400, 7, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("requiHit", "images/secondMap/monster/RequiHit.bmp", 1, 4, 80, 400, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("requiDead", "images/secondMap/monster/RequiDead.bmp", 700, 100, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("sphinxIdle", "images/secondMap/monster/SphinxIdle.bmp", 3200, 3200, 8, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("sphinxWalk", "images/secondMap/monster/SphinxWalk.bmp", 3200, 3200, 8, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("sphinxAttack", "images/secondMap/monster/SphinxAttack.bmp", 10080, 1600, 24, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("sphinxHit", "images/secondMap/monster/SphinxHit.bmp", 800, 1600, 2, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("sphinxDead", "images/secondMap/monster/SphinxDead.bmp", 5200, 400, 13, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("몬스터정보표시", "images/ui/enemyNameShow.bmp", 236, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("몬스터체력표시바", "images/character/hpBar.bmp", 219, 7, true, RGB(255, 0, 255));
	//npc
	IMAGEMANAGER->addFrameImage("헌터 유리", "images/lobbyMap/npc/Hunter_Yuri.bmp", 245, 82, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("앤드류", "images/lobbyMap/npc/Andrew.bmp", 225, 82, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("어시스트헌터", "images/lobbyMap/npc/Assistant_Hunter.bmp", 168, 77, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("개발자", "images/secondMap/npc/Developer.bmp", 480, 89, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("헌터 유나", "images/lobbyMap/npc/Hunter_Yuna.bmp", 486, 81, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("루이스", "images/firstMap/npc/Louis.bmp", 318, 77, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("오피서 로버트", "images/lobbyMap/npc/Officer_Robert.bmp", 546, 87, 13, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("포티나", "images/lobbyMap/npc/Portina.bmp", 308, 78, 7, 1, true, RGB(255, 0, 255));

	//상점
	IMAGEMANAGER->addFrameImage("상점구입창", "images/ui/shopWindow.bmp", 361, 832, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("상점판매창", "images/ui/sellWindow.bmp", 361, 416, true, RGB(255, 0, 255));

	//아이템
	IMAGEMANAGER->addImage("악세1", "images/item/acc1.bmp", 23, 21, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("악세2", "images/item/acc2.bmp", 25, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("악세3", "images/item/acc3.bmp", 32, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("드릴1", "images/item/drill1.bmp", 19, 27, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("드릴2", "images/item/drill2.bmp", 19, 27, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("드릴3", "images/item/drill3.bmp", 25, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("모자1", "images/item/helmet1.bmp", 25, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("모자2", "images/item/helmet2.bmp", 25, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("모자3", "images/item/helmet3.bmp", 25, 22, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("방패1", "images/item/shield1.bmp", 19, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("방패2", "images/item/shield2.bmp", 20, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("방패3", "images/item/shield3.bmp", 21, 26, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("무기1", "images/item/weapon1.bmp", 25, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("무기2", "images/item/weapon2.bmp", 25, 18, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("무기3", "images/item/weapon3.bmp", 25, 17, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("포션1", "images/item/potion1.bmp", 24, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("포션2", "images/item/potion2.bmp", 24, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("악세1확대", "images/item/showAcc1.bmp", 103, 103, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("악세2확대", "images/item/showAcc2.bmp", 103, 103, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("악세3확대", "images/item/showAcc3.bmp", 103, 103, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("드릴1확대", "images/item/showDrill1.bmp", 97, 97, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("드릴2확대", "images/item/showDrill2.bmp", 95, 94, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("드릴3확대", "images/item/showDrill3.bmp", 103, 103, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("모자1확대", "images/item/showHelmet1.bmp", 103, 103, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("모자2확대", "images/item/showHelmet2.bmp", 96, 101, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("모자3확대", "images/item/showHelmet3.bmp", 102, 93, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("방패1확대", "images/item/showShield1.bmp", 103, 103, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("방패2확대", "images/item/showShield2.bmp", 103, 103, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("방패3확대", "images/item/showShield3.bmp", 103, 103, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("무기1확대", "images/item/showWeapon1.bmp", 103, 103, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("무기2확대", "images/item/showWeapon2.bmp", 103, 103, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("무기3확대", "images/item/showWeapon3.bmp", 85, 86, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("포션1확대", "images/item/showPotion1.bmp", 100, 98, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("포션2확대", "images/item/showPotion2.bmp", 94, 96, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("아이템정보표시", "images/ui/itemInfoShow.bmp", 346, 328, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("스펙업", "images/ui/specUp.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("스펙다운", "images/ui/specDown.bmp", 16, 16, true, RGB(255, 0, 255));
	
	//드릴 UI
	IMAGEMANAGER->addImage("드릴창", "images/ui/drillUi.bmp", 141, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("드릴게이지", "images/ui/drillGauge.bmp", 115, 6);
	IMAGEMANAGER->addFrameImage("드릴기어1", "images/ui/drillGear1.bmp", 104, 26, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("드릴기어2", "images/ui/drillGear2.bmp", 64, 16, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("드릴기어3", "images/ui/drillGear3.bmp", 80, 20, 4, 1, true, RGB(255, 0, 255));

	//스킬
	IMAGEMANAGER->addImage("스킬1카드", "images/ui/skill1Card.bmp", 23, 27);
	IMAGEMANAGER->addImage("스킬2카드", "images/ui/skill2Card.bmp", 23, 27);
	IMAGEMANAGER->addImage("스킬3카드", "images/ui/skill3Card.bmp", 23, 27);
	IMAGEMANAGER->addImage("스킬1확대", "images/ui/showSkill1.bmp", 103, 103);
	IMAGEMANAGER->addImage("스킬2확대", "images/ui/showSkill2.bmp", 103, 103);
	IMAGEMANAGER->addImage("스킬3확대", "images/ui/showSkill3.bmp", 103, 103);
	IMAGEMANAGER->addFrameImage("스킬1이펙트", "images/skill/skill1Effect.bmp", 768, 132, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("스킬2이펙트", "images/skill/skill2Effect.bmp", 414, 62, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("스킬3이펙트", "images/skill/skill3Effect.bmp", 400, 100, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("스킬3지속표시", "images/skill/skill3On.bmp", 180, 32, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("스킬마스터", "images/skill/skillMaster.bmp", 840, 94, 7, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("로딩2", "images/로딩2.bmp", WINSIZEX, WINSIZEY);
	IMAGEMANAGER->addImage("로딩3", "images/로딩3.bmp", WINSIZEX, WINSIZEY);

	IMAGEMANAGER->addFrameImage("tm레벨업", "images/skill/tmLvUp.bmp", 560, 70, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("스킬레벨업", "images/skill/skillLvUp.bmp", 640, 70, 8, 1, true, RGB(255, 0, 255));
	

	//아이템 추가
	ITEMDB->addItem("무기_1", ITEM_WEAPON_1);
	ITEMDB->addItem("무기_2", ITEM_WEAPON_2);
	ITEMDB->addItem("무기_3", ITEM_WEAPON_3);
	ITEMDB->addItem("모자_1", ITEM_HAT_1);
	ITEMDB->addItem("모자_2", ITEM_HAT_2);
	ITEMDB->addItem("모자_3", ITEM_HAT_3);
	ITEMDB->addItem("방패_1", ITEM_SHIELD_1);
	ITEMDB->addItem("방패_2", ITEM_SHIELD_2);
	ITEMDB->addItem("방패_3", ITEM_SHIELD_3);
	ITEMDB->addItem("악세_1", ITEM_ACCESSORY_1);
	ITEMDB->addItem("악세_2", ITEM_ACCESSORY_2);
	ITEMDB->addItem("악세_3", ITEM_ACCESSORY_3);
	ITEMDB->addItem("드릴_1", ITEM_DRILL_1);
	ITEMDB->addItem("드릴_2", ITEM_DRILL_2);
	ITEMDB->addItem("드릴_3", ITEM_DRILL_3);
	ITEMDB->addItem("포션_1", ITEM_SPEND_1);
	ITEMDB->addItem("포션_2", ITEM_SPEND_2);
	ITEMDB->addItem("스킬카드_1", ITEM_SKILLCARD_1);
	ITEMDB->addItem("스킬카드_2", ITEM_SKILLCARD_2);
	ITEMDB->addItem("스킬카드_3", ITEM_SKILLCARD_3);

	//로딩 테스트
	for (int i = 0; i < 100; i++)
	{
		_loading->loadImage("테스트", WINSIZEX, WINSIZEY);
	}

}

//로딩 사운드 함수(이곳에 사운드를 전부 넣어라!)
void loadingScene::loadingSound()
{
	SOUNDMANAGER->addSound("로비맵", "sound/bgs_beach.wav", false, true);
	SOUNDMANAGER->addSound("사냥맵", "sound/bgs_forest.wav", false, true);
	SOUNDMANAGER->addSound("보스맵", "sound/bgs_Shrine_loop.wav", false, true);
	SOUNDMANAGER->addSound("공격소리1", "sound/dmg_normal_a.wav", false, false);
	SOUNDMANAGER->addSound("공격소리2", "sound/dmg_normal_b.wav", false, false);
	SOUNDMANAGER->addSound("공격소리3", "sound/dmg_normal_c.wav", false, false);
	SOUNDMANAGER->addSound("공격소리4", "sound/dmg_normal_d.wav", false, false);
	SOUNDMANAGER->addSound("공격소리5", "sound/dmg_normal_e.wav", false, false);
	SOUNDMANAGER->addSound("공격소리6", "sound/dmg_normal_f.wav", false, false);
	SOUNDMANAGER->addSound("공격소리7", "sound/dmg_normal_g.wav", false, false);
	SOUNDMANAGER->addSound("공격소리8", "sound/dmg_normal_h.wav", false, false);
	SOUNDMANAGER->addSound("공격소리9", "sound/dmg_normal_i.wav", false, false);
	SOUNDMANAGER->addSound("공격소리10", "sound/dmg_normal_j.wav", false, false);

	SOUNDMANAGER->addSound("천둥소리", "sound/eff_light_explosion.wav", false, false);
	SOUNDMANAGER->addSound("스킬2사용", "sound/skill_hvup_bg.wav", false, false);
	SOUNDMANAGER->addSound("스킬1사용", "sound/skill_steelpunch.wav", false, false);

	SOUNDMANAGER->addSound("레벨업", "sound/etc_levelup.wav", false, false);
	SOUNDMANAGER->addSound("미스", "sound/etc_miss.wav", false, false);
	SOUNDMANAGER->addSound("몬스터죽음", "sound/etc_mon_death.wav", false, false);
	SOUNDMANAGER->addSound("시작할때", "sound/intro_start.wav", false, false);

	SOUNDMANAGER->addSound("무기1소리", "sound/weapon001.wav", false, false);
	SOUNDMANAGER->addSound("무기2소리", "sound/weapon002.wav", false, false);
	SOUNDMANAGER->addSound("무기3소리", "sound/weapon006.wav", false, false);

	SOUNDMANAGER->addSound("치명타", "sound/etc_critical.wav", false, false);

	SOUNDMANAGER->addSound("드릴_모래", "sound/etc_drill_sand.wav", false, true);
	SOUNDMANAGER->addSound("드릴_잔디", "sound/etc_drill_grass.wav", false, true);
	SOUNDMANAGER->addSound("드릴_돌", "sound/etc_drill_ston.wav", false, true);

	SOUNDMANAGER->addSound("창닫기", "sound/ui_close.wav", false, false);
	SOUNDMANAGER->addSound("창클릭1", "sound/ui_click.wav", false, false);

	SOUNDMANAGER->addSound("구입소리", "sound/ui_buy.wav", false, false);
	SOUNDMANAGER->addSound("판매소리", "sound/ui_sell.wav", false, false);

	SOUNDMANAGER->addSound("스킬레벨업", "sound/slevelup.wav", false, false);
	SOUNDMANAGER->addSound("스킬마스터", "sound/skill_cardidentify_ap.wav", false, false);

	SOUNDMANAGER->addSound("기본브금", "sound/0068.mp3", false, true);
}