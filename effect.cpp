#include "stdafx.h"
#include "effect.h"
effect::effect() : _effectImage(NULL), _effectAni(NULL), _isRunning(FALSE), _x(0), _y(0)
{
}
effect::~effect()
{
}
//==================================================================
//		## ���̻� ������, �Ҹ��ڴ� ������� �ʴ´� ##
//==================================================================

//����Ʈ �ʱ�ȭ(����Ʈ�̹���, ����Ʈ�� �������� ���α���, ����Ʈ�� ���������� ���α���, FPS(1), ����Ʈ�ӵ�)
HRESULT effect::init(image* effectImage, int frameW, int frameH, int FPS, float elapsedTime)
{
	//����Ʈ �̹��� ������ �ٷ� ����
	if (!effectImage) return E_FAIL;

	//������ �ʱ�ȭ
	_effectImage = effectImage;
	_elapsedTime = elapsedTime;
	_isRunning = false;

	//����Ʈ �ִϸ��̼��� ������ ���� �����ϱ�
	if (!_effectAni) _effectAni = new animation;
	//�ִϸ��̼� ���� �ʱ�ȭ
	_effectAni->init(_effectImage->getWidth(), _effectImage->getHeight(), frameW, frameH);
	_effectAni->setDefPlayFrame();
	_effectAni->setFPS(FPS);

	return S_OK;
}

void effect::release(void)
{
	SAFE_DELETE(_effectAni);
}

void effect::update(void)
{
	if (_isRunning)
	{
		_effectAni->frameUpdate(_elapsedTime);
	}

	//����Ʈ �ִϸ��̼��� ���ᰡ �Ǹ� ���߱�
	if (!_effectAni->isPlay()) stopEffect();
}

void effect::render(void)
{
	if (_isRunning)
	{
		_effectImage->aniRender(getMemDC(), _x, _y, _effectAni);
	}
}

//���� ���ϴ� ��ǥ�� ����Ʈ ��Ʈ����
void effect::startEffect(int x, int y)
{
	//��ġ��ǥ�� ���� ��ǥ�� �����
	_x = x - (_effectAni->getFrameWidth() / 2);
	_y = y - (_effectAni->getFrameHeight() / 2);

	_isRunning = true;
	_effectAni->start();
}

//����Ʈ ���߱�
void effect::stopEffect(void)
{
	_isRunning = false;
}
