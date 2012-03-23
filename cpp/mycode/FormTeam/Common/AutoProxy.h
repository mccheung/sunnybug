// AutoProxy.h: declare for the CAutoProxy class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AUTOPROXY_H__5708545C_E8F2_4155_AC66_4191BE0F150E__INCLUDED_)
#define AFX_AUTOPROXY_H__5708545C_E8F2_4155_AC66_4191BE0F150E__INCLUDED_

#include "common.h"
#include "basetype.h"
#include "mycom.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define DEFINE_AUTOPROXY(P,T,v)	\
public:	\
	static P* CreateNew(T* p)	{ return new P(p); }	\
	virtual	void ReleaseProxy()	{ if((--proxy_count)==0) delete this; }	\
	virtual	void AddRef()		{ ++proxy_count; }	\
protected:	\
	P(T* p) : v(p),proxy_count(1) {}	\
	T* v;	\
	int proxy_count;	/*�������ü���*/

//////////////////////////////////////////////////////////////////////
// ˵�����Զ��ͷŶ���Ĵ�������֧��COPY��=����ģ����ҪReleaseProxy()����֧��
// �����ָ�����ΪNULL��
// ע�⣺��Ҫ��һ������������ͬʱ�ŵ�����CAutoProxy�У������Release���Ρ�

//////////////////////////////////////////////////////////////////////
template<TYPENAME T>
class POINT_NO_RELEASEPROXY : public T
{
	virtual void	ReleaseProxy()			= 0;		// prevent call this function
};

template<TYPENAME T, TYPENAME T2=T>
class CAutoProxy
{
public:
	CAutoProxy() : m_ptr(NULL)					{}
	~CAutoProxy()									{ ReleaseProxy(); }

public: // ע�⣺ÿ������ֻ����һ��CAutoProxy��������ÿ������ֻ������һ��CAutoProxy�ĳ�ʼ����
	CAutoProxy(T* ptr) : m_ptr(ptr)				{}		// may be null	// if(m_ptr) m_ptr->AddRef(); 
private: // ע�⣺�����޸ġ���ֹһ������ֵ�����CAutoProxy��
//	CAutoProxy& operator=(T* ptr)					{ if(m_ptr && m_ptr!=ptr) ReleaseProxy(); m_ptr=ptr; AddRef(); return *this; }

public:	//use yet	private: // can't use these
	CAutoProxy& operator=(const CAutoProxy& ptr)	{ if(this!=&ptr){ ReleaseProxy(); m_ptr=ptr.m_ptr; AddRef(); } return *this; }
	CAutoProxy(const CAutoProxy& ref) : m_ptr(ref.m_ptr)	{ AddRef(); }

protected: // ��ֹ�ⲿ����
	void AddRef()										{ if(m_ptr) m_ptr->AddRef(); }
	void ReleaseProxy()									{ if(m_ptr) m_ptr->ReleaseProxy(); m_ptr=NULL; }

private: // ע�⣺�����޸ġ���ֹ��ת��ָ�롣��ֹ�����õ���ָ�롣���⣬Ҳ��ֹ��CreateNewObj��ReleaseObj�Դ˶���Ϊ������
//	operator T*()										{ return m_ptr; }
//	operator const T*()	 	 const						{ return m_ptr; }
//	T*	pop()										{ T* p=m_ptr; m_ptr=NULL; return p; }

public:
	operator bool()										{ return !!m_ptr; }
	POINT_NO_RELEASEPROXY<T>*	operator->()			{ MYASSERT(m_ptr); return static_cast<POINT_NO_RELEASEPROXY<T>* >(m_ptr); }
	const POINT_NO_RELEASEPROXY<T>*	operator->() const	{ MYASSERT(m_ptr); return static_cast<POINT_NO_RELEASEPROXY<T>* >(m_ptr); }

protected:
	T*			m_ptr;
};
template<TYPENAME T, TYPENAME T2>
inline void		safe_release(CAutoProxy<T,T2>& pT)		{ pT.ReleaseProxy(); }
template<TYPENAME T, TYPENAME T2>
inline void		safe_delete(CAutoProxy<T,T2>& pT)		{ pT.ReleaseProxy(); }





#endif // !defined(AFX_GAMEAUTOPTR_H__5708545C_E8F2_4155_AC66_4191BE0F150E__INCLUDED_)
