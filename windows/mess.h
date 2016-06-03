#ifndef MESS_H
#define MESS_H

//ע�����Ϣ
#define REGED "registerEd"
#define STARTTIME "startDate"
#define ENDDATE "endDate"

#include "stdafx.h"
#include "mmlTool.h"
#include "unit.h"
#include "mystring.h"
#include "file.h"
#include "md5.h"
#include <io.h>

#include "BtnST.h"
#include "libxl.h"
using namespace libxl;

#include "CApplication.h"
#include "CFont0.h"
#include "CWorkbook.h"
#include "CWorkbooks.h"
#include "CWorksheet.h"
#include "CWorksheets.h"
#include "CRange.h"

#include <iostream>
#include <algorithm> 
#include <vector>
#include <string>
using namespace std;
//���Ҫ������MML����
extern vector<string> g_orders;

//�������xml�ļ�·��
extern CString g_XML_path;


// Ψһ��һ�� CmmlToolApp ����
extern CmmlToolApp theApp;


//���ڽ�������Ϣ
extern CString MMLorder;
extern int nowNum;
extern int totalNum;

//����Ŀ¼
extern CString WorkPath;


//��鹤��Ŀ¼Ϊ��
#define CHECK_WORK_PATH CString str;                          \
                        str.Format("%s", WorkPath);           \
                        if(str.IsEmpty()) {                                     \
							int res = selectPathDlg(WorkPath, &m_hWnd); \
							if(res == 0)                      \
							return;                           \
						}                                     \
						CString file;                         \
						file = WorkPath + "\\" + "TotalMML.txt";  \
						if( (_access( file, 0 )) != -1 )          \
						{                                         \
							printf( "File TotalMML.txt exists " ); \
						}                                          \
						else                                       \
						{                                          \
							AfxMessageBox("Ŀ¼ѡ�����, ������ѡ��");  \
							WorkPath = "";                                   \
							return;                                          \
						}                                                    \





#endif