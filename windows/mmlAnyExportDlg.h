#pragma once
#include "afxwin.h"
#include "mess.h"

// CmmlAnyExportDlg �Ի���

class CmmlAnyExportDlg : public CDialog
{
	DECLARE_DYNAMIC(CmmlAnyExportDlg)

public:
	CmmlAnyExportDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CmmlAnyExportDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_EXPORT_ANY_MML };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()
public:
	// //��
	CListBox m_listOrder;

	CButtonST m_buttonRight;
	CButtonST m_buttonLeft;
	afx_msg void OnBnClickedButtonRight();
	afx_msg void OnBnClickedButtonLeft();
	CListBox m_listExport;
	afx_msg void OnBnClickedButtonExport();
};
