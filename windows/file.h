#ifndef FILE_H
#define FILE_H
#include "mess.h"
#include <vector>
using namespace std;
//读当前目录下的config.txt文件
int readConfig(vector<string> &orders);

//删除文件夹目录(非空) 
bool DeleteDirectory(char* sDirName);


//判断一个目录下是否存在某文件
int FindFile(char *pFilePath, char* filename);


//选择目录对话框
int selectPathDlg(CString &WorkPath, HWND *m_hWnd);


BOOL DirectoryList(char* Path, vector<string> &file);

#endif