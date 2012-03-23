// AutoLinkSet.h: interface for the CAutoLinkSet class.
// paled, 2003.8.27
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AUTOLINKSET_H__5708545C_E8F2_4155_AC66_4191BE0F150E__INCLUDED_)
#define AFX_AUTOLINKSET_H__5708545C_E8F2_4155_AC66_4191BE0F150E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

////////////////////////////////////////////////////////////////
// ˵��:����AutoLink������Ҫ�ø������ָ���ʼ���Լ�������Ϊ�ա�Init()
//		����AutoLinkSet����ֱ����Iterator���������еĿն���ᱻ�Զ������
////////////////////////////////////////////////////////////////
// ˵��:��ģ����ҪGetID()����֧�֣�ͬʱҲ��Ҫ����DWORD
//		���������ʵ��һ��������CAutoLink<T>& QueryLink(const CAutoLink<T>&)�����ء���AutoLink�������á�(����ֻ�����ͣ�������)
// ��ע��� Size()������������ж���Ч�ʲ��ߡ������ʱ��Ҫ̫Ƶ����

#include "AutoLink.h"
#include <vector>
using namespace std;

template<class T>
class CAutoLinkSet
{
protected:
	typedef	vector<CAutoLink<T> >	VECTOR_SET;
public:
	CAutoLinkSet() {}
	virtual ~CAutoLinkSet();
public:
	static CAutoLinkSet<T>*	CreateNew() { return new CAutoLinkSet<T>(); }
	void		Release			()				{ delete this; }

//////////////////////////////////////////////////////
public:	// new traversal
	class	Iterator{
	private: // create by parent class
		Iterator(VECTOR_SET* pSet) : m_pSet(pSet),m_idx(pSet->size()-1),m_pObj(0) {}
		friend class CAutoLinkSet<T>;
	public:
//		Iterator(const Iterator& iter);		// need not define this ^_^

	public: // application
		bool	Next()
		{
			if(m_idx<0) return m_pObj=NULL,false; 
			
			do
			{
				m_pObj=m_pSet->at(m_idx);
				if(!m_pObj)
					m_pSet->erase(m_pSet->begin() + m_idx);
				m_idx--;
			}
			while(m_idx>=0 && m_pObj==0);
			
			return m_pObj != NULL;
		}

		void	Reset()		{ m_idx=m_pSet->size()-1; m_pObj=NULL; }
		operator T*()							{ return m_pObj; }
		T * operator->()						{ return m_pObj; }

	protected:
		VECTOR_SET*	m_pSet;
		int			m_idx;
		T*			m_pObj;
	};
public: // traverse
	Iterator	NewEnum		() 						{ return Iterator(&m_setObj); }
	int			Size		();
//////////////////////////////////////////////////////

public: // application
	bool		AddObj			(const CAutoLink<T>& pObj);
	bool		AddObj			(T* ptr);
	bool		DelObj			(DWORD idObj);
	bool		DelObj			(Iterator& iter);
	T*			GetObj			(DWORD idObj);

protected:
	VECTOR_SET			m_setObj;
};

//////////////////////////////////////////////////////////////////////
template<class T>
CAutoLinkSet<T>::~CAutoLinkSet()
{
}

//////////////////////////////////////////////////////////////////////
template<class T>
bool CAutoLinkSet<T>::AddObj(const CAutoLink<T>& pObj)
{
	CHECKF(pObj && pObj->GetID());
	ASSERT(!DelObj(pObj->GetID()));

	m_setObj.push_back(pObj);
	return true;
}

//////////////////////////////////////////////////////////////////////
template<class T>
bool CAutoLinkSet<T>::AddObj(T* ptr)
{
	CHECKF(ptr && ptr->GetID());
	ASSERT(!DelObj(ptr->GetID()));

	CAutoLink<T>	link(ptr->QueryLink(), ptr);
	m_setObj.push_back(link);
	return true;
}

//////////////////////////////////////////////////////////////////////
template<class T>
bool CAutoLinkSet<T>::DelObj(Iterator& iter)
{
	if(iter.m_pObj)
	{
		iter.m_pObj	= NULL;

		int	idx = iter.m_idx+1;
		IF_OK(idx < m_setObj.size())
			m_setObj.erase(m_setObj.begin() + idx);

		return true;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////
template<class T>
bool CAutoLinkSet<T>::DelObj(DWORD idObj)
{
	CHECKF(idObj);
	for(int i=0;i<m_setObj.size();i++)
	{ 
		T* pObj=m_setObj[i];
		if(pObj && pObj->GetID()==idObj)
		{
			m_setObj.erase(m_setObj.begin()+i);
			return true; 
		}
	}
	return false;
}

//////////////////////////////////////////////////////////////////////
template<class T>
T* CAutoLinkSet<T>::GetObj(DWORD idObj)
{
	for(int i=0;i<m_setObj.size();i++)
	{
		T* pObj=m_setObj[i];
		if(pObj && pObj->GetID()==idObj)
		{
			return pObj;
		}
	}
	return NULL;
}

//////////////////////////////////////////////////////////////////////
template<class T>
int CAutoLinkSet<T>::Size()
{
	for(int i=m_setObj.size()-1; i>=0; i--)		// ɾ��������
	{
		T* pObj=m_setObj[i];
		if(!pObj)
		{
			m_setObj.erase(m_setObj.begin()+i);
		}
	}
	return m_setObj.size();
}



#endif // !defined(AFX_AUTOLINKSET_H__5708545C_E8F2_4155_AC66_4191BE0F150E__INCLUDED_)
