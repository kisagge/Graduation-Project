//==================================================================
//		## ������� ���ش� ##
//==================================================================
#include "stdafx.h"
#include "mainGame.h"

//==================================================================
//		## �������� ���ش� ##
//==================================================================
HINSTANCE _hInstance;
HWND _hWnd;
POINT _ptMouse = { 0, 0 };
vector<tagZorderImage> _zorderVec;
int cameraX, cameraY;
RECT _cllipingRc = RectMake(cameraX, cameraY, WINSIZEX, WINSIZEY);
SCENETYPE _sceneType;
itemDb* _itemDb;
//���ΰ��� Ŭ���� ����
mainGame _mg;

//==================================================================
//		## �Լ� ���漱�� ##
//==================================================================
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height);

//==================================================================
//		## ������ �����Լ� ##
//==================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	//hInstance : ���α׷��� �ν��Ͻ� �ڵ�
	//hPrevInstance : ������ ����� �ν��Ͻ� �ڵ� (������ ������)
	//lpszCmdParam : ��������� �Էµ� ���α׷� �μ�
	//nCmdShow : ���α׷��� ���۵� ���� (�ּ�ȭ, ����ũ����..)

	//�ν��Ͻ��� ���������� ��Ƶд�
	_hInstance = hInstance;

	//WNDCLASS : �������� ������ �����ϱ� ���� ����ü
	WNDCLASS wndClass;

	wndClass.cbClsExtra = 0;										//Ŭ���� ���� �޸�
	wndClass.cbWndExtra = 0;										//������ ���� �޸�
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//��׶���
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);					//Ŀ��
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				//������
	wndClass.hInstance = hInstance;									//�ν��Ͻ�
	wndClass.lpfnWndProc = (WNDPROC)WndProc;						//������ ���ν���
	wndClass.lpszClassName = WINNAME;								//Ŭ�����̸�
	wndClass.lpszMenuName = NULL;									//�޴��̸�
	wndClass.style = CS_HREDRAW | CS_VREDRAW;						//������ ��Ÿ��

	//������ Ŭ���� ���
	RegisterClass(&wndClass);

	//������ ����
	_hWnd = CreateWindow(
		WINNAME,				//������ Ŭ������ �̸�
		WINNAME,				//������ Ÿ��Ʋ�� �̸�
		WINSTYLE,				//������ ��Ÿ��
		WINSTARTX,				//������ ȭ����ǥ x
		WINSTARTY,				//������ ȭ����ǥ y
		WINSIZEX,				//������ ȭ����ǥ width
		WINSIZEY,				//������ ȭ����ǥ height
		NULL,					//�θ� ������
		(HMENU)NULL,			//�޴��ڵ�
		hInstance,				//�ν��Ͻ� ����
		NULL);					//������ �� �ڽ� �����츦 �����ϸ� �������ֵ� �׷��� ������ NULL

	//ȭ�� �۾� ������ ���� ���
	setWindowSize(WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY);

	//ȭ�鿡 ������ �����ش�
	ShowWindow(_hWnd, nCmdShow);


	//���ΰ��� Ŭ������ �ʱ�ȭ�� �����ߴٸ� �ٷ� ������Ѷ�
	if (FAILED(_mg.init()))
	{
		return 0;
	}


	//MSG : �ü������ �����ϴ� �޽��� ������ �����ϱ� ���� ����ü
	MSG message;

	//�޽��� ����~~
	//GetMessage : GetMessage�� �޽����� ������ �� ���������� �����ִ� �Լ��̰�,
	//PeekMessage : PeekMessage�� �޽����� ������ ���ϵǴ� �Լ��μ�, ��� �����Ǵ� �Լ��̴�. 

	
	//���ӿ� �޼��� ���� ���߿� ���������� ������ �״�� ���Ѱ�!!!
	while (true)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT) break;
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			//�ʴ� 60���������� ������Ʈ ���Ѷ�
			TIMEMANAGER->update(60.0f);
			//���ΰ��� Ŭ���� ������Ʈ �� ����
			_mg.update();
			_mg.render();
		}
	}
	
	

	//TranslateMessage : Ű���� �Է¸޽��� ó���� ����Ѵ�.
	//�Էµ� Ű�� ����Ű���� Ȯ���� �빮�� Ȥ�� �ҹ���, �ѱ�, ����, ������ ���� WM_CHAR�޽����� �߻���Ų��.

	//DispatchMessage : ������ ���ν������� ���޵� �޽����� ���� ������� �������ش�

	/*
	//�Ϲ� ���α׷��� �޼��� ������~
	//�޽��� ť�� �޽����� ������ �޽��� ó��...
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
	*/

	//���ΰ��� Ŭ���� ����
	_mg.release();

	//������ Ŭ���� ��� ����
	UnregisterClass(WINNAME, hInstance);

	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	//���ΰ��� Ŭ������ ���� ���ν������� ó������ ���� ������ �޼����� ó�����ش�
	return _mg.MainProc(hWnd, iMessage, wParam, lParam);
}

//==================================================================
//		## ������ ũ�� ���� ## (Ŭ���̾�Ʈ ������ ����� ��Ȯ�� ����ش�)
//==================================================================
void setWindowSize(int x, int y, int width, int height)
{
	RECT rc;
	rc.left = 0;
	rc.top = 0;
	rc.right = width;
	rc.bottom = height;

	//���� ������ ũ�� ����
	AdjustWindowRect(&rc, WINSTYLE, false);
	//�� ��Ʈ ������ ������ Ŭ���̾�Ʈ ������ ����
	SetWindowPos(_hWnd, NULL, x, y, (rc.right - rc.left), (rc.bottom - rc.top),
		SWP_NOZORDER | SWP_NOMOVE);
}
