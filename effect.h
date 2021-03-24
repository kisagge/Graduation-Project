#pragma once
#include "gameNode.h"
//==================================================================
//		## effect ## (이펙트 클래스)
//==================================================================

class effect : public gameNode
{
private:
	image* _effectImage;			//이펙트 이미지
	animation* _effectAni;			//이펙트 애니메이션

	int _x, _y;						//이펙트 터트릴 좌표
	float _elapsedTime;				//이펙트 경과시간(이펙트 속도조절)
	bool _isRunning;				//이펙트 재생중이냐?

public:
	//이펙트 초기화(이펙트이미지, 이펙트의 한프레임 가로길이, 이펙트의 한프레임의 세로길이, FPS(1), 이펙트속도)
	HRESULT init(image* effectImage, int frameW, int frameH, int FPS, float elapsedTime);
	void release(void);
	void update(void);
	void render(void);

	//내가 원하는 좌표에 이펙트 터트리기
	void startEffect(int x, int y);
	//이펙트 멈추기
	void stopEffect(void);
	
	//이펙트 재생중인지 상태값 가져오기
	bool getIsRunning(void) { return _isRunning; }
	
	effect();
	~effect();
};

