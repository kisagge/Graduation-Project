#pragma once
#include "singletonBase.h"
//==================================================================
//		## iniData ## (INI 데이터)
//==================================================================

//INI데이터 구조체
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

	//데이터 추가하기(섹션, 키, 밸류)
	void addData(char* section, char* key, char* value);
	//세이브 (파일이름) =>파일이름만 넣어도 (파일이름.ini) 파일로 자동 저장되게 만들자
	void iniSave(char* fileName);

	//문자값 로드하기 (파일이름, 섹션, 키)
	char* loadDataString(char* fileName, char* section, char* key);
	//정수값 로드하기 (파일이름, 섹션, 키)
	int loadDataInteger(char* fileName, char* section, char* key);

	iniData();
	~iniData();
};

