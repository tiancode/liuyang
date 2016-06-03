#pragma once
#include "afxwin.h"
#include "mess.h"

// CmmlAnyExportDlg 对话框

class CmmlAnyExportDlg : public CDialog
{
	DECLARE_DYNAMIC(CmmlAnyExportDlg)

public:
	CmmlAnyExportDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CmmlAnyExportDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_EXPORT_ANY_MML };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()
public:
	// //左
	CListBox m_listOrder;

	CButtonST m_buttonRight;
	CButtonST m_buttonLeft;
	afx_msg void OnBnClickedButtonRight();
	afx_msg void OnBnClickedButtonLeft();
	CListBox m_listExport;
	afx_msg void OnBnClickedButtonExport();
};
