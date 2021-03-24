#pragma once
#include "singletonBase.h"
#include "image.h"
//==================================================================
//		## animationManager ## (애니메이션 매니져)
//==================================================================

class animationManager : public singletonBase <animationManager>
{
private:
	typedef map<string, animation*> arrAnimation;
	typedef map<string, animation*>::iterator iterAnimation;

private:
	arrAnimation _mTotalAnimation;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	/*애니메이션 추가*/
	//처음부터 끝까지
	void addDefAnimation(string animationKeyName, char* imageKeyName, int fps, BOOL reverse = FALSE, BOOL loop = FALSE);
	//배열에 담아서
	void addAnimation(string animationKeyName, char* imageKeyName, int* playArr, int arrLen, int fps, BOOL loop = FALSE);
	//구간 정해서
	void addAnimation(string animationKeyName, char* imageKeyName, int start, int end, int fps, BOOL reverse = FALSE, BOOL loop = FALSE);
	
	//플레이
	void start(string animationKeyName);
	//정지
	void stop(string animationKeyName);
	//일시정지
	void pause(string animationKeyName);
	//다시재생
	void resume(string animationKeyName);

	//애니메이션 찾기
	animation* findAnimation(string animationKeyName);

	//애니메이션 전부삭제
	void deleteAll(void);


	animationManager();
	~animationManager();
};

