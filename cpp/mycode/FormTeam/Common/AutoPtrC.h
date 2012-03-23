// GameAutoPtr.h: declare for the CAutoPtrC class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAMEAUTOPTRC_H__5708545C_E8F2_4155_AC66_4191BE0F150E__INCLUDED_)
#define AFX_GAMEAUTOPTRC_H__5708545C_E8F2_4155_AC66_4191BE0F150E__INCLUDED_

#include "common.h"
#include "basetype.h"
#include "mycom.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////////
// ˵����������ָ�룬��֧��COPY��=����ģ����Ҫnew��delete����֧��
// �����ָ�����ΪNULL��
// ע�⣺�����ö����������Ǹ�����COYP��=���ࡣ

template<TYPENAME T, TYPENAME T2=T>
class CAutoPtrC
{
public:
	CAutoPtrC() : m_ptr(NULL)					{}
	CAutoPtrC(T* ptr) : m_ptr(ptr)				{}		// may be null
	~CAutoPtrC()									{ Release(); }
	CAutoPtrC& operator=(T* ptr)					{ if(m_ptr && m_ptr!=ptr) Release(); m_ptr=ptr; return *this; }
	T*	pop()									{ T* p=m_ptr; m_ptr=NULL; return p; }
private: // can't use these
	CAutoPtrC& operator=(const CAutoPtrC& ptr);
	CAutoPtrC(const CAutoPtrC&);

public: // create new
	T* New(CLS_ID id)								{ Release(); m_ptr=new T2(id); MYASSERT(m_ptr); return m_ptr; }
	void Release()									{ if(m_ptr) delete m_ptr; m_ptr=NULL; }

public:
	operator T*()									{ return m_ptr; }
	T*	operator->()			{ MYASSERT(m_ptr); return static_cast<T* >(m_ptr); }
	operator const T*()	 	 const					{ return m_ptr; }
	const T*	operator->() const	{ MYASSERT(m_ptr); return static_cast<T* >(m_ptr); }

protected:
	T*			m_ptr;
};
template<TYPENAME T, TYPENAME T2>
inline void		safe_release(CAutoPtrC<T,T2>& pT)		{ pT.Release(); }


//////////////////////////////////////////////////////////////////////
// ˵��������JAVA���󣬲�֧��COPY��=����ģ����Ҫnew��delete����֧��
// �����ָ�벻��ΪNULL�����������ڡ�
// ע�⣺�����ö����������Ǹ�����COYP��=���ࡣ

template<TYPENAME T, TYPENAME T2=T>
class CJavaObjC
{
public:
	CJavaObjC() : m_ptr(NULL)						{}
	~CJavaObjC()										{ Release(); }
private: // can't use these
	CJavaObjC& operator=(const CJavaObjC& ptr);
	CJavaObjC(const CJavaObjC&);

public: // create new
	T* New(CLS_ID id)								{ CHECKF(!m_ptr); m_ptr=new T2(id); MYASSERT(m_ptr); return m_ptr; }
	void Release()									{ if(m_ptr) delete m_ptr; m_ptr=NULL; }

public:
	operator T*()									{ if(!m_ptr) m_ptr=new T2; MYASSERT(m_ptr); return m_ptr; }
	T*	operator->()			{ if(!m_ptr) m_ptr=new T2; MYASSERT(m_ptr); return static_cast<T* >(m_ptr); }
	operator const T*()	 	 const					{ if(!m_ptr) m_ptr=new T2; MYASSERT(m_ptr); return m_ptr; }
	const T*	operator->() const	{ if(!m_ptr) m_ptr=new T2; MYASSERT(m_ptr); return static_cast<T* >(m_ptr); }

protected:
	T*			m_ptr;
};
template<TYPENAME T, TYPENAME T2>
inline void		safe_delete(CJavaObjC<T,T2>& pT)		{ pT.Release(); }


//////////////////////////////////////////////////////////////////////
// ˵������ָͨ�룬��֧��COPY��=����ģ�塰����Ҫ��Release()����֧��
// �����ָ�����ΪNULL��

template<TYPENAME T, TYPENAME T2>
class CAutoRefC
{
public:
	CAutoRefC() : m_ptr(NULL)					{}
	CAutoRefC(T* ptr) : m_ptr(ptr)				{}		// may be null
	~CAutoRefC()									{}
	CAutoRefC& operator=(T* ptr)					{ m_ptr=ptr; return *this; }
	T*	pop()									{ T* p=m_ptr; m_ptr=NULL; return p; }
public: // enable
	CAutoRefC& operator=(const CAutoRefC& ptr)	{ m_ptr=ptr.m_ptr; }
	CAutoRefC(const CAutoRefC&)					{ m_ptr=ptr.m_ptr; }

public:
	operator T*()									{ return m_ptr; }
	T*	operator->()			{ MYASSERT(m_ptr); return static_cast<T* >(m_ptr); }
	operator const T*()	 	 const					{ return m_ptr; }
	const T*	operator->() const	{ MYASSERT(m_ptr); return static_cast<T* >(m_ptr); }

protected:
	T*			m_ptr;
};





#endif // !defined(AFX_GAMEAUTOPTR_H__5708545C_E8F2_4155_AC66_4191BE0F150E__INCLUDED_)
