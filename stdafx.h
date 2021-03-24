// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include <SDKDDKVer.h>

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <Windows.h>
//������ (�ּ�ġ�� �ܼ�â�� �������)
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>

// C++ ��Ÿ�� ��� �����Դϴ�.
#include <iostream>
using namespace std;
// ���ֻ���ϴ� STL
#include <string>
#include <vector>
#include <list>
#include <map>

//==================================================================
//		## ���� ���� ��������� �̰��� �߰��Ѵ� ##
//==================================================================
#include "commonMacroFunction.h"
#include "keyManager.h"
#include "randomFunction.h"
#include "imageManager.h"
#include "timeManager.h"
#include "txtData.h"
#include "iniData.h"
#include "sceneManager.h"
#include "soundManager.h"
#include "effectManager.h"
#include "animationManager.h"

//==================================================================
//		## �̱����� �߰��Ѵ� ##
//==================================================================
#define KEYMANAGER keyManager::getSingleton()
#define RND randomFunction::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define TIMEMANAGER timeManager::getSingleton()
#define TXTDATA	txtData::getSingleton()
#define INIDATA iniData::getSingleton()
#define SCENEMANAGER sceneManager::getSingleton()
#define SOUNDMANAGER soundManager::getSingleton()
#define EFFECTMANAGER effectManager::getSingleton()
#define ANIMANAGER animationManager::getSingleton()

//==================================================================
//		## ���ӽ����̽� �߰��Ѵ� ##
//==================================================================
#include "util.h"
using namespace MY_UTIL;

//==================================================================
//		## �����ι� ## (������â �ʱ�ȭ)
//==================================================================
#define WINNAME (LPTSTR)(TEXT("TRICKSTER"))
#define WINSTARTX 0
#define WINSTARTY 0
#define WINSIZEX	1400
#define WINSIZEY	800
#define WINSTYLE WS_CAPTION | WS_SYSMENU

//==================================================================
//		## ��ũ���Լ� ## (Ŭ�������� �����Ҵ�� �κ� ������ ����Ѵ�)
//==================================================================
#define SAFE_DELETE(p)			{if(p) {delete(p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p)		{if(p) {delete[] (p); (p) = NULL;}}

//==================================================================
//		## �������� ## (Ŭ�������� �����Ҵ�� �κ� ������ ����Ѵ�)
//==================================================================
#include "itemDb.h"
extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINT _ptMouse;
extern vector<tagZorderImage> _zorderVec;
extern int cameraX, cameraY;
extern RECT _cllipingRc;
extern SCENETYPE _sceneType;

#define ITEMDB itemDb::getSingleton()

// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
