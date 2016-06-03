// mmlToolDlg.h : ͷ�ļ�
//

#pragma once

#include "stdafx.h"
#include "afxcmn.h"


// CmmlToolDlg �Ի���
class CmmlToolDlg : public CDialog
{
// ����
public:
	CmmlToolDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MMLTOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);  //����ENTER ESC��
	afx_msg void OnClose();

public:
	CStatusBar   m_wndStatusBar; //״̬��

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnMenuQuit();
	afx_msg void OnMenuImport();
	afx_msg void OnMenuWorkPath();
	afx_msg void OnNCellInfo();

	// �������ϵ�ListControl
	CListCtrl m_DataList;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnStaticCellbar();
	afx_msg void OnExportNineTable();
	afx_msg void OnExportCellbarTable();
	afx_msg void OnMmlBaowenTable();
	afx_msg void OnIscp();
	afx_msg void OnTopKpi();
	afx_msg void OnAbout();
	afx_msg void OnSelectOrderTable();
	afx_msg void OnRncMmlFile();
	afx_msg void OnRncOut();
};
