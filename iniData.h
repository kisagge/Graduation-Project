#pragma once
#include "singletonBase.h"
//==================================================================
//		## iniData ## (INI ������)
//==================================================================

//INI������ ����ü
struct tagIniData
{
	char* section;
	char* key;
	char* value;
};

class iniData : public singletonBase <iniData>
{
private:
	typedef vector<tagIniData> arrIniData;
	typedef vector<tagIniData>::iterator arrIniDataIter;
	typedef vector<arrIniData> arrIniDatas;
	typedef vector<arrIniData>::iterator arrIniDatasIter;

private:
	arrIniDatas _vIniData;

public:
	HRESULT init(void);

	//������ �߰��ϱ�(����, Ű, ���)
	void addData(char* section, char* key, char* value);
	//���̺� (�����̸�) =>�����̸��� �־ (�����̸�.ini) ���Ϸ� �ڵ� ����ǰ� ������
	void iniSave(char* fileName);

	//���ڰ� �ε��ϱ� (�����̸�, ����, Ű)
	char* loadDataString(char* fileName, char* section, char* key);
	//������ �ε��ϱ� (�����̸�, ����, Ű)
	int loadDataInteger(char* fileName, char* section, char* key);

	iniData();
	~iniData();
};

