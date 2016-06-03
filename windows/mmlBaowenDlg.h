#pragma once
#include "afxwin.h"


// CmmlBaowenDlg 对话框

class CmmlBaowenDlg : public CDialog
{
	DECLARE_DYNAMIC(CmmlBaowenDlg)

public:
	CmmlBaowenDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CmmlBaowenDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_MMLBAOWEN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()
public:
	// // listbox 控件
	CListBox m_fileList;

	BOOL ExportAllData(CString FileName);
	afx_msg void OnBnClickedButtonSelectFile();
	afx_msg void OnBnClickedButtonRun();
};
