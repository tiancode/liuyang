#ifndef FILE_H
#define FILE_H
#include "mess.h"
#include <vector>
using namespace std;
//����ǰĿ¼�µ�config.txt�ļ�
int readConfig(vector<string> &orders);

//ɾ���ļ���Ŀ¼(�ǿ�) 
bool DeleteDirectory(char* sDirName);


//�ж�һ��Ŀ¼���Ƿ����ĳ�ļ�
int FindFile(char *pFilePath, char* filename);


//ѡ��Ŀ¼�Ի���
int selectPathDlg(CString &WorkPath, HWND *m_hWnd);


BOOL DirectoryList(char* Path, vector<string> &file);

#endif