#ifndef MESS_H
#define MESS_H

//注册表信息
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
//存放要解析的MML命令
extern vector<string> g_orders;

//解析完的xml文件路径
extern CString g_XML_path;


// 唯一的一个 CmmlToolApp 对象
extern CmmlToolApp theApp;


//正在解析的信息
extern CString MMLorder;
extern int nowNum;
extern int totalNum;

//工作目录
extern CString WorkPath;


//检查工作目录为空
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
							AfxMessageBox("目录选择错误, 请重新选择！");  \
							WorkPath = "";                                   \
							return;                                          \
						}                                                    \





#endif