#pragma once
#include "gameNode.h"
#include "progressBar.h"

//�ε� ������ ����
enum LOAD_KIND
{
	LOAD_KIND_IMAGE_0,		//�� ��Ʈ�� �̹���
	LOAD_KIND_IMAGE_1,		//�Ϲ� �̹���
	LOAD_KIND_IMAGE_2,		//�Ϲ� �̹���(��ġ ��ǥ ����)
	LOAD_KIND_FRAMEIMAGE_0,	//������ �̹���
	LOAD_KIND_FRAMEIMAGE_1,	//������ �̹���(��ġ ��ǥ ����)
	LOAD_KIND_SOUND,		//����
	LOAD_KIND_END
};

//�̹��� ���ҽ� ����ü
struct tagImageResource
{
	string keyName;			//�̹��� Ű��
	const char* fileName;	//���� �̸�
	int x, y;				//��ġ ��ǥ
	int width, height;		//���� ���� ũ��
	int frameX, frameY;		//������
	bool trans;				//��� ���ٰų�?
	COLORREF transColor;	//���� �÷�Ű
};

class loadItem
{
private:
	LOAD_KIND _kind;
	tagImageResource _imageResource;

public:
	//Ű������ �� ��Ʈ������ �ʱ�ȭ
	HRESULT initForImage(string keyName, int width, int height);
	//Ű������ �̹��� ���Ϸ� �ʱ�ȭ (�� ���)
	HRESULT initForImage(string keyName, const char* fileName, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT initForImage(string keyName, const char* fileName, float x, float y, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	//Ű������ ������ �̹��� ���Ϸ� �ʱ�ȭ
	HRESULT initForFrameImage(string keyName, const char* fileName, int width, int height, int frameX, int frameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT initForFrameImage(string keyName, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	//�ε������� ���� ��������
	LOAD_KIND getLoadingKind() { return _kind; }
	//�̹��� ���ҽ� ��������
	tagImageResource getImageResource() { return _imageResource; }

	loadItem() {}
	~loadItem() {}
};

class loading :public gameNode
{
private:
	//�ε� ������ Ŭ������ ���� ���� �� �ݺ���
	typedef vector<loadItem*> arrLoadItem;
	typedef vector<loadItem*>::iterator addLoadItemIter;

private:
	arrLoadItem _vLoadItem;

	//�ε�ȭ�鿡 ����� �̹��� �� �ε���
	image* _background;			//�ε�ȭ�鿡�� ����� ��׶��� �̹���
	progressBar* _loadingBar;	//ȣ��ȭ�鿡�� ����� �ε���
	int _currentGauge;			//�ε��� ������

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//Ű������ �� ��Ʈ������ �ʱ�ȭ
	void loadImage(string strKey, int width, int height);
	//Ű������ �̹��� ���Ϸ� �ʱ�ȭ (�� ���)
	void loadImage(string strKey, const char* fileName, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	void loadImage(string strKey, const char* fileName, float x, float y, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	//Ű������ ������ �̹��� ���Ϸ� �ʱ�ȭ
	void loadFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	void loadFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	//�߿��ϴ�
	//�ε� �Ϸ� ���(�ε��Ϸ��� �� ����)
	BOOL loadingDone();

	//�ε� ������ ���� ��������
	vector<loadItem*> getLoadItem() { return _vLoadItem; }

	loading() {}
	~loading() {}
};

