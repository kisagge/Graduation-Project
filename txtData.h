#pragma once
#include "singletonBase.h"
//==================================================================
//		## txtData ## (�ؽ�Ʈ ������)
//==================================================================

class txtData : public singletonBase <txtData>
{
public:
	HRESULT init();

	//���̺�
	void txtSave(char* saveFileName, vector<string> vStr);
	char* vectorArrayCombine(vector<string> vArray);

	//�ε�
	vector<string> txtLoad(char* loadFileName);
	vector<string> charArraySeparation(char charArray[]);

	txtData();
	~txtData();
};

