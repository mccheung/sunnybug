// ��ȫ������
// CAutoPtr��CAutoLink�����Ϻͼ�ǿ��
// �ɽ���, 2007.3.14 �½�
// �ɽ���, 2007.3.20 ��ɵ�Ԫ����
// �ɽ���, 2007.3.21 ģ�����������֧���������໥��ֵ�������Ʋ�ͬ����Ĳ����໥��ֵ��
////////////////////////////////////////////////////////////////
// ˵��:��CSafeLink����ʹ�ø�ֵ�ķ�ʽ����������LINK������������OWN��ָ��ͬһ����ʱ���Ὣ�Զ�ɾ���Ĺ����Ƹ���һ��OWNer��[���Զ���ֻ֤��һ������ġ�owner]
//		��OWN_TRUE�͵�CSafeLink������ʱ���Զ�ɾ������(ֻ�������һ��OWNer)��ͬʱ�������йص�CSafeLink���Զ����(��ΪNULL)��[���ֶ�ǿ��ɾ������]
//		�����С�CSafeLink���Ͽ�ʱ(���������Ƿ���OWN�Ͷ���)�������Զ�ɾ����[����smartptr����֤���Զ�����]
//           ���Ծ�����Ҫֱ��ʹ��δ��װ����(raw)ָ�룬���Ҫʹ�ã�һ��Ҫ��֤������һ��CSafeLink�����ڡ�������ָ���п���ָ��Ƿ��ڴ档
//		��CSafeLink����ʱ�ɸ�ֵΪNULL��[CSafeLink<CUser> pUser; pUser = NULL;]
//		��CSafeLink��֧���������ʵ�ֵĽӿ��ࡣ[CSafeLink<CUser, OWN_FALSE, IRole> pRole;]
////////////////////////////////////////////////////////////////
// ʹ�÷�������CAutoLink(��CAutoLinkSet)�������е�T*������T����ָ�룬������ʹ��T*�������÷�����ʹ��T*��
// ���ӣ�typedef CSafeLink<CUser> CUserPtr���Ժ�����ʹ��CUser*�ĵط����ĳ�CUserPtr��(Ϊ��ʹ�÷��㣬ջ�ϵ���ʱ����Ҳ�ɿ���ֱ����CUser*)
// ע��:��CSafeLink����ָ�Ķ�����ʱ���ܱ�����������գ�����ÿ��ʹ�á�CSafeLink��ʱ��Ӧ���ȼ���Ƿ�ΪNULL��[����CAutoLink�Ĺ���]
////////////////////////////////////////////////////////////////
// ��Ҫ��ӵĽӿڣ�
//		��CSafeLink��������Ķ��������ӳ�Ա����: SAFELINK_DEFINE		// �������VIRTUAL_SAFELINK_DEFINE
//		��CSafeLink��������Ķ������ʵ�ֳ�Ա����: void Release();


////////////////////////////////////////////////////////////////
// ʵ�ַ�(server��)ʾ����
//	class ITest{					// ����
//	public:
//		virtual void	Release() =0;
//		VIRTUAL_SAFELINK_DEFINE(ITest)
//	};
//	
//	class CTest : public ITest{		// �����࣬����public�̳С�
//	public:
//		void	Release() { delete this; }
//		SAFELINK_DEFINE(ITest)
//	};
//	
//	class CTest2{					// ����ص��࣬�����໥��ֵ
//	public:
//		void	Release() { delete this; }
//		SAFELINK_DEFINE(CTest2)
//	};

///////////////////////////////////////////////////////////////
// ���÷�(client��)ʾ����
//	CSafeLink<CTest, OWN_TRUE , ITest>	pOwner = new CTest;
//	CSafeLink<CTest, OWN_FALSE, ITest>	ptr = pOwner;
//	CSafeLink<ITest, OWN_TRUE>	ptrI = ptr;			// �����������֮����໥��ֵ
//	ptrI.BreakOwner();
//	ptrI = ptr;
//	ptrI = new CTest;
//	ptr = (CTest*)(ITest*)ptrI;
//	ptrI = pOwner;
//	//error		CSafeLink<CTest2, OWN_FALSE, CTest2> ptrX = ptr;		// error : ��ͬ���͵�CSafeLink�����໥��ֵ
//	ptr = NULL;
//	ptrI = NULL;

////////////////////////////////////////////////////////////////
// �߼�˵����(�ɲ���)
// ��OWNER������POP������ʱ��Ҫ����BreakOwner()���������Լ���ӵ��Ȩ�ޡ�(��Ȼ�����㲻��������һ��OWN����ӵ����ʱ���Զ��Ͽ���һ�����OWNȨ��)
// �������Ķ���ġ�ȫ��ָ�롱���ߡ���Ա����ָ�롱������ʹ��CSafePtr���з�װ�������޷������������
// ջ�ϵġ���ʱ����ָ�롱��������ͨ����(raw)ָ��(CUser*)����ʹ��ʱ�������װ����ǰ�Զ�ɾ���˶��󣬻��������ָ�롱�������⣬������������Ƿ�ָ�롱��
// ������ʹ��CSafeLinkSet��CSafeLinkMap��CSafeLinkArray��Ҳ��ʹ������stl�������������еĶ��������CSafeLink��װ���ָ�����
// ע�ⲻ�ܽ��˹�������CreateNew֮��Ĵ����¶���ĺ����ڲ�����Ϊ���ຯ�����������(raw)ָ�룬�����OWN_FALSE�������Զ����˶��������������Ǻ�������CSafeLink���͡�
// �벻Ҫ�������CAutoPtr��CAutoLink��CGameObjSet��CSingleMap֮��Ļ��á��ɽ�ԭ����CAutoPtr��ΪCSafeLink<T,OWN_TRUE>����CAutoLink��ΪCSafeLink<T,OWN_FALSE>��CGameObjSet��CSingleMap��ΪCSafeSet��CSafeMap��
// ��ò�Ҫ��ȫ��ָ����CSafeLink<T,OWN_TRUE>���з�װ������ȫ�ֵ��ڴ�������g_AllocForSafeLinkNote���ܻ���ǰ���ͷţ������´����LOG�������쳣�������ڳ����˳�֮ǰ��������ȫ��ָ����󸳿�(NULL)ֵ�������һ���⡣
// ���������CSafePtr��ֵ(���ṩ�������)�������CSafePtrʱ��û��ֱ�ӵĸ�ֵ����(���߹��캯��)�ɹ����ã����Զ�����operator T*()ת����ָ�룬��ͨ��operator=(T* ptr)����ֵ(����)��Ч���ϻ�����ʧ�����ܱ�֤������ֻ���ָ��ֱ�Ӹ�ֵ��������ָ��Ĵ���Ҳ�ܷ�ֹ��ͬ��CSafePtr<T>֮��Ļ��á�

////////////////////////////////////////////////////////////////
// ����ΪԴ�룺(�ɲ���)
#ifndef	SAFE_LINK_H
#define	SAFE_LINK_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "common.h"
#include "basetype.h"
#include "sgialloc.h"

////////////////////////////////////////////////////////////////
// ����Ա��Ҫֱ��ʹ�ô˽ṹ��������Ϸ�����QuerySafeLink()���Զ�ʹ�á�
template<TYPENAME I>
struct SAFELINK_NOTE{
	I*				pTrueObj;				// ָ������װ��ԭʼ����(T* ����)
	int				nCount;					// ָ�򱾽ڵ��CSafeLink������
	const void*		pMasterLink;			// ӵ���߽ڵ�ķ���ָ�롣(const CSafeLink<T,OWN_TRUE>* ����)

	void Init(I* ptr=NULL, int num=1)		{ pTrueObj=ptr; nCount=num; pMasterLink=NULL; }
	void Inc()								{ CHECK(pTrueObj); nCount++; }
	void Dec()								{ CHECK(!IsCorrupt()); nCount--; }
	bool IsCorrupt()						{ return nCount < 1; }
};

// ����Աʹ�����SAFELINK_DEFINE����.H�ļ���class������
// I�ǻ��������(�޻����Ϊ����T)
#define	SAFELINK_DEFINE(I)	\
public:	\
	SAFELINK_NOTE<I>* QuerySafeLink() const	{ return m_pSafeLinkHostNote; }	\
	void InitSafeLink(SAFELINK_NOTE<I>* ptr) { m_pSafeLinkHostNote=ptr; }	\
protected:	\
	auto_point<SAFELINK_NOTE<I> > m_pSafeLinkHostNote;		// ��CSafePtr����ֵ���������ڲ�����ա�

// ����Աʹ�����VIRTUAL_SAFELINK_DEFINE����������.H�ļ���class������
// I�ǻ��������
#define VIRTUAL_SAFELINK_DEFINE(I)	\
public:	\
	virtual SAFELINK_NOTE<I>* QuerySafeLink() const	PURE_VIRTUAL_FUNCTION_0	\
	virtual void InitSafeLink(SAFELINK_NOTE<I>* ptr) PURE_VIRTUAL_FUNCTION

enum OWN_ENUM { OWN_FALSE=0, OWN_TRUE=1 };

////////////////////////////////////////////////////////////////
template<TYPENAME T, OWN_ENUM OWN=OWN_FALSE, TYPENAME I=T>
class	CSafeLink
{
public: // cter & dter & assignment
	CSafeLink()										{ m_pData=NULL; }
	CSafeLink(const CSafeLink<T,OWN_FALSE,I>& link)	{ m_pData=NULL; if(link._pData()) Insert(link._pData()); }
	CSafeLink(const CSafeLink<T,OWN_TRUE,I>& link)	{ m_pData=NULL; if(link._pData()) Insert(link._pData()); }
	~CSafeLink()									{ Break(); }
	CSafeLink(T* ptr)								{ m_pData=NULL; if(ptr) Insert(ptr); }
	CSafeLink&	operator=(const CSafeLink<T,OWN_FALSE,I>& link)	{ if(link._pData()==m_pData) return *this; Break(); if(link._pData()) Insert(link._pData()); return *this; }
	CSafeLink&	operator=(const CSafeLink<T,OWN_TRUE,I>& link)	{ if(link._pData()==m_pData) return *this; Break(); if(link._pData()) Insert(link._pData()); return *this; }
	CSafeLink&	operator=(T* ptr)					{ if(ptr && ptr->QuerySafeLink()==m_pData) return *this; Break(); if(ptr) Insert(ptr); return *this; }

public: // const for client call
	operator T*() const								{ return m_pData ? (T*)m_pData->pTrueObj : NULL; }
	POINT_NO_RELEASE<T>* operator->() const			{ MYASSERT(IsValidPt()); return static_cast<POINT_NO_RELEASE<T>*>((T*)m_pData->pTrueObj); }

	///////////////////////////////////////////////////////////////////////////////////////////
	// �ⲿ�߼��ӿڡ�һ�����������ʹ�á�
public:
	// �Ͽ��Լ���OWNȨ�ޣ��൱��Pop�������Լ����OWN_FALSE���󡣽��������OWNer(Master)���á�
	void	BreakOwner()							{ CHECK(m_pData && m_pData->pMasterLink == this); m_pData->pMasterLink = NULL; }
	// ǿ��ɾ������װ�Ķ���(��MASTERҲ�ܵ���)
	void	ReleaseObj()							{ if(IsValidPt()) SAFE_RELEASE(reinterpret_cast<T*&>(m_pData->pTrueObj)); }	// ǿ��ɾ���������ǲ���Owner��
	// �ǲ���MASTER
	bool	IsMaster()		const					{ return OWN && IsValidPt() && reinterpret_cast<const CSafeLink<T,OWN,I>*>(m_pData->pMasterLink) == this; }	// ���һ��OWNer������
	// ȡָ��
	T*		GetPtr()		const					{ return m_pData ? ((T*)m_pData->pTrueObj) : NULL; }
	// ָ���Ƿ�Ϊ��
	bool	IsValidPt()		const					{ return m_pData && m_pData->pTrueObj; }

	///////////////////////////////////////////////////////////////////////////////////////////
	// ����Ϊ�ڲ��ӿڼ�����
protected:
	void	NewNote(I* pTrueObj);
	void	DelNoteAndObj();
	void	Insert(I* pTrueObj);					// insert to next, only for !IsMaster
	void	Insert(SAFELINK_NOTE<I>* pNote)			{ if(pNote && pNote->pTrueObj) Insert(reinterpret_cast<T*>(pNote->pTrueObj)); }
	void	Erase();								// erase from list, only for !IsMaster
	void	Break();								// clear this note. Erase() for !IsMaster, erase all note for IsMaster

protected:
	SAFELINK_NOTE<I>*		m_pData;	// �����ڱ�pTrueObj����pTrueObj������ǰ��ա������ڱ����е����CSafeLink��������ָ֤�벻��ʧЧ��

public: // �ڲ��߼��ӿڣ�����ʹ�á������ڲ�ͬģ�������CSafeLink֮����á�
	SAFELINK_NOTE<I>* _pData() const				{ return m_pData; }
};

////////////////////////////////////////////////////////////////
template<TYPENAME T, OWN_ENUM OWN, TYPENAME I>
void CSafeLink<T,OWN,I>::Break()			// �Ͽ��˶���;ɵ�NOTE֮������ӣ�׼�����������ݡ�
{
	if(IsMaster())		// master
	{
		SAFE_RELEASE(reinterpret_cast<T*&>(m_pData->pTrueObj));
		m_pData->pMasterLink=NULL;
	}

	Erase();
}

////////////////////////////////////////////////////////////////
template<TYPENAME T, OWN_ENUM OWN, TYPENAME I>
void CSafeLink<T,OWN,I>::NewNote(I* pTrueObj)		// �½�һ��NOTE������ʼ��TrueObj�ڲ��ڵ㡣���ظ����á�
{
	CHECK(!m_pData);
	CHECK(pTrueObj);
	CHECK(!pTrueObj->QuerySafeLink());		// û��NOTE

	extern CSgiAlloc g_AllocForSafeLinkNote;	// only for SAFELINK_NOTE<I>
	CHECK(m_pData = (SAFELINK_NOTE<I>*)g_AllocForSafeLinkNote.Alloc(sizeof(SAFELINK_NOTE<I>)));
	m_pData->Init(pTrueObj, 1);

	pTrueObj->InitSafeLink(m_pData);		// ͬʱ��ʼ��TrueObj�ڲ��Ľڵ�ָ��
}

////////////////////////////////////////////////////////////////
template<TYPENAME T, OWN_ENUM OWN, TYPENAME I>
void CSafeLink<T,OWN,I>::DelNoteAndObj()						// erase note obj
{
	IF_OK(m_pData->pMasterLink == NULL)		// �������һ�����϶�û��������
	{
		SAFE_RELEASE(reinterpret_cast<T*&>(m_pData->pTrueObj));	// ��û��MASTERʱ���Զ�ɾ����������smart_point��
	}

	extern CSgiAlloc g_AllocForSafeLinkNote;	// only for SAFELINK_NOTE<I>
	g_AllocForSafeLinkNote.Free(m_pData, sizeof(SAFELINK_NOTE<I>));
	m_pData=NULL;
}

////////////////////////////////////////////////////////////////
template<TYPENAME T, OWN_ENUM OWN, TYPENAME I>
void CSafeLink<T,OWN,I>::Insert(I* pTrueObj)		// insert to reference list
{
	if(!pTrueObj->QuerySafeLink())
		NewNote(pTrueObj);
	else
	{
		SAFELINK_NOTE<I>* pData = pTrueObj->QuerySafeLink();
		CHECK(!m_pData);
		CHECK(pData);
		m_pData		= pData;
		m_pData->Inc();
	}
	CHECK(m_pData);

	if(OWN)
		m_pData->pMasterLink	= this;
}

////////////////////////////////////////////////////////////////
template<TYPENAME T, OWN_ENUM OWN, TYPENAME I>
void CSafeLink<T,OWN,I>::Erase()						// erase from reference list
{
	if(m_pData)
	{
		CHECK(!m_pData->IsCorrupt());

		m_pData->Dec();
		if(m_pData->IsCorrupt())	// û��ָ��ָ������ˣ������ͷŶ����ˡ�
			DelNoteAndObj();

		m_pData = NULL;		// ����ָ��NOTE
	}
}

#endif // SAFE_LINK_H
