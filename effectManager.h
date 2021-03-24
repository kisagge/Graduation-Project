#pragma once
#include "singletonBase.h"
//==================================================================
//		## effectManager ## (이펙트 매니져)
//==================================================================

//이펙트 클래스 전방선언 (이펙트클래스는 게임노드를 상속 받았기때문에 뻥난다)
class effect;

class effectManager : public singletonBase <effectManager>
{
private:
	//이펙트클래스를 담을 벡터
	typedef vector<effect*> vEffect;
	typedef vector<effect*>::iterator viEffect;
	//이펙트클래스가 담겨있는 벡터를 담을 맵
	typedef map<string, vEffect> mEffect;
	typedef map<string, vEffect>::iterator miEffect;
	//모든 이펙트를 관리할 벡터(이벡트가 담겨있는 벡터를 담은 맵을 다시 담은 벡터)
	typedef vector<mEffect> vTotalEffect;
	typedef vector<mEffect>::iterator viTotalEffect;

private:
	//실제 모든 이펙트가 담겨있는 벡터
	vTotalEffect _vTotalEffect;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//이펙트추가(이펙트키값, 이미지이름, 이미지가로크기, 이미지세로크기, 한프레임가로크기, 한프레임세로크기, FPS, 이펙트속도, 버퍼갯수)
	void addEffect(string effectKey, char* imageName, int imageW, int imageH, int frameW, int frameH, int fps, float elapsedTime, int buffer);

	//이펙트 플레이(이펙트키값, 이펙트 터트릴 x, y 좌표)
	void play(string effectKey, int x, int y);

	effectManager();
	~effectManager();
};

