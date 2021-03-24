#include "stdafx.h"
#include "iniData.h"
iniData::iniData()
{
}
iniData::~iniData()
{
}
//==================================================================
//		## 더이상 생성자, 소멸자는 사용하지 않는다 ##
//==================================================================

HRESULT iniData::init(void)
{
	return S_OK;
}


//데이터 추가하기(섹션, 키, 밸류)
void iniData::addData(char* section, char* key, char* value)
{
	//ini데이터 구조체 선언, 초기화
	tagIniData iniData;
	iniData.section = section;
	iniData.key = key;
	iniData.value = value;

	//ini데이터 구조체 벡터에 담기
	arrIniData vIniData;
	vIniData.push_back(iniData);

	//모든데이터는 _vIniData에 구조체를 담을 벡터를 담기
	_vIniData.push_back(vIniData);
}


//세이브 (파일이름) =>파일이름만 넣어도 (파일이름.ini) 파일로 자동 저장되게 만들자
void iniData::iniSave(char* fileName)
{
	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));
	sprintf(dir, "\\%s.ini", fileName);

	GetCurrentDirectory(256, str);
	strcat(str, dir);

	for (int i = 0; i < _vIniData.size(); i++)
	{
		arrIniData vData = _vIniData[i];
		WritePrivateProfileString(vData[0].section, vData[0].key, vData[0].value, str);
		vData.clear();
	}

	_vIniData.clear();
}

//문자값 로드하기 (파일이름, 섹션, 키)
char* iniData::loadDataString(char* fileName, char* section, char* key)
{
	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));
	sprintf(dir, "\\%s.ini", fileName);

	GetCurrentDirectory(256, str);
	strcat(str, dir);

	char data[64] = { NULL };
	GetPrivateProfileString(section, key, "", data, 64, str);

	return data;
}

//정수값 로드하기 (파일이름, 섹션, 키)
int iniData::loadDataInteger(char* fileName, char* section, char* key)
{
	char str[256];
	char dir[256];
	ZeroMemory(str, sizeof(str));
	ZeroMemory(dir, sizeof(dir));
	sprintf(dir, "\\%s.ini", fileName);

	GetCurrentDirectory(256, str);
	strcat(str, dir);

	return GetPrivateProfileInt(section, key, 0, str);
}
