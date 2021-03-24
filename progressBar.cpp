#include "stdafx.h"
#include "progressBar.h"
progressBar::progressBar()
{
}
progressBar::~progressBar()
{
}
//==================================================================
//		## 더이상 생성자, 소멸자는 사용하지 않는다 ##
//==================================================================

//체력바 초기화(앞이미지키값, 백이미지키값, x, y, 가로길이, 세로길이)
HRESULT progressBar::init(char* frontImageKey, char* backImageKey, float x, float y, int width, int height)
{
	//체력바 위치 초기화
	_x = x;
	_y = y;

	//체력바 렉트 위치 및 크기 초기화
	_rcProgress = RectMake(x, y, width, height);

	//키값으로 이미지이름(~.bmp)을 바로 초기화 하기
	char frontImageName[128];
	char backImageName[128];

	//메모리를 깔끔하게 밀어주자
	ZeroMemory(frontImageName, sizeof(frontImageName));
	ZeroMemory(backImageName, sizeof(backImageName));
	
	//프로그래스바.bmp를 프로그래스바 라는 키값으로 만들자
	sprintf(frontImageName, "%s", frontImageKey);
	sprintf(backImageName, "%s", backImageKey);

	//체력바 이미지 초기화
	_progressBarFront = IMAGEMANAGER->addImage(frontImageKey, frontImageName, x, y, width, height, true, RGB(255, 0, 255));
	_progressBarBack = IMAGEMANAGER->addImage(backImageKey, backImageName, x, y, width, height, true, RGB(255, 0, 255));

	//가로길이 초기화
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
	//프로그래스바 백 이미지(변경될 필요 없다)
	_progressBarBack->render(getMemDC(), _rcProgress.left, _y,
		0, 0, _progressBarBack->getWidth(), _progressBarBack->getHeight());
	//프로그래스바 앞 이미지(가로길이가 변경되야 한다)
	_progressBarFront->render(getMemDC(), _rcProgress.left, _y,
		0, 0, _width, _progressBarBack->getHeight());
}

//프로그래스바 게이지 셋팅(초기화 후 꼭 해주자!!)
void progressBar::setGauge(float currentGauge, float maxGauge)
{
	_width = (currentGauge / maxGauge) * _progressBarBack->getWidth();
}
