#include "stdafx.h"
#include "progressBar.h"
progressBar::progressBar()
{
}
progressBar::~progressBar()
{
}
//==================================================================
//		## ���̻� ������, �Ҹ��ڴ� ������� �ʴ´� ##
//==================================================================

//ü�¹� �ʱ�ȭ(���̹���Ű��, ���̹���Ű��, x, y, ���α���, ���α���)
HRESULT progressBar::init(char* frontImageKey, char* backImageKey, float x, float y, int width, int height)
{
	//ü�¹� ��ġ �ʱ�ȭ
	_x = x;
	_y = y;

	//ü�¹� ��Ʈ ��ġ �� ũ�� �ʱ�ȭ
	_rcProgress = RectMake(x, y, width, height);

	//Ű������ �̹����̸�(~.bmp)�� �ٷ� �ʱ�ȭ �ϱ�
	char frontImageName[128];
	char backImageName[128];

	//�޸𸮸� ����ϰ� �о�����
	ZeroMemory(frontImageName, sizeof(frontImageName));
	ZeroMemory(backImageName, sizeof(backImageName));
	
	//���α׷�����.bmp�� ���α׷����� ��� Ű������ ������
	sprintf(frontImageName, "%s", frontImageKey);
	sprintf(backImageName, "%s", backImageKey);

	//ü�¹� �̹��� �ʱ�ȭ
	_progressBarFront = IMAGEMANAGER->addImage(frontImageKey, frontImageName, x, y, width, height, true, RGB(255, 0, 255));
	_progressBarBack = IMAGEMANAGER->addImage(backImageKey, backImageName, x, y, width, height, true, RGB(255, 0, 255));

	//���α��� �ʱ�ȭ
	_width = _progressBarFront->getWidth();

	return S_OK;
}

void progressBar::release(void)
{
}

void progressBar::update(void)
{
	_rcProgress = RectMakeCenter(
		_x + _progressBarBack->getWidth() / 2,
		_y + _progressBarBack->getHeight() / 2,
		_progressBarBack->getWidth(),
		_progressBarBack->getHeight());
}

void progressBar::render(void)
{
	//���α׷����� �� �̹���(����� �ʿ� ����)
	_progressBarBack->render(getMemDC(), _rcProgress.left, _y,
		0, 0, _progressBarBack->getWidth(), _progressBarBack->getHeight());
	//���α׷����� �� �̹���(���α��̰� ����Ǿ� �Ѵ�)
	_progressBarFront->render(getMemDC(), _rcProgress.left, _y,
		0, 0, _width, _progressBarBack->getHeight());
}

//���α׷����� ������ ����(�ʱ�ȭ �� �� ������!!)
void progressBar::setGauge(float currentGauge, float maxGauge)
{
	_width = (currentGauge / maxGauge) * _progressBarBack->getWidth();
}
