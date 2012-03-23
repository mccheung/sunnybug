// ��COM֧��
// paled, 2003.5.25

#pragma warning(disable:4786)
#ifndef	MY_COM_H
#define	MY_COM_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "common.h"

////////////////////////////////////////////////////////////////
#define	NO_COPY(T)	\
protected:	\
	T(const T&);	\
	T& operator=(const T&);		// ��ʵ�ִ���(��ͬ)


////////////////////////////////////////////////////////////////
#define	NEW_RELEASE(T)	\
public:	\
	static T* CreateNew(DWORD idCls=0) 	{ return new T; }	\
	void Release() 			{ delete this; }	\
	template< TYPENAME X >	static X* CreateNew(X**) { return static_cast<X>(new T); }	\
	template< TYPENAME X > X* QueryInterface(X**) { return static_cast<X*>(this); }	\
protected:
//	T* Clone() 				{ return new T(*this); }

#define	NEW_RELEASE2(T,I)	\
public:	\
	static I* CreateNew(DWORD idCls=0) 	{ return new T; }	\
	void Release() 			{ delete this; }	\
	template< TYPENAME X >	static X* CreateNew(X**) { return static_cast<X>(new T); }	\
	template< TYPENAME X > X* QueryInterface(X**) { return static_cast<X*>(this); }	\
protected:
//	I* Clone() 				{ return new T(*this); }


////////////////////////////////////////////////////////////////
#define	COM_STYLE(T)	\
	NEW_RELEASE(T)	\
	NO_COPY(T)	\
protected:

#define	COM_STYLE2(T,I)	\
	NEW_RELEASE2(T,I)	\
	NO_COPY(T)	\
protected:


////////////////////////////////////////////////////////////////
#define	COM_STYLE_HEAP(T)	\
	COM_STYLE(T)	\
protected:	\
	T() {}	\
	virtual ~T() {}	\
protected:


////////////////////////////////////////////////////////////////
#define	COM_STYLE_STACK(T)	\
	COM_STYLE(T)	\
public:	\
	T() {}	\
	virtual ~T() {}	\
protected:


////////////////////////////////////////////////////////////////
// typedef
//////////////////////////////////////////////////////////////////////
#define	TYPE_OF(x)			((x**)0)

typedef	DWORD	I_ID;
typedef	DWORD	CLS_ID;


//////////////////////////////////////////////////////////////////////
template<TYPENAME T>
	struct guid_traits { enum{ id=1 }; };			// ȱʡֵ������CJavaObj����Щ�ɵ�����ȱʡΪtrue������1��
template<int id>
struct cls_traits {};
#define GUID_DECLARE(T,I)					template<> struct guid_traits< T > { enum{ id=(I) }; };	\
											template<> struct cls_traits< I > { typedef T t; };
// GUID_DECLARE(CUser, OBJ_USER)
#define GUID_DEFINE(T,I,n)	class T; enum {I=n}; GUID_DECLARE(T,I)
// GUID_DEFINE(CUser, OBJ_USER, 0x1001)
#define	GUID_OF(T)			(guid_traits< T >::id)
// GUID_OF(CUser)
#define CLS_OF(id)			cls_traits< id >::t
// CLS_OF(OBJ_USER)

#define OFFSET_OF(T,V) (size_t)&(((T *)0)->V) 
#define DEFINE_THIS(T,V)	T* This() { return (T*)( ((DWORD)this) - OFFSET_OF(T,V) ); }


//////////////////////////////////////////////////////////////////////
// Createnew ����

//////////////////////////////////////////////////////////////////////
// ���� IClass.cpp �еĶ�̬new���壬��֧��ͨ���ⲿ���ݶ�̬��������
//////////////////////////////////////////////////////////////////////
#define DECLARE_INTERFACE_CREATENEW(I)	T* CreateNew(CLS_ID );
#define	IMPLEMENT_CREATENEW_BEGIN(T,i)	T* T::CreateNew(CLS_ID i){ switch(i) {
#define	IMPLEMENT_CREATENEW_SUB(I)		case I:		return cls_traits<I>::t::CreateNew(); break;
#define	IMPLEMENT_CREATENEW_END			default:	ASSERT(!"switch(IMPLEMENT_CREATENEW)"); } return NULL; }


//////////////////////////////////////////////////////////////////////
// QueryInterface ����
// ע�⣺T* QueryInterface(TYPE_OF(x)) ������CLIENT�����õģ�x�������Ʋ����������з���ֵ��

//////////////////////////////////////////////////////////////////////
// ����IClass�еĽӿڶ��壬ͨ��QueryInterface(T**)�ɲ�ѯ��CClass�������Ӷ���
//////////////////////////////////////////////////////////////////////
// (in *.h of interface)
// DEFINE_INTERFACE_QI(IRole)
#define DEFINE_INTERFACE_QI(T)	\
	template<TYPENAME T> T*	QueryInterface(T**) { T* p=0; if(QueryInterface(GUID_OF(T), (void**)&p)) return p; return NULL; }	\
	virtual bool QueryInterface (I_ID idObjType, void** ppv)	PURE_VIRTUAL_FUNCTION_0

//////////////////////////////////////////////////////////////////////
// �������ӿں;ۺ�������Query�ӿڣ�����������鵽�ۺ϶���
//////////////////////////////////////////////////////////////////////
// DEFINE_BASE_QI										// ����Ľӿ�(COM_STYLE���Ѿ�������)
// DEFINE_QI(CUser, m_pOwner)							// �϶��еľۺϽӿ�
// DEFINE_QI0(CMonster, OBJ_CALLPET)					// ����Ϊ�յľۺϽӿ�
//(����)#define DEFINE_BASE_QI	\
//(����)	template<TYPENAME T> T* QueryInterface(T**) { return static_cast<T*>(this); }
#define DEFINE_QI(T,v)	\
	T* QueryInterface(T**) { ASSERT(v); return v; }
#define DEFINE_QI0(T,v)	\
	T* QueryInterface(T**) { return v; }

//////////////////////////////////////////////////////////////////////
// ����һЩ�ۺ���Ķ�������������ṩ���ӽӿڵġ�
//////////////////////////////////////////////////////////////////////
// (in *.h of class)
// DEFINE_CLASS_QI(CUser, OBJ_USER)						// �򵥵ģ��޾ۺ�
// DEFINE_CLASS_QI_BEGIN(CNpc, OBJ_NPC)					// ���ۺϵ�
//		DEFINE_CLASS_QI_SUB(OBJ_NPCSHOP, m_pShop)
// DEFINE_CLASS_QI_END
#define DEFINE_CLASS_QI(T,I)	\
	virtual	bool	QueryInterface(I_ID idObjType, void** ppv) { if(idObjType==I) return *ppv=this,true; return *ppv=NULL,false; }
#define DEFINE_CLASS_QI_BEGIN(T,I)	\
	virtual bool	QueryInterface(I_ID idObjType, void** ppv){	\
	CHECKF(ppv);	\
	switch(idObjType)	{	\
	case	I:		*ppv=this;		return true;		break;
#define DEFINE_CLASS_QI_SUB(I,v)	\
	case	I:		*ppv=v;		return true;		break;
#define DEFINE_CLASS_QI_END	\
	}	*ppv = NULL;	return false; }


//////////////////////////////////////////////////////////////////////
// ��QueryInterface�򻯳�Cast����
//////////////////////////////////////////////////////////////////////
// CNpc* pNpc = Cast<CNpc>(pRole);
template<TYPENAME T, TYPENAME X>
inline T* Cast(X* pX) { if(pX) return pX->QueryInterface((T**)0); return NULL; }

// Cast(pNpc, pRole);
template<TYPENAME T, TYPENAME X>
inline bool Cast(T** ppT, X* pX) { CHECKF(ppT); if(pX) return pX->QueryInterface(ppT) != NULL; return *ppT=NULL,false; }



#endif // MY_COM_H
