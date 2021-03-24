#pragma once
#include "singletonBase.h"
//==================================================================
//		## effectManager ## (����Ʈ �Ŵ���)
//==================================================================

//����Ʈ Ŭ���� ���漱�� (����ƮŬ������ ���ӳ�带 ��� �޾ұ⶧���� ������)
class effect;

class effectManager : public singletonBase <effectManager>
{
private:
	//����ƮŬ������ ���� ����
	typedef vector<effect*> vEffect;
	typedef vector<effect*>::iterator viEffect;
	//����ƮŬ������ ����ִ� ���͸� ���� ��
	typedef map<string, vEffect> mEffect;
	typedef map<string, vEffect>::iterator miEffect;
	//��� ����Ʈ�� ������ ����(�̺�Ʈ�� ����ִ� ���͸� ���� ���� �ٽ� ���� ����)
	typedef vector<mEffect> vTotalEffect;
	typedef vector<mEffect>::iterator viTotalEffect;

private:
	//���� ��� ����Ʈ�� ����ִ� ����
	vTotalEffect _vTotalEffect;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//����Ʈ�߰�(����ƮŰ��, �̹����̸�, �̹�������ũ��, �̹�������ũ��, �������Ӱ���ũ��, �������Ӽ���ũ��, FPS, ����Ʈ�ӵ�, ���۰���)
	void addEffect(string effectKey, char* imageName, int imageW, int imageH, int frameW, int frameH, int fps, float elapsedTime, int buffer);

	//����Ʈ �÷���(����ƮŰ��, ����Ʈ ��Ʈ�� x, y ��ǥ)
	void play(string effectKey, int x, int y);

	effectManager();
	~effectManager();
};

