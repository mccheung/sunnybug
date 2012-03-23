// lint_sample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <TChar.h>
#include "../../../toolkits/PCLint.h"
#pragma warning(disable:4996)
using namespace std;

#define LOGSAVE LogSave
#define UNUSED_ALWAYS(x) x

//////////////////////////////////////////////////////////////////////////

struct SMALL_BUF
{
	char ac[100];
};

struct LARGE_BUF
{
	char ac[1024];
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

SMALL_BUF* my_new()
{
	return new SMALL_BUF;
}

LINT_LIKE_FUNC(memcpy, my_memcpy)
void* my_memcpy(void* dst, const void* src, const int len)
{
	if(!dst || !src)
		return NULL;
	return memcpy(dst, src, len);
}

LINT_LIKE_FUNC(memset, my_memset)
void* my_memset(void* dst, const int val, const int len)
{
	if(!dst)
		return NULL;
	return memset(dst, val, len);
}

LINT_LIKE_FUNC(free, my_delete)
template<class T>
void my_delete(T*& p)
{
	if(!p)
		return;
	delete p;
	p = NULL;
}

void LogSave(const char* fmt, ...)
{
	if(!fmt)
		return;
	char buf[1024] = {0};
	_vsnprintf(buf, sizeof(buf), fmt, (char*) ((&fmt)+1));
	buf[sizeof(buf)-1] = 0;
}

#define SAFE_DELETE(ptr)	do{ try{ delete ptr; }catch(...){ LogSave("in %s %d", __FILE__, __LINE__); } }while(0)


template <class T>
class TMyPtrMap
{
public:
	static TMyPtrMap<T>* CreateNew()	{ return new TMyPtrMap<T>; }
	TMyPtrMap():m_p(NULL)				{ }
	virtual ~TMyPtrMap()				{ }

	LINT_CUSTODIAL_TEMPLATE(TMyPtrMap, AddObj);
	void	AddObj(T* p)				{ SAFE_DELETE(m_p); m_p = p; }
protected:
	T* m_p;
};
typedef TMyPtrMap<int> CMyPtrMap;

 
void Check(char* pParam)
{
  	SMALL_BUF schar1 = {0};
  	my_memcpy(pParam, schar1.ac, sizeof(schar1));	//�澯���������ο���Ϊ��ָ��
 
	if(!pParam)
		return;

 	SMALL_BUF stSmallBuff;
 	my_memcpy(pParam, stSmallBuff.ac, sizeof(stSmallBuff));	//�澯������δ��ֵ/��ʼ��
 	my_memset(&stSmallBuff, 0x00, sizeof(stSmallBuff)+1);	//�澯�����������
	
	std::string str = "log";
	LOGSAVE("%s", str);	//�澯����ʽ���Ͳ�ƥ��
	
	ETYPE1 eType1 = ETYPE1_A;
	switch (eType1)
	{
	case ETYPE2_A:	//�澯��switch��case�����Ͳ�ƥ��
		break;
	}

	LARGE_BUF* pMalloc = new LARGE_BUF;
	my_memcpy(pMalloc, &stSmallBuff, sizeof(LARGE_BUF));	//�澯���ڶ��������Ļ��������

	SAFE_DELETE(pMalloc);
	my_memset(pMalloc, 0x00, sizeof(*pMalloc));

	CMyPtrMap* pMyMap = CMyPtrMap::CreateNew();
	int* pInt = new int;
	pMyMap->AddObj(pInt);
	*pInt = 3;				//�澯��Ұָ�룬��Ϊָ��Ӧ���ѱ�AddObj()�й�
	//SAFE_DELETE(pMyMap);
}

int main(int argc, char* argv[])
{
	UNUSED_ALWAYS(argc);
	UNUSED_ALWAYS(argv);
	Check(NULL);

	return 0;
}

