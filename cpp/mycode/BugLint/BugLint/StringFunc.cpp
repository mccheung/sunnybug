#include "StringFunc.h"
#include <iostream>
#include <assert.h>

using namespace std;

//�ҵ������ַ����м���ַ�
bool GetFirstSubString(const std::string& str, const std::string& strHead, const std::string& strTail, std::string strSub)
{
	string::size_type szHead = str.find(strHead, 0);
	if(szHead == string::npos)
		return false;

	string::size_type szTail = str.find(strTail, szHead+1);
	if(szTail == string::npos)
		return false;

	if(szTail <= szHead)
	{
		assert(false);
		return false;
	}

	strSub = str.substr(szHead+1, szTail-szHead-1);

	return true;
}

bool ParsePathString()
{
	const string pathname = "D:\\demo\\xswrun\\BugLint\\BugLint/BugLint.vcproj";

	// ʶ�����һ��'\'����'/'��λ��
	string::size_type backslashIndex = pathname.find_last_of('\\');
	string::size_type backslashIndex2 = pathname.find_last_of('/');
	backslashIndex = max(backslashIndex, backslashIndex2);

	//·���������һ��'\'֮ǰ���ַ�
	const string path = pathname.substr(0,backslashIndex);

	// ·����β�����ļ���
	const std::string filename = pathname.substr(backslashIndex+1,-1);

	// ��չ����
	// �����ҵ����һ��'.'��λ�á� ���
	// û��'.'����dotIndexΪ-1
	const int dotIndex = filename.find_last_of('.');
	//�����Ƿ���'.'��������ַ��Ƿ�Ϊ"cpp"
	if (dotIndex != -1 )
	{
		const std::string ext = filename.substr(dotIndex+1, string::npos);
	}

	return 0;
}
