#pragma once
#include "singletonBase.h"
#include "image.h"
//==================================================================
//		## animationManager ## (�ִϸ��̼� �Ŵ���)
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

	/*�ִϸ��̼� �߰�*/
	//ó������ ������
	void addDefAnimation(string animationKeyName, char* imageKeyName, int fps, BOOL reverse = FALSE, BOOL loop = FALSE);
	//�迭�� ��Ƽ�
	void addAnimation(string animationKeyName, char* imageKeyName, int* playArr, int arrLen, int fps, BOOL loop = FALSE);
	//���� ���ؼ�
	void addAnimation(string animationKeyName, char* imageKeyName, int start, int end, int fps, BOOL reverse = FALSE, BOOL loop = FALSE);
	
	//�÷���
	void start(string animationKeyName);
	//����
	void stop(string animationKeyName);
	//�Ͻ�����
	void pause(string animationKeyName);
	//�ٽ����
	void resume(string animationKeyName);

	//�ִϸ��̼� ã��
	animation* findAnimation(string animationKeyName);

	//�ִϸ��̼� ���λ���
	void deleteAll(void);


	animationManager();
	~animationManager();
};

