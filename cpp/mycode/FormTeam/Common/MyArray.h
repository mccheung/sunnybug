// MyArray.h: interface for the CMyArray class.
// paled, 2004.6.4
// �����װ�ࣺ
// ���ڷ�װC++���������ͣ����ڱ߽����ʱ���LOG��
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYARRAY_H__04538BAC_0EF7_46EB_AAF7_9201677B5D10__INCLUDED_)
#define AFX_MYARRAY_H__04538BAC_0EF7_46EB_AAF7_9201677B5D10__INCLUDED_

#pragma warning( disable : 4786 ) 
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "vector"
#include "common.h"

//////////////////////////////////////////////////////////////////////
// ʾ����
// ֻ��Ҫ�޸�H�ļ��ж��岿�֣�������ȫ���䡣
// ԭ����: int									m_setPuzzleCells[PUZZLE_CELLS_NUM];
// �ɸĳ�: CMyArray<int,PUZZLE_CELLS_NUM>		m_setPuzzleCells;
//////////////////////////////////////////////////////////////////////

// T: �����Ԫ������
// SIZE: ����ĳߴ�
// HINT: �����������಻ͬ���͵����飬�������������������LOGʱ�������ĸ����͵����������⡣Ҳ�ɲ��
template<class T, int SIZE, int HINT=0>
class CMyArray
{
public:
	CMyArray()	{ MYASSERT(SIZE); memset(m_set, 0, SIZE*sizeof(T));}
	CMyArray(const T* buf, int nSize)	{ MYASSERT(SIZE); IF_OK(nSize && nSize>=SIZE) memcpy(m_set, buf, SIZE*sizeof(T)); }
//��֧������	virtual ~CMyArray() {}

public: // �������������
	template<class E>
	T& operator [] (E nPos)	{ IF_OK(nPos>=0 && nPos<SIZE) return m_set[nPos]; LogSave("��MyArray(?,%d,%d)��",SIZE,HINT); throw; }
	template<class E>
	const T& operator [] (E nPos) const	{ IF_OK(nPos>=0 && nPos<SIZE) return m_set[nPos]; LogSave("��MyArray(?,%d,%d)��",SIZE,HINT); throw; }
public: // ���ݽӿ�
	operator char* ()			{ return (char*)m_set; }
	operator T*		()			{ return (T*)m_set; }
	template<class E>
	T& GetObj(E nPos)	{ IF_OK(nPos>=0 && nPos<SIZE) return m_set[nPos]; LogSave("��MyArray(?,%d,%d)��",SIZE,HINT); throw; }
protected:
	T	m_set[SIZE];
};

// ��ά����
#define	MY_ARRAY2(T,CX,CY,H)		CMyArray<CMyArray<T, CY, (H)+1>, CX, H>

// ��ά����
#define	MY_ARRAY3(T,CX,CY,CZ,H)		CMyArray<MY_ARRAY2(T, CY,CZ, (H)+1), CX, H>

////////////////////////////////////////////////////////////////////////////////////
// ������ָ���ʼ����CMyArray��
// 1����������鲻����ǰɾ��(!!!)
// 2���ߴ�����ԭ������ȫ��ͬ(!!!)
template<class T, int SIZE, int HINT=0>
class CMyArrayPtr
{
public:
	CMyArrayPtr(T* buf) : m_set(0)	{ MYASSERT(SIZE && buf); m_set = buf; }
	CMyArrayPtr(T* buf, int nSize) : m_set(0)	{ MYASSERT(SIZE && buf); IF_OK(nSize && nSize>=SIZE) m_set = buf; }
//��֧������	virtual ~CMyArrayPtr() {}

public: // �������������
	template<class E>
	T& operator [] (E nPos)	{ IF_OK(nPos>=0 && nPos<SIZE) return m_set[nPos]; LogSave("��MyArrayPtr(?,%d,%d)��",SIZE,HINT); throw; }
	template<class E>
	const T& operator [] (E nPos) const	{ IF_OK(nPos>=0 && nPos<SIZE) return m_set[nPos]; LogSave("��MyArrayPtr(?,%d,%d)��",SIZE,HINT); throw; }
public: // ���ݽӿ�
	operator char* ()			{ return (char*)m_set; }
	operator T*		()			{ return (T*)m_set; }
protected:
	T*	m_set;
};

#endif // !defined(AFX_MYARRAY_H__04538BAC_0EF7_46EB_AAF7_9201677B5D10__INCLUDED_)
