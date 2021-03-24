#pragma once
#include "singletonBase.h"
//==================================================================
//		## sceneManager ## (씬매니져)
//==================================================================

//게임노드 클래스 전방선언
class gameNode;

class sceneManager : public singletonBase <sceneManager>
{
private:
	typedef map<string, gameNode*> mSceneList;
	typedef map<string, gameNode*>::iterator miSceneList;

private:
	static gameNode* _currentScene;		//현재씬
	mSceneList _mSceneList;				//씬(화면) 목록

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//씬추가
	gameNode* addScene(string sceneName, gameNode* scene);

	//씬변경
	HRESULT changeScene(string sceneName);

	sceneManager();
	~sceneManager();
};

