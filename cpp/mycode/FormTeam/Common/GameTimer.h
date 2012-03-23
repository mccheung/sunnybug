// GameTimer.h: interface for the CGameTimer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAMETIMER_H__059AED43_D21C_4072_A172_20A7D8B6DF52__INCLUDED_)
#define AFX_GAMETIMER_H__059AED43_D21C_4072_A172_20A7D8B6DF52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <time.h>
#include "BaseFunc.h"

//////////////////////////////////////////////////////////////////////
// ʱ���࣬ÿ�졢�ܡ��´���һ�ε�ʱ�ӡ�
// ��ʽ��MMWWHHMMSS��MM��Ϊ0��ʾÿ�´���һ�Σ�WW��Ϊ0��ʾÿ�ܴ���һ�Σ�����Ϊÿ�촥��һ�Ρ�SSͨ��Ϊ0��
template<int I>
class CGameTimer_
{
public:
	CGameTimer_(int nFormat = I) : m_nFormat(nFormat), m_bActive(false)	{}
//	virtual ~CGameTimer_() {}

public:
	void	SetTimer(int nFormat)			{ m_nFormat = nFormat; }
	// ʱ���Ƿ񴥷�(ֻ����һ��)����SetTimer���ʹ�ã���ʵ��ֻ����һ�ε�ʱ�ӡ�
	bool	ActiveTimer	()					{ return ActiveTimer(m_nFormat); }
	// ʱ���Ƿ񴥷�(ֻ����һ��)����ʵ��ֻ����һ�ε�ʱ�ӡ�
	bool	ActiveTimer	(int nFormat)		{ if(!::IsActiveTime(time(NULL), nFormat)) return (m_bActive=false),false; if(!m_bActive) return (m_bActive=true),true; else return false; }

public: // get
	int		GetTimeStamp()					{ return m_nFormat; }

protected:
	int		m_nFormat;
	bool	m_bActive;
};
typedef	CGameTimer_<246060>	CGameTimer;		// =246060 : ���������ʼ���������ܵ�ʱ��


#endif // !defined(AFX_GAMETIMER_H__059AED43_D21C_4072_A172_20A7D8B6DF52__INCLUDED_)
