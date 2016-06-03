#ifndef UNIT_H
#define UNIT_H
#include "mess.h"
#include "stdafx.h"
#include "tinyxml.h"

#include "libxl.h"
using namespace libxl;

//���ClistCtrl
void earseAllListControl(CListCtrl *m_list);


//��ȡxml root��ǩ
TiXmlElement* getXMLRoot(CString filename);


//��ȡĳRNCID ��ĳ��������
int numOfCellN(int rncid, TiXmlElement *ADDTCELLRoot);


//CELLBARͳ������
int numOfCELLBARN(int rncid, TiXmlElement *ADDTCELLRoot);

/************************************************************************/  
//pRootEle ���ڵ�  
//strNodeName ���ҵĽڵ��� 
//destNode ���ҵĽڵ�ָ��
/************************************************************************/  
bool GetNodePointerByName(TiXmlElement* pRootEle, char* strNodeName,TiXmlElement* &destNode);


//�����ű�  filename ��Ҫ������ļ���
int ExportNineData(CString filename);

//����sheet �� Tixml ���һ��sheet
void addOneSheet(Sheet* sheet, TiXmlElement *Tixroot);


//����cellbar��
int ExportCellbar(CString filename);

void BaraddOneSheet(Sheet* sheet, TiXmlElement *Tixroot);



int ExportRncData(CString filename);

#endif