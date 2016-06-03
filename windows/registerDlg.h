#pragma once
#include "afxwin.h"


// CregisterDlg 对话框

class CregisterDlg : public CDialog
{
	DECLARE_DYNAMIC(CregisterDlg)

public:
	CregisterDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CregisterDlg();

// 对话框数据
	enum { IDD = IDD_REGISTER_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	// 公司图标
	CStatic m_com_picture;
	virtual BOOL OnInitDialog();
	CString m_mechine;
	CString m_regNum;
	CString True_md5;
	afx_msg void OnBnClickedButtonRegister();
	afx_msg void OnBnClickedButtonCancel();
};
