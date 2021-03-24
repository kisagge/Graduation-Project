#include "stdafx.h"
#include "image.h"
#pragma comment(lib, "msimg32.lib") //���ĺ��带 ����ϱ� ���� ���̺귯�� �߰�
image::image() : _imageInfo(NULL), _fileName(NULL), _isTrans(FALSE), _transColor(RGB(0, 0, 0)), _blendImage(NULL)
{
}
image::~image()
{
}
//==================================================================
//		## ���̻� ������, �Ҹ��ڴ� ������� �ʴ´� ##
//==================================================================

//�� ��Ʈ������ �ʱ�ȭ
HRESULT image::init(int width, int height)
{
	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� ��������� ���ٰ�!
	if (_imageInfo != NULL) release();

	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ���� �����ϱ�
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//�����̸�
	_fileName = NULL;

	//����Ű �÷� ����
	_isTrans = FALSE;
	_transColor = RGB(0, 0, 0);

	//���ҽ� �����µ� ����������
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC ����
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

//�̹��� ���ҽ��� �ʱ�ȭ (������)
HRESULT image::init(const DWORD resID, int width, int height, BOOL isTrans, COLORREF transColor)
{
	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� ��������� ���ٰ�!
	if (_imageInfo != NULL) release();

	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ���� �����ϱ�
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_RESOURCE;
	_imageInfo->resID = resID;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadBitmap(_hInstance, MAKEINTRESOURCE(_imageInfo->resID));
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//�����̸�
	_fileName = NULL;

	//����Ű �÷� ����
	_isTrans = isTrans;
	_transColor = transColor;

	//���ҽ� �����µ� ����������
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC ����
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}
//�̹��� ���Ϸ� �ʱ�ȭ (�� ���)
HRESULT image::init(const char* fileName, int width, int height, BOOL isTrans, COLORREF transColor)
{
	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� ��������� ���ٰ�!
	if (_imageInfo != NULL) release();

	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ���� �����ϱ�
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//�����̸�
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//����Ű �÷� ����
	_isTrans = isTrans;
	_transColor = transColor;

	//���ҽ� �����µ� ����������
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC ����
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char* fileName, float x, float y, int width, int height, BOOL isTrans, COLORREF transColor)
{
	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� ��������� ���ٰ�!
	if (_imageInfo != NULL) release();

	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ���� �����ϱ�
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x - (width / 2);
	_imageInfo->y = y - (height / 2);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//�����̸�
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//����Ű �÷� ����
	_isTrans = isTrans;
	_transColor = transColor;

	//���ҽ� �����µ� ����������
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC ����
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}
//������ �̹��� ���Ϸ� �ʱ�ȭ
HRESULT image::init(const char* fileName, int width, int height, int frameX, int frameY, BOOL isTrans, COLORREF transColor)
{
	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� ��������� ���ٰ�!
	if (_imageInfo != NULL) release();

	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ���� �����ϱ�
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;

	//�����̸�
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//����Ű �÷� ����
	_isTrans = isTrans;
	_transColor = transColor;

	//���ҽ� �����µ� ����������
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC ����
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}
HRESULT image::init(const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL isTrans, COLORREF transColor)
{
	//���ʱ�ȭ ������, �̹��� ������ ���� ��� �ִٸ� ��������� ���ٰ�!
	if (_imageInfo != NULL) release();

	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//�̹��� ���� ���� �����ϱ�
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x - (width / frameX / 2);
	_imageInfo->y = y - (height / frameY / 2);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;

	//�����̸�
	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//����Ű �÷� ����
	_isTrans = isTrans;
	_transColor = transColor;

	//���ҽ� �����µ� ����������
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC ����
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

//���ĺ��� �ʱ�ȭ
HRESULT image::initForAlphaBlend(void)
{
	//DC ��������
	HDC hdc = GetDC(_hWnd);

	//���ĺ��� �ɼ�
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	_blendFunc.BlendOp = AC_SRC_OVER;

	//���ĺ��� ����ϱ� ���� �̹��� �ʱ�ȭ
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_EMPTY;
	_blendImage->resID = 0;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	//���ҽ� �����µ� ����������
	if (_imageInfo->hBit == 0)
	{
		release();
		return E_FAIL;
	}

	//DC ����
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

//����Ű ����
void image::setTransColor(BOOL isTrans, COLORREF transColor)
{
	_isTrans = isTrans;
	_transColor = transColor;
}

//����
void image::release(void)
{
	//�̹��� ������ ���� �ִٸ� ���� ���Ѷ�
	if (_imageInfo)
	{
		//�̹��� ����
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		//������ ����
		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_fileName);

		//�����÷�Ű �ʱ�ȭ
		_isTrans = FALSE;
		_transColor = RGB(0, 0, 0);
	}

	//���� �̹��� ������ ���� �ִٸ� ���� ���Ѷ�
	if (_blendImage)
	{
		//�̹��� ����
		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);
		//������ ����
		SAFE_DELETE(_blendImage);
	}
}

//==================================================================
//		## �Ϲݷ��� ##
//==================================================================
void image::render(HDC hdc)
{
	if (_isTrans) //���� ���ٲ���?
	{
		//GdiTransparentBlt : ��Ʈ���� �ҷ��ô� Ư�������� �����ϰ� �������ִ� �Լ�
		GdiTransparentBlt(
			hdc,						//������ ����� DC
			0,						//����� ��ǥ ������ x
			0,						//����� ��ǥ ������ y
			_imageInfo->width,			//����� �̹��� ����ũ��
			_imageInfo->height,			//����� �̹��� ����ũ��
			_imageInfo->hMemDC,			//����� ��� DC
			0, 0,						//���� ��������
			_imageInfo->width,			//���� ���� ����ũ��
			_imageInfo->height,			//���� ���� ����ũ��
			_transColor					//�����Ҷ� ������ ����(����Ÿ���� �����)
			);
	}
	else //���� �̹��� �״�� ����Ҳ���?
	{
		//BitBlt : DC���� �������� ���� ��Ӻ��縦 ���ִ� �Լ�
		BitBlt(hdc, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

//���� (���� ������ ��ǥ�� �̹����� ����Ѵ�)
void image::render(HDC hdc, int destX, int destY)
{
	if (_isTrans) //���� ���ٲ���?
	{
		//GdiTransparentBlt : ��Ʈ���� �ҷ��ô� Ư�������� �����ϰ� �������ִ� �Լ�
		GdiTransparentBlt(
			hdc,						//������ ����� DC
			destX,						//����� ��ǥ ������ x
			destY,						//����� ��ǥ ������ y
			_imageInfo->width,			//����� �̹��� ����ũ��
			_imageInfo->height,			//����� �̹��� ����ũ��
			_imageInfo->hMemDC,			//����� ��� DC
			0, 0,						//���� ��������
			_imageInfo->width,			//���� ���� ����ũ��
			_imageInfo->height,			//���� ���� ����ũ��
			_transColor					//�����Ҷ� ������ ����(����Ÿ���� �����)
			);
	}
	else //���� �̹��� �״�� ����Ҳ���?
	{
		//BitBlt : DC���� �������� ���� ��Ӻ��縦 ���ִ� �Լ�
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
	
}

void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_isTrans) //���� ���ٲ���?
	{
		//GdiTransparentBlt : ��Ʈ���� �ҷ��ô� Ư�������� �����ϰ� �������ִ� �Լ�
		GdiTransparentBlt(
			hdc,						//������ ����� DC
			destX,						//����� ��ǥ ������ x
			destY,						//����� ��ǥ ������ y
			sourWidth,			//����� �̹��� ����ũ��
			sourHeight,			//����� �̹��� ����ũ��
			_imageInfo->hMemDC,			//����� ��� DC
			sourX, sourY,						//���� ��������
			sourWidth,			//���� ���� ����ũ��
			sourHeight,			//���� ���� ����ũ��
			_transColor					//�����Ҷ� ������ ����(����Ÿ���� �����)
			);
	}
	else //���� �̹��� �״�� ����Ҳ���?
	{
		//BitBlt : DC���� �������� ���� ��Ӻ��縦 ���ִ� �Լ�
		BitBlt(hdc, destX, destY, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}


//==================================================================
//		## ���ķ��� ##
//==================================================================
void image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	//���ĺ��� ó������ϳ�?
	//���ĺ��� ����� �� �ֵ��� �ʱ�ȭ �ض�
	if (!_blendImage) initForAlphaBlend();

	//���İ� �ʱ�ȭ
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans) //����(����Ÿ) ������ ���ĺ��� �Ҳ���?
	{
		//1. ����ؾ� �� DC�� �׷��� �ִ� ������ �����̹����� �׷��ش�
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY);
		//2. ����ؾ� �� �̹����� ���忡 �׷��ش�(����Ÿ ���� �����ش�)
		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _transColor);
		//3. ���� DC�� ����ؾ� �� DC�� �׸���
		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else //���� �̹��� �״�� ���ĺ��� �Ҳ���?
	{
		AlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	//���ĺ��� ó������ϳ�?
	//���ĺ��� ����� �� �ֵ��� �ʱ�ȭ �ض�
	if (!_blendImage) initForAlphaBlend();

	//���İ� �ʱ�ȭ
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans) //����(����Ÿ) ������ ���ĺ��� �Ҳ���?
	{
		//1. ����ؾ� �� DC�� �׷��� �ִ� ������ �����̹����� �׷��ش�
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY);
		//2. ����ؾ� �� �̹����� ���忡 �׷��ش�(����Ÿ ���� �����ش�)
		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, _transColor);
		//3. ���� DC�� ����ؾ� �� DC�� �׸���
		AlphaBlend(hdc, destX, destY, sourWidth, sourHeight,
			_blendImage->hMemDC, 0, 0, sourWidth, sourHeight, _blendFunc);
	}
	else //���� �̹��� �״�� ���ĺ��� �Ҳ���?
	{
		AlphaBlend(hdc, destX, destY, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, _blendFunc);
	}
}

//==================================================================
//		## �����ӷ��� ##
//==================================================================
void image::frameRender(HDC hdc, int destX, int destY)
{
	if (_isTrans) //���� ���ٲ���?
	{
		//GdiTransparentBlt : ��Ʈ���� �ҷ��ô� Ư�������� �����ϰ� �������ִ� �Լ�
		GdiTransparentBlt(
			hdc,						//������ ����� DC
			destX,						//����� ��ǥ ������ x
			destY,						//����� ��ǥ ������ y
			_imageInfo->frameWidth,		//����� �̹��� ����ũ��
			_imageInfo->frameHeight,	//����� �̹��� ����ũ��
			_imageInfo->hMemDC,			//����� ��� DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,		//���� ��������
			_imageInfo->currentFrameY * _imageInfo->frameHeight,	//���� ��������
			_imageInfo->frameWidth,		//���� ���� ����ũ��
			_imageInfo->frameHeight,	//���� ���� ����ũ��
			_transColor					//�����Ҷ� ������ ����(����Ÿ���� �����)
			);
	}
	else //���� �̹��� �״�� ����Ҳ���?
	{
		//BitBlt : DC���� �������� ���� ��Ӻ��縦 ���ִ� �Լ�
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC, 
			_imageInfo->currentFrameX * _imageInfo->frameWidth, 
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}
void image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (currentFrameX > _imageInfo->maxFrameX)
	{
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	if (currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	if (_isTrans) //���� ���ٲ���?
	{
		//GdiTransparentBlt : ��Ʈ���� �ҷ��ô� Ư�������� �����ϰ� �������ִ� �Լ�
		GdiTransparentBlt(
			hdc,						//������ ����� DC
			destX,						//����� ��ǥ ������ x
			destY,						//����� ��ǥ ������ y
			_imageInfo->frameWidth,		//����� �̹��� ����ũ��
			_imageInfo->frameHeight,	//����� �̹��� ����ũ��
			_imageInfo->hMemDC,			//����� ��� DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,		//���� ��������
			_imageInfo->currentFrameY * _imageInfo->frameHeight,	//���� ��������
			_imageInfo->frameWidth,		//���� ���� ����ũ��
			_imageInfo->frameHeight,	//���� ���� ����ũ��
			_transColor					//�����Ҷ� ������ ����(����Ÿ���� �����)
			);
	}
	else //���� �̹��� �״�� ����Ҳ���?
	{
		//BitBlt : DC���� �������� ���� ��Ӻ��縦 ���ִ� �Լ�
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}
void image::frameAlphaRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{

	//���ĺ��� ó������ϳ�?
	//���ĺ��� ����� �� �ֵ��� �ʱ�ȭ �ض�
	if (!_blendImage) initForAlphaBlend();

	//���İ� �ʱ�ȭ
	_blendFunc.SourceConstantAlpha = alpha;

	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (currentFrameX > _imageInfo->maxFrameX)
	{
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	if (currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	if (_isTrans) //����(����Ÿ) ������ ���ĺ��� �Ҳ���?
	{
		//1. ����ؾ� �� DC�� �׷��� �ִ� ������ �����̹����� �׷��ش�
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight,
			hdc, destX, destY, SRCCOPY);
		//2. ����ؾ� �� �̹����� ���忡 �׷��ش�(����Ÿ ���� �����ش�)
		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC, _imageInfo->currentFrameX * _imageInfo->frameWidth
			, _imageInfo->currentFrameY * _imageInfo->frameHeight, _imageInfo->frameWidth, _imageInfo->frameHeight, _transColor);
		//3. ���� DC�� ����ؾ� �� DC�� �׸���
		AlphaBlend(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
	}
	else //���� �̹��� �״�� ���ĺ��� �Ҳ���?
	{
		AlphaBlend(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
	}
}

//==================================================================
//		## �������� ##
//==================================================================
void image::loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	//offset ���� ������ ��� �����ϱ�
	if (offsetX < 0) offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0) offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

	//�׷����� ������ �����ϱ�
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//�׷����� DC ����
	RECT rcDest;

	//�׷��� �� ��ü ����
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//���� ���� ����
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//�ҽ� ������ ���� ���
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//�ҽ� ������ �׸��� ȭ���� �Ѿ�ٸ� (ȭ������� ��������)
		if (y + sourHeight > drawAreaH)
		{
			//�Ѿ �׸��� ����ŭ ���� ���� �÷��ش�
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//�׷����� ����
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//���� ���� ����
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//�ҽ� ������ ���� ���
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right= _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			//�ҽ� ������ �׸��� ȭ���� �Ѿ�ٸ� (ȭ������� ��������)
			if (x + sourWidth > drawAreaW)
			{
				//�Ѿ �׸��� ����ŭ ���� ���� �÷��ش�
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			//�׷����� ����
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			//�׷�����
			render(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top,
				rcSour.right - rcSour.left, rcSour.bottom - rcSour.top);
		}
	}
}

void image::loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{
	//offset ���� ������ ��� �����ϱ�
	if (offsetX < 0) offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0) offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

	//�׷����� ������ �����ϱ�
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//�׷����� DC ����
	RECT rcDest;

	//�׷��� �� ��ü ����
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//���� ���� ����
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//�ҽ� ������ ���� ���
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//�ҽ� ������ �׸��� ȭ���� �Ѿ�ٸ� (ȭ������� ��������)
		if (y + sourHeight > drawAreaH)
		{
			//�Ѿ �׸��� ����ŭ ���� ���� �÷��ش�
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//�׷����� ����
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//���� ���� ����
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//�ҽ� ������ ���� ���
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			//�ҽ� ������ �׸��� ȭ���� �Ѿ�ٸ� (ȭ������� ��������)
			if (x + sourWidth > drawAreaW)
			{
				//�Ѿ �׸��� ����ŭ ���� ���� �÷��ش�
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			//�׷����� ����
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			//�׷�����
			alphaRender(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top,
				rcSour.right - rcSour.left, rcSour.bottom - rcSour.top, alpha);
		}
	}
}

//==================================================================
//		## �ִϷ��� ##
//==================================================================
void image::aniRender(HDC hdc, int destX, int destY, animation* ani)
{
	render(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight());
}
void image::aniAlphaRender(HDC hdc, int destX, int destY, animation* ani, BYTE alpha)
{
	alphaRender(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight(), alpha);
}

