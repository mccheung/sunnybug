// �ⲿ����ֱ�� include ����ļ�
//
#ifndef ANALYST_SHARED_COMMON_HEADER
#define ANALYST_SHARED_COMMON_HEADER

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//1. ����CLIENT��ص�SEND��RECV��ʱ�䡢��������Ϣ���ߴ硣
//2������NPC��������SEND��RECV��ʱ�䡢��������Ϣ���ߴ硣
//3�����ÿ���̣߳�ͳ��SOCKET�շ��������߼�����(�������ݿ�)�����ݿ���ã���3�����ʱ�䣬����������Եı�����
//4�����ÿ�����ݿ����ӣ�ͳ��SELECT��UPDATE��INSERT��DELETE��������������������Եı�����SELECT������ͳ��һ�½��յļ�¼����
//5�����ÿ���̣߳�ͳ��ITEM��USER��������3��������ݿ�������������������Եı�����(��������FARMITEMһ��)
//6��������Ҫͳ�Ƶ����ݡ�

// 1.ͳ��SELECT��UPDATE��INSERT��DELETE��������
// 2.socket�ֽ���
enum ANALYST_WHAT_COMMON
{
		ANALYST_LOGSAVE,
		//...(�������������)

		// ��COMMON����������ֵ���뱣����
		ANALYST_WHAT_COMMON_END
};



#endif //ANALYST_SHARED_COMMON_HEADER