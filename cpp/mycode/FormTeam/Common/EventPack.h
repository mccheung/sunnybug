// EventPack.h: interface for the CEventPack class.
// paled: 2004.3.11
// �ڲ���Ϣ������ߡ�
//
// �����
// CEventPack(DWORD idEvent, ULONG idKey, DWORD idAction=0);	// ������Ϣ���
//																// Ŀǰ idEvent �� idAction ֻ֧��USHORT, idKey ֧��DWORD��
// CEventPack& operator <<(...)									// ��������Ϣ����Ӹ��Ӳ���
//
// ������
// CEventPack(const char* pPackBuf, int nPackSize);				// ������Ϣ����
// CEventPack& operator >>(...);								// ���ڴ���Ϣ�н��������Ӳ���
//
// EVENTPACK_MORE_CHECK : ���Լ���ǰ32�����������ʹ���
//////////////////////////////////////////////////////////////////////
// ���÷�����
// idEvent ͨ������CLS_ID��Ҳ���Ǵ����ĸ���
// idAction ͨ��������Ϣ�����ͣ�����WORD�͹���
// idKey ͨ�����ڶ���ID��ͨ��GetID()��ȡ��
// �������ܴ�һ����������һ���������ڲ���Ϣ��


#if !defined(AFX_EVENTPACK_H__7565C398_0FA3_4E78_9344_860F1D15C840__INCLUDED_)
#define AFX_EVENTPACK_H__7565C398_0FA3_4E78_9344_860F1D15C840__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "basefunc.h"

#define	EVENTPACK_MORE_CHECK

#ifdef	EVENTPACK_MORE_CHECK
const int EVENTPACK_HEAD		= sizeof(USHORT) + sizeof(ULONG) + sizeof(DWORD) + sizeof(DWORD);
#else
const int EVENTPACK_HEAD		= sizeof(USHORT) + sizeof(ULONG) + sizeof(DWORD);
#endif
const int EVENTPACK_SIZE		= 1024 + EVENTPACK_HEAD;

class CEventPack  
{
public:
	CEventPack(DWORD idEvent, ULONG idKey, DWORD idAction=0);
	CEventPack(const char* pPackBuf, int nPackSize);
	virtual ~CEventPack();

public: // appilcation
	class Buffer;
	class PackBuffer;
	CEventPack& operator <<(const int nData);
	CEventPack& operator <<(const String& str);
	CEventPack& operator <<(const Buffer buf);			// size >=0 && <=255
	CEventPack& operator <<(const PackBuffer& buf);		// size >=0 && <=255
	CEventPack& operator >>(int& nData);
	CEventPack& operator >>(String& str);
	CEventPack& operator >>(Buffer buf);				// size >=0 && <=255, psize ���س���
	CEventPack& operator >>(PackBuffer& buf);			// size >=0 && <=255

	CEventPack& operator >>(unsigned int& nData)	{ return operator >>( (int&) nData ); }
	CEventPack& operator >>(long& nData)			{ return operator >>( (int&) nData ); }
	CEventPack& operator >>(unsigned long& nData)	{ return operator >>( (int&) nData ); }

public: // const
	int		GetObjType()	const		{ return m_idObjType; }
	ULONG	GetObjID()		const		{ return m_idKey; }
	int		GetAction()		const		{ return m_idAction; }

	const char*	GetBuf()	const		{ return m_buf; }
	int		GetSize()		const		{ return m_bSplit ? m_size : m_ptr-m_buf; }

protected:
	union{
		char	m_buf[EVENTPACK_SIZE +1];		// +1: ���࣬���һ�������ڷ�ֹ�����
		struct{
			DWORD	m_idObjType;				// ���ĳߴ�����EVENTPACK_HEAD��ͬ
			USHORT	m_idAction;
			ULONG	m_idKey;
#ifdef	EVENTPACK_MORE_CHECK
			DWORD	m_bitParam;					// �������ͣ���BIT�Ӹߵ���(0��INT��1��STR)
#endif
			char	m_setParam[1];
		};
	};

protected: // ctrl
	bool	IsUnite()				{ return !m_bSplit; }
	bool	IsSplit()				{ return m_bSplit; }
	bool	CheckPush(int nSize)	{ return m_ptr+nSize <= m_buf + EVENTPACK_SIZE; }
	bool	CheckPop(int nSize)		{ return m_ptr+nSize <= m_buf + m_size; }
protected:
	bool	m_bSplit;		// false: ���ͷ���true: ���շ�
	char*	m_ptr;			// ��ǰ����ָ�롣���ͷ���һ��д���λ�ã����߽��շ���һ�οɶ����λ��
	int		m_size;			// ���շ�����ϢSIZE�������ڷ��ͷ�
#ifdef	EVENTPACK_MORE_CHECK
	UCHAR	m_nCount;		// ����������������ȥ����0��ʼ�����32��
#endif

public:
	///////////////////////////////////
	// �ں���
	///////////////////////////////////
	// ����
	// pack << 3 << 4 << CEventPack::Buffer(pBuf, 3) << "56" << 56 << "78";
	// pack2 >> a >> b >> CEventPack::Buffer(buf, 3) >> sb >> c >> sc;			// У�鳤��Ϊ3
	// pack2 >> a >> b >> CEventPack::Buffer(buf, &nSize) >> sb >> c >> sc;		// ȡ������
	class Buffer
	{
	public:
		Buffer(char* pBuf, int nSize) : ptr(pBuf), size(nSize), psize(0) {
		}			// ��У�鳤��
		Buffer(char* pBuf, int* pSize) : ptr(pBuf), size(0), psize(pSize) {
		}		// ���س���
	private:
		char*	ptr;
		int		size;
		int*	psize;
		friend CEventPack;
	};
	class PackBuffer
	{
	public:
		PackBuffer()  { Clear(); }
		PackBuffer(const char* pBuf, int nSize) { Clear(); m_nSize=nSize; memcpy(m_Buffer, pBuf, nSize);}
		char*	GetBuf()	const	{ return (char*)m_Buffer; }
		int		GetSize()	const	{ return m_nSize; }
		void	Clear()		{ memset(m_Buffer, 0, sizeof(m_Buffer)); m_nSize=0; }

	private:
		char m_Buffer[255];
		int  m_nSize;
		friend CEventPack;
	};
};

#endif // !defined(AFX_EVENTPACK_H__7565C398_0FA3_4E78_9344_860F1D15C840__INCLUDED_)

