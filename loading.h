#pragma once
#include "gameNode.h"
#include "progressBar.h"

//로드 아이템 종류
enum LOAD_KIND
{
	LOAD_KIND_IMAGE_0,		//빈 비트맵 이미지
	LOAD_KIND_IMAGE_1,		//일반 이미지
	LOAD_KIND_IMAGE_2,		//일반 이미지(위치 좌표 있음)
	LOAD_KIND_FRAMEIMAGE_0,	//프레임 이미지
	LOAD_KIND_FRAMEIMAGE_1,	//프레임 이미지(위치 좌표 있음)
	LOAD_KIND_SOUND,		//사운드
	LOAD_KIND_END
};

//이미지 리소스 구조체
struct tagImageResource
{
	string keyName;			//이미지 키값
	const char* fileName;	//파일 이름
	int x, y;				//위치 좌표
	int width, height;		//가로 세로 크기
	int frameX, frameY;		//프레임
	bool trans;				//배경 없앨거냐?
	COLORREF transColor;	//투명 컬러키
};

class loadItem
{
private:
	LOAD_KIND _kind;
	tagImageResource _imageResource;

public:
	//키값으로 빈 비트맵으로 초기화
	HRESULT initForImage(string keyName, int width, int height);
	//키값으로 이미지 파일로 초기화 (주 사용)
	HRESULT initForImage(string keyName, const char* fileName, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT initForImage(string keyName, const char* fileName, float x, float y, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	//키값으로 프레임 이미지 파일로 초기화
	HRESULT initForFrameImage(string keyName, const char* fileName, int width, int height, int frameX, int frameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	HRESULT initForFrameImage(string keyName, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	//로딩아이템 종류 가져오기
	LOAD_KIND getLoadingKind() { return _kind; }
	//이미지 리소스 가져오기
	tagImageResource getImageResource() { return _imageResource; }

	loadItem() {}
	~loadItem() {}
};

class loading :public gameNode
{
private:
	//로드 아이템 클래스를 담을 벡터 및 반복자
	typedef vector<loadItem*> arrLoadItem;
	typedef vector<loadItem*>::iterator addLoadItemIter;

private:
	arrLoadItem _vLoadItem;

	//로딩화면에 사용할 이미지 및 로딩바
	image* _background;			//로딩화면에서 사용할 백그라운드 이미지
	progressBar* _loadingBar;	//호딩화면에서 사용할 로딩바
	int _currentGauge;			//로딩바 게이지

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//키값으로 빈 비트맵으로 초기화
	void loadImage(string strKey, int width, int height);
	//키값으로 이미지 파일로 초기화 (주 사용)
	void loadImage(string strKey, const char* fileName, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	void loadImage(string strKey, const char* fileName, float x, float y, int width, int height, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	//키값으로 프레임 이미지 파일로 초기화
	void loadFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));
	void loadFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL isTrans = FALSE, COLORREF transColor = RGB(0, 0, 0));

	//중요하다
	//로딩 완료 됬냐(로딩완료후 씬 변경)
	BOOL loadingDone();

	//로드 아이템 벡터 가져오기
	vector<loadItem*> getLoadItem() { return _vLoadItem; }

	loading() {}
	~loading() {}
};

