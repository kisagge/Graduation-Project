#include "stdafx.h"
#include "mainGame.h"
mainGame::mainGame()
{
}
mainGame::~mainGame()
{
}

//==================================================================
//		## �ʱ�ȭ ## init(void)
//==================================================================
HRESULT mainGame::init(void)
{
	SCENEMANAGER->addScene("Ʈ������", new trickster);
	SCENEMANAGER->changeScene("Ʈ������");

	return S_OK;
}

//==================================================================
//		## ���� ## release(void)
//==================================================================
void mainGame::release(void)
{
	gameNode::release();
}

//==================================================================
//		## ������Ʈ ## update(void)
//==================================================================
void mainGame::update(void)
{
	gameNode::update();

	//���Ŵ��� ������Ʈ
	SCENEMANAGER->update();

	//����Ŵ��� ������Ʈ
	SOUNDMANAGER->update();
}

//==================================================================
//		## ���� ## render(void)
//==================================================================
void mainGame::render(void)
{
	//��� �� ��Ʈ��(�̰� ������ �׳� �״�� �Ѱ�)
	PatBlt(getCameraDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//���Ŵ��� ����
	SCENEMANAGER->render();
}
