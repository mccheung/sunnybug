// GameAutoPtr.h: declare for the CAutoPtrF class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAMEAUTOPTRF_H__5708545C_E8F2_4155_AC66_4191BE0F150E__INCLUDED_)
#define AFX_GAMEAUTOPTRF_H__5708545C_E8F2_4155_AC66_4191BE0F150E__INCLUDED_

#include "common.h"
#include "basetype.h"
#include "mycom.h"
#include "MyClassFactory.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////////
// ˵����������ָ�룬��֧��COPY��=����ģ����ҪCMyClassFactory�೧֧��
// �����ָ�����ΪNULL��
// ע�⣺�����ö����������Ǹ�����COYP��=���ࡣ

template<TYPENAME T, TYPENAME T2=T>
class CAutoPtrF
{
public:
	CAutoPtrF() : m_ptr(NULL)					{}
	CAutoPtrF(T* ptr) : m_ptr(ptr)				{}		// may be null
	~CAutoPtrF()									{ Release(); }
	CAutoPtrF& operator=(T* ptr)					{ if(m_ptr && m_ptr!=ptr) Release(); m_ptr=ptr; return *this; }
	T*	pop()										{ T* p=m_ptr; m_ptr=NULL; return p; }
private: // can't use these
	CAutoPtrF& operator=(const CAutoPtrF& ptr);
	CAutoPtrF(const CAutoPtrF&);

public: // create new
	T* New(CLS_ID id)								{ Release(); CreateNewObj(GUID_OF(T2), PPV_OF(m_ptr)); MYASSERT(m_ptr); return m_ptr; }
	void Release()									{ if(m_ptr) ReleaseObj(GUID_OF(T2), PPV_OF(m_ptr)); m_ptr=NULL; }

public:
	operator T*()									{ return m_ptr; }
	T*	operator->()			{ MYASSERT(m_ptr); return static_cast<T* >(m_ptr); }
	operator const T*()	 	 const					{ return m_ptr; }
	const T*	operator->() const	{ MYASSERT(m_ptr); return static_cast<T* >(m_ptr); }

protected:
	T*			m_ptr;
};
template<TYPENAME T, TYPENAME T2>
inline void		safe_release(CAutoPtrF<T,T2>& pT)		{ pT.Release(); }


//////////////////////////////////////////////////////////////////////
// ˵��������JAVA���󣬲�֧��COPY��=����ģ����ҪCMyClassFactory�೧֧��
// �����ָ�벻��ΪNULL�����������ڡ�
// ע�⣺�����ö����������Ǹ�����COYP��=���ࡣ

template<TYPENAME T, TYPENAME T2=T>
class CJavaObjF
{
public:
	CJavaObjF() : m_ptr(NULL)						{}
	~CJavaObjF()										{ Release(); }
private: // can't use these
	CJavaObjF& operator=(const CJavaObjF& ptr);
	CJavaObjF(const CJavaObjF&);

public: // create new
	T* New(CLS_ID id)								{ CHECKF(!m_ptr); CreateNewObj(GUID_OF(T2), PPV_OF(m_ptr)); MYASSERT(m_ptr); return m_ptr; }
	void Release()									{ if(m_ptr) ReleaseObj(GUID_OF(T2), PPV_OF(m_ptr)); m_ptr=NULL; }

public:
	operator T*()									{ if(!m_ptr) CreateNewObj(GUID_OF(T2), PPV_OF(m_ptr)); MYASSERT(m_ptr); return m_ptr; }
	T*	operator->()								{ if(!m_ptr) CreateNewObj(GUID_OF(T2), PPV_OF(m_ptr)); MYASSERT(m_ptr); return static_cast<T* >(m_ptr); }
	operator const T*()	 	 const					{ if(!m_ptr) CreateNewObj(GUID_OF(T2), PPV_OF(m_ptr)); MYASSERT(m_ptr); return m_ptr; }
	const T*	operator->() const					{ if(!m_ptr) CreateNewObj(GUID_OF(T2), PPV_OF(m_ptr)); MYASSERT(m_ptr); return static_cast<T* >(m_ptr); }

protected:
	T*			m_ptr;
};
template<TYPENAME T, TYPENAME T2>
inline void		safe_delete(CJavaObjF<T,T2>& pT)		{ pT.Release(); }


//////////////////////////////////////////////////////////////////////
// ˵������ָͨ�룬��֧��COPY��=����ģ�塰����Ҫ��Release()����֧��
// �����ָ�����ΪNULL��

template<TYPENAME T, TYPENAME T2>
class CAutoRefF
{
public:
	CAutoRefF() : m_ptr(NULL)					{}
	CAutoRefF(T* ptr) : m_ptr(ptr)				{}		// may be null
	~CAutoRefF()									{}
	CAutoRefF& operator=(T* ptr)					{ m_ptr=ptr; return *this; }
	T*	pop()									{ T* p=m_ptr; m_ptr=NULL; return p; }
public: // enable
	CAutoRefF& operator=(const CAutoRefF& ptr)	{ m_ptr=ptr.m_ptr; }
	CAutoRefF(const CAutoRefF&)					{ m_ptr=ptr.m_ptr; }

public:
	operator T*()									{ return m_ptr; }
	T*	operator->()			{ MYASSERT(m_ptr); return static_cast<T* >(m_ptr); }
	operator const T*()	 	 const					{ return m_ptr; }
	const T*	operator->() const	{ MYASSERT(m_ptr); return static_cast<T* >(m_ptr); }

protected:
	T*			m_ptr;
};





#endif // !defined(AFX_GAMEAUTOPTR_H__5708545C_E8F2_4155_AC66_4191BE0F150E__INCLUDED_)
