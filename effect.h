#pragma once
#include "gameNode.h"
//==================================================================
//		## effect ## (����Ʈ Ŭ����)
//==================================================================

class effect : public gameNode
{
private:
	image* _effectImage;			//����Ʈ �̹���
	animation* _effectAni;			//����Ʈ �ִϸ��̼�

	int _x, _y;						//����Ʈ ��Ʈ�� ��ǥ
	float _elapsedTime;				//����Ʈ ����ð�(����Ʈ �ӵ�����)
	bool _isRunning;				//����Ʈ ������̳�?

public:
	//����Ʈ �ʱ�ȭ(����Ʈ�̹���, ����Ʈ�� �������� ���α���, ����Ʈ�� ���������� ���α���, FPS(1), ����Ʈ�ӵ�)
	HRESULT init(image* effectImage, int frameW, int frameH, int FPS, float elapsedTime);
	void release(void);
	void update(void);
	void render(void);

	//���� ���ϴ� ��ǥ�� ����Ʈ ��Ʈ����
	void startEffect(int x, int y);
	//����Ʈ ���߱�
	void stopEffect(void);
	
	//����Ʈ ��������� ���°� ��������
	bool getIsRunning(void) { return _isRunning; }
	
	effect();
	~effect();
};
