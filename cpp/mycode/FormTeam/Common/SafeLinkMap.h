// SafeLinkMap.h: interface for the CSafeLinkMap class.
// paled, 2007-3-29 �½�
// paled, 2007-3-29 ��ɵ�Ԫ����
//////////////////////////////////////////////////////////////////////

#if !defined(AUTOLINKMAP_H)
#define AUTOLINKMAP_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

////////////////////////////////////////////////////////////////
// ˵��:
//    ��SafeLinkMap����ֱ����Iterator���������еĿն���͡�OWN_TRUE����SET�еķ�MASTER����ָ�롱ָ��ᱻ�Զ������
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

// USE_HASH_MAP ʹ��SGISTL��HASH_MAP��ʵ�֣��Լ���GetObj()֮��Ĳ�����
#ifdef	USE_HASH_MAP
#include <hash_map>
#define	base_class_map	hash_map
#else // USE_HASH_MAP
#include <map>
#define	base_class_map	map
#endif // USE_HASH_MAP
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
class CSafeLinkMap : public IExpendForInterator
{
protected:
	typedef	CSafeLink<T,OWN>	SAFE_PTR_TYPE;
	typedef	CSafeLink<T,OWN_FALSE>	SAFE_PTR;
	typedef	base_class_map<DWORD, SAFE_PTR_TYPE>		MAP_SET;
	typedef	MAP_SET::iterator	MAP_ITER;
public:
	CSafeLinkMap() {}
	virtual ~CSafeLinkMap();
public:
	static CSafeLinkMap<T,OWN>*	CreateNew()		{ return new CSafeLinkMap<T,OWN>(); }
	void	Release			()					{ delete this; }

public: // �ṩ������Ա�ĵ�����
	class	Iterator;
	Iterator	NewEnum		() 					{ return Iterator(&m_map, this); }
	int			Size		()					{ return CalcSize(); }

public: // �ṩ������Ա�Ľӿ�
	bool		AddObj			(T* ptr);
	bool		DelObj			(DWORD idObj);
	bool		DelObj			(Iterator& iter);
	T*			GetObj			(DWORD idObj);
	T*			PopObj			(DWORD idObj);
	T*			PopObj			(Iterator& iter);
	void		Clear			()				{ m_map.clear(); }

//////////////////////////////////////////////////////
// �ڲ���Ա
//////////////////////////////////////////////////////
protected:
	int			CalcSize(bool bNeedCount=true);		// return size of set only include valid obj.
	long&		GetIteratorCount()				{ return m_nCountIterator; }
	void		SetUpdateFlag()					{ m_bEraseFlag = true; }
protected:
	MAP_SET				m_map;
	auto_bool			m_bEraseFlag;		// true: �ڲ�����Чָ��
	auto_long			m_nCountIterator;	// �����Ѿ��ж��ٸ�Iterator�ˣ�
	vector<SAFE_PTR>	m_setRecycle;		// ��ʱ��һ��ѭ����ɾ���Ķ��󣬱����ⲿ��(raw)ָ��ʹ�á�
public:	// new traversal
	class	Iterator{
	private: // create by parent class
		Iterator(MAP_SET* pSet, IExpendForInterator* pData) : m_pSet(pSet),m_iter(pSet->begin()),m_bInit(false),m_pData(pData)
			{ m_pData->CalcSize(false); m_pData->GetIteratorCount()++; }
		friend class CSafeLinkMap<T,OWN>;
		Iterator& operator=(const Iterator&);	// invalid func! please cannot use this function. no function body
	public:
		Iterator(const Iterator& iter) : m_pSet(iter.m_pSet),m_iter(iter.m_iter),m_bInit(iter.m_bInit),m_pData(iter.m_pData)	{ m_pData->GetIteratorCount()++; }
		~Iterator()								{ m_pData->GetIteratorCount()--; }

	public: // application
		bool	Next()
		{
			CHECKF(m_iter!=m_pSet->end());

			bool bFound = false;
			do
			{
				if(!m_bInit)
					m_bInit=true;
				else
					m_iter++;
				if(m_iter == m_pSet->end())
					break; // do, return false

				SAFE_PTR_TYPE& pObj = m_iter->second;
				if(OWN && pObj)		// ��ָ�룬���߷�MASTERָ�룬���Զ������
				{
					IF_NOT(pObj.IsMaster())					// ������Դ���ʾû�д�OWN_TRUE��SET��PopObj���ͽ�����ŵ���һOWN_TRUE�������ˡ����´�����ʧȥ��OWNȨ�ޡ�
					{
						pObj = NULL;						// m_map�е�ָ����ա�OWN_TRUE�ͻ�ɾ��OBJ
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
			while(m_iter!=m_pSet->end() && !bFound);

			return bFound;
		}

		void	Reset()							{ m_iter=m_pSet->begin(); m_bInit=false; }
		bool	IsValid() const					{ return m_bInit && m_iter!=m_pSet->end(); }
		operator T*()							{ CHECKF(IsValid()); return m_iter->second; }
		POINT_NO_RELEASE<T>* operator->()		{ CHECKF(IsValid()); return static_cast<POINT_NO_RELEASE<T>*>((T*)m_iter->second); }

	protected:
		MAP_SET*		m_pSet;
		MAP_ITER		m_iter;		// ��Ϊ��ǰ��������ָλ��(��ǰΪ��һλ��)
		bool			m_bInit;	// ����������һ��Next()
		IExpendForInterator*	m_pData;
	};
};

//////////////////////////////////////////////////////////////////////
template<class T, OWN_ENUM OWN>
CSafeLinkMap<T,OWN>::~CSafeLinkMap()
{
	// ������룬CSafeLink�����һ�С�
}

//////////////////////////////////////////////////////////////////////
template<class T, OWN_ENUM OWN>
bool CSafeLinkMap<T,OWN>::AddObj(T* ptr)
{
	CHECKF(ptr && ptr->GetID());
	ASSERT(!DelObj(ptr->GetID()));

	SAFE_PTR_TYPE	link(ptr);
	m_map[ptr->GetID()] = link;
	return true;
}

//////////////////////////////////////////////////////////////////////
template<class T, OWN_ENUM OWN>
bool CSafeLinkMap<T,OWN>::DelObj(Iterator& iter)
{
	CHECKF(iter.IsValid());

	if(iter.m_iter->second)
	{
		iter.m_iter->second = NULL;						// m_map�е�ָ����ա�OWN_TRUE�ͻ�ɾ��OBJ
		SetUpdateFlag();
		//m_map.erase(m_map.begin() + idx);

		return true;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////
template<class T, OWN_ENUM OWN>
bool CSafeLinkMap<T,OWN>::DelObj(DWORD idObj)
{
	CHECKF(idObj);
	MAP_ITER iter = m_map.find(idObj);
	if(iter != m_map.end())
	{ 
		iter->second = NULL;						// m_map�е�ָ����ա�OWN_TRUE�ͻ�ɾ��OBJ
		SetUpdateFlag();
		//m_map.erase(m_map.begin()+idx);
		return true; 
	}
	return false;
}

//////////////////////////////////////////////////////////////////////
template<class T, OWN_ENUM OWN>
T* CSafeLinkMap<T,OWN>::GetObj(DWORD idObj)
{
	CHECKF(idObj);
	MAP_ITER iter = m_map.find(idObj);
	if(iter != m_map.end())
	{
		return iter->second;
	}
	return NULL;
}

//////////////////////////////////////////////////////////////////////
template<class T, OWN_ENUM OWN>
T* CSafeLinkMap<T,OWN>::PopObj(DWORD idObj)
{
	CHECKF(idObj);
	MAP_ITER iter = m_map.find(idObj);
	if(iter != m_map.end())
	{
		MYASSERT(OWN);							// more check, ֻ��OWN_TRUE�ſɵ��á�(��ɾ��)
		MYASSERT(iter->second.IsMaster());
		T* pObj = iter->second;
		iter->second.BreakOwner();
		m_setRecycle.push_back(pObj);			// ��ʱ���֣������ⲿ��ʱ��(raw)ָ��ʹ�á�
		iter->second = NULL;
		SetUpdateFlag();
		//m_map.erase(m_map.begin() + idx);
		return pObj;
	}

	return NULL;
}

//////////////////////////////////////////////////////////////////////
template<class T, OWN_ENUM OWN>
T* CSafeLinkMap<T,OWN>::PopObj(Iterator& iter)
{
	CHECKF(iter.IsValid());

	if(iter.m_iter->second)
	{
		MYASSERT(OWN);							// more check, ֻ��OWN_TRUE�ſɵ��á�(��ɾ��)
		MYASSERT(iter.m_iter->second.IsMaster());

		T* pObj = iter.m_iter->second;
		iter.m_iter->second.BreakOwner();
		m_setRecycle.push_back(pObj);			// ��ʱ���֣������ⲿ��ʱ��(raw)ָ��ʹ�á�
		iter.m_iter->second = NULL;
		SetUpdateFlag();
		//m_map.erase(m_map.begin() + idx);
		return pObj;
	}

	return NULL;
}

//////////////////////////////////////////////////////////////////////
template<class T, OWN_ENUM OWN>
int CSafeLinkMap<T,OWN>::CalcSize(bool bNeedCount)
{
	if(!m_bEraseFlag || m_nCountIterator>0 && !bNeedCount)
		return m_map.size();

	bool bErase = m_bEraseFlag && m_nCountIterator==0;

	if(bErase)
		m_setRecycle.clear();

	int nCount = 0;		// only for !bErase
	for(MAP_ITER iter=m_map.begin(); iter!=m_map.end(); )		// ɾ����������++
	{
		if(iter->second.IsValidPt())
			nCount++;		// only for !bErase
		else
		{
			if(bErase)
			{
				MAP_ITER iterDel = iter;
				iter++;
				m_map.erase(iterDel);
				continue;	// ���������++
			}
		}
		
		iter++;
	}

	if(bErase)
	{
		m_bEraseFlag = false;
		return m_map.size();
	}
	else
		return nCount;		// only for !bErase
}



#endif // !defined(AUTOLINKMAP_H)
