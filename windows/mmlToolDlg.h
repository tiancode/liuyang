// mmlToolDlg.h : 头文件
//

#pragma once

#include "stdafx.h"
#include "afxcmn.h"


// CmmlToolDlg 对话框
class CmmlToolDlg : public CDialog
{
// 构造
public:
	CmmlToolDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MMLTOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);  //屏蔽ENTER ESC键
	afx_msg void OnClose();

public:
	CStatusBar   m_wndStatusBar; //状态栏

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnMenuQuit();
	afx_msg void OnMenuImport();
	afx_msg void OnMenuWorkPath();
	afx_msg void OnNCellInfo();

	// 主窗口上的ListControl
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
