// LoopCount.h: interface for the CLoopCount class.
// ��ѭ����������������ࡣ
// Init()	: ��ָ��ͷ��β������������ͷβ������ͬ�����ɴ�С����Ҳ�ɴӴ�С�����ɲ��ڷ�Χ�ڣ������岻ȷ�������ظ����á�
// Next()	: ���ص�ǰ�����ڲ�״̬�Ƶ���һ�����������������������������ͷβ��ȷ�������ָ��������������ô������ܳ�����ֵ��
// IsValid(): ����Ƿ񳬹���������
// Last()	: ǰһ��״̬��(��һ�ε���Next()���ص�ֵ)
// GetCount(): ����ȡ���Ĵ�����������Next()�Ĵ�����
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOOPCOUNT_H__B2E9D39C_2685_4AF5_8C78_78AF1F82A6C8__INCLUDED_)
#define AFX_LOOPCOUNT_H__B2E9D39C_2685_4AF5_8C78_78AF1F82A6C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLoopCount  
{
public:
	CLoopCount();
	/*virtual*/ ~CLoopCount();
	bool Init(int nFrom, int nTo, int nStart, int nAllCount=0);

public:
	int		Next();
	void	SetPos(int nPos);
public: // const
	int		Last()		const		{ return m_nLast; }
	bool	IsValid()	const		{ return m_bValid; }
	int		GetFirst()	const		{ return m_nStart; }
	int		GetCount()	const		{ return m_nCount; }

protected:
	int		m_nFrom;
	int		m_nTo;
	int		m_nStart;
	int		m_nCurr;
	int		m_nCount;
	int		m_nLimit;
	bool	m_bValid;
	int		m_nLast;
};

#endif // !defined(AFX_LOOPCOUNT_H__B2E9D39C_2685_4AF5_8C78_78AF1F82A6C8__INCLUDED_)
