// SafeLinkSet.h: interface for the CSafeLinkSet class.
// paled, 2007-3-21 �½�
// paled, 2007-3-28 ��ɵ�Ԫ����
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AUTOLINKSET_H__5708545C_E8F2_4155_AC66_4191BE0F150E__INCLUDED_)
#define AFX_AUTOLINKSET_H__5708545C_E8F2_4155_AC66_4191BE0F150E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

////////////////////////////////////////////////////////////////
// ˵��:
//    ��SafeLinkSet����ֱ����Iterator���������еĿն���͡�OWN_TRUE����SET�еķ�MASTER����ָ�롱ָ��ᱻ�Զ������
//     ����ѭ���е�ɾ�����󣬲��ᵼ�µ����ӷǷ���[�˹���ͨ���ӳ�ɾ��ʵ��]
//     PopObj��������ʱ���ڲ�����ʱ����CSafeLink(OWN_FALSE)ָ����󡣲�������Զ�ɾ���˶����������
//     ��ע��� Size()�������ܻ�������ж���Ч�ʲ��ߡ������ʱ��Ҫ̫Ƶ����
////////////////////////////////////////////////////////////////
// ��Ҫʵ�ֵĽӿ�:
//     ��ģ����ҪGetID()��Release()����֧�֣�ͬʱҲ��Ҫ����DWORD

////////////////////////////////////////////////////////////////
// ʹ��ʾ����


////////////////////////////////////////////////////////////////
// �߼�˵����(�ɲ��ÿ�)
// ��ΪPopObj֮�������������ʱ����(raw)ָ��ʹ�ö���������SETҲ����ʱ�ģ�����ǰ�ͷ��ˣ����Ǹ���ʱ����ָ���Ƿ������⣬(�����Iterator���)Size()����Ҳ�ᵼ�������ָ�롣
// ��һ�������һ��OWN_SET�Ƶ���һ��OWN_SET�����ǰһ��û����ʽִ��PopObj����MasterȨ�޻��Զ�ת�ơ������ת�ƺ���������ֱ�ɾ���ˣ���ʱ���ڿ��ܳ��ֵ������߼����⣬��ģ��û���ṩ���ԡ�
// ��Ϊ��Чָ������ʱ�����½������Iterator���������Iterator���Size()���õ�ʱ�򣬹���ʱ�ڲ���ӳ�ɾ�������п��ܵ��²��ܼ�ʱ�ͷ��ڴ棬����ڴ�ռ��ƫ�ࡣ(���������Ӱ�첻��)
// ��ָ������㺯������ʱ�����ܻ���Ϊ�ڲ�ɾ�������һ��SafeLink(��ǿ��ɾ����MASTER)�����´��ݳ�ȥ����ָ��Ϊ�Ƿ���ַ�����ز���Ӧ���ĳ�CSafePtr��װ���͡�
// DelObjʱ��OWN_TRUE���ڲ����Զ�����ɾ�����󡣵����ⲿ����(raw)ָ��ָ��Ƿ��ڴ档(���Ƿ���Ż��ɷ�һ��ʱ���У��ӳ�ɾ������ʲôʱ��ɾ��������?)
// ����ڱ���װ�����Release�����п�����Լ���NOTE�еĶ���ָ�룬�����ȫ����ʹ�ⲿ����ָ�������Release��Ҳ���ᵼ�·�װ���ķǷ��ڴ������

#include "SafeLink.h"
#include <vector>
using namespace std;

////////////////////////////////////////////////////////////////
// �ýӿڽ�����Iterator�ڲ�������Ա����ʹ�á�
class IExpendForInterator
{
public:
	virtual int		CalcSize(bool bNeedCount=true) = 0;
	virtual long&	GetIteratorCount() = 0;
	virtual void	SetUpdateFlag() = 0;
};

template<class T, OWN_ENUM OWN>
class CSafeLinkSet : public IExpendForInterator
{
protected:
	typedef	CSafeLink<T,OWN>	SAFE_PTR_TYPE;
	typedef	CSafeLink<T,OWN_FALSE>	SAFE_PTR;
	typedef	vector<SAFE_PTR_TYPE>	VECTOR_SET;
public:
	CSafeLinkSet() {}
	virtual ~CSafeLinkSet();
public:
	static CSafeLinkSet<T,OWN>*	CreateNew()		{ return new CSafeLinkSet<T,OWN>(); }
	void	Release			()					{ delete this; }

public: // �ṩ������Ա�ĵ�����
	class	Iterator;
	Iterator	NewEnum		() 					{ return Iterator(&m_setObj, this); }
	int			Size		()					{ return CalcSize(); }

public: // �ṩ������Ա�Ľӿ�
//	bool		AddObj			(const SAFE_PTR_TYPE& pObj);
	bool		AddObj			(T* ptr);
	bool		DelObj			(DWORD idObj);
	bool		DelObj			(Iterator& iter);
	T*			GetObj			(DWORD idObj);
	T*			PopObj			(DWORD idObj);
	T*			PopObj			(Iterator& iter);
	void		Clear			()				{ m_setObj.clear(); }

//////////////////////////////////////////////////////
// �ڲ���Ա
//////////////////////////////////////////////////////
protected:
	int			CalcSize(bool bNeedCount=true);		// return size of set only include valid obj.
	long&		GetIteratorCount()				{ return m_nCountIterator; }
	void		SetUpdateFlag()					{ m_bEraseFlag = true; }
protected:
	VECTOR_SET			m_setObj;
	auto_bool			m_bEraseFlag;		// true: �ڲ�����Чָ��
	auto_long			m_nCountIterator;	// �����Ѿ��ж��ٸ�Iterator�ˣ�
	vector<SAFE_PTR>		m_setRecycle;		// ��ʱ��һ��ѭ����ɾ���Ķ��󣬱����ⲿ��(raw)ָ��ʹ�á�
public:	// new traversal
	class	Iterator{
	private: // create by parent class
		Iterator(VECTOR_SET* pSet, IExpendForInterator* pData) : m_pSet(pSet),m_idx(pSet->size()),m_pData(pData)
			{ m_pData->CalcSize(false); m_pData->GetIteratorCount()++; }
		friend class CSafeLinkSet<T,OWN>;
		Iterator& operator=(const Iterator&);	// invalid func! please cannot use this function. no function body
	public:
		Iterator(const Iterator& iter) : m_pSet(iter.m_pSet),m_idx(iter.m_idx),m_pData(iter.m_pData)	{ m_pData->GetIteratorCount()++; }
		~Iterator()								{ m_pData->GetIteratorCount()--; }

	public: // application
		bool	Next()
		{
			if(m_idx<=0)
				return false; 

			bool bFound = false;
			do
			{
				m_idx--;

				SAFE_PTR_TYPE& pObj = m_pSet->at(m_idx);
				if(OWN && pObj)		// ��ָ�룬���߷�MASTERָ�룬���Զ������
				{
					IF_NOT(pObj.IsMaster())					// ������Դ���ʾû�д�OWN_TRUE��SET��PopObj���ͽ�����ŵ���һOWN_TRUE�������ˡ����´�����ʧȥ��OWNȨ�ޡ�
					{
						pObj = NULL;						// m_setObj�е�ָ����ա�OWN_TRUE�ͻ�ɾ��OBJ
						m_pData->SetUpdateFlag();
					}
				}

				if(!pObj.IsValidPt())
				{
					m_pData->SetUpdateFlag();
					//����Ҫ	m_pSet->at(m_idx).BreakOwner();		// ����ΪOWN_FALSE����ɾ���������ⲿ��(raw)ָ��ʹ�á�
					//m_pSet->erase(m_pSet->begin() + m_idx);			//??? client����ʹ�ö���ѭ��ʱɾ������(���Զ�ά��)�����ܻ�������!
				}
				else
					bFound = true;
			}
			while(m_idx>0 && !bFound);

			return bFound;
		}

		void	Reset()							{ m_idx=m_pSet->size(); }
		operator T*()							{ CHECKF(m_idx>=0&&m_idx<m_pSet->size()); return m_pSet->at(m_idx); }
		POINT_NO_RELEASE<T>* operator->()		{ CHECKF(m_idx>=0&&m_idx<m_pSet->size()); return static_cast<POINT_NO_RELEASE<T>*>((T*)m_pSet->at(m_idx)); }

	protected:
		VECTOR_SET*		m_pSet;
		int				m_idx;		// ��Ϊ��ǰ��������ָλ��(��ǰΪ��һλ��)
//		SAFE_PTR		m_pObj;		// OWN_FALSE�͵�CSafePtr
		IExpendForInterator*	m_pData;
	};
};

//////////////////////////////////////////////////////////////////////
template<class T, OWN_ENUM OWN>
CSafeLinkSet<T,OWN>::~CSafeLinkSet()
{
	// ������룬CSafeLink�����һ�С�

	// more log
//	if(OWN)
//	{
//		for(int i=0;i<m_setObj.size();i++)
//			MYASSERT(m_setObj.at(i).IsMaster());		// more log for auto change owner.
//	}
}

/*/////////////////////////////////////////////////////////////////////
template<class T, OWN_ENUM OWN>
bool CSafeLinkSet<T,OWN>::AddObj(const SAFE_PTR_TYPE& pObj)
{
	CHECKF(pObj && pObj->GetID());
	ASSERT(!DelObj(pObj->GetID()));

	m_setObj.push_back(pObj);
	return true;
}*/

//////////////////////////////////////////////////////////////////////
template<class T, OWN_ENUM OWN>
bool CSafeLinkSet<T,OWN>::AddObj(T* ptr)
{
	CHECKF(ptr && ptr->GetID());
	ASSERT(!DelObj(ptr->GetID()));

	SAFE_PTR_TYPE	link(ptr);
	m_setObj.push_back(link);
	return true;
}

//////////////////////////////////////////////////////////////////////
template<class T, OWN_ENUM OWN>
bool CSafeLinkSet<T,OWN>::DelObj(Iterator& iter)
{
	int idx = iter.m_idx;
	CHECKF(idx>=0 && idx < m_setObj.size());

	if(m_setObj[idx])
	{
		m_setObj[idx] = NULL;						// m_setObj�е�ָ����ա�OWN_TRUE�ͻ�ɾ��OBJ
		SetUpdateFlag();
		//m_setObj.erase(m_setObj.begin() + idx);

		return true;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////
template<class T, OWN_ENUM OWN>
bool CSafeLinkSet<T,OWN>::DelObj(DWORD idObj)
{
	CHECKF(idObj);
	for(int idx=0;idx<m_setObj.size();idx++)
	{ 
		T* pObj=m_setObj[idx];
		if(pObj && pObj->GetID()==idObj)
		{
			m_setObj[idx] = NULL;						// m_setObj�е�ָ����ա�OWN_TRUE�ͻ�ɾ��OBJ
			SetUpdateFlag();
			//m_setObj.erase(m_setObj.begin()+idx);
			return true; 
		}
	}
	return false;
}

//////////////////////////////////////////////////////////////////////
template<class T, OWN_ENUM OWN>
T* CSafeLinkSet<T,OWN>::GetObj(DWORD idObj)
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
template<class T, OWN_ENUM OWN>
T* CSafeLinkSet<T,OWN>::PopObj(DWORD idObj)
{
	for(int idx=0;idx<m_setObj.size();idx++)
	{
		T* pObj=m_setObj[idx];
		if(pObj && pObj->GetID()==idObj)
		{
			MYASSERT(OWN);	// more check, ֻ��OWN_TRUE�ſɵ��á�(��ɾ��)
			m_setObj[idx].BreakOwner();
			m_setRecycle.push_back(pObj);			// ��ʱ���֣������ⲿ��ʱ��(raw)ָ��ʹ�á�
			m_setObj[idx] = NULL;
			SetUpdateFlag();
			//m_setObj.erase(m_setObj.begin() + idx);
			return pObj;
		}
	}

	return NULL;
}

//////////////////////////////////////////////////////////////////////
template<class T, OWN_ENUM OWN>
T* CSafeLinkSet<T,OWN>::PopObj(Iterator& iter)
{
	int idx = iter.m_idx;
	CHECKF(idx>=0 && idx < m_setObj.size());

	if(m_setObj[idx])
	{
		MYASSERT(OWN);	// more check, ֻ��OWN_TRUE�ſɵ��á�(��ɾ��)
		MYASSERT(!OWN || OWN && m_setObj[idx].IsMaster());		// ֻ��POPһ��

		T* pObj = m_setObj[idx];
		m_setObj[idx].BreakOwner();
		m_setRecycle.push_back(pObj);			// ��ʱ���֣������ⲿ��ʱ��(raw)ָ��ʹ�á�
		m_setObj[idx] = NULL;
		SetUpdateFlag();
		//m_setObj.erase(m_setObj.begin() + idx);
		return pObj;
	}

	return NULL;
}

//////////////////////////////////////////////////////////////////////
template<class T, OWN_ENUM OWN>
int CSafeLinkSet<T,OWN>::CalcSize(bool bNeedCount)
{
	if(!m_bEraseFlag || m_nCountIterator>0 && !bNeedCount)
		return m_setObj.size();

	bool bErase = m_bEraseFlag && m_nCountIterator==0;

	if(bErase)
		m_setRecycle.clear();

	int nCount = 0;		// only for !bErase
	for(int idx=m_setObj.size()-1; idx>=0; idx--)		// ɾ��������
	{
		if(m_setObj[idx].IsValidPt())
			nCount++;		// only for !bErase
		else
		{
			if(bErase)
				m_setObj.erase(m_setObj.begin()+idx);
		}
	}

	if(bErase)
	{
		m_bEraseFlag = false;
		return m_setObj.size();
	}
	else
		return nCount;		// only for !bErase
}



#endif // !defined(AFX_AUTOLINKSET_H__5708545C_E8F2_4155_AC66_4191BE0F150E__INCLUDED_)
