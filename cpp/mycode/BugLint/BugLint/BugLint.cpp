#include "stdafx.h"
#include "StringFunc.h"
#include "ExcuteCmdLine.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <tinyxml.h>
#include <memory>
#include <fstream>
#include <string.h>
#include <io.h>
#include "getopt.h"

using std::string;
using namespace std;

//////////////////////////////////////////////////////////////////////////
typedef std::vector<std::string>	MyStringArray;


//////////////////////////////////////////////////////////////////////////
//const config
static const std::string strCpp = ".cpp";
static const std::string strC = ".c";

//////////////////////////////////////////////////////////////////////////

//��pParentNode�ڵ㣬����������pName������ֵpVal����ȡ��Ӧ���ӽڵ�
TiXmlElement* 
GetSubNodeByAttrVal( TiXmlElement* pParentNode, const std::string& strNodeName, const std::string& strAttrName, const std::string& strAttrVal ) 
{
// 	IF_NOT(pParentNode)
// 		return NULL;

	TiXmlElement* pSubNode = pParentNode->FirstChildElement(strNodeName);
	std::string strVal;
	while (pSubNode)
	{
		if (pSubNode->QueryValueAttribute(strAttrName, &strVal) == TIXML_SUCCESS)
		{
			if(strVal == strAttrVal)
				break;
		}

		pSubNode = pSubNode->NextSiblingElement();
	}

	return pSubNode;
}

//��pParentNode�ڵ㣬�����ӽڵ���������������ȡ��Ӧ������ֵ
std::string
GetAttrValByAttrName( TiXmlElement* pParentNode, const std::string& strNodeName, const std::string& strAttrName)
{
	IF_NOT(pParentNode)
		return NULL;

	TiXmlElement* pSubNode = pParentNode->FirstChildElement(strNodeName);
	std::string strVal;
	while (pSubNode)
	{
		if (pSubNode->QueryValueAttribute(strAttrName, &strVal) == TIXML_SUCCESS)
		{
			break;
		}

		pSubNode = pSubNode->NextSiblingElement();
	}
	if(!pSubNode)
		strVal.clear();

	return strVal;
}

bool 
MySplit(MyStringArray& _str_list,
			  const std::string& _str,
			  const MyStringArray& _separator_list,
			  const bool _ignore_empty=true)
{
	assert(!_separator_list.empty());
	_str_list.clear();

	string::const_iterator i = _str.begin();
	string::const_iterator last = i;

	for (; i != _str.end(); i++)
	{
		for (MyStringArray::const_iterator it_separator=_separator_list.begin();
			it_separator!=_separator_list.end();
			it_separator++)
		{
			if (string(i, i + it_separator->length()) == *it_separator)
			{
				string result_str(last,i);
				if(!result_str.empty() || !_ignore_empty)
				{
					_str_list.push_back(result_str);
				}
				last = i + it_separator->length();
			}
		}
	}

	if (last != i)
		_str_list.push_back(string(last, i));


	//unique()��Ҫ��������
	std::sort(_str_list.begin(),_str_list.end());

	//unique()���������򣬽��ظ���Ԫ���ƶ������к���
	MyStringArray::iterator new_end = std::unique(_str_list.begin(),_str_list.end());

	//����ǰ���Ԫ�ض���Ψһ�ģ�����ɾ��new_end�����Ԫ��
	_str_list.erase(new_end,_str_list.end());


	return (!_str_list.empty());
}

void 
AppendFile( TiXmlElement* pFilesNode, const std::string& strSubNodeName, MyStringArray &lstFile) 
{
// 	IF_NOT(pFilesNode)
// 		return;

	std::string strVal;

	//�����ӽڵ�
	TiXmlElement* pSubNode = pFilesNode->FirstChildElement(strSubNodeName);
	while (pSubNode)
	{
		//File�ڵ���ܰ����ļ��б�
		if(stricmp(strSubNodeName.c_str(), "File") == 0)
		{
			if (pSubNode->QueryValueAttribute("RelativePath", &strVal) == TIXML_SUCCESS)
			{
				if (strVal.compare(strVal.size() - strCpp.size(), strCpp.size(), strCpp) == 0
					|| strVal.compare(strVal.size() - strC.size(), strC.size(), strC) == 0)
				{
					lstFile.push_back(strVal);
				}
			}
		}

		TiXmlElement* pFile = pSubNode->FirstChildElement();
		while (pFile)
		{
			if (pFile->QueryValueAttribute("RelativePath", &strVal) == TIXML_SUCCESS)
			{
				if (strVal.compare(strVal.size() - strCpp.size(), strCpp.size(), strCpp) == 0
					|| strVal.compare(strVal.size() - strC.size(), strC.size(), strC) == 0)
				{
					lstFile.push_back(strVal);
				}
			}
			pFile = pFile->NextSiblingElement();
		}

		pSubNode = pSubNode->NextSiblingElement();
	}

}


void
WriteLnt(ofstream& file, const MyStringArray& lstStr, const std::string strFlag="", const bool bQuote=false)
{
	if(!file.is_open())
		return;

	std::string str;
	for (MyStringArray::const_iterator it=lstStr.begin(); it!=lstStr.end(); ++it)
	{
		str = strFlag + (bQuote?"\"":"") + *it + (bQuote?"\"":"") + "\n";
		file.write(str.c_str(), str.size());
	}
}

bool LintVCProject(const std::string& strVCProj, const std::string& strLnt, const string& strConfigurationName)
{
	std::auto_ptr<TiXmlDocument> myDocument (new TiXmlDocument());
	IF_NOT (myDocument->LoadFile(strVCProj))
	{
		std::cout << "�ļ�������:" << strVCProj << endl;
		return false;
	}

	//����lnt
	ofstream fLnt(strLnt.c_str(), ios::ate|ios::app);
	if(!fLnt.is_open())
	{
		std::cout << "�ļ�������:" << strLnt << endl;
		return false;
	}

	TiXmlElement* rootElement = myDocument->RootElement();  //Class
	IF_NOT(rootElement)
		return false;

	TiXmlElement* pConfigurations = rootElement->FirstChildElement("Configurations");
	IF_NOT(pConfigurations)
		return false;

	//��������Configuration��ֱ���ҵ�Win32Debug����
	TiXmlElement* pConfiguration = GetSubNodeByAttrVal(pConfigurations, "Configuration", "Name", strConfigurationName);
	if(!pConfiguration)
	{
		cout << "δ�ҵ�����:" << strConfigurationName << endl;
		return false;
	}

	//����Configuration���е�Tool�ڵ㣬�ҵ���������
	TiXmlElement* pCompiler = GetSubNodeByAttrVal(pConfiguration, "Tool", "Name", "VCCLCompilerTool");
	if(!pCompiler)
		return false;

	MyStringArray separator_list;
	separator_list.push_back(";");
	separator_list.push_back(",");

	//IncludeĿ¼
	std::string strInclude;
	pCompiler->QueryValueAttribute("AdditionalIncludeDirectories", &strInclude);
	MyStringArray lstInclude;
	MySplit(lstInclude, strInclude, separator_list);
	WriteLnt(fLnt, lstInclude, "-i", true);

	//PreprocessorDefinitions
	std::string strDefines;
	pCompiler->QueryValueAttribute("PreprocessorDefinitions", &strDefines);
	MyStringArray lstDefines;
	MySplit(lstDefines, strDefines, separator_list);
	WriteLnt(fLnt, lstDefines, "-d");

	//�ļ��б�ڵ�
	TiXmlElement* pFilesNode = rootElement->FirstChildElement("Files");
	IF_NOT(pFilesNode)
		return false;

	MyStringArray lstFile;
	//��ȡFilter�ļ��б�
	AppendFile(pFilesNode, "Filter", lstFile);
	//��ȡFile�ļ��б�
	AppendFile(pFilesNode, "File", lstFile);
	WriteLnt(fLnt, lstFile);

	return true;
}

bool VCProject_GetFileList(const std::string& strVCProj, const std::string& strLnt)
{
	std::auto_ptr<TiXmlDocument> myDocument (new TiXmlDocument());
	IF_NOT (myDocument->LoadFile(strVCProj))
	{
		std::cout << "�ļ�������:" << strVCProj << endl;
		return false;
	}

	//����lnt
	ofstream fLnt(strLnt.c_str(), ios::ate|ios::app);
	if(!fLnt.is_open())
	{
		std::cout << "�ļ�������:" << strLnt << endl;
		return false;
	}

	TiXmlElement* rootElement = myDocument->RootElement();  //Class
	IF_NOT(rootElement)
		return false;

	MyStringArray separator_list;
	separator_list.push_back(";");
	separator_list.push_back(",");

	//�ļ��б�ڵ�
	TiXmlElement* pFilesNode = rootElement->FirstChildElement("Files");
	IF_NOT(pFilesNode)
		return false;

	MyStringArray lstFile;
	//��ȡFilter�ļ��б�
	AppendFile(pFilesNode, "Filter", lstFile);
	//��ȡFile�ļ��б�
	AppendFile(pFilesNode, "File", lstFile);
	WriteLnt(fLnt, lstFile);

	return true;
}

bool ParseSln_GetProj(const string& strLine, string& strVCProj)
{
	const string strTail = ".vcproj\",";

	string::size_type szTail = strLine.find(strTail, 0);
	if(szTail == string::npos)
		return false;

	string::size_type szHead = strLine.find_last_of("\"", szTail);
	if(szHead == string::npos)
		return false;

	if(szTail <= szHead)
	{
		assert(false);
		return false;
	}

	strVCProj = strLine.substr(szHead+1, szTail-szHead-1 + strTail.size()-2);	//-2:",

	return true;
}

//��*.vcproj�������·������lnt
bool AppendVCprojPath2Lnt(const string& strProjPath, const string& strLntPath)
{
	ofstream fLnt(strLntPath.c_str());
	if(!fLnt.is_open())
	{
		assert(false);
		return false;
	}

	string::size_type backslashIndex = strProjPath.find_last_of('\\');
	string::size_type backslashIndex2 = strProjPath.find_last_of('/');
	backslashIndex = max(backslashIndex, backslashIndex2);

	const string path = strProjPath.substr(0, backslashIndex);

	if(path == strProjPath)
		return true;

	MyStringArray lstInclude;
	lstInclude.push_back(path);
	WriteLnt(fLnt, lstInclude, "-i", true);
	fLnt.close();

	return true;
}

bool LintSln(const std::string& strSln, const std::string& strLnt, const string& strConfigurationName)
{
	ifstream file(strSln.c_str());
	if(!file.is_open())
	{
		cout << "file open fail:" << strSln << endl;
		return false;
	}

	ofstream fSlnLnt(strLnt.c_str());
	if(!fSlnLnt.is_open())
	{
		cout << "file open fail:" << strLnt << endl;
		return false;
	}

	char acLine[256] = {0};
	string strProj;
//	string strLnt;
	//�����ļ����ݣ��ҵ�����vcproj
	while(!file.eof()) 
	{ 
		acLine[0] = 0;
		file.getline(acLine, sizeof(acLine)-1);
		if(!ParseSln_GetProj(acLine, strProj))
			continue;

// 		strLnt = strProj + ".lnt";
// 		AppendVCprojPath2Lnt(strProj, strLnt);
// 		if(!LintVCProject(strProj, strLnt, strConfigurationName))
// 		{
// 			cout << "����" << strProj	 << "ʧ��" << endl;
// 			break;
// 		}
		fSlnLnt.write(strProj.c_str(), strProj.size());
	}

	return true;
}

// extern int test_getopt(int argc, _TCHAR* argv[]);

//////////////////////////////////////////////////////////////////////////
//command linevoid
void PrintHelp()
{
	std::cout << "=========================" << std::endl;
	std::cout << "1������lnt:" << std::endl;
	std::cout << "ButLint.exe --prj=xxx.vcproj --lnt=xxx.lnt" << std::endl;
	std::cout << "2������sln:" << std::endl;
	std::cout << "ButLint.exe --sln=xxx.sln" << std::endl;
	std::cout << "3�������ļ��б�:" << std::endl;
	std::cout << "ButLint.exe --prj=xxx.vcproj --list=xxx.list" << std::endl;
	std::cout << "=========================" << std::endl;
}

static const string CMD_INPUTFILE= "";
static const string CMD_HELP	= "help";
static const string CMD_LNT		= "lnt";
static const string CMD_LIST	= "list";
static const string CMD_CFG		= "cfg";

bool InitParam(ParamContainer& p, int argc, TCHAR* argv[])
{
	p.addParam("", 0, ParamContainer::noname, "�����ļ�");  
	p.addParam(CMD_LNT, 0, ParamContainer::filename, "����lnt��ʽ�ļ�");  
	p.addParam(CMD_LIST, 0, ParamContainer::filename, "�����ļ��б�");
	p.addParam(CMD_CFG, 0, ParamContainer::regular, "��������", "Debug|Win32");
	p.addParam(CMD_HELP, 'h', ParamContainer::novalue, "����");  

	ParamContainer::errcode err = p.parseCommandLine(argc, argv);
	if(err != ParamContainer::errOk)
	{
		cout << p.getErrorMessage(err) << endl;
		return false;
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////
int _tmain(int argc, _TCHAR* argv[])
{
	_set_error_mode(_OUT_TO_MSGBOX);
	// 	return test_getopt(argc, argv);
	
	ParamContainer p;
	if(!InitParam(p, argc, argv))
	{
		return -1;
	}

	if(p.is_set(CMD_HELP))
	{
		stringstream strm;
		p.dumpHelp(strm);
		cout << strm.str();
		return 0;
	}
	
	const string strInputFile = p[CMD_INPUTFILE];
	if (access(strInputFile.c_str(), 0) != 0)
	{
		return ERROR_FILE_NOT_FOUND;
	}

	if (p.is_set(CMD_LIST))	//xxx.vcproj --list=xxx.lnt
	{
		const string strOutput = p[CMD_LIST];
	
		ofstream fLnt(strOutput.c_str());
		if(!fLnt.is_open())
		{
			cout << "����ļ�����ʧ��" << endl;
			return ERROR_FILE_CORRUPT;
		}
		fLnt.close();

		if(strInputFile.find(".vcproj") == string::npos)
		{
			cout << "ֻ֧������.vcproj�ļ�" << endl;
			return -1;
		}

		if(!VCProject_GetFileList(strInputFile, strOutput))
		{
			return -1;
		}
	}
	else if (p.is_set(CMD_LNT))	//xxx.vcproj --lnt=xxx.lnt --cfg=Debug|Win32
	{
		const string strConfigurationName = p[CMD_CFG];

		const string strLnt = p[CMD_LNT];
		ofstream fLnt(strLnt.c_str());
		if(!fLnt.is_open())
		{
			cout << "����ļ�����ʧ��" << endl;
			return ERROR_FILE_CORRUPT;
		}
		fLnt.close();

		if(strInputFile.find(".vcproj") != string::npos)
		{
			if(!LintVCProject(strInputFile, strLnt, strConfigurationName))
			{
				return -1;
			}
		}
		else if(strInputFile.find(".sln") != string::npos)
		{
			if(!LintSln(strInputFile, strLnt, strConfigurationName))
			{
				return -1;
			}
		}
		else
			return -1;
	}
	else
		return -1;

	system("echo success");

	return 0;
}

