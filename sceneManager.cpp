#include "stdafx.h"
#include "sceneManager.h"
#include "gameNode.h"
sceneManager::sceneManager()
{
}
sceneManager::~sceneManager()
{
}
//==================================================================
//		## 더이상 생성자, 소멸자는 사용하지 않는다 ##
//==================================================================

//스태틱변수 현재씬은 널값으로 초기화
gameNode* sceneManager::_currentScene = NULL;

HRESULT sceneManager::init(void)
{
	return S_OK;
}
void sceneManager::release(void)
{
	//반복자를 통해 맵을 돌면서 하나하나씩 삭제한다
	miSceneList iter = _mSceneList.begin();
	for (;iter != _mSceneList.end();)
	{
		//삭제
		if (iter->second != NULL)
		{
			if (iter->second == _currentScene) iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mSceneList.erase(iter);
		}
		else
		{
			//반복자 증가
			++iter;
		}
	}

	_mSceneList.clear();
}

void sceneManager::update(void)
{
	if (_currentScene) _currentScene->update();
}

void sceneManager::render(void)
{
	if (_currentScene) _currentScene->render();
}

//씬추가
gameNode* sceneManager::addScene(string sceneName, gameNode* scene)
{
	if (!scene) return NULL;
	_mSceneList.insert(make_pair(sceneName, scene));
	return scene;
}


//씬변경
HRESULT sceneManager::changeScene(string sceneName)
{
	miSceneList find = _mSceneList.find(sceneName);

	//못찾았으면 E_FAIL
	if (find == _mSceneList.end()) return E_FAIL;

	//바꾸려는 씬과 현재씬이 같으면 E_FAIL
	if (find->second == _currentScene) return E_FAIL;

	//여기까지 왔으면 문제가 없으니 씬을 초기화 하고 변경해준다
	if (SUCCEEDED(find->second->init()))
	{
		//혹시나 기존 씬이 있으면 릴리즈
		if (_currentScene) _currentScene->release();
		_currentScene = find->second;

		return S_OK;
	}

	return E_FAIL;
}
