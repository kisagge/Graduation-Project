#pragma once
#include "gameNode.h"
//==================================================================
//		## progressBar ## (���α׷�����)
//==================================================================

class progressBar : public gameNode
{
private:
	RECT _rcProgress;			//ü�¹� ��Ʈ
	int _x, _y;					//ü�¹� ��ǥ
	int _width;					//ü�¹� ���α���(�̰� �����Ѵ�1)

	image* _progressBarFront;	//ü�¹� ���̹���
	image* _progressBarBack;	//ü�¹� ���̹���
public:
	//ü�¹� �ʱ�ȭ(���̹���Ű��, ���̹���Ű��, x, y, ���α���, ���α���)
	HRESULT init(char* frontImageKey, char* backImageKey, float x, float y, int width, int height);
	void release(void);
	void update(void);
	void render(void);

	//���α׷����� ������ ����(�ʱ�ȭ �� �� ������!!)
	void setGauge(float currentGauge, float maxGauge);

	//���α׷����� ��ġ����
	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }
	//ü�¹� ��Ʈ ��������
	RECT getRect(void) { return _rcProgress; }

	progressBar();
	~progressBar();
};

