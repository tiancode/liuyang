#pragma once
#include "afxwin.h"


// CregisterDlg �Ի���

class CregisterDlg : public CDialog
{
	DECLARE_DYNAMIC(CregisterDlg)

public:
	CregisterDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CregisterDlg();

// �Ի�������
	enum { IDD = IDD_REGISTER_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	// ��˾ͼ��
	CStatic m_com_picture;
	virtual BOOL OnInitDialog();
	CString m_mechine;
	CString m_regNum;
	CString True_md5;
	afx_msg void OnBnClickedButtonRegister();
	afx_msg void OnBnClickedButtonCancel();
};
