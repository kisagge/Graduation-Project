#include "stdafx.h"
#include "effect.h"
effect::effect() : _effectImage(NULL), _effectAni(NULL), _isRunning(FALSE), _x(0), _y(0)
{
}
effect::~effect()
{
}
//==================================================================
//		## 더이상 생성자, 소멸자는 사용하지 않는다 ##
//==================================================================

//이펙트 초기화(이펙트이미지, 이펙트의 한프레임 가로길이, 이펙트의 한프레임의 세로길이, FPS(1), 이펙트속도)
HRESULT effect::init(image* effectImage, int frameW, int frameH, int FPS, float elapsedTime)
{
	//이펙트 이미지 없을땐 바로 리턴
	if (!effectImage) return E_FAIL;

	//변수들 초기화
	_effectImage = effectImage;
	_elapsedTime = elapsedTime;
	_isRunning = false;

	//이펙트 애니메이션이 없으면 새로 생성하기
	if (!_effectAni) _effectAni = new animation;
	//애니메이션 정보 초기화
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

	//이펙트 애니메이션이 종료가 되면 멈추기
	if (!_effectAni->isPlay()) stopEffect();
}

void effect::render(void)
{
	if (_isRunning)
	{
		_effectImage->aniRender(getMemDC(), _x, _y, _effectAni);
	}
}

//내가 원하는 좌표에 이펙트 터트리기
void effect::startEffect(int x, int y)
{
	//위치좌표를 센터 좌표로 만들기
	_x = x - (_effectAni->getFrameWidth() / 2);
	_y = y - (_effectAni->getFrameHeight() / 2);

	_isRunning = true;
	_effectAni->start();
}

//이펙트 멈추기
void effect::stopEffect(void)
{
	_isRunning = false;
}
