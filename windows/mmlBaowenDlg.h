#pragma once
#include "afxwin.h"


// CmmlBaowenDlg �Ի���

class CmmlBaowenDlg : public CDialog
{
	DECLARE_DYNAMIC(CmmlBaowenDlg)

public:
	CmmlBaowenDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CmmlBaowenDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_MMLBAOWEN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()
public:
	// // listbox �ؼ�
	CListBox m_fileList;

	BOOL ExportAllData(CString FileName);
	afx_msg void OnBnClickedButtonSelectFile();
	afx_msg void OnBnClickedButtonRun();
};
