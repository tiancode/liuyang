#include "mystring.h"
#include "file.h"
#include "stdafx.h"

int readConfig(vector<string> &orders)
{
	FILE *fd = fopen("config.txt", "r");
	if(fd == NULL)
	{
		AfxMessageBox("�����ļ������ڣ�");
		return 0;
	}

	char buff[128];
	while( fgets(buff, 128, fd) != NULL )
	{
		char *p = buff;
		if(*p == '/' || *p == ' ' || *p == '\n')
		{
			continue;
		}
		Trim(buff);
		trimmidspace(buff);
		orders.push_back(buff);
	}

	fclose(fd);
	return 1;
}

//ɾ���ļ���Ŀ¼(�ǿ�) 
bool DeleteDirectory(char* sDirName)  
{  
	CFileFind tempFind;  
	char sTempFileFind[200] ; 

	sprintf(sTempFileFind,"%s//*.*",sDirName);  
	BOOL IsFinded = tempFind.FindFile(sTempFileFind);  
	while (IsFinded)  
	{  
		IsFinded = tempFind.FindNextFile();  

		if (!tempFind.IsDots())  
		{  
			char sFoundFileName[200];  
			strcpy(sFoundFileName,tempFind.GetFileName().GetBuffer(200));  

			if (tempFind.IsDirectory())  
			{  
				char sTempDir[200];  
				sprintf(sTempDir,"%s//%s",sDirName,sFoundFileName);  
				DeleteDirectory(sTempDir);  
			}  
			else  
			{  
				char sTempFileName[200];  
				sprintf(sTempFileName,"%s//%s",sDirName,sFoundFileName);  
				DeleteFile(sTempFileName);  
			}  
		}  
	}  
	tempFind.Close();  
	if(!RemoveDirectory(sDirName))  
	{  
		return FALSE;  
	}  
	return TRUE;  
} 


int FindFile(char *pFilePath, char *filename)
{
	CString str;
	str.Format("%s\\%s", pFilePath, filename);
	CFileFind ff;
	if(ff.FindFile(str))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


int selectPathDlg(CString &WorkPath, HWND *m_hWnd)
{
	char szPath[MAX_PATH];     //���ѡ���Ŀ¼·�� 
	CString str;

	ZeroMemory(szPath, sizeof(szPath));   

	BROWSEINFO bi;   
	bi.hwndOwner = *m_hWnd;   
	bi.pidlRoot = NULL;   
	bi.pszDisplayName = szPath;   
	bi.lpszTitle = "��ѡ�����Ŀ¼��";   
	bi.ulFlags = 0;   
	bi.lpfn = NULL;   
	bi.lParam = 0;   
	bi.iImage = 0;   
	//����ѡ��Ŀ¼�Ի���
	LPITEMIDLIST lp = SHBrowseForFolder(&bi);   

	if(lp && SHGetPathFromIDList(lp, szPath))   
	{
		WorkPath = szPath;
	}
	else   
	{
		return 0;
	}
}

BOOL  DirectoryList(char* Path, vector<string> &file)
{
	WIN32_FIND_DATA FindData;
	HANDLE hError;

	char FilePathName[256];
		// ����·��
	char FullPathName[256];
	strcpy(FilePathName, Path);
	strcat(FilePathName, "\\*.*");
	printf("%s\n", FilePathName);
	hError = FindFirstFile(FilePathName, &FindData);
	if (hError == INVALID_HANDLE_VALUE)
	{
			printf("����ʧ��!");
			return 0;
	}
	while(::FindNextFile(hError, &FindData))
	{
		// ����.��..
		if (strcmp(FindData.cFileName, ".") == 0
			|| strcmp(FindData.cFileName, "..") == 0 )
		{
			continue;
		}

		if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
				//printf("<Dir>");
				//DirectoryList(FullPathName);
		}
		else
		{
			// ��������·��
			sprintf(FullPathName, "%s\\%s", Path,FindData.cFileName);

			// ����������ļ�
			//printf("\n%d  %s  ", FileCount, FullPathName);
			file.push_back(FullPathName);
		}
	}
	return 0;
}
