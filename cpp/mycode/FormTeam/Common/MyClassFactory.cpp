// MyClassFactory.cpp
//
//////////////////////////////////////////////////////////////////////
// ע�⣺���೧��ͨ��ȫ�ֺ����Զ�ע��ģ���֧����ȫ�ֶ���Ĺ��캯���е���CreateNewObj

#include <afxwin.h>
#include "MyClassFactory.h"
using namespace myclassfactory;

namespace myclassfactory{
//	typedef	map<CLS_ID, IMyClassFactory*>	FACTORY_SET;
	FACTORY_SET*	x_psetFactory=NULL;		// �ڲ�ʹ�á�(��Ϊû��extern������ÿ��DLL���Խ�һ����)
	int				x_nCountObj = 0;
};

bool myclassfactory::CreateNewObj(CLS_ID idCls, void** ppObj)
{
	CHECKF(ppObj);
	CHECKF(x_psetFactory);
	*ppObj = NULL;

	FACTORY_SET::iterator iter=x_psetFactory->find(idCls);
	if(iter != x_psetFactory->end())
	{
		iter->second->CreateNewObj(ppObj);
		x_nCountObj++;
		return *ppObj != NULL;
	}

	MYASSERT(!"invalid idCls in myclassfactory::CreateNewObj.");	// ע�⣺REGISTER_FACTORY(����غ�)��������С���Ч���롱��CPP�С�����ֻ�Ŵ����Զ��ꡣ
	return false;
}

void myclassfactory::ReleaseObj(CLS_ID idCls, void** ppObj)
{
	CHECK(ppObj);
	if(!*ppObj)
		return;		// δ��ʼ���Ķ���Ҳ������NULLָ����ô˺���

	CHECK(x_psetFactory);
	CHECK(x_nCountObj > 0);
	FACTORY_SET::iterator iter=x_psetFactory->find(idCls);
	if(iter != x_psetFactory->end())
	{
		iter->second->ReleaseObj(ppObj);
		x_nCountObj--;
//BUG		if(x_nCountObj <= 0)
//BUG		{
//BUG			// ʵ�����Զ�ɾ�������󣬿�����BUG	- paled
//BUG			// �Զ�ɾ���п��ܻ�Ƶ��ɾ���ʹ���������
//BUG			delete x_psetFactory;
//BUG			x_psetFactory = NULL;
//BUG		}
		return ;
	}

	MYASSERT(!"invalid idCls in myclassfactory::ReleaseObj.");
}

void myclassfactory::RegisterMyClass(CLS_ID idCls, IMyClassFactory* pFactory)
{
	TRACE("RegisterMyClass - 0x%X\n", idCls);

	if(!x_psetFactory)
		x_psetFactory = new FACTORY_SET;	// ������ͷţ����й̶���С�ڴ�й©	- paled

	FACTORY_SET::iterator iter=x_psetFactory->find(idCls);
	if(iter != x_psetFactory->end())
	{
		MYASSERT(!"multi register idCls in myclassfactory::RegisterMyClass.");
	}

	(*x_psetFactory)[idCls] = pFactory;
}

void AddFactorySet(FACTORY_SET* pSet)
{
	if(!x_psetFactory)
		x_psetFactory = new FACTORY_SET;	// ������ͷţ����й̶���С�ڴ�й©	- paled

	CHECK(x_psetFactory != pSet);

	for(FACTORY_SET::iterator iter = pSet->begin(); iter != pSet->end(); iter++)
	{
		CLS_ID idCls = iter->first;
		IMyClassFactory* pFactory = iter->second;

		TRACE("AddFactorySet - 0x%X\n", idCls);

		FACTORY_SET::iterator iter2=x_psetFactory->find(idCls);
		if(iter2 != x_psetFactory->end())
		{
			MYASSERT(!"multi AddFactorySet idCls in myclassfactory::RegisterMyClass.");
		}

		(*x_psetFactory)[idCls] = pFactory;
	}	
}
