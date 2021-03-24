#include "stdafx.h"
#include "txtData.h"
txtData::txtData()
{
}
txtData::~txtData()
{
}
//==================================================================
//		## 더이상 생성자, 소멸자는 사용하지 않는다 ##
//==================================================================

HRESULT txtData::init()
{
	return S_OK;
}

//세이브
void txtData::txtSave(char* saveFileName, vector<string> vStr)
{
	HANDLE file;
	char str[128];
	DWORD write;
	//100,200,300
	//strcpy(str, vectorArrayCombine(vStr));
	strncpy_s(str, 128, vectorArrayCombine(vStr), 126);

	file = CreateFile(saveFileName,
		GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, str, 128, &write, NULL);
	CloseHandle(file);
}

char* txtData::vectorArrayCombine(vector<string> vArray)
{
	char str[128];
	ZeroMemory(str, sizeof(str)); //memset(str, 0, sizeof(str));
	
	for (int i = 0; i < vArray.size(); i++)
	{
		//strcat(str, vArray[i].c_str());
		strncat_s(str, 128, vArray[i].c_str(), 126);
		if ((i + 1) < vArray.size())
		{
			strcat(str, ",");
		}
	}

	return str;
}

//로드
vector<string> txtData::txtLoad(char* loadFileName)
{
	HANDLE file;
	char str[128];
	DWORD read;

	ZeroMemory(str, sizeof(str));

	file = CreateFile(loadFileName,
		GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, 128, &read, NULL);

	CloseHandle(file);

	return charArraySeparation(str);
}

vector<string> txtData::charArraySeparation(char charArray[])
{
	vector<string> vArray;
	char* temp;
	char* separator = ",";
	char* token;

	token = strtok(charArray, separator);
	vArray.push_back(token);

	while (NULL != (token = strtok(NULL, separator)))
	{
		vArray.push_back(token);
	}

	return vArray;
}