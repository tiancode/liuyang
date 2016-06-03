// registerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mmlTool.h"
#include "registerDlg.h"
#include <atlimage.h>
#include "mmlToolDlg.h"
#include "registry.h"
#include "md5.h"
#include "mess.h"
#include "systemInfo.h"


// CregisterDlg �Ի���

IMPLEMENT_DYNAMIC(CregisterDlg, CDialog)

CregisterDlg::CregisterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CregisterDlg::IDD, pParent)
	, m_mechine(_T(""))
	, m_regNum(_T(""))
{

}

CregisterDlg::~CregisterDlg()
{
}

void CregisterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CO_PICTURE, m_com_picture);
	DDX_Text(pDX, IDC_EDIT_UNIQE, m_mechine);
	DDX_Text(pDX, IDC_EDIT_REGISTER_NUM, m_regNum);
}


BEGIN_MESSAGE_MAP(CregisterDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_REGISTER, &CregisterDlg::OnBnClickedButtonRegister)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CregisterDlg::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// CregisterDlg ��Ϣ�������

BOOL CregisterDlg::PreTranslateMessage(MSG* pMsg)
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

CRegistry regidit;
BOOL CregisterDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	//��ʾͼ��
	CImage image;  
	HRESULT res = image.Load(_T("com.png"));  
	HBITMAP hBmp = image.Detach();  
	m_com_picture.SetBitmap(hBmp);  
	m_com_picture.SetWindowPos(NULL, 0, 0, 527, 157, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOZORDER);  


	//��ʼ��ע���
	res = regidit.CreateKey(HKEY_LOCAL_MACHINE, "SOFTWARE\\MMLHE", "");
	if(res == FALSE)
		printf("error createkey\n");
	res = regidit.Open(HKEY_LOCAL_MACHINE, "SOFTWARE\\MMLHE");
	if(res == FALSE)
	{
		AfxMessageBox("��ʼ��ʧ�ܣ���ȷ�����Թ���Ա��ʽ���У�");
		this->EndDialog(0);
		ExitProcess(0);
	}

	DWORD regres = 100;
	res = regidit.ReadDWORD(REGED, &regres);
	if(regres == 1)
	{
		int now = time(NULL);
		DWORD tim;
		regidit.ReadDWORD(STARTTIME, &tim);
		if(now - tim > 3600 * 24 * 90)
		{
			regidit.WriteDWORD(REGED, 0);
			unsigned int ti = time(NULL);
			res = regidit.WriteDWORD(STARTTIME, ti);
			res = regidit.WriteDWORD(ENDDATE, ti + 3600 * 24 * 90);
		}
		else
		{
			this->EndDialog(0);
		}
	}
	else
	{
		//ûע���
		regidit.WriteDWORD(REGED, 0);
		unsigned int ti = time(NULL);
		res = regidit.WriteDWORD(STARTTIME, ti);
		res = regidit.WriteDWORD(ENDDATE, ti + 3600 * 24 * 90);
	}


	//����������
	GetSysInfo info;
	CString info1,info2;
	info.GetMemoryInfo(info1, info2);
	CString mechine;
	mechine = info1 + info2;
	DWORD a,b;
	info.GetCpuInfo(info1, info2, a, b);
	mechine = mechine + info1 + info2;

	unsigned char buff[16] = {0};
	char temp[4];
	CString str = mechine + "tianshuai";

	struct tm *local; 
	time_t t; 
	t=time(NULL); 
	local=localtime(&t); 
	char buff1[32];
	sprintf(buff1,"%d",local->tm_year);
	str += buff1;
	sprintf(buff1,"%d",local->tm_mon + 1);
	str += buff1;
//2047 MB2047 MBIntel(R) Pentium(R) CPU G640 @ 2.80GHzIntel Pentium Processortianshuai1141
	md5(( const unsigned char *)str.GetBuffer(0), str.GetLength(), buff);
	for(int i = 0; i<16; i++)
	{
		sprintf(temp, "%02X", buff[i]);
		m_mechine += temp;
	}


	md5(( const unsigned char *)m_mechine.GetBuffer(0), m_mechine.GetLength(), buff);
	
	for(int i = 0; i<16; i++)
	{
		sprintf(temp, "%02X", buff[i]);
		True_md5 += temp;
	}

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}



void CregisterDlg::OnBnClickedButtonRegister()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_regNum = "";
	UpdateData(TRUE);
	if(strcmp(True_md5, m_regNum) != 0)
	{
		AfxMessageBox("ע�������!");
		return;
	}
	regidit.WriteDWORD(REGED, 1);
	unsigned int ti = time(NULL);
	regidit.WriteDWORD(STARTTIME, ti);
	regidit.WriteDWORD(ENDDATE, ti + 3600 * 24 * 90);
	this->EndDialog(0);
}


void CregisterDlg::OnBnClickedButtonCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ���������� 
	if(MessageBox("�Ƿ�Ҫ�˳���","��ʾ",MB_ICONQUESTION | MB_YESNO) != IDYES)
		return;
	this->EndDialog(0);
	ExitProcess(0);
}
