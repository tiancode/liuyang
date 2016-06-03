#include "parseMMLThreadFunc.h"
#include "mess.h"
#include "tinyxml.h"
#include "mystring.h"
#include "stdafx.h"
#include "mmlToolDlg.h"

CString MMLorder;
int nowNum;
int totalNum;

void ParseMML(CString fileName)    //解析MML文件
{
	int RNCID[2000] = {0};// 存放RNCID
	int RNCID_n = 0;
	
	CStdioFile file;
	CString str;
	file.Open(fileName,CFile::modeRead,NULL);

	totalNum = g_orders.size();

	int curNum = 0;
	for(vector<string>::iterator TotalHeadIt = g_orders.begin(); TotalHeadIt != g_orders.end(); TotalHeadIt++)
	{
		MMLorder = TotalHeadIt->c_str();

		RNCID_n = 0;

		TiXmlDocument doc;	
		TiXmlDeclaration* head = new TiXmlDeclaration( "1.0", "", "" ); 
		doc.LinkEndChild( head );
		TiXmlElement * root = new TiXmlElement( "tianshuai" );
		doc.LinkEndChild( root );

		char fname[1024] = {0};

		file.Seek(0, CFile::begin);

		while(file.ReadString(str) == TRUE) 
		{
			if(*str.GetBuffer(0) == '/')
			{
				string stdsrc = str.GetBuffer(0);
				string stdtar = "System RNCID";
				int nIndex = KMP(stdsrc, stdtar, 0);
				if(nIndex == -1)  //没用找到匹配的数据
				{
					continue;
				}
				char *p = findColon(str.GetBuffer(0) + nIndex);
				unsigned int RNCID_num = getFirstNum(p);    //找到 //中  RNCID 的值
				if(RNCID_num == -1)
					AfxMessageBox("RNCID数据错误");
				else               //找到RNCID    289  290
				{
					CString str;
					str.Format("%d", RNCID_num);
					RNCID[RNCID_n] = RNCID_num;
					RNCID_n++;
					continue;
				}
			}
			char out[1024] = {0};
			findColonPreStr(str.GetBuffer(0), out);
			removeSpace(out);
			if(strcmp(out, TotalHeadIt->c_str()) == 0)
			{
				strcpy(fname, out);
				TiXmlElement *child = new TiXmlElement( out ); 
				root->LinkEndChild( child );
				TiXmlElement *Number = new TiXmlElement("RNCID"); 
				char buff[20];
				sprintf(buff, "%d", RNCID[RNCID_n - 1]);
				Number->LinkEndChild( new TiXmlText( buff ) );
				child->LinkEndChild( Number );
				char *p = str.GetBuffer(0);
				while(1)
				{
					char preOut[1024] = {0};
					char behindOut[1024] = {0};
					char *next = getEqualSine(p, preOut, behindOut);
					if((int)next == -1)
						break;
					p = next;
					TiXmlElement *msg = new TiXmlElement( preOut );
					findHex_to_dig10(behindOut);
					msg->LinkEndChild( new TiXmlText( behindOut ));
					child->LinkEndChild( msg );
				}
			}
		}

		CString szfile = g_XML_path + "\\" + fname + ".xml";
		doc.SaveFile(szfile);

		nowNum = ++curNum;
	}

	theApp.m_pMainWnd->GetMenu()->GetSubMenu(0)->EnableMenuItem(0,MF_ENABLED|MF_BYPOSITION);
	theApp.m_pMainWnd->GetMenu()->GetSubMenu(0)->EnableMenuItem(1,MF_ENABLED|MF_BYPOSITION);

	WorkPath = g_XML_path;
}

void ParseThreadFunc(LPVOID lpParameter)  //解析MML文件线程
{
	CString str;
	str.Format("%s", (char*)lpParameter);
	free((char*)lpParameter);
	ParseMML(str);	
}



/*************************************************************************
*																		 *
*																	     *
*																		 *
**************************************************************************/
void ParseMML_FOR_RNC(CString fileName)    //解析MML文件
{
	int RNCID[2000] = {0};// 存放RNCID
	int RNCID_n = 0;

	CStdioFile file;
	CString str;
	file.Open(fileName,CFile::modeRead,NULL);

	vector<string> needParse;
	needParse.push_back("ADDTCELL");
	needParse.push_back("ADDTCARRIER");
	needParse.push_back("ACTHSDPATCARRIER");

	for(vector<string>::iterator TotalHeadIt = needParse.begin(); TotalHeadIt != needParse.end(); TotalHeadIt++)
	{

		RNCID_n = 0;

		TiXmlDocument doc;	
		TiXmlDeclaration* head = new TiXmlDeclaration( "1.0", "", "" ); 
		doc.LinkEndChild( head );
		TiXmlElement * root = new TiXmlElement( "tianshuai" );
		doc.LinkEndChild( root );

		char fname[1024] = {0};

		file.Seek(0, CFile::begin);

		while(file.ReadString(str) == TRUE) 
		{
			if(*str.GetBuffer(0) == '/')
			{
				string stdsrc = str.GetBuffer(0);
				string stdtar = "System RNCID";
				int nIndex = KMP(stdsrc, stdtar, 0);
				if(nIndex == -1)  //没用找到匹配的数据
				{
					continue;
				}
				char *p = findColon(str.GetBuffer(0) + nIndex);
				unsigned int RNCID_num = getFirstNum(p);    //找到 //中  RNCID 的值
				if(RNCID_num == -1)
					AfxMessageBox("RNCID数据错误");
				else               //找到RNCID    289  290
				{
					CString str;
					str.Format("%d", RNCID_num);
					RNCID[RNCID_n] = RNCID_num;
					RNCID_n++;
					continue;
				}
			}
			char out[1024] = {0};
			findColonPreStr(str.GetBuffer(0), out);
			removeSpace(out);
			if(strcmp(out, TotalHeadIt->c_str()) == 0)
			{
				strcpy(fname, out);
				TiXmlElement *child = new TiXmlElement( out ); 
				root->LinkEndChild( child );
				TiXmlElement *Number = new TiXmlElement("RNCID"); 
				char buff[20];
				sprintf(buff, "%d", RNCID[RNCID_n - 1]);
				Number->LinkEndChild( new TiXmlText( buff ) );
				child->LinkEndChild( Number );
				char *p = str.GetBuffer(0);
				while(1)
				{
					char preOut[1024] = {0};
					char behindOut[1024] = {0};
					char *next = getEqualSine(p, preOut, behindOut);
					if((int)next == -1)
						break;
					p = next;
					TiXmlElement *msg = new TiXmlElement( preOut );
					findHex_to_dig10(behindOut);
					msg->LinkEndChild( new TiXmlText( behindOut ));
					child->LinkEndChild( msg );
				}
			}
		}

		CString szfile = g_XML_path + "\\" + fname + ".xml";
		doc.SaveFile(szfile);
	}
	WorkPath = g_XML_path;
}

void ParseThreadFunc_FOR_RNC(LPVOID lpParameter)  //解析MML文件线程
{
	CString str;
	str.Format("%s", (char*)lpParameter);
	free((char*)lpParameter);
	ParseMML_FOR_RNC(str);	
}