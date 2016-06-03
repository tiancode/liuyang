// mmlToolDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "mmlTool.h"
#include "mmlToolDlg.h"
#include "mmlBaowenDlg.h"
#include "registerDlg.h"
#include "mmlAnyExportDlg.h"
#include "file.h"
#include "parseMMLThreadFunc.h"
#include <io.h>
#include "test.h"

#include <string>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CString m_info;
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
, m_info(_T(""))
{
	m_info = "2014.1.18\r\n本工具可通过修改安装目录下的config文件\r\n实现导出任意MML命令";
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_info);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()







// CmmlToolDlg 对话框

//全局变量
//存放要解析的MML命令
vector<string> g_orders;

//解析完的xml文件路径
CString g_XML_path;

//工作目录 MML xml 目录
CString WorkPath;

// 解析MML线程句柄
HANDLE parseThread;

static UINT BASED_CODE indicators [] =  
{  
	BAR_ID_OPERATOR,  
	BAR_ID_EMAIL,  
	BAR_ID_TIME  
};  

CmmlToolDlg::CmmlToolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CmmlToolDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmmlToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_DataList);
}

BEGIN_MESSAGE_MAP(CmmlToolDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_CLOSE()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_COMMAND(ID_MENU_QUIT, &CmmlToolDlg::OnMenuQuit)
	ON_COMMAND(ID_MENU_IMPORT, &CmmlToolDlg::OnMenuImport)
	ON_COMMAND(ID_MENU_WORK_PATH, &CmmlToolDlg::OnMenuWorkPath)
	ON_COMMAND(ID_N_CELL_INFO, &CmmlToolDlg::OnNCellInfo)
	ON_WM_SIZE()
	ON_COMMAND(ID_STATIC_CELLBAR, &CmmlToolDlg::OnStaticCellbar)
	ON_COMMAND(ID_EXPORT_NINE_TABLE, &CmmlToolDlg::OnExportNineTable)
	ON_COMMAND(ID_EXPORT_CELLBAR_TABLE, &CmmlToolDlg::OnExportCellbarTable)
	ON_COMMAND(ID_MML_BAOWEN_TABLE, &CmmlToolDlg::OnMmlBaowenTable)
	ON_COMMAND(ID_ISCP, &CmmlToolDlg::OnIscp)
	ON_COMMAND(ID_TOP_KPI, &CmmlToolDlg::OnTopKpi)
	ON_COMMAND(ID_ABOUT, &CmmlToolDlg::OnAbout)
	ON_COMMAND(ID_SELECT_ORDER_TABLE, &CmmlToolDlg::OnSelectOrderTable)
	ON_COMMAND(ID_RNC_MML_FILE, &CmmlToolDlg::OnRncMmlFile)
	ON_COMMAND(ID_RNC_OUT, &CmmlToolDlg::OnRncOut)
END_MESSAGE_MAP()


// CmmlToolDlg 消息处理程序

BOOL CmmlToolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}


	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_MAXIMIZE);

	// TODO: 在此添加额外的初始化代码
	m_wndStatusBar.Create(AfxGetMainWnd());  
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));
	SetTimer(1,100,NULL); 
	//注册窗口
	CregisterDlg dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	
	TEST();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CmmlToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CmmlToolDlg::OnPaint()
{
//	CRect ct;  
//	GetClientRect(&ct);  
//	CString str;  
//	str = _T("PROCESS : Done");  
//	m_wndStatusBar.SetPaneInfo(0, BAR_ID_OPERATOR, SBPS_NORMAL, (int) ct.Width() * 0.45);  
////	m_wndStatusBar.SetPaneText(0, str);  
//	str = _T("EMAIL：tianshuai@wellservicenet.com, QQ:811627469");  
//	m_wndStatusBar.SetPaneInfo(1, BAR_ID_EMAIL, SBPS_NORMAL, (int) ct.Width() * 0.40);  
//	m_wndStatusBar.SetPaneText(1, str);  
//	str = _T("时间：");  
//	m_wndStatusBar.SetPaneInfo(2, BAR_ID_TIME, SBPS_NORMAL, (int) ct.Width() * 0.25);  
//	m_wndStatusBar.SetPaneText(2, str);  
//	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0); 

	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CmmlToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BOOL CmmlToolDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
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

void CmmlToolDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(MessageBox("是否要退出？","提示",MB_ICONQUESTION | MB_YESNO) != IDYES)
		return;
	KillTimer(1);
	CDialog::OnClose();
}

int CmmlToolDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	
	//读命令文件
	readConfig(g_orders);

	return 0;
}

void CmmlToolDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect ct;  
	GetClientRect(&ct);  
	CString str;  
	str.Format("PROCESS : %s   %d/%d", MMLorder.GetBuffer(0), nowNum, totalNum);
	m_wndStatusBar.SetPaneInfo(0, BAR_ID_OPERATOR, SBPS_NORMAL, (int) ct.Width() * 0.45);  
	m_wndStatusBar.SetPaneText(0, str);  
	if(nowNum == totalNum)
	{
		str.Format("PROCESS : %s", "完成");
		m_wndStatusBar.SetPaneInfo(0, BAR_ID_OPERATOR, SBPS_NORMAL, (int) ct.Width() * 0.45);  
		m_wndStatusBar.SetPaneText(0, str);  
	}
	str = _T("EMAIL：tianshuai@wellservicenet.com, QQ:811627469");  
	m_wndStatusBar.SetPaneInfo(1, BAR_ID_EMAIL, SBPS_NORMAL, (int) ct.Width() * 0.40);  
	m_wndStatusBar.SetPaneText(1, str); 
	str = _T("时间：");  
	CTime time;  
	time=CTime::GetCurrentTime();  
	CString s_time=time.Format("%H:%M:%S");  
	m_wndStatusBar.SetPaneInfo(2, BAR_ID_TIME, SBPS_NORMAL, (int) ct.Width() * 0.25);  
	m_wndStatusBar.SetPaneText(2, str + s_time);  
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0); 


	CDialog::OnTimer(nIDEvent);
}

//menu 退出
void CmmlToolDlg::OnMenuQuit()
{
	// TODO: 在此添加命令处理程序代码
	// TODO: 在此添加命令处理程序代码
	if(MessageBox("是否要退出？","提示",MB_ICONQUESTION | MB_YESNO) != IDYES)
		return;
	else
	{
		KillTimer(1);
		exit(0);
	}
}

//menu 导入MML文件（txt）
void CmmlToolDlg::OnMenuImport()
{
	WorkPath = "";
	// TODO: 在此添加命令处理程序代码
	CFileDialog Dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT
		| OFN_ALLOWMULTISELECT, "TXT|*.txt|");  ///TRUE为OPEN对话框，FALSE为SAVE AS对话框
	DWORD MAXFILE = 40000;
	Dlg.m_ofn.nMaxFile = MAXFILE;
	char* pc = new char[MAXFILE];
	Dlg.m_ofn.lpstrFile = pc;
	Dlg.m_ofn.lpstrFile[0] = NULL;
	int iReturn = Dlg.DoModal();
	if(iReturn ==  IDOK)
	{
		POSITION pos = Dlg.GetStartPosition();
		g_XML_path = Dlg.GetFolderPath();
		g_XML_path += "\\XMLCACHE";
		if ( !::CreateDirectory( g_XML_path, NULL ) )
		{
			DeleteDirectory(g_XML_path.GetBuffer(0));
			Sleep(500);
			::CreateDirectory( g_XML_path, NULL );
		}
		HANDLE FileOnehandle = CreateFile(g_XML_path + "\\" + "TotalMML.txt", GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_NEW, 0, 0);
		while (pos != NULL)
		{
			CString fileName = Dlg.GetNextPathName(pos);		
			
			HANDLE handle = CreateFile(fileName, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
			int fileSize = GetFileSize(handle, NULL);
			char *memFile = (char*)malloc(fileSize);
			memset(memFile,0,sizeof(fileSize));
			unsigned long size;
			ReadFile(handle, memFile, fileSize, &size, NULL); 
			WriteFile(FileOnehandle, memFile, fileSize, &size, NULL);
			CloseHandle(handle);
			free(memFile);
		}
		CloseHandle(FileOnehandle);
	}
	else
	{
		return;
	}
	delete []pc;



	CString strFile;
	strFile = g_XML_path + "\\" + "TotalMML.txt";
	char *memFileName = (char*)malloc(1024);
	strcpy(memFileName, strFile.GetBuffer(0));

	DWORD ThreadID;
	HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ParseThreadFunc, (LPVOID)memFileName, 0, &ThreadID);
	parseThread = hThread;

	GetMenu()->GetSubMenu(0)->EnableMenuItem(0,MF_GRAYED|MF_BYPOSITION);
	GetMenu()->GetSubMenu(0)->EnableMenuItem(1,MF_GRAYED|MF_BYPOSITION);
}



//menu  选择xml目录
void CmmlToolDlg::OnMenuWorkPath()
{
	// TODO: 在此添加命令处理程序代码
	selectPathDlg(WorkPath, &m_hWnd);
	CString file;
	file = WorkPath + "\\" + "TotalMML.txt";
	if( (_access( file, 0 )) != -1 )
	{
		printf( "File TotalMML.txt exists " );
	}
	else
	{
		AfxMessageBox("目录选择错误, 请重新选择！");
		WorkPath = "";
		return;
	}
}

//menu 邻区统计
void CmmlToolDlg::OnNCellInfo()
{
	// TODO: 在此添加命令处理程序代码
	BeginWaitCursor();

	earseAllListControl(&m_DataList); 

	CHECK_WORK_PATH;

	char buff[16] = {0};

	m_DataList.InsertColumn(0, "RNCID", LVCFMT_LEFT, 90);
	m_DataList.InsertColumn(1, "TD-TD邻区对数", LVCFMT_LEFT, 90);
	m_DataList.InsertColumn(2, "TD-GSM邻区对数", LVCFMT_LEFT, 90);
	m_DataList.InsertColumn(3, "TD-LTE邻区对数", LVCFMT_LEFT, 90);

	int RNCID[1280] = {0};
	int RNCID_n;
	{
		RNCID_n = 0;
		CString strFile;
		strFile = WorkPath + "\\" + "TotalMML.txt";
		CStdioFile linefile;
		linefile.Open(strFile,CFile::modeRead,NULL);
		while(linefile.ReadString(str) == TRUE) 
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
		}
	}

	int i;
	for(i = 0; i < RNCID_n; i++)
	{
		sprintf(buff, "%d", RNCID[i]);
		m_DataList.InsertItem(i, buff);
	}
	m_DataList.InsertItem(i, "合计");

	int alltncellnum = 0;
	int allgsmnnum = 0;
	int allltennum = 0;
	TiXmlElement *ADDTCELLRoot = getXMLRoot("ADDTNCELL.xml");
	TiXmlElement *ADDTGSMNCELLRoot = getXMLRoot("ADDTGSMNCELL.xml");
	TiXmlElement *ADDTLTENCELLRoot = getXMLRoot("ADDTLTENCELL.xml");
	for(i = 0; i < RNCID_n; i++)
	{
		int n = numOfCellN(RNCID[i], ADDTCELLRoot);
		sprintf(buff, "%d", n);
		alltncellnum += n;
		m_DataList.SetItemText(i,1, buff);

		int gsmn = numOfCellN(RNCID[i], ADDTGSMNCELLRoot);
		sprintf(buff, "%d", gsmn);
		allgsmnnum += gsmn;
		m_DataList.SetItemText(i, 2, buff);

		int lten = numOfCellN(RNCID[i], ADDTLTENCELLRoot);
		sprintf(buff, "%d", lten);
		allltennum += lten;
		m_DataList.SetItemText(i, 3, buff);
	}
	sprintf(buff, "%d", alltncellnum);
	m_DataList.SetItemText(i,1, buff);
	sprintf(buff, "%d", allgsmnnum);
	m_DataList.SetItemText(i,2, buff);
	sprintf(buff, "%d", allltennum);
	m_DataList.SetItemText(i,3, buff);

	EndWaitCursor();
}


//窗口改变响应消息
void CmmlToolDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	static unsigned int i = 0;
	if(i == 0)
	{
		i++;
		return;
	}
	m_DataList.MoveWindow(0, 0, cx, cy - 18);
}


//menu CELLBAR信息
void CmmlToolDlg::OnStaticCellbar()
{
	// TODO: 在此添加命令处理程序代码
	BeginWaitCursor();

	earseAllListControl(&m_DataList); 

	CHECK_WORK_PATH;

	char buff[16] = {0};

	m_DataList.InsertColumn(0, "RNCID", LVCFMT_LEFT, 90);
	m_DataList.InsertColumn(1, "CELLBAR小区数", LVCFMT_LEFT, 90);

	int RNCID[1280] = {0};
	int RNCID_n;
	{
		RNCID_n = 0;
		CString strFile;
		strFile = WorkPath + "\\" + "TotalMML.txt";
		CStdioFile linefile;
		linefile.Open(strFile,CFile::modeRead,NULL);
		while(linefile.ReadString(str) == TRUE) 
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
		}
	}

	int i;
	for(i = 0; i < RNCID_n; i++)
	{
		sprintf(buff, "%d", RNCID[i]);
		m_DataList.InsertItem(i, buff);
	}
	m_DataList.InsertItem(i, "合计");

	int alltncellnum = 0;
	TiXmlElement *ADDTCELLACCESSSTRICTRoot = getXMLRoot("ADDTCELLACCESSSTRICT.xml");
	for(i = 0; i < RNCID_n; i++)
	{
		int n = numOfCELLBARN(RNCID[i], ADDTCELLACCESSSTRICTRoot);
		sprintf(buff, "%d", n);
		alltncellnum += n;
		m_DataList.SetItemText(i,1, buff);
	}
	sprintf(buff, "%d", alltncellnum);
	m_DataList.SetItemText(i,1, buff);

	EndWaitCursor();
}

//menu  导出九表
void CmmlToolDlg::OnExportNineTable()
{
	// TODO: 在此添加命令处理程序代码

	CHECK_WORK_PATH;

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
	int res = ExportNineData(FilePathName);
	EndWaitCursor();
	if(res == 1)
	{
		AfxMessageBox("文件保存成功!");
	}
	else
		AfxMessageBox("文件保存失败!");

}

//menu 导出cellbar表
void CmmlToolDlg::OnExportCellbarTable()
{
	// TODO: 在此添加命令处理程序代码
	CHECK_WORK_PATH;

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
	int res = ExportCellbar(FilePathName);
	EndWaitCursor();
	if(res == 1)
	{
		AfxMessageBox("文件保存成功!");
	}
	else
		AfxMessageBox("文件保存失败!");
}


//menu //把MML报文TXT格式 输出到excel  小区/载波/接入限制提取
void CmmlToolDlg::OnMmlBaowenTable()
{
	// TODO: 在此添加命令处理程序代码
	CmmlBaowenDlg dlg;
	dlg.DoModal();
}


//menu TSCP指标排序
struct ISCP
{
	string iscp_time;
	string rnc;
	string cellname;
	string cellid;
	double sts1;
	double sts2;
	double cts3;
	double cts4;
};
bool SortByCARR_TddMeanIscp_Ts1( const ISCP &v1, const ISCP &v2)//注意：本函数的参数的类型一定要与vector中元素的类型一致  
{  
	return v1.sts1 > v2.sts1;//降序排列  
}  
bool SortByCARR_TddMeanIscp_Ts2( const ISCP &v1, const ISCP &v2)//注意：本函数的参数的类型一定要与vector中元素的类型一致  
{  
	return v1.sts2 > v2.sts2;//降序排列  
}  

void CmmlToolDlg::OnIscp()
{
	// TODO: 在此添加命令处理程序代码
	Book *book = xlCreateBook();
	if(!book)
	{
		printf("%s\n", "CreateBook error");
		return;
	}

	CString  FileName;
	CFileDialog dlg(TRUE, NULL, NULL, 0, "Excel|*.xls|All Files (*.*)|*.*||");  ///TRUE为OPEN对话框，FALSE为SAVE AS对话框
	if(dlg.DoModal()==IDOK)
		FileName = dlg.GetPathName();
	else
	{
		return;
	}

	BeginWaitCursor();
	//printf("%s\n", FileName.GetBuffer(0));
	if( !book->load(FileName.GetBuffer(0)) )
	{
		printf("%s\n", "load error");
		return;
	}

	Sheet* sheet = book->getSheet(0);
	if( !sheet )
	{
		printf("%s\n", "getSheet error");
		return;
	}

	if(sheet->lastCol() != 7)
	{
		AfxMessageBox("文件选择错误,请重新选择！");
		return;
	}

	vector<ISCP> ISCPSet;
	ISCP info;
	for(int row = 1; row < sheet->lastRow(); row++)
	{
		for(int col = 0; col <= 6; col++)
		{
			switch( col )
			{
			case 0:
				info.iscp_time = sheet->readStr(row, col);
				break;
			case 1:
				info.rnc = sheet->readStr(row, col);
				break;
			case 2:
				char cellname[256];
				char cellid[32];
				splitCellIDandName(sheet->readStr(row, col), cellname, cellid);
				info.cellname = cellname;
				info.cellid = cellid;
				break;
			case 3:
				info.sts1 = sheet->readNum(row, col);
				break;
			case 4:
				info.sts2 = sheet->readNum(row, col);
				break;
			case 5:
				info.cts3 = sheet->readNum(row, col);
				break;
			case 6:
				info.cts4 =  sheet->readNum(row, col);
				break;
			}
		}
		ISCPSet.push_back(info);
	}

	//删除无用数据
	for(vector<ISCP>::iterator it = ISCPSet.begin(); it != ISCPSet.end(); )  
	{  
		if(it->sts1 > -0.000001 && it->sts1 < 0.000001)
		{
			it = ISCPSet.erase(it); //不能写成ISCPSet.erase(it);
		}
		else
		{
			it++;
		}
	}  

	//按CARR.TddMeanIscp.Ts1排序
	sort(ISCPSet.begin(),ISCPSet.end(),SortByCARR_TddMeanIscp_Ts1);  

	//写入到新sheet
	Sheet *sheet1 = book->addSheet("CARRTddMeanIscpTs1");
	sheet1->writeStr(0, 0, "DATE");
	sheet1->writeStr(0, 1, "RNCID");
	sheet1->writeStr(0, 2, "CELLNAME");
	sheet1->writeStr(0, 3, "CELLID");
	sheet1->writeStr(0, 4, "CARR.TddMeanIscp.Ts1");
	sheet1->writeStr(0, 5, "CARR.TddMeanIscp.Ts2");
	sheet1->writeStr(0, 6, "CARR.TddMaxIscp.Ts1");
	sheet1->writeStr(0, 7, "CARR.TddMaxIscp.Ts2");
	int row = 1;
	for(vector<ISCP>::iterator it = ISCPSet.begin(); it != ISCPSet.end(); it++)  
	{
		sheet1->writeStr( row, 0, it->iscp_time.c_str() );
		sheet1->writeStr( row, 1, it->rnc.c_str() );
		sheet1->writeStr( row, 2, it->cellname.c_str() );
		sheet1->writeNum( row, 3, atoi(it->cellid.c_str()) );
		sheet1->writeNum( row, 4, it->sts1 );
		sheet1->writeNum( row, 5, it->sts2 );
		sheet1->writeNum( row, 6, it->cts3 );
		sheet1->writeNum( row, 7, it->cts4 );
		row++;
		if(row == 101)
			break;
	}


	//排序
	sort(ISCPSet.begin(),ISCPSet.end(),SortByCARR_TddMeanIscp_Ts2); 

	Sheet *sheet2 = book->addSheet("CARRTddMeanIscpTs2");
	sheet2->writeStr(0, 0, "DATE");
	sheet2->writeStr(0, 1, "RNCID");
	sheet2->writeStr(0, 2, "CELLNAME");
	sheet2->writeStr(0, 3, "CELLID");
	sheet2->writeStr(0, 4, "CARR.TddMeanIscp.Ts1");
	sheet2->writeStr(0, 5, "CARR.TddMeanIscp.Ts2");
	sheet2->writeStr(0, 6, "CARR.TddMaxIscp.Ts1");
	sheet2->writeStr(0, 7, "CARR.TddMaxIscp.Ts2");
	row = 1;
	for(vector<ISCP>::iterator it = ISCPSet.begin(); it != ISCPSet.end(); it++)  
	{
		sheet2->writeStr( row, 0, it->iscp_time.c_str() );
		sheet2->writeStr( row, 1, it->rnc.c_str() );
		sheet2->writeStr( row, 2, it->cellname.c_str() );
		sheet2->writeNum( row, 3, atoi(it->cellid.c_str()) );
		sheet2->writeNum( row, 4, it->sts1 );
		sheet2->writeNum( row, 5, it->sts2 );
		sheet2->writeNum( row, 6, it->cts3 );
		sheet2->writeNum( row, 7, it->cts4 );
		row++;
		if(row == 101)
			break;
	}

	if( !book->save( FileName.GetBuffer(0) ))
	{
		AfxMessageBox("请关闭要排序的文件!");
		book->release();
		return;
	}

	book->release();
	AfxMessageBox("排序已完成，结果在新生成的sheet中");
	EndWaitCursor();
	return;
}

//menu top小区
struct TopCell
{
	string type;
	string date;
	string rnc;
	string cellid;
	string cellname;
	double cscon;
	double pscon;
	double csdrop;
	double psdrop;
	double cschan;
	double pschan;
};
bool csconcmp( const TopCell &v1, const TopCell &v2)//注意：本函数的参数的类型一定要与vector中元素的类型一致  
{  
	return v1.cscon < v2.cscon;//升序排列  
}  
bool psconcmp( const TopCell &v1, const TopCell &v2)//注意：本函数的参数的类型一定要与vector中元素的类型一致  
{  
	return v1.pscon < v2.pscon;//升序排列  
}  
bool csdropcmp( const TopCell &v1, const TopCell &v2)//注意：本函数的参数的类型一定要与vector中元素的类型一致  
{  
	return v1.csdrop > v2.csdrop;//降序排列  
} 
bool psdropcmp( const TopCell &v1, const TopCell &v2)//注意：本函数的参数的类型一定要与vector中元素的类型一致  
{  
	return v1.psdrop > v2.psdrop;//降序排列  
} 
bool cschancmp( const TopCell &v1, const TopCell &v2)//注意：本函数的参数的类型一定要与vector中元素的类型一致  
{  
	return v1.cschan < v2.cschan;//升序排列  
} 
bool pschancmp( const TopCell &v1, const TopCell &v2)//注意：本函数的参数的类型一定要与vector中元素的类型一致  
{  
	return v1.pschan < v2.pschan;//升序排列  
} 
//希望可以计算出如附件中的TOP小区“TOP小区-20140101”。原始数据见“NSN北京KPI”
void CmmlToolDlg::OnTopKpi()
{
	// TODO: 在此添加命令处理程序代码
	Book *book = xlCreateBook();
	if(!book)
	{
		printf("%s\n", "CreateBook error");
		return;
	}

	CString  FileName;
	CFileDialog dlg(TRUE, NULL, NULL, 0, "Excel|*.xls|All Files (*.*)|*.*||");  ///TRUE为OPEN对话框，FALSE为SAVE AS对话框
	if(dlg.DoModal()==IDOK)
		FileName = dlg.GetPathName();
	else
	{
		return;
	}
	BeginWaitCursor();

	if( !book->load(FileName.GetBuffer(0)) )
	{
		printf("%s\n", "load error");
		return;
	}

	Sheet* sheet = book->getSheet(0);
	if( !sheet )
	{
		printf("%s\n", "getSheet error");
		return;
	}

	if(sheet->lastCol() != 53)
	{
		AfxMessageBox("文件选择错误,请重新选择！");
		return;
	}

	vector<TopCell> TopCellSet;
	TopCell info;
	for(int row = 1; row < sheet->lastRow(); row++)
	{
		for(int col = 0; col <= 52; col++)
		{
			switch(col)
			{
			case 0:
				info.date = sheet->readStr(row, col);
				break;
			case 1:
				info.rnc = sheet->readStr(row, col);
				break;
			case 2:
				char cellname[256];
				char cellid[32];
				splitCellIDandName(sheet->readStr(row, col), cellname, cellid);
				info.cellname = cellname;
				info.cellid = cellid;
				break;
			case 12:
				info.cscon = sheet->readNum(row, col);
				break;
			case 19:
				info.pscon = sheet->readNum(row, col);
				break;
			case 25:
				info.csdrop = sheet->readNum(row, col);
				break;
			case 27:
				info.psdrop = sheet->readNum(row, col);
				break;
			case 32:
				info.cschan = sheet->readNum(row, col);
				break;
			case 35:
				info.pschan = sheet->readNum(row, col);
			}
		}
		TopCellSet.push_back(info);
	}

	//cs接通率-----------------------------------------------------------------------
	vector<TopCell> temp = TopCellSet; 
	//删除无用数据
	for(vector<TopCell>::iterator it = temp.begin(); it != temp.end(); )  
	{  
		if(it->cscon > -0.000001 && it->cscon < 0.000001)
		{
			it = temp.erase(it); //不能写成ISCPSet.erase(it);
		}
		else
		{
			it++;
		}
	}  

	//cs掉话率排序
	sort(temp.begin(), temp.end(), csconcmp);  


	//写入到新sheet
	Sheet *sheet1 = book->addSheet("TOP CELL");
	sheet1->writeStr(0, 0, "问题类型");
	sheet1->writeStr(0, 1, "日期");
	sheet1->writeStr(0, 2, "RNC");
	sheet1->writeStr(0, 3, "小区号");
	sheet1->writeStr(0, 4, "小区");
	sheet1->writeStr(0, 5, "CS接通率");
	sheet1->writeStr(0, 6, "PS接通率");
	sheet1->writeStr(0, 7, "CS掉话率");
	sheet1->writeStr(0, 8, "PS掉线率");
	sheet1->writeStr(0, 9, "CS异系统切换成功率");
	sheet1->writeStr(0, 10, "PS异系统切换成功率");
	int row = 1;
	for(vector<TopCell>::iterator it = temp.begin(); it != temp.end(); it++)  
	{
		sheet1->writeStr( row, 0, "CS接通率");
		sheet1->writeStr( row, 1,  it->date.c_str());
		sheet1->writeStr( row, 2,  it->rnc.c_str());
		sheet1->writeNum( row, 3,  atoi(it->cellid.c_str()));
		sheet1->writeStr( row, 4,  it->cellname.c_str());
		sheet1->writeNum( row, 5,  it->cscon);
		sheet1->writeNum( row, 6,  it->pscon);
		sheet1->writeNum( row, 7,  it->csdrop);
		sheet1->writeNum( row, 8, it->psdrop);
		sheet1->writeNum( row, 9, it->cschan);
		sheet1->writeNum( row, 10, it->pschan);
		row++;
		if(row == 31)
			break;
	}
	//cs接通率-----------------------------------------------------------------------

	//ps接通率-----------------------------------------------------------------------
	temp = TopCellSet;
	//删除无用数据
	for(vector<TopCell>::iterator it = temp.begin(); it != temp.end(); )  
	{  
		if(it->pscon > -0.000001 && it->pscon < 0.000001)
		{
			it = temp.erase(it); //不能写成ISCPSet.erase(it);
		}
		else
		{
			it++;
		}
	}
	sort(temp.begin(), temp.end(), psconcmp);
	row = 32;
	for(vector<TopCell>::iterator it = temp.begin(); it != temp.end(); it++)  
	{
		sheet1->writeStr( row, 0, "PS接通率");
		sheet1->writeStr( row, 1,  it->date.c_str());
		sheet1->writeStr( row, 2,  it->rnc.c_str());
		sheet1->writeNum( row, 3,  atoi(it->cellid.c_str()));
		sheet1->writeStr( row, 4,  it->cellname.c_str());
		sheet1->writeNum( row, 5,  it->cscon);
		sheet1->writeNum( row, 6,  it->pscon);
		sheet1->writeNum( row, 7,  it->csdrop);
		sheet1->writeNum( row, 8, it->psdrop);
		sheet1->writeNum( row, 9, it->cschan);
		sheet1->writeNum( row, 10, it->pschan);
		row++;
		if(row == 62)
			break;
	}
	//ps接通率-----------------------------------------------------------------------


	//cs掉话率-----------------------------------------------------------------------
	temp = TopCellSet;
	//删除无用数据
	for(vector<TopCell>::iterator it = temp.begin(); it != temp.end(); )  
	{  
		if(it->csdrop > -0.000001 && it->csdrop < 0.000001)
		{
			it = temp.erase(it); //不能写成ISCPSet.erase(it);
		}
		else
		{
			it++;
		}
	}
	sort(temp.begin(), temp.end(), csdropcmp);
	row = 63;
	for(vector<TopCell>::iterator it = temp.begin(); it != temp.end(); it++)  
	{
		sheet1->writeStr( row, 0, "CS掉话率");
		sheet1->writeStr( row, 1,  it->date.c_str());
		sheet1->writeStr( row, 2,  it->rnc.c_str());
		sheet1->writeNum( row, 3,  atoi(it->cellid.c_str()));
		sheet1->writeStr( row, 4,  it->cellname.c_str());
		sheet1->writeNum( row, 5,  it->cscon);
		sheet1->writeNum( row, 6,  it->pscon);
		sheet1->writeNum( row, 7,  it->csdrop);
		sheet1->writeNum( row, 8, it->psdrop);
		sheet1->writeNum( row, 9, it->cschan);
		sheet1->writeNum( row, 10, it->pschan);
		row++;
		if(row == 93)
			break;
	}
	//cs掉话率-----------------------------------------------------------------------

	//ps掉话率-----------------------------------------------------------------------
	temp = TopCellSet;
	//删除无用数据
	for(vector<TopCell>::iterator it = temp.begin(); it != temp.end(); )  
	{  
		if(it->psdrop > -0.000001 && it->psdrop < 0.000001)
		{
			it = temp.erase(it); //不能写成ISCPSet.erase(it);
		}
		else
		{
			it++;
		}
	}
	sort(temp.begin(), temp.end(), psdropcmp);
	row = 94;
	for(vector<TopCell>::iterator it = temp.begin(); it != temp.end(); it++)  
	{
		sheet1->writeStr( row, 0, "PS掉话率");
		sheet1->writeStr( row, 1,  it->date.c_str());
		sheet1->writeStr( row, 2,  it->rnc.c_str());
		sheet1->writeNum( row, 3,  atoi(it->cellid.c_str()));
		sheet1->writeStr( row, 4,  it->cellname.c_str());
		sheet1->writeNum( row, 5,  it->cscon);
		sheet1->writeNum( row, 6,  it->pscon);
		sheet1->writeNum( row, 7,  it->csdrop);
		sheet1->writeNum( row, 8, it->psdrop);
		sheet1->writeNum( row, 9, it->cschan);
		sheet1->writeNum( row, 10, it->pschan);
		row++;
		if(row == 124)
			break;
	}
	//ps掉话率-----------------------------------------------------------------------


	//CS异系统切换成功率------------------------------------------------------------
	temp = TopCellSet;
	//删除无用数据
	for(vector<TopCell>::iterator it = temp.begin(); it != temp.end(); )  
	{  
		if(it->cschan > -0.000001 && it->cschan < 0.000001)
		{
			it = temp.erase(it); //不能写成ISCPSet.erase(it);
		}
		else
		{
			it++;
		}
	}
	sort(temp.begin(), temp.end(), cschancmp);
	row = 125;
	for(vector<TopCell>::iterator it = temp.begin(); it != temp.end(); it++)  
	{
		sheet1->writeStr( row, 0, "CS异系统切换成功率");
		sheet1->writeStr( row, 1,  it->date.c_str());
		sheet1->writeStr( row, 2,  it->rnc.c_str());
		sheet1->writeNum( row, 3,  atoi(it->cellid.c_str()));
		sheet1->writeStr( row, 4,  it->cellname.c_str());
		sheet1->writeNum( row, 5,  it->cscon);
		sheet1->writeNum( row, 6,  it->pscon);
		sheet1->writeNum( row, 7,  it->csdrop);
		sheet1->writeNum( row, 8, it->psdrop);
		sheet1->writeNum( row, 9, it->cschan);
		sheet1->writeNum( row, 10, it->pschan);
		row++;
		if(row == 155)
			break;
	}
	//CS异系统切换成功率------------------------------------------------------------

	//PS异系统切换成功率------------------------------------------------------------
	temp = TopCellSet;
	//删除无用数据
	for(vector<TopCell>::iterator it = temp.begin(); it != temp.end(); )  
	{  
		if(it->pschan > -0.000001 && it->pschan < 0.000001)
		{
			it = temp.erase(it); //不能写成ISCPSet.erase(it);
		}
		else
		{
			it++;
		}
	}
	sort(temp.begin(), temp.end(), pschancmp);
	row = 156;
	for(vector<TopCell>::iterator it = temp.begin(); it != temp.end(); it++)  
	{
		sheet1->writeStr( row, 0, "PS异系统切换成功率");
		sheet1->writeStr( row, 1,  it->date.c_str());
		sheet1->writeStr( row, 2,  it->rnc.c_str());
		sheet1->writeNum( row, 3,  atoi(it->cellid.c_str()));
		sheet1->writeStr( row, 4,  it->cellname.c_str());
		sheet1->writeNum( row, 5,  it->cscon);
		sheet1->writeNum( row, 6,  it->pscon);
		sheet1->writeNum( row, 7,  it->csdrop);
		sheet1->writeNum( row, 8, it->psdrop);
		sheet1->writeNum( row, 9, it->cschan);
		sheet1->writeNum( row, 10, it->pschan);
		row++;
		if(row == 186)
			break;
	}
	//PS异系统切换成功率------------------------------------------------------------

	if( !book->save( FileName.GetBuffer(0) ))
	{
		AfxMessageBox("请关闭要统计的文件!");
		book->release();
		return;
	}

	book->release();
	AfxMessageBox("统计已完成，结果在新生成的sheet中");
	EndWaitCursor();
	return;
}

//menu 关于
void CmmlToolDlg::OnAbout()
{
	// TODO: 在此添加命令处理程序代码
	CAboutDlg dlg;
	dlg.DoModal();
}

//menu 导出指定表
void CmmlToolDlg::OnSelectOrderTable()
{
	// TODO: 在此添加命令处理程序代码
	CmmlAnyExportDlg dlg;
	dlg.DoModal();
}






/************************************************************************
*                                                                       *
*			RNC统计      NODEB统计									*
*																		*
*************************************************************************/


//导入mml文件
void CmmlToolDlg::OnRncMmlFile()
{
	// TODO: 在此添加命令处理程序代码
	CFileDialog Dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT
		| OFN_ALLOWMULTISELECT, "TXT|*.txt|");  ///TRUE为OPEN对话框，FALSE为SAVE AS对话框
	DWORD MAXFILE = 40000;
	Dlg.m_ofn.nMaxFile = MAXFILE;
	char* pc = new char[MAXFILE];
	Dlg.m_ofn.lpstrFile = pc;
	Dlg.m_ofn.lpstrFile[0] = NULL;
	int iReturn = Dlg.DoModal();
	if(iReturn ==  IDOK)
	{
		POSITION pos = Dlg.GetStartPosition();
		g_XML_path = Dlg.GetFolderPath();
		g_XML_path += "\\XMLCACHE";
		if ( !::CreateDirectory( g_XML_path, NULL ) )
		{
			DeleteDirectory(g_XML_path.GetBuffer(0));
			Sleep(500);
			::CreateDirectory( g_XML_path, NULL );
		}
		HANDLE FileOnehandle = CreateFile(g_XML_path + "\\" + "TotalMML.txt", GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_NEW, 0, 0);
		while (pos != NULL)
		{
			CString fileName = Dlg.GetNextPathName(pos);		

			HANDLE handle = CreateFile(fileName, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
			int fileSize = GetFileSize(handle, NULL);
			char *memFile = (char*)malloc(fileSize);
			memset(memFile,0,sizeof(fileSize));
			unsigned long size;
			ReadFile(handle, memFile, fileSize, &size, NULL); 
			WriteFile(FileOnehandle, memFile, fileSize, &size, NULL);
			CloseHandle(handle);
			free(memFile);
		}
		CloseHandle(FileOnehandle);
	}
	else
	{
		return;
	}
	delete []pc;



	CString strFile;
	strFile = g_XML_path + "\\" + "TotalMML.txt";
	char *memFileName = (char*)malloc(1024);
	strcpy(memFileName, strFile.GetBuffer(0));

	DWORD ThreadID;
	HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ParseThreadFunc_FOR_RNC, (LPVOID)memFileName, 0, &ThreadID);
	parseThread = hThread;

}

//导出
void CmmlToolDlg::OnRncOut()
{
	// TODO: 在此添加命令处理程序代码
	CHECK_WORK_PATH;

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
	int res = ExportRncData(FilePathName);
	EndWaitCursor();
	if(res == 1)
	{
		AfxMessageBox("文件保存成功!");
	}
	else
		AfxMessageBox("文件保存失败!");

}

