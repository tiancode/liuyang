// mmlTool.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once


#include "resource.h"		// ������


// CmmlToolApp:
// �йش����ʵ�֣������ mmlTool.cpp
//

class CmmlToolApp : public CWinApp
{
public:
	CmmlToolApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CmmlToolApp theApp;