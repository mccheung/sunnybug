#ifndef _DBGFUNC_H
#define _DBGFUNC_H
#include "windows.h"
#include <eh.h> 

#pragma optimize( "y", off )	// ��֤CALL FRAME���ᱻ�Ż���

//���غ������õ�ַ����nLevel��0�����ص���DumpFuncAddress�����ĵ�ַ��nLevelÿ��1�����ظ���һ�����õ�ַ
//���ѵ��ö�ջ��ʽ����pBuf������
PBYTE DumpFuncAddress(int nLevel=0, char* pBuf=NULL, PEXCEPTION_POINTERS pException=NULL);
class CSEHException
{
public:
	static  void trans_func( unsigned int u, EXCEPTION_POINTERS* pExp ); 
	void initialize_seh_trans_to_ce();
	CSEHException(){OldFanc=NULL;}
	~CSEHException()
	{
		if(OldFanc)_set_se_translator(OldFanc); 
	}
	_se_translator_function OldFanc;
};
#endif