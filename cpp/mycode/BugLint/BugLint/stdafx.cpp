// stdafx.cpp : source file that includes just the standard includes
// BugLint.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
#include <string>

using namespace std;
// TODO: reference any additional headers you need in STDAFX.H
// and not in this file


//����ʾ��

struct SNotUsed
{
	string str;
	char ac[100];
};

struct SChar
{
	char ac[100];
};

enum ETYPE1
{
	ETYPE1_A,
};

enum ETYPE2
{
	ETYPE2_A,
	ETYPE2_B,
};

void LogSave(const char* fmt, ...)
{
	if(!fmt)
		return;
	char buf[1024] = {0};
	_vsnprintf(buf, sizeof(buf), fmt, (char*) ((&fmt)+1));
	buf[sizeof(buf)-1] = 0;
}
#define LOGSAVE LogSave

void NotNULL(char* p)
{

}

void CheckFormat(char* pMayNull)
{
// 	//�澯���������ο���Ϊ��ָ��
// 	SChar schar1 = {0};
// 	memcpy(pMayNull, schar1.ac, sizeof(schar1));
// 
// 	if(!pMayNull)
// 		return;
// 
// 	SChar schar;
// 	//�澯������δ��ֵ/��ʼ���ͱ�ʹ�ã���������sizeof(schar.ac)==sizeof(schar)����pclint���澯
// 	memcpy(pMayNull, schar.ac, sizeof(schar));
// 
// 	//�澯�����������
// 	memset(&schar, 0x00, sizeof(SNotUsed));
// 
// 	//�澯���⺯���ĸ�ʽ���Ͳ�ƥ��
// 	sprintf(schar.ac, "%s", 1);
//
//	//�澯���Զ��庯���ĸ�ʽ���Ͳ�ƥ��
//	LOGSAVE("%s", 1);
//
// 	
// 	char* p = new char;//�澯���ڴ�й¶
 	char *p2 = NULL;
 	memset(p2, 0x00, 3);	//�澯����ָ��	

// 	ETYPE1 eType1 = ETYPE2_A;
// 	switch (eType1)
// 	{
// 	case ETYPE2_A:	//�澯��switch��case�����Ͳ�ƥ��
// 		
// 		break;
// 	}

}