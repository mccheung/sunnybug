// FormTeam.h: interface for the CFormTeam class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FORMTEAM_H__758D0A09_6278_41C3_BC67_EC29E3E3D9E0__INCLUDED_)
#define AFX_FORMTEAM_H__758D0A09_6278_41C3_BC67_EC29E3E3D9E0__INCLUDED_

#pragma once

#ifdef _NOGAME
#include "GameWord.h"
#include "TimeOut.h"
#endif // _NOGAME

#include "FormTeamMember.h"
#include <AutoPtr.h>
#include <GameObjSet.h>

class CFormTeam  
{
public:
	enum FormTeamStaus
	{
		FORMTEAM_NONE,
		FORMTEAM_MARCH,			//�о�
		FORMTEAM_SORTFORM,		//����
		FORMTEAM_PASSBLOCK,		//���ϰ�
		FORMTEAM_IDLE,			//��Ӳ��ƶ�
	};
	typedef CGameObjSet<CFormTeamMember> CFormTeamMemberSet;	//���վ���˳���������
	typedef std::list<int> DirList;

public:
	CFormTeam();
	~CFormTeam();

	//////////////////////////////////////////////////////////////////////////
	//��Ӿ���
public:
	int		GetDir()						{ return m_nDir;}
	int		GetOldDir()						{ return m_nOldDir;}
	void	SetDir(int nDir);
	const MatrixIndex& GetPathFinderIdx()	{ return m_idxPathFinder;}

protected:
	//��idxRotateCenterΪ������תnDegree��
	//ptRotateCenter	[in]	���ĵ���������
// 	bool	Rotate(OBJPOS& ptRotate, 
// 		const MatrixIndex& idxRotate, 
// 		const MatrixIndex& idxRotateCenter, 
// 		const OBJPOS& ptRotateCenter, 
// 		const int nDegree);
	bool	RotateDir(OBJPOS& ptRotate, 
		const MatrixIndex& idxRotate, 
		const MatrixIndex& idxRotateCenter, 
		const OBJPOS& ptRotateCenter, 
		const int nDir);
	int		GetMatrixWidth() { return m_szMatrix.cx;}
	//����ֲ�����->��ͼ����
	bool	CalcMatrixPos(OBJPOS& posWorld, const MatrixIndex& idxMatrix);	

	//////////////////////////////////////////////////////////////////////////
	//���ɱ��
public:
	bool	Create();
	void	OnTimer();

	//////////////////////////////////////////////////////////////////////////
	//��Ա����
public:
	CFormTeamMemberSet* QueryMemberSet() { return m_pTeamMembersSet;}

protected:
	bool	AddMember(CFormTeamMember* pMember);
	CFormTeamMember*	QueryMember(const MatrixIndex& idxMatrix);
	//������ߵ������ĳ�Ա�ٶȣ�Ϊ����ٶ�
	bool	CalcSpeed();

	//////////////////////////////////////////////////////////////////////////
	//״̬
protected:
	FormTeamStaus	GetStatus() { return m_eStatus;}
	bool	SetStatus(FormTeamStaus eStatus);

	//��ͬ״̬����
	bool	ProcessMarch();		//FORMTEAM_MARCH
	bool	ProcessSortForm();	//FORMTEAM_SORTFORM
	bool	ProcessPassBlock();
	bool	ProcessIdle();
	
	//////////////////////////////////////////////////////////////////////////
	//���Ѱ·
public:
	bool	SetTarget(const OBJPOS& ptTarget);	//���ñ��ǰ��Ŀ���

	OBJPOS	GetFinderPos();
	OBJPOS	GetMatrix00Pos();
	bool	GetTmpTarget(OBJPOS& pt);

protected:
	//����Ŀ�������ڱ�ӵ�λ�ã�����Ŀ������ĸ��ӿ�ʼѰ·
	bool	SelectPathFinderPos(const OBJPOS& ptTarget);
	CFormTeamMember*	QueryPathFinderMember();	//�����й�������·��Ҳ����û��

	//////////////////////////////////////////////////////////////////////////
protected:
	OBJSIZE			m_szMatrix;
	int				m_nDir;				//�����һ�е���������
	int				m_nOldDir;

	//////////////////////////////////////////////////////////////////////////
	//��ʱϸ��Ѱ·
	MatrixIndex		m_idxPathFinder;	//Ѱ·��Ա
	OBJPOS			m_ptTmpTarget;		//Ѱ·��Ա��Ҫ�����Ŀ���
	OBJPOS			m_ptPosFinder;		//Ѱ·��Ա��ǰ����
	DirList			m_lstDir;			//Ѱ·��Ա����ʱ·��

	//////////////////////////////////////////////////////////////////////////
	//����Ŀ��Ѱ·
	OBJPOS			m_ptFianlTarget;	//�������Ŀ���
	DirList			m_lstFinalDir;		//Ѱ·��Ա������·��

	//////////////////////////////////////////////////////////////////////////
	//��Ա
	CAutoPtr<CFormTeamMemberSet>	m_pTeamMembersSet;

	FormTeamStaus	m_eStatus;
	CTimeOutMS		m_MoveTimer;		//����ms��1��

	//////////////////////////////////////////////////////////////////////////
	//link
public:
	const AUTOLINK_NOTE* QueryLink() const	{ return m_link.QueryNote(); }
protected:
	CAutoLink<CFormTeam>	m_link;
};

#endif // !defined(AFX_FORMTEAM_H__758D0A09_6278_41C3_BC67_EC29E3E3D9E0__INCLUDED_)
