#ifndef _PCLINT_H_
#define _PCLINT_H_

//pclint�ӿ�

//////////////////////////////////////////////////////////////////////////
//������
//�ü��func_template�Ĺ���ȥ���func
#define LINT_LIKE_FUNC(func_template, func)	/*lint --function(func_template, func) */

//������Ľӿ�func�й�ָ��
#define LINT_CUSTODIAL(func)				/*-sem(func,custodial(t)) */

//����ģ��t�Ľӿ�func�й�ָ��
#define LINT_CUSTODIAL_TEMPLATE(t, func)	LINT_LIKE_FUNC(free, t::func);LINT_NOERR_CALLFUNC(424, t<*>::func)

#define TEST_ME(func)

//////////////////////////////////////////////////////////////////////////
//���ظ澯

//���ص��ú���funcʱ�����ĸ澯
#define LINT_NOERR_CALLFUNC(err, func)	/*lint -ecall(err, func) */

//���ص��÷���ʱ�����ĸ澯
#define LINT_NOERR_SYM(err, sym)	/*lint -esym(err, sym) */

//���ص�ǰ�в����ĸ澯
#define LINT_NOERR_LINE(err)			/*line !e{err} */

//���غ����ڵĸ澯
#define LINT_NOERR_INFUNC(err, func)	/*line -efunc(err,func) */

//////////////////////////////////////////////////////////////////////////


#endif