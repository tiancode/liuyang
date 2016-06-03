// mmlBaowenDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "mmlTool.h"
#include "mmlBaowenDlg.h"
#include "mess.h"

struct mypair
{
	string field;
	string data;
};
//小区状态信息
struct cell_info
{
	string date;
	string rnc;

	mypair cellid;
	mypair cellname;
	mypair operatorstate;
	mypair manstate;
	mypair powerbigdown;
	mypair powersmalldown;
	mypair MCJD;
	mypair state;

	cell_info()
	{
		date = '\0';
		rnc = '\0';

		cellid.field = "小区标识";
		cellid.data = '\0';
		cellname.field = "小区名称";
		cellname.data = '\0';
		operatorstate.field = "操作状态";
		operatorstate.data = '\0';
		manstate.field = "管理状态";
		manstate.data = '\0';
		powerbigdown.field = "NODEB的最大下行功率";
		powerbigdown.data = '\0';
		powersmalldown.field = "NODEB的最小下行功率";
		powersmalldown.data = '\0';
		MCJD.field = "小区MCJD功能状态";
		MCJD.data = '\0';
		state.field = "状态说明";
		state.data = '\0';
	}
};

//载频基本信息
struct carrier
{
	string date;
	string rnc;

	mypair cellid;
	mypair cellname;
	mypair carrierindex;
	mypair UARFCN;
	mypair opswitch;
	mypair state;

	carrier()
	{
		date = '\0';
		rnc = '\0';

		cellid.field = "小区标识";
		cellid.data = '\0';
		cellname.field = "小区名称";
		cellname.data = '\0';
		carrierindex.field = "载频索引";
		carrierindex.data = '\0';
		UARFCN.field = "载频UARFCN频率";
		UARFCN.data = '\0';
		opswitch.field = "载频功能开关";
		opswitch.data = '\0';
		state.field = "状态说明";
		state.data = '\0';
	}
};


//查询小区接入限制信息
struct limitin
{
	string date;
	string rnc;

	mypair cellid;
	mypair cellname;
	mypair yunyingshang;
	mypair externs;
	mypair noin0;
	mypair noin1;
	mypair noin2;
	mypair noin3;
	mypair noin4;
	mypair noin5;
	mypair noin6;
	mypair noin7;
	mypair noin8;
	mypair noin9;
	mypair noin10;
	mypair noin11;
	mypair noin12;
	mypair noin13;
	mypair noin14;
	mypair noin15;
	mypair isindeny;
	mypair csfield;
	mypair psfield;
	mypair calldeny;
	mypair cellparg;
	mypair cell1;
	mypair cell2;
	mypair freestate;
	mypair repickfree;
	mypair repickdeny;
	mypair concell;
	mypair consamecell;
	mypair repicktime;

	limitin()
	{
		date = '\0';
		rnc = '\0';
		cellid.field = "小区标识";
		cellid.data = '\0';
		cellname.field = "小区名称";
		cellname.data = '\0';
		yunyingshang.field = "运营商保留使用指示";
		yunyingshang.data = '\0';
		externs.field = "扩展保留使用指示";
		externs.data = '\0';
		noin0.field = "小区接入禁止指示";
		noin0.data = '\0';
		noin1.field = "小区接入禁止指示1";
		noin1.data = '\0';
		noin2.field = "小区接入禁止指示2";
		noin2.data = '\0';
		noin3.field = "小区接入禁止指示3";
		noin3.data = '\0';
		noin4.field = "小区接入禁止指示4";
		noin4.data = '\0';
		noin5.field = "小区接入禁止指示5";
		noin5.data = '\0';
		noin6.field = "小区接入禁止指示6";
		noin6.data = '\0';
		noin7.field = "小区接入禁止指示7";
		noin7.data = '\0';
		noin8.field = "小区接入禁止指示8";
		noin8.data = '\0';
		noin9.field = "小区接入禁止指示9";
		noin9.data = '\0';
		noin10.field = "小区接入禁止指示10";
		noin10.data = '\0';
		noin11.field = "小区接入禁止指示11";
		noin11.data = '\0';
		noin12.field = "小区接入禁止指示12";
		noin12.data = '\0';
		noin13.field = "小区接入禁止指示13";
		noin13.data = '\0';
		noin14.field = "小区接入禁止指示14";
		noin14.data = '\0';
		noin15.field = "小区接入禁止指示15";
		noin15.data = '\0';
		isindeny.field = "是否区分域填写接入禁止指示";
		isindeny.data = '\0';
		csfield.field = "小区CS域接入禁止指示";
		csfield.data = '\0';
		psfield.field = "小区PS域接入禁止指示";
		psfield.data = '\0';
		calldeny.field = "是否允许填写寻呼禁止信息指示";
		calldeny.data = '\0';
		cellparg.field = "小区寻呼响应禁止类型";
		cellparg.data = '\0';
		cell1.field = "小区位置更新/注册禁止类型";
		cell1.data = '\0';
		cell2.field = "小区位置更新/注册禁止指示";
		cell2.data = '\0';
		freestate.field = "空闲模式小区禁止指示";
		freestate.data = '\0';
		repickfree.field = "空闲模式同频小区重选指示";
		repickfree.data = '\0';
		repickdeny.field = "空闲模式小区重选禁止时间";
		repickdeny.data = '\0';
		concell.field = "连接模式小区禁止指示";
		concell.data = '\0';
		consamecell.field = "连接模式同频小区重选指示";
		consamecell.data = '\0';
		repicktime.field = "连接模式小区重选禁止时间";
		repicktime.data = '\0';
	}
};

//HSDPA信息
struct Hsdpa
{
	string date;
	string rnc;

	mypair cellid;
	mypair cellname;
	mypair carrierindex;
	mypair UARFCN;
	mypair opestate;
	
	Hsdpa()
	{
		date = '\0';
		rnc = '\0';

		cellid.field = "小区标识";
		cellid.data = '\0';
		cellname.field = "小区名称";
		cellname.data = '\0';
		carrierindex.field = "载频索引";
		carrierindex.data = "\0";
		UARFCN.field = "载频UARFCN频率";
		UARFCN.data = "\0";
		opestate.field = "操作状态";
		opestate.data = "\0";
	}
};


//listbox 列
static int Col = 0;
// CmmlBaowenDlg 对话框

IMPLEMENT_DYNAMIC(CmmlBaowenDlg, CDialog)

CmmlBaowenDlg::CmmlBaowenDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CmmlBaowenDlg::IDD, pParent)
{

}

CmmlBaowenDlg::~CmmlBaowenDlg()
{
}

void CmmlBaowenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_FILE, m_fileList);
}


BEGIN_MESSAGE_MAP(CmmlBaowenDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SELECT_FILE, &CmmlBaowenDlg::OnBnClickedButtonSelectFile)
	ON_BN_CLICKED(IDC_BUTTON_RUN, &CmmlBaowenDlg::OnBnClickedButtonRun)
END_MESSAGE_MAP()


// CmmlBaowenDlg 消息处理程序

BOOL CmmlBaowenDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	Col = 0;
	return TRUE;
}

BOOL CmmlBaowenDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_RETURN:
			//MessageBox(_T("回车键按下"));
			return TRUE;
		case VK_ESCAPE:
			//MessageBox(_T("ESC键按下"));
			return TRUE;
		default:
			break;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

//选择数据
void CmmlBaowenDlg::OnBnClickedButtonSelectFile()
{
	// TODO: 在此添加控件通知处理程序代码
	//打开文件对话框
	CFileDialog fileDlg( TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT
		| OFN_ALLOWMULTISELECT, "TXT|*.txt|");
	DWORD MAXFILE = 40000;
	fileDlg.m_ofn.nMaxFile = MAXFILE;
	char* pc = new char[MAXFILE];
	fileDlg.m_ofn.lpstrFile = pc;
	fileDlg.m_ofn.lpstrFile[0] = NULL;
	int iReturn = fileDlg.DoModal();
	if(iReturn ==  IDOK)
	{
		POSITION pos = fileDlg.GetStartPosition();

		while (pos != NULL)
		{
			CString fileName = fileDlg.GetNextPathName(pos);
			if(!fileExternName(fileName.GetBuffer(0), "txt"))
			{
				AfxMessageBox("文件不是TXT格式");
				return;
			}
			m_fileList.InsertString(Col, fileName);
			Col++;
		}
	}
	else
	{
		return;
	}
}
//生成excel表格
void CmmlBaowenDlg::OnBnClickedButtonRun()
{
	// TODO: 在此添加控件通知处理程序代码
	CString FilePathName;
	CFileDialog dlg(FALSE,NULL,"default.xls",NULL,"Excel 文档(*.xls) | 全部文件(*.*)| *.*");///TRUE为OPEN对话框，FALSE为SAVE AS对话框
	//dlg.m_ofn.lpstrInitialDir=_T("d:\\"); //这里就设置了对话框的默认目录d盘
	INT_PTR nRes = dlg.DoModal();
	if(nRes == IDOK)
		FilePathName=dlg.GetPathName();
	else
		return;
	if(FilePathName.IsEmpty())
	{
		AfxMessageBox("请输入保存的文件");
		return;
	}
	FilePathName = FilePathName;
	BeginWaitCursor();
	int res = ExportAllData(FilePathName);
	if(res == FALSE)
	{
		return;
	}
	EndWaitCursor();
	if(res == 1)
	{
		AfxMessageBox("文件保存成功!");
	}
	else
		AfxMessageBox("文件保存失败!");

	m_fileList.ResetContent();
	Col = 0;
}
char* getFileName(char *file)
{
	FILE *filefd = fopen(file, "r");
	char buff[128];
	char *dst = (char*)malloc(128);
	fgets(buff, 128, filefd);
	char *p = buff;
	while(*p != NULL)
	{
		p++;
	}
	p--;
	*p = '\0';
	strcpy(dst, buff);
	
	fclose(filefd);
	return dst;
}

char* getFileName1(char *file)
{
	FILE *filefd = fopen(file, "r");
	char buff[128];
	char *dst = (char*)malloc(128);
	fgets(buff, 128, filefd);
	char *p = buff;
	while(*p != ':')
	{
		p++;
	}
	*p = '\0';
	strcpy(dst, buff);

	fclose(filefd);
	return dst;
}
void getDateandRnc(char *buff_line, cell_info *cell, FILE *file)
{
	fgets(buff_line, 1024*4, file);
	Trim(buff_line);
	trimmidspace(buff_line);
	cell->rnc = buff_line;
	
	fgets(buff_line, 1024*4, file);
	Trim(buff_line);
	trimmidspace(buff_line);
	char *p = buff_line;
	while(*p)
	{
		if(isdigit(*p) && *p++ == '2' && *p++ == '0' && *p++ == '1')
		{
			break;
		}
		p++;
	}
	p = p - 3;
	printf("%s\n", p);
	cell->date = p;
}
void getDateandRnc1(char *buff_line, carrier *cell, FILE *file)
{
	fgets(buff_line, 1024*4, file);
	Trim(buff_line);
	trimmidspace(buff_line);
	cell->rnc = buff_line;

	fgets(buff_line, 1024*4, file);
	Trim(buff_line);
	trimmidspace(buff_line);
	char *p = buff_line;
	while(*p)
	{
		if(isdigit(*p) && *p++ == '2' && *p++ == '0' && *p++ == '1')
		{
			break;
		}
		p++;
	}
	p = p - 3;
	printf("%s\n", p);
	cell->date = p;
}
void getDateandRnc2(char *buff_line, limitin *cell, FILE *file)
{
	fgets(buff_line, 1024*4, file);
	Trim(buff_line);
	trimmidspace(buff_line);
	cell->rnc = buff_line;

	fgets(buff_line, 1024*4, file);
	Trim(buff_line);
	trimmidspace(buff_line);
	char *p = buff_line;
	while(*p)
	{
		if(isdigit(*p) && *p++ == '2' && *p++ == '0' && *p++ == '1')
		{
			break;
		}
		p++;
	}
	p = p - 3;
	printf("%s\n", p);
	cell->date = p;
}
void getDateandRnc3(char *buff_line, Hsdpa *cell, FILE *file)
{
	fgets(buff_line, 1024*4, file);
	Trim(buff_line);
	trimmidspace(buff_line);
	cell->rnc = buff_line;

	fgets(buff_line, 1024*4, file);
	Trim(buff_line);
	trimmidspace(buff_line);
	char *p = buff_line;
	while(*p)
	{
		if(isdigit(*p) && *p++ == '2' && *p++ == '0' && *p++ == '1')
		{
			break;
		}
		p++;
	}
	p = p - 3;
	printf("%s\n", p);
	cell->date = p;
}
BOOL CmmlBaowenDlg::ExportAllData(CString FileName)
{
	Book *book = xlCreateBook();
	if(!book)
		return FALSE;

	int fileCount = m_fileList.GetCount();
	/*printf("%d\n", fileCount);*/
	if(fileCount == 0)
	{
		AfxMessageBox("请添加文件");
		return FALSE;
	}

	CString str;
	int n;
	char buff_line[1024 * 4];

	for (int i = 0; i < fileCount; i++)
	{
		n = m_fileList.GetTextLen(i);
		m_fileList.GetText( i, str.GetBuffer(n) );
		//printf("%s\n", str.GetBuffer(0));

		CString strr;
		strr.Format("%s%d", "sheet", i+1);
		Sheet *sheet = book->addSheet(strr.GetBuffer(0));
		if(!sheet)
			return FALSE;

		//小区状态信息
		if( strcmp(getFileName(str.GetBuffer(0)), "DSP TCELL:DSPT=BYCELLID;") == 0 )
		{
			cell_info cell;
			sheet->writeStr(0, 0, "DATE");
			sheet->writeStr(0, 1, "RNCID");
			sheet->writeStr(0, 2, cell.cellid.field.c_str());
			sheet->writeStr(0, 3, cell.cellname.field.c_str());
			sheet->writeStr(0, 4, cell.operatorstate.field.c_str());
			sheet->writeStr(0, 5, cell.manstate.field.c_str());
			sheet->writeStr(0, 6, cell.powerbigdown.field.c_str());
			sheet->writeStr(0, 7, cell.powersmalldown.field.c_str());
			sheet->writeStr(0, 8, cell.MCJD.field.c_str());
			sheet->writeStr(0, 9, cell.state.field.c_str());
			int row = 1;
			FILE *file = fopen(str.GetBuffer(0), "r");
			while( fgets(buff_line, 1024*4, file) != NULL )
			{
				//一行一行遍历文件
				Trim(buff_line);
				trimmidspace(buff_line);// 去掉空格

				if(strcmp(buff_line, "DSPTCELL:DSPT=BYCELLID;") == 0) //得到日期和RNC
				{
					getDateandRnc(buff_line, &cell, file);
				}

				int index = KMP(buff_line, "=", 0);
				if(index == 8 || index == 19 || index == 16)
				{
					*(buff_line + index) = '\0';
					if(strcmp(buff_line, cell.cellid.field.c_str()) == 0)
					{
						cell.cellid.data = buff_line + index + 1;
					}
					else if( strcmp(buff_line, cell.cellname.field.c_str()) == 0 )
					{
						cell.cellname.data = buff_line + index + 1;
					}
					else if( strcmp(buff_line, cell.operatorstate.field.c_str()) == 0)
					{
						cell.operatorstate.data = buff_line + index + 1;
					}
					else if(strcmp(buff_line, cell.manstate.field.c_str()) == 0)
					{
						cell.manstate.data = buff_line + index + 1;
					}
					else if( strcmp(buff_line, cell.powerbigdown.field.c_str()) == 0)
					{
						cell.powerbigdown.data = buff_line + index + 1;
					}
					else if( strcmp(buff_line, cell.powersmalldown.field.c_str()) == 0)
					{
						cell.powersmalldown.data = buff_line + index + 1;
					}
					else if( strcmp(buff_line, cell.MCJD.field.c_str()) == 0)
					{
						cell.MCJD.data = buff_line + index + 1;
					}
					else if( strcmp(buff_line, cell.state.field.c_str()) == 0)
					{
						cell.state.data = buff_line + index + 1;

						sheet->writeStr(row, 0, cell.date.c_str());
						sheet->writeStr(row, 1, cell.rnc.c_str());
						sheet->writeNum(row, 2, atoi(cell.cellid.data.c_str()));
						sheet->writeStr(row, 3, cell.cellname.data.c_str());
						sheet->writeStr(row, 4, cell.operatorstate.data.c_str());
						sheet->writeStr(row, 5, cell.manstate.data.c_str());
						int isNum = isString((char*)cell.powerbigdown.data.c_str());
						if(isNum)
						{
							sheet->writeNum(row, 6, atoi(cell.powerbigdown.data.c_str()));
						}
						else
						{
							sheet->writeStr(row, 6, _T(cell.powerbigdown.data.c_str()));
						}
						isNum = isString((char*)cell.powersmalldown.data.c_str());
						if(isNum)
						{
							sheet->writeNum(row, 7, atoi(cell.powersmalldown.data.c_str()));
						}
						else
						{
							sheet->writeStr(row, 7, _T(cell.powersmalldown.data.c_str()));
						}
						sheet->writeStr(row, 8, cell.MCJD.data.c_str());
						sheet->writeStr(row, 9, cell.state.data.c_str());
						row++;
					}
				}
			}
			fclose(file);
		}

		//载频基本信息
		else if(  strcmp(getFileName(str.GetBuffer(0)), "DSP TCARRIER:;") == 0 )
		{
			carrier cell;
			sheet->writeStr(0, 0, "DATE");
			sheet->writeStr(0, 1, "RNCID");
			sheet->writeStr(0, 2, cell.cellid.field.c_str());
			sheet->writeStr(0, 3, cell.cellname.field.c_str());
			sheet->writeStr(0, 4, cell.carrierindex.field.c_str());
			sheet->writeStr(0, 5, cell.UARFCN.field.c_str());
			sheet->writeStr(0, 6, cell.opswitch.field.c_str());
			sheet->writeStr(0, 7, cell.state.field.c_str());
			int row = 1;
			FILE *file = fopen(str.GetBuffer(0), "r");
			while( fgets(buff_line, 1024*4, file) != NULL )
			{
				//一行一行遍历文件
				Trim(buff_line);
				trimmidspace(buff_line);

				if(strcmp(buff_line, "DSPTCARRIER:;") == 0)
				{
					getDateandRnc1(buff_line, &cell, file);
				}

				int index = KMP(buff_line, "=", 0);
				if(index == 8 || index == 14 || index == 12)
				{
					*(buff_line + index) = '\0';
					if(strcmp(buff_line, cell.cellid.field.c_str()) == 0)
					{
						cell.cellid.data = buff_line + index + 1;
					}
					else if( strcmp(buff_line, cell.cellname.field.c_str()) == 0 )
					{
						cell.cellname.data = buff_line + index + 1;
					}
					else if(strcmp(buff_line, cell.carrierindex.field.c_str()) == 0)
					{
						cell.carrierindex.data = buff_line + index + 1;
					}
					else if( strcmp(buff_line, cell.UARFCN.field.c_str()) == 0 )
					{
						cell.UARFCN.data = buff_line + index + 1;
					}
					else if(  strcmp(buff_line, cell.opswitch.field.c_str()) == 0 )
					{
						cell.opswitch.data = buff_line + index + 1;
					}
					else if( strcmp(buff_line, cell.state.field.c_str()) == 0 )
					{
						cell.state.data = buff_line + index + 1;
						
						sheet->writeStr(row, 0, cell.date.c_str());
						sheet->writeStr(row, 1, cell.rnc.c_str());
						sheet->writeNum(row, 2, atoi(cell.cellid.data.c_str()));
						sheet->writeStr(row, 3, cell.cellname.data.c_str());
						sheet->writeStr(row, 4, cell.carrierindex.data.c_str());
						sheet->writeNum(row, 5, atoi(cell.UARFCN.data.c_str()) );
						sheet->writeStr(row, 6, cell.opswitch.data.c_str());
						sheet->writeStr(row, 7, cell.state.data.c_str());
						row++;
					}
				}
			}
			fclose(file);
		}

		//查询小区接入限制信息
		else if(  strcmp(getFileName(str.GetBuffer(0)), "LST TCELLACCESSSTRICT:;") == 0 )
		{
			limitin cell;
			sheet->writeStr(0, 0, "DATE");
			sheet->writeStr(0, 1, "RNCID");
			sheet->writeStr(0, 2, cell.cellid.field.c_str());
			sheet->writeStr(0, 3, cell.cellname.field.c_str());
			sheet->writeStr(0, 4, cell.yunyingshang.field.c_str());
			sheet->writeStr(0, 5, cell.externs.field.c_str());
			sheet->writeStr(0, 6, cell.noin0.field.c_str());
			/*sheet->writeStr(0, 7, cell.noin1.field.c_str());
			sheet->writeStr(0, 8, cell.noin2.field.c_str());
			sheet->writeStr(0, 9, cell.noin3.field.c_str());
			sheet->writeStr(0, 10, cell.noin4.field.c_str());
			sheet->writeStr(0, 11, cell.noin5.field.c_str());
			sheet->writeStr(0, 12, cell.noin6.field.c_str());
			sheet->writeStr(0, 13, cell.noin7.field.c_str());
			sheet->writeStr(0, 14, cell.noin8.field.c_str());
			sheet->writeStr(0, 15, cell.noin9.field.c_str());
			sheet->writeStr(0, 16, cell.noin10.field.c_str());
			sheet->writeStr(0, 17, cell.noin11.field.c_str());
			sheet->writeStr(0, 18, cell.noin12.field.c_str());
			sheet->writeStr(0, 19, cell.noin13.field.c_str());
			sheet->writeStr(0, 20, cell.noin14.field.c_str());
			sheet->writeStr(0, 21, cell.noin15.field.c_str());*/
			sheet->writeStr(0, 7, cell.isindeny.field.c_str());
			sheet->writeStr(0, 8, cell.csfield.field.c_str());
			sheet->writeStr(0, 9, cell.psfield.field.c_str());
			sheet->writeStr(0, 10, cell.calldeny.field.c_str());
			sheet->writeStr(0, 11, cell.cellparg.field.c_str());
			sheet->writeStr(0, 12, cell.cell1.field.c_str());
			sheet->writeStr(0, 13, cell.cell2.field.c_str());
			sheet->writeStr(0, 14, cell.freestate.field.c_str());
			sheet->writeStr(0, 15, cell.repickfree.field.c_str());
			sheet->writeStr(0, 16, cell.repickdeny.field.c_str());
			sheet->writeStr(0, 17, cell.concell.field.c_str());
			sheet->writeStr(0, 18, cell.consamecell.field.c_str());
			sheet->writeStr(0, 19, cell.repicktime.field.c_str());
			int row = 1;
			FILE *file = fopen(str.GetBuffer(0), "r");
			while( fgets(buff_line, 1024*4, file) != NULL )
			{
				//一行一行遍历文件
				Trim(buff_line);
				trimmidspace(buff_line);

				if(strcmp(buff_line, "LSTTCELLACCESSSTRICT:;") == 0)
				{
					getDateandRnc2(buff_line, &cell, file);
				}

				int index = KMP(buff_line, "=", 0);
				if(index == 8 || index == 18 || index == 16 || index ==0 || index == 26 || index == 20 || index == 28 || index == 25 || index == 24)
				{
					*(buff_line + index) = '\0';
					if(strcmp(buff_line, cell.cellid.field.c_str()) == 0)
					{
						cell.cellid.data = buff_line + index + 1;
					}
					else if( strcmp(buff_line, cell.cellname.field.c_str()) == 0 )
					{
						cell.cellname.data = buff_line + index + 1;
					}
					else if( strcmp(buff_line, cell.yunyingshang.field.c_str()) == 0 )
					{
						cell.yunyingshang.data = buff_line + index + 1;
					}
					else if( strcmp(buff_line, cell.externs.field.c_str()) == 0 )
					{
						cell.externs.data = buff_line + index + 1;
					}
					else if(strcmp(buff_line, "小区接入禁止指示") == 0 )
					{
						cell.noin0.data = buff_line + index + 1;
					}
					else if( strcmp(buff_line, cell.isindeny.field.c_str()) == 0 )
					{
						cell.isindeny.data = buff_line + index + 1;
					}
					else if( strcmp(buff_line, cell.csfield.field.c_str()) == 0 )
					{
						cell.csfield.data = buff_line + index + 1;
					}
					else if( strcmp(buff_line, cell.psfield.field.c_str()) == 0)
					{
						cell.psfield.data = buff_line + index + 1;
					}
					else if(strcmp(buff_line, cell.calldeny.field.c_str()) == 0)
					{
						cell.calldeny.data = buff_line + index + 1;
					}
					else if(strcmp(buff_line, cell.cellparg.field.c_str()) == 0)
					{
						cell.cellparg.data = buff_line + index + 1;
					}
					else if(strcmp(buff_line, cell.cell1.field.c_str()) == 0)
					{
						cell.cell1.data = buff_line + index + 1;
					}
					else if(strcmp(buff_line, cell.cell2.field.c_str()) == 0)
					{
						cell.cell2.data = buff_line + index + 1;
					}
					else if(strcmp(buff_line, cell.freestate.field.c_str()) == 0)
					{
						cell.freestate.data = buff_line + index + 1;
					}
					else if(strcmp(buff_line, cell.repickfree.field.c_str()) == 0)
					{
						cell.repickfree.data = buff_line + index + 1;
					}
					else if(strcmp(buff_line, cell.repickdeny.field.c_str()) == 0)
					{
						cell.repickdeny.data = buff_line + index + 1;
					}
					else if(strcmp(buff_line, cell.concell.field.c_str()) == 0)
					{
						cell.concell.data = buff_line + index + 1;
					}
					else if(strcmp(buff_line, cell.consamecell.field.c_str()) == 0)
					{
						cell.consamecell.data = buff_line + index + 1;
					}
					else if(strcmp(buff_line, cell.repicktime.field.c_str()) == 0)
					{
						cell.repicktime.data = buff_line + index + 1;

						sheet->writeStr(row, 0, cell.date.c_str());
						sheet->writeStr(row, 1, cell.rnc.c_str());
						sheet->writeNum(row, 2, atoi(cell.cellid.data.c_str()));
						sheet->writeStr(row, 3, cell.cellname.data.c_str());
						sheet->writeStr(row, 4, cell.yunyingshang.data.c_str());
						sheet->writeStr(row, 5, cell.externs.data.c_str());
						sheet->writeStr(row, 6, cell.noin0.data.c_str());
						//sheet->writeStr(row, 7, cell.noin1.data.c_str());
						//sheet->writeStr(row, 8, cell.noin2.data.c_str());
						//sheet->writeStr(row, 9, cell.noin3.data.c_str());
						//sheet->writeStr(row, 10, cell.noin4.data.c_str());
						//sheet->writeStr(row, 11, cell.noin5.data.c_str());
						//sheet->writeStr(row, 12, cell.noin6.data.c_str());
						//sheet->writeStr(row, 13, cell.noin7.data.c_str());
						//sheet->writeStr(row, 14, cell.noin8.data.c_str());
						//sheet->writeStr(row, 15, cell.noin9.data.c_str());
						//sheet->writeStr(row, 16, cell.noin10.data.c_str());
						//sheet->writeStr(row, 17, cell.noin11.data.c_str());
						//sheet->writeStr(row, 18, cell.noin12.data.c_str());
						//sheet->writeStr(row, 19, cell.noin13.data.c_str());
						//sheet->writeStr(row, 20, cell.noin14.data.c_str());
						//sheet->writeStr(row, 21, cell.noin15.data.c_str());
						sheet->writeStr(row, 7, cell.isindeny.data.c_str());
						sheet->writeStr(row, 8, cell.csfield.data.c_str());
						sheet->writeStr(row, 9, cell.psfield.data.c_str());
						sheet->writeStr(row, 10, cell.calldeny.data.c_str());
						sheet->writeStr(row, 11, cell.cellparg.data.c_str());
						sheet->writeStr(row, 12, cell.cell1.data.c_str());
						sheet->writeStr(row, 13, cell.cell2.data.c_str());
						sheet->writeStr(row, 14, cell.freestate.data.c_str());
						sheet->writeStr(row, 15, cell.repickfree.data.c_str());
						sheet->writeStr(row, 16, cell.repickdeny.data.c_str());
						sheet->writeStr(row, 17, cell.concell.data.c_str());
						sheet->writeStr(row, 18, cell.consamecell.data.c_str());
						sheet->writeStr(row, 19, cell.repicktime.data.c_str());

						row++;
					}
				}
			}
			fclose(file);
		}

		//HSDPA信息
		else if( strcmp(getFileName1(str.GetBuffer(0)), "DSP THSDPA") == 0 )
		{
			Hsdpa cell;
			sheet->writeStr(0, 0, "DATE");
			sheet->writeStr(0, 1, "RNCID");
			sheet->writeStr(0, 2, cell.cellid.field.c_str());
			sheet->writeStr(0, 3, cell.cellname.field.c_str());
			sheet->writeStr(0, 4, cell.carrierindex.field.c_str());
			sheet->writeStr(0, 5, cell.UARFCN.field.c_str());
			sheet->writeStr(0, 6, cell.opestate.field.c_str());
			int row = 1;
			FILE *file = fopen(str.GetBuffer(0), "r");
			while( fgets(buff_line, 1024*4, file) != NULL )
			{
				//一行一行遍历文件
				Trim(buff_line);
				trimmidspace(buff_line);

				if(*buff_line == 'D')
				{
					getDateandRnc3(buff_line, &cell, file);
				}

				int index = KMP(buff_line, "=", 0);
				if(index == 8 || index == 14 )
				{
					*(buff_line + index) = '\0';
					if(strcmp(buff_line, cell.cellid.field.c_str()) == 0)
					{
						cell.cellid.data = buff_line + index + 1;
					}
					else if( strcmp(buff_line, cell.cellname.field.c_str()) == 0 )
					{
						cell.cellname.data = buff_line + index + 1;
					}
					else if(strcmp(buff_line, cell.carrierindex.field.c_str()) == 0)
					{
						cell.carrierindex.data = buff_line + index + 1;
					}
					else if( strcmp(buff_line, cell.UARFCN.field.c_str()) == 0 )
					{
						cell.UARFCN.data = buff_line + index + 1;
					}
					else if(  strcmp(buff_line, cell.opestate.field.c_str()) == 0 )
					{
						cell.opestate.data = buff_line + index + 1;

						sheet->writeStr(row, 0, cell.date.c_str());
						sheet->writeStr(row, 1, cell.rnc.c_str());
						sheet->writeNum(row, 2, atoi(cell.cellid.data.c_str()));
						sheet->writeStr(row, 3, cell.cellname.data.c_str());
						sheet->writeStr(row, 4, cell.carrierindex.data.c_str());
						sheet->writeNum(row, 5, atoi(cell.UARFCN.data.c_str()) );
						sheet->writeStr(row, 6, cell.opestate.data.c_str());
						row++;
					}
				}
			}
			fclose(file);
		}

	}
	
	if(book->save(_T(FileName.GetBuffer(0)) )) 
	{
		return 1;
	}
	else
	{
		return 0;
	}

	book->release();
	return TRUE;
}