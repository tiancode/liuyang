#ifndef UNIT_H
#define UNIT_H
#include "mess.h"
#include "stdafx.h"
#include "tinyxml.h"

#include "libxl.h"
using namespace libxl;

//清空ClistCtrl
void earseAllListControl(CListCtrl *m_list);


//获取xml root标签
TiXmlElement* getXMLRoot(CString filename);


//获取某RNCID 下某命令行数
int numOfCellN(int rncid, TiXmlElement *ADDTCELLRoot);


//CELLBAR统计行数
int numOfCELLBARN(int rncid, TiXmlElement *ADDTCELLRoot);

/************************************************************************/  
//pRootEle 根节点  
//strNodeName 查找的节点名 
//destNode 查找的节点指针
/************************************************************************/  
bool GetNodePointerByName(TiXmlElement* pRootEle, char* strNodeName,TiXmlElement* &destNode);


//导出九表  filename 是要保存的文件名
int ExportNineData(CString filename);

//传入sheet 和 Tixml 填充一个sheet
void addOneSheet(Sheet* sheet, TiXmlElement *Tixroot);


//导出cellbar表
int ExportCellbar(CString filename);

void BaraddOneSheet(Sheet* sheet, TiXmlElement *Tixroot);



int ExportRncData(CString filename);

#endif