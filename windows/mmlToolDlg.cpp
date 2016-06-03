// mmlToolDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CString m_info;
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
, m_info(_T(""))
{
	m_info = "2014.1.18\r\n�����߿�ͨ���޸İ�װĿ¼�µ�config�ļ�\r\nʵ�ֵ�������MML����";
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_info);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()







// CmmlToolDlg �Ի���

//ȫ�ֱ���
//���Ҫ������MML����
vector<string> g_orders;

//�������xml�ļ�·��
CString g_XML_path;

//����Ŀ¼ MML xml Ŀ¼
CString WorkPath;

// ����MML�߳̾��
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


// CmmlToolDlg ��Ϣ�������

BOOL CmmlToolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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


	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_MAXIMIZE);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_wndStatusBar.Create(AfxGetMainWnd());  
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));
	SetTimer(1,100,NULL); 
	//ע�ᴰ��
	CregisterDlg dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	
	TEST();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CmmlToolDlg::OnPaint()
{
//	CRect ct;  
//	GetClientRect(&ct);  
//	CString str;  
//	str = _T("PROCESS : Done");  
//	m_wndStatusBar.SetPaneInfo(0, BAR_ID_OPERATOR, SBPS_NORMAL, (int) ct.Width() * 0.45);  
////	m_wndStatusBar.SetPaneText(0, str);  
//	str = _T("EMAIL��tianshuai@wellservicenet.com, QQ:811627469");  
//	m_wndStatusBar.SetPaneInfo(1, BAR_ID_EMAIL, SBPS_NORMAL, (int) ct.Width() * 0.40);  
//	m_wndStatusBar.SetPaneText(1, str);  
//	str = _T("ʱ�䣺");  
//	m_wndStatusBar.SetPaneInfo(2, BAR_ID_TIME, SBPS_NORMAL, (int) ct.Width() * 0.25);  
//	m_wndStatusBar.SetPaneText(2, str);  
//	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0); 

	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CmmlToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BOOL CmmlToolDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_RETURN:
			//MessageBox(_T("�س�������"));
			return TRUE;
		case VK_ESCAPE:
			//MessageBox(_T("ESC������"));
			return TRUE;
		default:
			break;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CmmlToolDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(MessageBox("�Ƿ�Ҫ�˳���","��ʾ",MB_ICONQUESTION | MB_YESNO) != IDYES)
		return;
	KillTimer(1);
	CDialog::OnClose();
}

int CmmlToolDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	
	//�������ļ�
	readConfig(g_orders);

	return 0;
}

void CmmlToolDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CRect ct;  
	GetClientRect(&ct);  
	CString str;  
	str.Format("PROCESS : %s   %d/%d", MMLorder.GetBuffer(0), nowNum, totalNum);
	m_wndStatusBar.SetPaneInfo(0, BAR_ID_OPERATOR, SBPS_NORMAL, (int) ct.Width() * 0.45);  
	m_wndStatusBar.SetPaneText(0, str);  
	if(nowNum == totalNum)
	{
		str.Format("PROCESS : %s", "���");
		m_wndStatusBar.SetPaneInfo(0, BAR_ID_OPERATOR, SBPS_NORMAL, (int) ct.Width() * 0.45);  
		m_wndStatusBar.SetPaneText(0, str);  
	}
	str = _T("EMAIL��tianshuai@wellservicenet.com, QQ:811627469");  
	m_wndStatusBar.SetPaneInfo(1, BAR_ID_EMAIL, SBPS_NORMAL, (int) ct.Width() * 0.40);  
	m_wndStatusBar.SetPaneText(1, str); 
	str = _T("ʱ�䣺");  
	CTime time;  
	time=CTime::GetCurrentTime();  
	CString s_time=time.Format("%H:%M:%S");  
	m_wndStatusBar.SetPaneInfo(2, BAR_ID_TIME, SBPS_NORMAL, (int) ct.Width() * 0.25);  
	m_wndStatusBar.SetPaneText(2, str + s_time);  
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0); 


	CDialog::OnTimer(nIDEvent);
}

//menu �˳�
void CmmlToolDlg::OnMenuQuit()
{
	// TODO: �ڴ���������������
	// TODO: �ڴ���������������
	if(MessageBox("�Ƿ�Ҫ�˳���","��ʾ",MB_ICONQUESTION | MB_YESNO) != IDYES)
		return;
	else
	{
		KillTimer(1);
		exit(0);
	}
}

//menu ����MML�ļ���txt��
void CmmlToolDlg::OnMenuImport()
{
	WorkPath = "";
	// TODO: �ڴ���������������
	CFileDialog Dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT
		| OFN_ALLOWMULTISELECT, "TXT|*.txt|");  ///TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���
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



//menu  ѡ��xmlĿ¼
void CmmlToolDlg::OnMenuWorkPath()
{
	// TODO: �ڴ���������������
	selectPathDlg(WorkPath, &m_hWnd);
	CString file;
	file = WorkPath + "\\" + "TotalMML.txt";
	if( (_access( file, 0 )) != -1 )
	{
		printf( "File TotalMML.txt exists " );
	}
	else
	{
		AfxMessageBox("Ŀ¼ѡ�����, ������ѡ��");
		WorkPath = "";
		return;
	}
}

//menu ����ͳ��
void CmmlToolDlg::OnNCellInfo()
{
	// TODO: �ڴ���������������
	BeginWaitCursor();

	earseAllListControl(&m_DataList); 

	CHECK_WORK_PATH;

	char buff[16] = {0};

	m_DataList.InsertColumn(0, "RNCID", LVCFMT_LEFT, 90);
	m_DataList.InsertColumn(1, "TD-TD��������", LVCFMT_LEFT, 90);
	m_DataList.InsertColumn(2, "TD-GSM��������", LVCFMT_LEFT, 90);
	m_DataList.InsertColumn(3, "TD-LTE��������", LVCFMT_LEFT, 90);

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
				if(nIndex == -1)  //û���ҵ�ƥ�������
				{
					continue;
				}
				char *p = findColon(str.GetBuffer(0) + nIndex);
				unsigned int RNCID_num = getFirstNum(p);    //�ҵ� //��  RNCID ��ֵ
				if(RNCID_num == -1)
					AfxMessageBox("RNCID���ݴ���");
				else               //�ҵ�RNCID    289  290
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
	m_DataList.InsertItem(i, "�ϼ�");

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


//���ڸı���Ӧ��Ϣ
void CmmlToolDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	static unsigned int i = 0;
	if(i == 0)
	{
		i++;
		return;
	}
	m_DataList.MoveWindow(0, 0, cx, cy - 18);
}


//menu CELLBAR��Ϣ
void CmmlToolDlg::OnStaticCellbar()
{
	// TODO: �ڴ���������������
	BeginWaitCursor();

	earseAllListControl(&m_DataList); 

	CHECK_WORK_PATH;

	char buff[16] = {0};

	m_DataList.InsertColumn(0, "RNCID", LVCFMT_LEFT, 90);
	m_DataList.InsertColumn(1, "CELLBARС����", LVCFMT_LEFT, 90);

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
				if(nIndex == -1)  //û���ҵ�ƥ�������
				{
					continue;
				}
				char *p = findColon(str.GetBuffer(0) + nIndex);
				unsigned int RNCID_num = getFirstNum(p);    //�ҵ� //��  RNCID ��ֵ
				if(RNCID_num == -1)
					AfxMessageBox("RNCID���ݴ���");
				else               //�ҵ�RNCID    289  290
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
	m_DataList.InsertItem(i, "�ϼ�");

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

//menu  �����ű�
void CmmlToolDlg::OnExportNineTable()
{
	// TODO: �ڴ���������������

	CHECK_WORK_PATH;

	CString FilePathName;
	CFileDialog dlg(FALSE,NULL,"default.xls",NULL,"Excel �ĵ�(*.xls) | ȫ���ļ�(*.*)| *.*");///TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���
	//dlg.m_ofn.lpstrInitialDir=_T("d:\\"); //����������˶Ի����Ĭ��Ŀ¼d��
	INT_PTR nRes = dlg.DoModal();
	if(nRes == IDOK)
		FilePathName=dlg.GetPathName();
	else
		return;
	if(FilePathName.IsEmpty())
	{
		AfxMessageBox("�����뱣����ļ�");
		return;
	}
	FilePathName = FilePathName;
	BeginWaitCursor();
	int res = ExportNineData(FilePathName);
	EndWaitCursor();
	if(res == 1)
	{
		AfxMessageBox("�ļ�����ɹ�!");
	}
	else
		AfxMessageBox("�ļ�����ʧ��!");

}

//menu ����cellbar��
void CmmlToolDlg::OnExportCellbarTable()
{
	// TODO: �ڴ���������������
	CHECK_WORK_PATH;

	CString FilePathName;
	CFileDialog dlg(FALSE,NULL,"default.xls",NULL,"Excel �ĵ�(*.xls) | ȫ���ļ�(*.*)| *.*");///TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���
	//dlg.m_ofn.lpstrInitialDir=_T("d:\\"); //����������˶Ի����Ĭ��Ŀ¼d��
	INT_PTR nRes = dlg.DoModal();
	if(nRes == IDOK)
		FilePathName=dlg.GetPathName();
	else
		return;
	if(FilePathName.IsEmpty())
	{
		AfxMessageBox("�����뱣����ļ�");
		return;
	}
	FilePathName = FilePathName;
	BeginWaitCursor();
	int res = ExportCellbar(FilePathName);
	EndWaitCursor();
	if(res == 1)
	{
		AfxMessageBox("�ļ�����ɹ�!");
	}
	else
		AfxMessageBox("�ļ�����ʧ��!");
}


//menu //��MML����TXT��ʽ �����excel  С��/�ز�/����������ȡ
void CmmlToolDlg::OnMmlBaowenTable()
{
	// TODO: �ڴ���������������
	CmmlBaowenDlg dlg;
	dlg.DoModal();
}


//menu TSCPָ������
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
bool SortByCARR_TddMeanIscp_Ts1( const ISCP &v1, const ISCP &v2)//ע�⣺�������Ĳ���������һ��Ҫ��vector��Ԫ�ص�����һ��  
{  
	return v1.sts1 > v2.sts1;//��������  
}  
bool SortByCARR_TddMeanIscp_Ts2( const ISCP &v1, const ISCP &v2)//ע�⣺�������Ĳ���������һ��Ҫ��vector��Ԫ�ص�����һ��  
{  
	return v1.sts2 > v2.sts2;//��������  
}  

void CmmlToolDlg::OnIscp()
{
	// TODO: �ڴ���������������
	Book *book = xlCreateBook();
	if(!book)
	{
		printf("%s\n", "CreateBook error");
		return;
	}

	CString  FileName;
	CFileDialog dlg(TRUE, NULL, NULL, 0, "Excel|*.xls|All Files (*.*)|*.*||");  ///TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���
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
		AfxMessageBox("�ļ�ѡ�����,������ѡ��");
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

	//ɾ����������
	for(vector<ISCP>::iterator it = ISCPSet.begin(); it != ISCPSet.end(); )  
	{  
		if(it->sts1 > -0.000001 && it->sts1 < 0.000001)
		{
			it = ISCPSet.erase(it); //����д��ISCPSet.erase(it);
		}
		else
		{
			it++;
		}
	}  

	//��CARR.TddMeanIscp.Ts1����
	sort(ISCPSet.begin(),ISCPSet.end(),SortByCARR_TddMeanIscp_Ts1);  

	//д�뵽��sheet
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


	//����
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
		AfxMessageBox("��ر�Ҫ������ļ�!");
		book->release();
		return;
	}

	book->release();
	AfxMessageBox("��������ɣ�����������ɵ�sheet��");
	EndWaitCursor();
	return;
}

//menu topС��
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
bool csconcmp( const TopCell &v1, const TopCell &v2)//ע�⣺�������Ĳ���������һ��Ҫ��vector��Ԫ�ص�����һ��  
{  
	return v1.cscon < v2.cscon;//��������  
}  
bool psconcmp( const TopCell &v1, const TopCell &v2)//ע�⣺�������Ĳ���������һ��Ҫ��vector��Ԫ�ص�����һ��  
{  
	return v1.pscon < v2.pscon;//��������  
}  
bool csdropcmp( const TopCell &v1, const TopCell &v2)//ע�⣺�������Ĳ���������һ��Ҫ��vector��Ԫ�ص�����һ��  
{  
	return v1.csdrop > v2.csdrop;//��������  
} 
bool psdropcmp( const TopCell &v1, const TopCell &v2)//ע�⣺�������Ĳ���������һ��Ҫ��vector��Ԫ�ص�����һ��  
{  
	return v1.psdrop > v2.psdrop;//��������  
} 
bool cschancmp( const TopCell &v1, const TopCell &v2)//ע�⣺�������Ĳ���������һ��Ҫ��vector��Ԫ�ص�����һ��  
{  
	return v1.cschan < v2.cschan;//��������  
} 
bool pschancmp( const TopCell &v1, const TopCell &v2)//ע�⣺�������Ĳ���������һ��Ҫ��vector��Ԫ�ص�����һ��  
{  
	return v1.pschan < v2.pschan;//��������  
} 
//ϣ�����Լ�����總���е�TOPС����TOPС��-20140101����ԭʼ���ݼ���NSN����KPI��
void CmmlToolDlg::OnTopKpi()
{
	// TODO: �ڴ���������������
	Book *book = xlCreateBook();
	if(!book)
	{
		printf("%s\n", "CreateBook error");
		return;
	}

	CString  FileName;
	CFileDialog dlg(TRUE, NULL, NULL, 0, "Excel|*.xls|All Files (*.*)|*.*||");  ///TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���
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
		AfxMessageBox("�ļ�ѡ�����,������ѡ��");
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

	//cs��ͨ��-----------------------------------------------------------------------
	vector<TopCell> temp = TopCellSet; 
	//ɾ����������
	for(vector<TopCell>::iterator it = temp.begin(); it != temp.end(); )  
	{  
		if(it->cscon > -0.000001 && it->cscon < 0.000001)
		{
			it = temp.erase(it); //����д��ISCPSet.erase(it);
		}
		else
		{
			it++;
		}
	}  

	//cs����������
	sort(temp.begin(), temp.end(), csconcmp);  


	//д�뵽��sheet
	Sheet *sheet1 = book->addSheet("TOP CELL");
	sheet1->writeStr(0, 0, "��������");
	sheet1->writeStr(0, 1, "����");
	sheet1->writeStr(0, 2, "RNC");
	sheet1->writeStr(0, 3, "С����");
	sheet1->writeStr(0, 4, "С��");
	sheet1->writeStr(0, 5, "CS��ͨ��");
	sheet1->writeStr(0, 6, "PS��ͨ��");
	sheet1->writeStr(0, 7, "CS������");
	sheet1->writeStr(0, 8, "PS������");
	sheet1->writeStr(0, 9, "CS��ϵͳ�л��ɹ���");
	sheet1->writeStr(0, 10, "PS��ϵͳ�л��ɹ���");
	int row = 1;
	for(vector<TopCell>::iterator it = temp.begin(); it != temp.end(); it++)  
	{
		sheet1->writeStr( row, 0, "CS��ͨ��");
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
	//cs��ͨ��-----------------------------------------------------------------------

	//ps��ͨ��-----------------------------------------------------------------------
	temp = TopCellSet;
	//ɾ����������
	for(vector<TopCell>::iterator it = temp.begin(); it != temp.end(); )  
	{  
		if(it->pscon > -0.000001 && it->pscon < 0.000001)
		{
			it = temp.erase(it); //����д��ISCPSet.erase(it);
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
		sheet1->writeStr( row, 0, "PS��ͨ��");
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
	//ps��ͨ��-----------------------------------------------------------------------


	//cs������-----------------------------------------------------------------------
	temp = TopCellSet;
	//ɾ����������
	for(vector<TopCell>::iterator it = temp.begin(); it != temp.end(); )  
	{  
		if(it->csdrop > -0.000001 && it->csdrop < 0.000001)
		{
			it = temp.erase(it); //����д��ISCPSet.erase(it);
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
		sheet1->writeStr( row, 0, "CS������");
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
	//cs������-----------------------------------------------------------------------

	//ps������-----------------------------------------------------------------------
	temp = TopCellSet;
	//ɾ����������
	for(vector<TopCell>::iterator it = temp.begin(); it != temp.end(); )  
	{  
		if(it->psdrop > -0.000001 && it->psdrop < 0.000001)
		{
			it = temp.erase(it); //����д��ISCPSet.erase(it);
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
		sheet1->writeStr( row, 0, "PS������");
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
	//ps������-----------------------------------------------------------------------


	//CS��ϵͳ�л��ɹ���------------------------------------------------------------
	temp = TopCellSet;
	//ɾ����������
	for(vector<TopCell>::iterator it = temp.begin(); it != temp.end(); )  
	{  
		if(it->cschan > -0.000001 && it->cschan < 0.000001)
		{
			it = temp.erase(it); //����д��ISCPSet.erase(it);
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
		sheet1->writeStr( row, 0, "CS��ϵͳ�л��ɹ���");
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
	//CS��ϵͳ�л��ɹ���------------------------------------------------------------

	//PS��ϵͳ�л��ɹ���------------------------------------------------------------
	temp = TopCellSet;
	//ɾ����������
	for(vector<TopCell>::iterator it = temp.begin(); it != temp.end(); )  
	{  
		if(it->pschan > -0.000001 && it->pschan < 0.000001)
		{
			it = temp.erase(it); //����д��ISCPSet.erase(it);
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
		sheet1->writeStr( row, 0, "PS��ϵͳ�л��ɹ���");
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
	//PS��ϵͳ�л��ɹ���------------------------------------------------------------

	if( !book->save( FileName.GetBuffer(0) ))
	{
		AfxMessageBox("��ر�Ҫͳ�Ƶ��ļ�!");
		book->release();
		return;
	}

	book->release();
	AfxMessageBox("ͳ������ɣ�����������ɵ�sheet��");
	EndWaitCursor();
	return;
}

//menu ����
void CmmlToolDlg::OnAbout()
{
	// TODO: �ڴ���������������
	CAboutDlg dlg;
	dlg.DoModal();
}

//menu ����ָ����
void CmmlToolDlg::OnSelectOrderTable()
{
	// TODO: �ڴ���������������
	CmmlAnyExportDlg dlg;
	dlg.DoModal();
}






/************************************************************************
*                                                                       *
*			RNCͳ��      NODEBͳ��									*
*																		*
*************************************************************************/


//����mml�ļ�
void CmmlToolDlg::OnRncMmlFile()
{
	// TODO: �ڴ���������������
	CFileDialog Dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT
		| OFN_ALLOWMULTISELECT, "TXT|*.txt|");  ///TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���
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

//����
void CmmlToolDlg::OnRncOut()
{
	// TODO: �ڴ���������������
	CHECK_WORK_PATH;

	CString FilePathName;
	CFileDialog dlg(FALSE,NULL,"default.xls",NULL,"Excel �ĵ�(*.xls) | ȫ���ļ�(*.*)| *.*");///TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���
	//dlg.m_ofn.lpstrInitialDir=_T("d:\\"); //����������˶Ի����Ĭ��Ŀ¼d��
	INT_PTR nRes = dlg.DoModal();
	if(nRes == IDOK)
		FilePathName=dlg.GetPathName();
	else
		return;
	if(FilePathName.IsEmpty())
	{
		AfxMessageBox("�����뱣����ļ�");
		return;
	}
	FilePathName = FilePathName;
	BeginWaitCursor();
	int res = ExportRncData(FilePathName);
	EndWaitCursor();
	if(res == 1)
	{
		AfxMessageBox("�ļ�����ɹ�!");
	}
	else
		AfxMessageBox("�ļ�����ʧ��!");

}

