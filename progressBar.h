#pragma once
#include "gameNode.h"
//==================================================================
//		## progressBar ## (프로그래스바)
//==================================================================

class progressBar : public gameNode
{
private:
	RECT _rcProgress;			//체력바 렉트
	int _x, _y;					//체력바 좌표
	int _width;					//체력바 가로길이(이걸 조정한다1)

	image* _progressBarFront;	//체력바 앞이미지
	image* _progressBarBack;	//체력바 백이미지
public:
	//체력바 초기화(앞이미지키값, 백이미지키값, x, y, 가로길이, 세로길이)
	HRESULT init(char* frontImageKey, char* backImageKey, float x, float y, int width, int height);
	void release(void);
	void update(void);
	void render(void);

	//프로그래스바 게이지 셋팅(초기화 후 꼭 해주자!!)
	void setGauge(float currentGauge, float maxGauge);

	//프로그래스바 위치셋팅
	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }
	//체력바 렉트 가져오기
	RECT getRect(void) { return _rcProgress; }

	progressBar();
	~progressBar();
};

