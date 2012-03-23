// SgiAlloc.h: interface for the CSgiAlloc class.
// paled, 2007.1.24
//////////////////////////////////////////////////////////////////////
// ��SGISTL��ʵ�ֵ��ڴ���������ܽ���ڴ������Ƭ�����⡣
// (ע�⣺���ж������ڴ��в��������ռ䣬��һ����CMyHeap��ͬ��)
// put line in *.h:		SGIALLOC_DECLARATION(s_heap)
// put line in *.cpp:	SGIALLOC_IMPLEMENTATION(TypeName,s_heap)

#if !defined(AFX_SGIALLOC_H__CFFE0003_9790_4E6B_B0C8_16CF55F89B19__INCLUDED_)
#define AFX_SGIALLOC_H__CFFE0003_9790_4E6B_B0C8_16CF55F89B19__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>

class CSgiAlloc
{
public:
	CSgiAlloc(LPCTSTR pszClassName = NULL);
	~CSgiAlloc();
//	static CSgiAlloc* CreateNew()		{ return new CSgiAlloc; }
public:
	void*	Alloc(size_t size);
	void	Free(void* ptr, size_t size);
	BOOL	IsValidPt(void* p);
protected:
	enum { CLASSNAME_SIZE = 32 };
//	HANDLE			m_hAlloc;
	long			m_uNumAllocsInAlloc;
	char			m_szClassName[CLASSNAME_SIZE];		// ����DEBUG
};

#ifdef	_DEBUG ////////////////////////////////////////////////////////

#define	SGIALLOC_DECLARATION(VAR)
#define	SGIALLOC_IMPLEMENTATION(T,VAR)

#else // _DEBUG ////////////////////////////////////////////////////////

#define	SGIALLOC_DECLARATION(VAR)				\
	void*  operator new	(size_t size);			\
	void   operator delete	(void* p);			\
public:											\
	static BOOL		IsValidPt(void* p);			\
protected:										\
	static CSgiAlloc	VAR;


#define	SGIALLOC_IMPLEMENTATION(T,VAR)			\
CSgiAlloc	T::VAR(#T);							\
void * T::operator new(size_t size)				\
	{ MYASSERT(size==sizeof(T)); return VAR.Alloc(size); }	\
void T::operator delete(void* p)				\
	{ VAR.Free(p, sizeof(T)); }					\
BOOL T::IsValidPt(void* p)						\
	{ return VAR.IsValidPt(p); }

#endif // _DEBUG ////////////////////////////////////////////////////////


#endif // !defined(AFX_SGIALLOC_H__CFFE0003_9790_4E6B_B0C8_16CF55F89B19__INCLUDED_)
