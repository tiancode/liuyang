#ifndef PARSEMMLTHREADFUC_H
#define PARSEMMLTHREADFUC_H
#include "stdafx.h"

void ParseMML(CString fileName);    //解析MML文件

void ParseThreadFunc(LPVOID lpParameter);  //解析MML文件线程




void ParseMML_FOR_RNC(CString fileName);
void ParseThreadFunc_FOR_RNC(LPVOID lpParameter);

#endif