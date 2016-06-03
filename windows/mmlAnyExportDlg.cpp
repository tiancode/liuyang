// mmlAnyExportDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "mmlTool.h"
#include "mmlAnyExportDlg.h"
#include "mess.h"


// CmmlAnyExportDlg 对话框

IMPLEMENT_DYNAMIC(CmmlAnyExportDlg, CDialog)

CmmlAnyExportDlg::CmmlAnyExportDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CmmlAnyExportDlg::IDD, pParent)
{

}

CmmlAnyExportDlg::~CmmlAnyExportDlg()
{
}

void CmmlAnyExportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MML, m_listOrder);
	DDX_Control(pDX, IDC_BUTTON_RIGHT, m_buttonRight);
	DDX_Control(pDX, IDC_BUTTON_LEFT, m_buttonLeft);
	DDX_Control(pDX, IDC_LIST_MML_SELECT, m_listExport);
}


BOOL CmmlAnyExportDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//设置图标按钮
	m_buttonRight.SetIcon(IDI_ICON_RIGHT);
	m_buttonRight.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);
	m_buttonRight.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 128, 0));

	m_buttonLeft.SetIcon(IDI_ICON_LEFT);
	m_buttonLeft.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);
	m_buttonLeft.SetColor(CButtonST::BTNST_COLOR_FG_IN, RGB(0, 128, 0));

	
	int Col = 0;
	for(vector<string>::iterator it = g_orders.begin(); it != g_orders.end(); it++)
	{
		m_listOrder.InsertString(Col++, it->c_str());
	}
	

	return TRUE;
}

BOOL CmmlAnyExportDlg::PreTranslateMessage(MSG* pMsg)
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

BEGIN_MESSAGE_MAP(CmmlAnyExportDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT, &CmmlAnyExportDlg::OnBnClickedButtonRight)
	ON_BN_CLICKED(IDC_BUTTON_LEFT, &CmmlAnyExportDlg::OnBnClickedButtonLeft)
	ON_BN_CLICKED(IDC_BUTTON_EXPORT, &CmmlAnyExportDlg::OnBnClickedButtonExport)
END_MESSAGE_MAP()


// CmmlAnyExportDlg 消息处理程序

//响应arrow
void CmmlAnyExportDlg::OnBnClickedButtonRight()
{
	// TODO: 在此添加控件通知处理程序代码
	int n = m_listOrder.GetCurSel();
	if(n == -1)
		return;

	CString str;
	m_listOrder.GetText(n,str);

	m_listExport.InsertString(0, str);

	m_listOrder.DeleteString(n);
}
//响应arrow
void CmmlAnyExportDlg::OnBnClickedButtonLeft()
{
	// TODO: 在此添加控件通知处理程序代码
	int n = m_listExport.GetCurSel();
	if(n == -1)
		return;
	
	CString str;
	m_listExport.GetText(n,str);

	m_listOrder.InsertString(0, str);

	m_listExport.DeleteString(n);
}


int ExportAnyData(CString filename, vector<string> &orders)
{
	Book* book = xlCreateBook();
	if(!book)
		return 0;

	for(vector<string>::iterator it = orders.begin(); it != orders.end(); it++)
	{
		CString Filename = it->c_str();
		Filename += ".xml";
		TiXmlElement *Root = getXMLRoot(Filename);
		Sheet* sheet = book->addSheet(it->c_str());
		if(!sheet)
			return 0;
		addOneSheet(sheet, Root);

		delete Root->GetDocument();
	}

	if(book->save(_T(filename.GetBuffer(0)) )) 
	{
		return 1;
	}
	else
	{
		return 0;
	}

	book->release();
}

//导出按钮
void CmmlAnyExportDlg::OnBnClickedButtonExport()
{
	// TODO: 在此添加控件通知处理程序代码
	int MMLCount = m_listExport.GetCount();

	vector<string> orders;

	int n;
	CString str1;
	for (int i = 0; i < MMLCount; i++)
	{
		n = m_listExport.GetTextLen(i);
		m_listExport.GetText( i, str1.GetBuffer(n) );

		orders.push_back(str1.GetBuffer(0));  //存放要导出的命令
	}
	
	CHECK_WORK_PATH;

	CString FilePathName;
	CFileDialog dlg(FALSE,NULL,"default.xls",NULL,"Excel 文档(*.xls) | 全部文件(*.*)| *.*");///TRUE为OPEN对话框，FALSE为SAVE AS对话框
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
	int res = ExportAnyData(FilePathName, orders);
	EndWaitCursor();
	if(res == 1)
	{
		AfxMessageBox("文件保存成功!");
	}
	else
		AfxMessageBox("文件保存失败!");

}
