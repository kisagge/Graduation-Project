#pragma once
#include "singletonBase.h"
#include "image.h"
//==================================================================
//		## imageManager ## (�̹��� �Ŵ���)
//==================================================================

class imageManager : public singletonBase <imageManager>
{
private:
	typedef map<string, image*> mapImageList;			//������ ���� �̹������
	typedef map<string, image*>::iterator mapImageIter;	//������ ���� �̹�������� �ݺ���

private:
	mapImageList _mImageList;	//������ ������ �̹������

public:
	//�̹����Ŵ��� �ʱ�ȭ
	HRESULT init(void);
	//�̹����Ŵ��� ����
	void release(void);

	//Ű������ �� ��Ʈ������ �ʱ�ȭ
	image* addImage(string strKey, int width, int height);
	//Ű������ �̹��� ���Ϸ� �ʱ�ȭ (�� ���)
	image* addImage(string strKey, const char* fileName, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	image* addImage(string strKey, const char* fileName, float x, float y, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	//Ű������ ������ �̹��� ���Ϸ� �ʱ�ȭ
	image* addFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	image* addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	//�̹��� Ű������ ã��
	image* findImage(string strKey);
	//�̹��� Ű������ ����
	BOOL deleteImage(string strKey);
	//�̹��� ��ü ����
	BOOL deleteAll(void);

//==================================================================
//		## �Ϲݷ��� ##
//==================================================================
	void render(string strKey, HDC hdc);
	void render(string strKey, HDC hdc, int destX, int destY);
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

//==================================================================
//		## ���ķ��� ##
//==================================================================
	void alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

//==================================================================
//		## �����ӷ��� ##
//==================================================================
	void frameRender(string strKey, HDC hdc, int destX, int destY);
	void frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);
	void frameAlphaRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);

//==================================================================
//		## �������� ##
//==================================================================
	void loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);


	imageManager();
	~imageManager();
};

