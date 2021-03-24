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
	//�ε� Ŭ���� �ʱ�ȭ
	_loading = new loading;
	_loading->init();
	//�̹��� �ε�����
	this->loadingImage();
	//���� �ε�����
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

	//�ε� �Ϸ� �� �� ��ȯ
	if (_loading->loadingDone())
	{
		SOUNDMANAGER->play("�⺻���", 0.35f);
		_sceneType = TITLE;
	}
}

void loadingScene::render(void)
{
	_loading->render();
}

//�ε� �̹��� �Լ�(�̰��� �ε� �̹����� ���� �־��!)
void loadingScene::loadingImage()
{
	//_loading->loadImage();

	//���ȭ��
	IMAGEMANAGER->addImage("����", "images/�ε�.bmp", WINSIZEX, WINSIZEY);
	IMAGEMANAGER->addImage("�κ��", "images/lobbyMap/lobbyMap.bmp", 1920, 960, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�Ҷ���", "images/lobbyMap/shellObj.bmp", 48 * 5, 48 * 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ķ��1", "images/lobbyMap/camp1.bmp", 48 * 4, 48 * 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�Ƕ�̵�", "images/lobbyMap/phyramid.bmp", 48 * 6, 48 * 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�����", "images/lobbyMap/ship.bmp", 48 * 4, 48 * 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ĵ����", "images/lobbyMap/candyHouse.bmp", 48 * 5, 48 * 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ķ�����̾�", "images/lobbyMap/fire.bmp", 48 * 12, 48 * 3, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�Ҷ���2", "images/lobbyMap/shellHouse.bmp", 48 * 4, 48 * 5, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("��ɸ�", "images/firstMap/firstMap.bmp", 1920, 960, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ĳ��", "images/firstMap/castle.bmp", 48 * 3, 48 * 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������", "images/firstMap/treeHouse.bmp", 48 * 4, 48 * 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����1", "images/firstMap/tree1.bmp", 48 * 6 * 8, 48 * 6, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�����ٴ���", "images/firstMap/�����ٴ���.bmp", 48 * 6, 48 * 4, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("������", "images/secondMap/secondMap.bmp", 1920, 960, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���㼺", "images/secondMap/batCastle.bmp", 48 * 18, 48 * 10, 3, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("npcǥ��", "images/UI/npcDot.bmp", 100, 75, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�÷��̾�ǥ��", "images/UI/playerDot.bmp", 160, 120, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��Żǥ��", "images/UI/portalDot.bmp", 100, 75, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�޼����ڽ�", "images/UI/messageBox.bmp", 250, 200, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��Ż", "images/UI/portal.bmp", 200, 100, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��Ʈ1", "images/UI/numeric1.bmp", 192, 14, 12, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��Ʈ2", "images/UI/numeric2.bmp", 180, 24, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��Ʈ3", "images/ui/numeric3.bmp", 140, 18, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��Ʈ4", "images/ui/numeric4.bmp", 180, 24, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��Ʈ5", "images/ui/numeric5.bmp", 160, 20, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��Ʈ6", "images/ui/numeric6.bmp", 130, 16, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��Ʈ7", "images/ui/numeric7.bmp", 120, 15, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�޴���", "images/UI/menuBar.bmp", 473, 23, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��ų����ư", "images/UI/skillButton.bmp", 40, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ī������ư", "images/UI/cardButton.bmp", 40, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����������ư", "images/UI/itemButton.bmp", 40, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�������ư", "images/UI/equipButton.bmp", 40, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��������ư", "images/UI/myviewButton.bmp", 40, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����Ʈ����ư", "images/UI/questButton.bmp", 40, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�������ư", "images/UI/guildButton.bmp", 40, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ģ������ư", "images/UI/friendButton.bmp", 40, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��ų������", "images/UI/skillIcon.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ī�������", "images/ui/cardIcon.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�����۾�����", "images/ui/itemIcon.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��������", "images/ui/equipIcon.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����Ʈ������", "images/ui/questIcon.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����������", "images/ui/myviewIcon.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��������", "images/ui/guildIcon.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ģ��������", "images/ui/friendIcon.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��ǥ��", "images/ui/moneySign.bmp", 12, 10, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����ǥ��", "images/ui/weightIcon.bmp", 11, 11, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��ų������", "images/ui/skillQuickUi.bmp", 96, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��ų1������", "images/ui/skill1Icon.bmp", 26, 26, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��ų2������", "images/ui/skill2Icon.bmp", 26, 26, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("��ų3������", "images/ui/skill3Icon.bmp", 26, 26, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�̽�", "images/ui/miss.bmp", 43, 12, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ġ��Ÿ�޹��", "images/ui/crit.bmp", 54, 49, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("�޴���ư���", "images/ui/menuButton.bmp", 40, 40);
	IMAGEMANAGER->addFrameImage("���콺Ŀ��", "images/ui/cursor.bmp", 45, 374, 1, 11, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("ĳ����OK", "images/ui/selectOK.bmp", 53, 75, 1, 3, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ĳ����back", "images/ui/selectBack.bmp", 53, 75, 1, 3, true, RGB(255, 0, 255));

	//�÷��̾�
	IMAGEMANAGER->addFrameImage("�⺻", "images/character/chaIdle.bmp", 412.8, 88, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ȱ�0", "images/character/chaWalk0.bmp", 344, 84, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ȱ�1", "images/character/chaWalk1.bmp", 353, 89, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ȱ�2", "images/character/chaWalk2.bmp", 288, 88, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ȱ�3", "images/character/chaWalk3.bmp", 353, 89, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ȱ�4", "images/character/chaWalk4.bmp", 344, 84, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ȱ�5", "images/character/chaWalk5.bmp", 288, 88, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ȱ�6", "images/character/chaWalk6.bmp", 302, 85, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ȱ�7", "images/character/chaWalk7.bmp", 288, 88, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Ư��", "images/character/chaSpecial.bmp", 994, 86, 12, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���ݴ��0", "images/character/chaAttackIdle0.bmp", 480, 85, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���ݴ��1", "images/character/chaAttackIdle1.bmp", 480, 85, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���ݴ��2", "images/character/chaAttackIdle2.bmp", 456, 85, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���ݴ��3", "images/character/chaAttackIdle3.bmp", 456, 85, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����0", "images/character/chaAttack0.bmp", 504, 86, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����1", "images/character/chaAttack1.bmp", 504, 86, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����2", "images/character/chaAttack2.bmp", 504, 86, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����3", "images/character/chaAttack3.bmp", 504, 86, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�帱", "images/character/drill.bmp", 40, 60, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ĳ���帱", "images/character/chaDrill.bmp", 396, 110, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ǰ�", "images/character/chaHit.bmp", 144, 348, 2, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ü�¹̴Ϲ�", "images/character/hpMiniBar.bmp", 70, 5);
	IMAGEMANAGER->addImage("�����̴Ϲ�", "images/character/mpMiniBar.bmp", 70, 5);

	//����
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

	IMAGEMANAGER->addImage("��������ǥ��", "images/ui/enemyNameShow.bmp", 236, 52, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����ü��ǥ�ù�", "images/character/hpBar.bmp", 219, 7, true, RGB(255, 0, 255));
	//npc
	IMAGEMANAGER->addFrameImage("���� ����", "images/lobbyMap/npc/Hunter_Yuri.bmp", 245, 82, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ص��", "images/lobbyMap/npc/Andrew.bmp", 225, 82, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��ý�Ʈ����", "images/lobbyMap/npc/Assistant_Hunter.bmp", 168, 77, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������", "images/secondMap/npc/Developer.bmp", 480, 89, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���� ����", "images/lobbyMap/npc/Hunter_Yuna.bmp", 486, 81, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���̽�", "images/firstMap/npc/Louis.bmp", 318, 77, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���Ǽ� �ι�Ʈ", "images/lobbyMap/npc/Officer_Robert.bmp", 546, 87, 13, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��Ƽ��", "images/lobbyMap/npc/Portina.bmp", 308, 78, 7, 1, true, RGB(255, 0, 255));

	//����
	IMAGEMANAGER->addFrameImage("��������â", "images/ui/shopWindow.bmp", 361, 832, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�����Ǹ�â", "images/ui/sellWindow.bmp", 361, 416, true, RGB(255, 0, 255));

	//������
	IMAGEMANAGER->addImage("�Ǽ�1", "images/item/acc1.bmp", 23, 21, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�Ǽ�2", "images/item/acc2.bmp", 25, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�Ǽ�3", "images/item/acc3.bmp", 32, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�帱1", "images/item/drill1.bmp", 19, 27, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�帱2", "images/item/drill2.bmp", 19, 27, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�帱3", "images/item/drill3.bmp", 25, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����1", "images/item/helmet1.bmp", 25, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����2", "images/item/helmet2.bmp", 25, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����3", "images/item/helmet3.bmp", 25, 22, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����1", "images/item/shield1.bmp", 19, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����2", "images/item/shield2.bmp", 20, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����3", "images/item/shield3.bmp", 21, 26, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����1", "images/item/weapon1.bmp", 25, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����2", "images/item/weapon2.bmp", 25, 18, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����3", "images/item/weapon3.bmp", 25, 17, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����1", "images/item/potion1.bmp", 24, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����2", "images/item/potion2.bmp", 24, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�Ǽ�1Ȯ��", "images/item/showAcc1.bmp", 103, 103, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�Ǽ�2Ȯ��", "images/item/showAcc2.bmp", 103, 103, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�Ǽ�3Ȯ��", "images/item/showAcc3.bmp", 103, 103, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�帱1Ȯ��", "images/item/showDrill1.bmp", 97, 97, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�帱2Ȯ��", "images/item/showDrill2.bmp", 95, 94, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�帱3Ȯ��", "images/item/showDrill3.bmp", 103, 103, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����1Ȯ��", "images/item/showHelmet1.bmp", 103, 103, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����2Ȯ��", "images/item/showHelmet2.bmp", 96, 101, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����3Ȯ��", "images/item/showHelmet3.bmp", 102, 93, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����1Ȯ��", "images/item/showShield1.bmp", 103, 103, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����2Ȯ��", "images/item/showShield2.bmp", 103, 103, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����3Ȯ��", "images/item/showShield3.bmp", 103, 103, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����1Ȯ��", "images/item/showWeapon1.bmp", 103, 103, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����2Ȯ��", "images/item/showWeapon2.bmp", 103, 103, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����3Ȯ��", "images/item/showWeapon3.bmp", 85, 86, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����1Ȯ��", "images/item/showPotion1.bmp", 100, 98, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����2Ȯ��", "images/item/showPotion2.bmp", 94, 96, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����������ǥ��", "images/ui/itemInfoShow.bmp", 346, 328, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�����", "images/ui/specUp.bmp", 16, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("����ٿ�", "images/ui/specDown.bmp", 16, 16, true, RGB(255, 0, 255));
	
	//�帱 UI
	IMAGEMANAGER->addImage("�帱â", "images/ui/drillUi.bmp", 141, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�帱������", "images/ui/drillGauge.bmp", 115, 6);
	IMAGEMANAGER->addFrameImage("�帱���1", "images/ui/drillGear1.bmp", 104, 26, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�帱���2", "images/ui/drillGear2.bmp", 64, 16, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�帱���3", "images/ui/drillGear3.bmp", 80, 20, 4, 1, true, RGB(255, 0, 255));

	//��ų
	IMAGEMANAGER->addImage("��ų1ī��", "images/ui/skill1Card.bmp", 23, 27);
	IMAGEMANAGER->addImage("��ų2ī��", "images/ui/skill2Card.bmp", 23, 27);
	IMAGEMANAGER->addImage("��ų3ī��", "images/ui/skill3Card.bmp", 23, 27);
	IMAGEMANAGER->addImage("��ų1Ȯ��", "images/ui/showSkill1.bmp", 103, 103);
	IMAGEMANAGER->addImage("��ų2Ȯ��", "images/ui/showSkill2.bmp", 103, 103);
	IMAGEMANAGER->addImage("��ų3Ȯ��", "images/ui/showSkill3.bmp", 103, 103);
	IMAGEMANAGER->addFrameImage("��ų1����Ʈ", "images/skill/skill1Effect.bmp", 768, 132, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��ų2����Ʈ", "images/skill/skill2Effect.bmp", 414, 62, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��ų3����Ʈ", "images/skill/skill3Effect.bmp", 400, 100, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��ų3����ǥ��", "images/skill/skill3On.bmp", 180, 32, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��ų������", "images/skill/skillMaster.bmp", 840, 94, 7, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("�ε�2", "images/�ε�2.bmp", WINSIZEX, WINSIZEY);
	IMAGEMANAGER->addImage("�ε�3", "images/�ε�3.bmp", WINSIZEX, WINSIZEY);

	IMAGEMANAGER->addFrameImage("tm������", "images/skill/tmLvUp.bmp", 560, 70, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��ų������", "images/skill/skillLvUp.bmp", 640, 70, 8, 1, true, RGB(255, 0, 255));
	

	//������ �߰�
	ITEMDB->addItem("����_1", ITEM_WEAPON_1);
	ITEMDB->addItem("����_2", ITEM_WEAPON_2);
	ITEMDB->addItem("����_3", ITEM_WEAPON_3);
	ITEMDB->addItem("����_1", ITEM_HAT_1);
	ITEMDB->addItem("����_2", ITEM_HAT_2);
	ITEMDB->addItem("����_3", ITEM_HAT_3);
	ITEMDB->addItem("����_1", ITEM_SHIELD_1);
	ITEMDB->addItem("����_2", ITEM_SHIELD_2);
	ITEMDB->addItem("����_3", ITEM_SHIELD_3);
	ITEMDB->addItem("�Ǽ�_1", ITEM_ACCESSORY_1);
	ITEMDB->addItem("�Ǽ�_2", ITEM_ACCESSORY_2);
	ITEMDB->addItem("�Ǽ�_3", ITEM_ACCESSORY_3);
	ITEMDB->addItem("�帱_1", ITEM_DRILL_1);
	ITEMDB->addItem("�帱_2", ITEM_DRILL_2);
	ITEMDB->addItem("�帱_3", ITEM_DRILL_3);
	ITEMDB->addItem("����_1", ITEM_SPEND_1);
	ITEMDB->addItem("����_2", ITEM_SPEND_2);
	ITEMDB->addItem("��ųī��_1", ITEM_SKILLCARD_1);
	ITEMDB->addItem("��ųī��_2", ITEM_SKILLCARD_2);
	ITEMDB->addItem("��ųī��_3", ITEM_SKILLCARD_3);

	//�ε� �׽�Ʈ
	for (int i = 0; i < 100; i++)
	{
		_loading->loadImage("�׽�Ʈ", WINSIZEX, WINSIZEY);
	}

}

//�ε� ���� �Լ�(�̰��� ���带 ���� �־��!)
void loadingScene::loadingSound()
{
	SOUNDMANAGER->addSound("�κ��", "sound/bgs_beach.wav", false, true);
	SOUNDMANAGER->addSound("��ɸ�", "sound/bgs_forest.wav", false, true);
	SOUNDMANAGER->addSound("������", "sound/bgs_Shrine_loop.wav", false, true);
	SOUNDMANAGER->addSound("���ݼҸ�1", "sound/dmg_normal_a.wav", false, false);
	SOUNDMANAGER->addSound("���ݼҸ�2", "sound/dmg_normal_b.wav", false, false);
	SOUNDMANAGER->addSound("���ݼҸ�3", "sound/dmg_normal_c.wav", false, false);
	SOUNDMANAGER->addSound("���ݼҸ�4", "sound/dmg_normal_d.wav", false, false);
	SOUNDMANAGER->addSound("���ݼҸ�5", "sound/dmg_normal_e.wav", false, false);
	SOUNDMANAGER->addSound("���ݼҸ�6", "sound/dmg_normal_f.wav", false, false);
	SOUNDMANAGER->addSound("���ݼҸ�7", "sound/dmg_normal_g.wav", false, false);
	SOUNDMANAGER->addSound("���ݼҸ�8", "sound/dmg_normal_h.wav", false, false);
	SOUNDMANAGER->addSound("���ݼҸ�9", "sound/dmg_normal_i.wav", false, false);
	SOUNDMANAGER->addSound("���ݼҸ�10", "sound/dmg_normal_j.wav", false, false);

	SOUNDMANAGER->addSound("õ�ռҸ�", "sound/eff_light_explosion.wav", false, false);
	SOUNDMANAGER->addSound("��ų2���", "sound/skill_hvup_bg.wav", false, false);
	SOUNDMANAGER->addSound("��ų1���", "sound/skill_steelpunch.wav", false, false);

	SOUNDMANAGER->addSound("������", "sound/etc_levelup.wav", false, false);
	SOUNDMANAGER->addSound("�̽�", "sound/etc_miss.wav", false, false);
	SOUNDMANAGER->addSound("��������", "sound/etc_mon_death.wav", false, false);
	SOUNDMANAGER->addSound("�����Ҷ�", "sound/intro_start.wav", false, false);

	SOUNDMANAGER->addSound("����1�Ҹ�", "sound/weapon001.wav", false, false);
	SOUNDMANAGER->addSound("����2�Ҹ�", "sound/weapon002.wav", false, false);
	SOUNDMANAGER->addSound("����3�Ҹ�", "sound/weapon006.wav", false, false);

	SOUNDMANAGER->addSound("ġ��Ÿ", "sound/etc_critical.wav", false, false);

	SOUNDMANAGER->addSound("�帱_��", "sound/etc_drill_sand.wav", false, true);
	SOUNDMANAGER->addSound("�帱_�ܵ�", "sound/etc_drill_grass.wav", false, true);
	SOUNDMANAGER->addSound("�帱_��", "sound/etc_drill_ston.wav", false, true);

	SOUNDMANAGER->addSound("â�ݱ�", "sound/ui_close.wav", false, false);
	SOUNDMANAGER->addSound("âŬ��1", "sound/ui_click.wav", false, false);

	SOUNDMANAGER->addSound("���ԼҸ�", "sound/ui_buy.wav", false, false);
	SOUNDMANAGER->addSound("�ǸżҸ�", "sound/ui_sell.wav", false, false);

	SOUNDMANAGER->addSound("��ų������", "sound/slevelup.wav", false, false);
	SOUNDMANAGER->addSound("��ų������", "sound/skill_cardidentify_ap.wav", false, false);

	SOUNDMANAGER->addSound("�⺻���", "sound/0068.mp3", false, true);
}