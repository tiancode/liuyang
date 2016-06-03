#include "unit.h"


void earseAllListControl(CListCtrl *m_list)
{
	m_list->DeleteAllItems();//首先清空listview

	int iCount = m_list->GetHeaderCtrl()->GetItemCount();
	for(int i = 0; i < iCount; i++)
	{
		m_list->DeleteColumn(0);
	}
	for(int i = 0; i < iCount; i++)
	{
		m_list->GetHeaderCtrl()->DeleteItem(0);
	}
}


TiXmlElement* getXMLRoot(CString filename) //获取root目录
{
	CString strTran;
	strTran.Format("%s\\%s", WorkPath.GetBuffer(0), filename.GetBuffer(0));
	TiXmlDocument *ADDTCELLURAdoc = new TiXmlDocument(strTran.GetBuffer(0));//ADDTCELLURA.xml
	int nRes = ADDTCELLURAdoc->LoadFile();
	if(nRes == false)
	{
		return NULL;
	}
	TiXmlElement* ADDTCELLURARoot =ADDTCELLURAdoc->RootElement(); 
	return ADDTCELLURARoot;
}


int numOfCellN(int rncid, TiXmlElement *ADDTCELLRoot)
{
	TiXmlElement *temp;
	int n = 0;
	for(TiXmlElement* ADDTCELL = ADDTCELLRoot->FirstChildElement();ADDTCELL;ADDTCELL = ADDTCELL->NextSiblingElement())
	{
		GetNodePointerByName(ADDTCELL, "RNCID", temp);
		if(atoi(temp->GetText()) == rncid)
			n++;
	}
	return n;
}


bool GetNodePointerByName(TiXmlElement* pRootEle, char* strNodeName, TiXmlElement* &destNode)  
{  
	destNode = NULL;
	// if equal root node then return  
/*	if (0 == strcmp(strNodeName, pRootEle->Value()))  
	{  
		destNode = pRootEle;  
		return true;  
	}  */

	TiXmlElement* pEle = pRootEle;    
	for (pEle = pRootEle->FirstChildElement(); pEle; pEle = pEle->NextSiblingElement())    
	{    
		// recursive find sub node return node pointer    
		if (0 != strcmp(pEle->Value(), strNodeName))  
		{  
			//GetNodePointerByName(pEle,strNodeName,destNode);
			continue;
		}  
		else  
		{  
			destNode = pEle;  
		//	printf("destination node name: %s\n", pEle->Value());  
			return true;  
		}  
	}    
	return false;  
}  

int numOfCELLBARN(int rncid, TiXmlElement *ADDTCELLRoot)
{
	TiXmlElement *temp;
	int n = 0;
	for(TiXmlElement* ADDTCELL = ADDTCELLRoot->FirstChildElement();ADDTCELL;ADDTCELL = ADDTCELL->NextSiblingElement())
	{
		GetNodePointerByName(ADDTCELL, "CELLRESERVEDFOROPERATORUSE", temp);
		if(strcmp(temp->GetText(), "NOT_RESERVED") == 0)
		{
			continue;
		}
		GetNodePointerByName(ADDTCELL, "RNCID", temp);
		if(atoi(temp->GetText()) == rncid)
			n++;
	}
	return n;
}


void addOneSheet(Sheet* sheet, TiXmlElement *Tixroot)
{
	TiXmlElement* ADDTCELL = Tixroot->FirstChildElement();
	int loop = 0;
	int nRow = 1;
	int nCol;
	for(; ADDTCELL;ADDTCELL = ADDTCELL->NextSiblingElement())
	{
		nCol = 0;
		for(TiXmlElement *elem = ADDTCELL->FirstChildElement(); elem; elem = elem->NextSiblingElement())
		{
			if(loop == 10 )
			{
				sheet->writeStr(0, nCol, _T(elem->Value()));
			}
			char *str = (char*)elem->GetText();
			removeQuot(str);
			int isNum = isString(str);
			if(isNum)
			{
				sheet->writeNum(nRow, nCol, atoi(str));
			}
			else
			{
				sheet->writeStr(nRow, nCol, _T(str));
			}
			nCol++;
		}
		nRow++;
		loop++;
	}
}


int ExportNineData(CString filename)
{
	Book* book = xlCreateBook();
	if(!book)
		return 0;

	TiXmlElement *ADDTCELLRoot = getXMLRoot("ADDTCELL.xml");
	TiXmlElement *ADDTCELLNLTECELLSELRESELRoot = getXMLRoot("ADDTCELLNLTECELLSELRESEL.xml");
	TiXmlElement *ADDTCELLSELRESELRoot = getXMLRoot("ADDTCELLSELRESEL.xml");
	TiXmlElement *ADDTGSMCELLRoot = getXMLRoot("ADDTGSMCELL.xml");
	TiXmlElement *ADDTGSMNCELLRoot = getXMLRoot("ADDTGSMNCELL.xml");
	TiXmlElement *ADDTLTECELLRoot = getXMLRoot("ADDTLTECELL.xml");
	TiXmlElement *ADDTLTENCELLRoot = getXMLRoot("ADDTLTENCELL.xml");
	TiXmlElement *ADDTNCELLRoot = getXMLRoot("ADDTNCELL.xml");
	TiXmlElement *ADDTNRNCCELLRoot = getXMLRoot("ADDTNRNCCELL.xml");


	Sheet* sheetTCELL = book->addSheet(_T("ADDTCELL"));
	if(!sheetTCELL)
		return 0;
	addOneSheet(sheetTCELL, ADDTCELLRoot);
	delete ADDTCELLRoot->GetDocument();

	Sheet* sheetTNCELL = book->addSheet(_T("ADDTNCELL"));
	if(!sheetTNCELL)
		return 0;
	addOneSheet(sheetTNCELL, ADDTNCELLRoot);
	delete ADDTNCELLRoot->GetDocument();

	Sheet* sheetTNRNCCELL = book->addSheet(_T("ADDTNRNCCELL"));
	if(!sheetTNRNCCELL)
		return 0;
	addOneSheet(sheetTNRNCCELL, ADDTNRNCCELLRoot);
	delete ADDTNRNCCELLRoot->GetDocument();

	Sheet* sheetTCELLSELRESEL = book->addSheet(_T("ADDTCELLSELRESEL"));
	if(!sheetTCELLSELRESEL)
		return 0;
	addOneSheet(sheetTCELLSELRESEL, ADDTCELLSELRESELRoot);
	delete ADDTCELLSELRESELRoot->GetDocument();

	Sheet* sheetTCELLNLTECELLSELRESEL = book->addSheet(_T("ADDTCELLNLTECELLSELRESEL"));
	if(!sheetTCELLNLTECELLSELRESEL)
		return 0;
	addOneSheet(sheetTCELLNLTECELLSELRESEL, ADDTCELLNLTECELLSELRESELRoot);
	delete ADDTCELLNLTECELLSELRESELRoot->GetDocument();

	Sheet* sheetTGSMCELL = book->addSheet(_T("ADDTGSMCELL"));
	if(!sheetTGSMCELL)
		return 0;
	addOneSheet(sheetTGSMCELL, ADDTGSMCELLRoot);
	delete ADDTGSMCELLRoot->GetDocument();

	Sheet* sheetTGSMNCELL = book->addSheet(_T("ADDTGSMNCELL"));
	if(!sheetTGSMNCELL)
		return 0;
	addOneSheet(sheetTGSMNCELL, ADDTGSMNCELLRoot);
	delete ADDTGSMNCELLRoot->GetDocument();

	Sheet* sheetTLTECELL = book->addSheet(_T("ADDTLTECELL"));
	if(!sheetTLTECELL)
		return 0;
	addOneSheet(sheetTLTECELL, ADDTLTECELLRoot);
	delete ADDTLTECELLRoot->GetDocument();

	Sheet* sheetTLTENCELL = book->addSheet(_T("ADDTLTENCELL"));
	if(!sheetTLTENCELL)
		return 0;
	addOneSheet(sheetTLTENCELL, ADDTLTENCELLRoot);
	delete ADDTLTENCELLRoot->GetDocument();


	if(book->save(_T(filename.GetBuffer(0)) )) 
	{
		return 1;
	}
	else
	{
		return 0;
	}

	book->release();
}


void BaraddOneSheet(Sheet* sheet, TiXmlElement *Tixroot)
{
	TiXmlElement* ADDTCELL = Tixroot->FirstChildElement();
	int loop = 0;
	int nRow = 1;
	int nCol;
	for(; ADDTCELL;ADDTCELL = ADDTCELL->NextSiblingElement())
	{
		if(strcmp(ADDTCELL->FirstChildElement()->NextSiblingElement()->NextSiblingElement()->GetText(), "NOT_RESERVED") == 0)
		{
			continue;
		}

		nCol = 0;
		for(TiXmlElement *elem = ADDTCELL->FirstChildElement(); elem; elem = elem->NextSiblingElement())
		{
			if(loop <= 65535 )
			{
				sheet->writeStr(0, nCol, _T(elem->Value()));
			}
			char *str = (char*)elem->GetText();
			removeQuot(str);
			int isNum = isString(str);
			if(isNum)
			{
				sheet->writeNum(nRow, nCol, atoi(str));
			}
			else
			{
				sheet->writeStr(nRow, nCol, _T(str));
			}
			nCol++;
		}
		nRow++;
		loop++;
	}
}
int ExportCellbar(CString filename)
{
	Book* book = xlCreateBook();
	if(!book)
		return 0;

	TiXmlElement *ADDTCELLACCESSSTRICTRoot = getXMLRoot("ADDTCELLACCESSSTRICT.xml");

	Sheet* sheetTCELLACCESSSTRICT = book->addSheet(_T("ADDTCELLACCESSSTRICT"));
	if(!sheetTCELLACCESSSTRICT)
		return 0;
	BaraddOneSheet(sheetTCELLACCESSSTRICT, ADDTCELLACCESSSTRICTRoot);

	delete ADDTCELLACCESSSTRICTRoot->GetDocument();

	if(book->save(_T(filename.GetBuffer(0)) )) 
	{
		return 1;
	}
	else
	{
		return 0;
	}

	book->release();
}



#define WRITESTR(r, c, name)  sheet->writeStr(r,c , name, FormatHead);

#define AABBCCDD(col, com)  				else if(strcmp(temp->GetText(), com) == 0)      \
											{                                                  \
												bool n = GetNodePointerByName(ADDTCARRIER, "UARFCN", temp);  \
												if(n == true)               \
												{	       \
													sheet->writeNum(row, col, atoi(temp->GetText()));   \
													zaipingshu++;    \
												}     \
												else    \
													sheet->writeStr(row, col, "NULL");     \
											}   

#define DDCCBBAA(col, com)                				else if(strcmp(temp->GetText(), com) == 0)   \
														{    \
															int num = sheet->readNum(row, col);    \
															sheet->writeNum(row, col, num,FormatHIGH);   \
															Hzaiboshu++;    \
														}     

int ExportRncData(CString filename)
{
	Book* book = xlCreateBook();
	if(!book)
		return 0;

	Font* boldFont = book->addFont();
	boldFont->setBold();

	Format* FormatHIGH = book->addFormat();
	FormatHIGH->setBorder(BORDERSTYLE_THIN);
	FormatHIGH->setFont(boldFont);
	FormatHIGH->setFillPattern(FILLPATTERN_SOLID);
	FormatHIGH->setPatternForegroundColor(COLOR_RED);

	Format* FormatHead = book->addFormat();
	FormatHead->setBorder(BORDERSTYLE_THIN);
	FormatHead->setFont(boldFont);
	FormatHead->setFillPattern(FILLPATTERN_SOLID);
	FormatHead->setPatternForegroundColor(COLOR_YELLOW);

	Sheet *sheet = book->addSheet("RNC_INFO");
	if(!sheet)
		return 0;
	WRITESTR(0, 0, "RNCID");
	WRITESTR(0, 1, "CELLID");
	WRITESTR(0, 2, "CELLNAME");
	WRITESTR(0 ,3, "载频数");
	WRITESTR(0, 4, "R4载波数");
	WRITESTR(0, 5, "H载波数");
	WRITESTR(0, 6, "LAC");
	WRITESTR(0, 7, "CELLPARAID");
	WRITESTR(0, 8, "PRIMARY");
	WRITESTR(0, 9, "SECONDARY_1");
	WRITESTR(0 ,10, "SECONDARY_2");
	WRITESTR(0, 11, "SECONDARY_3");
	WRITESTR(0, 12, "SECONDARY_4");
	WRITESTR(0 ,13, "SECONDARY_5");
	WRITESTR(0, 14, "SECONDARY_6");
	WRITESTR(0, 15, "SECONDARY_7");
	WRITESTR(0, 16, "SECONDARY_8");
	WRITESTR(0, 17, "SECONDARY_9");
	WRITESTR(0, 18, "SECONDARY_10");
	WRITESTR(0, 19, "SECONDARY_11");
	WRITESTR(0, 20, "SECONDARY_12");
	WRITESTR(0, 21, "SECONDARY_13");
	WRITESTR(0, 22, "SECONDARY_14");

	TiXmlElement *ADDTCELLRoot = getXMLRoot("ADDTCELL.xml");
	TiXmlElement *ADDTCARRIERRoot = getXMLRoot("ADDTCARRIER.xml");
	TiXmlElement *ACTHSDPATCARRIERRoot = getXMLRoot("ACTHSDPATCARRIER.xml");

	TiXmlElement *RNCID;
	TiXmlElement *CELLID;
	int row = 1;
	TiXmlElement *temp;
	char buff[256];

	for(TiXmlElement* ADDTCELL = ADDTCELLRoot->FirstChildElement(); ADDTCELL; ADDTCELL = ADDTCELL->NextSiblingElement())
	{
		int zaipingshu = 0;
		GetNodePointerByName(ADDTCELL, "RNCID", RNCID);
		sheet->writeNum(row, 0, atoi(RNCID->GetText()) );
		GetNodePointerByName(ADDTCELL, "CELLID", CELLID);
		sheet->writeNum(row, 1, atoi(CELLID->GetText()));
		GetNodePointerByName(ADDTCELL, "CELLNAME", temp);
		strcpy(buff, temp->GetText());
		removeQuot(buff);
		sheet->writeStr(row, 2, buff);

		GetNodePointerByName(ADDTCELL, "LAC", temp);
		sheet->writeNum(row, 6, atoi(temp->GetText()));
		GetNodePointerByName(ADDTCELL, "CELLPARAID", temp);
		sheet->writeNum(row, 7, atoi(temp->GetText()));

		for(TiXmlElement* ADDTCARRIER = ADDTCARRIERRoot->FirstChildElement(); ADDTCARRIER; ADDTCARRIER = ADDTCARRIER->NextSiblingElement())
		{
			GetNodePointerByName(ADDTCARRIER, "CELLID", temp);
			if(strcmp(CELLID->GetText(), temp->GetText()) == 0)
			{
				GetNodePointerByName(ADDTCARRIER, "CARRIERINDEX", temp);

				if(strcmp(temp->GetText(), "PRIMARY") == 0)
				{
					bool n = GetNodePointerByName(ADDTCARRIER, "UARFCN", temp);
					if(n == true)
					{
						sheet->writeNum(row, 8, atoi(temp->GetText()));
						zaipingshu++;
					}
					else
						sheet->writeStr(row, 8, "NULL");
				}
				AABBCCDD(9, "SECONDARY_1")
				AABBCCDD(10, "SECONDARY_2")
				AABBCCDD(11, "SECONDARY_3")
				AABBCCDD(12, "SECONDARY_4")
				AABBCCDD(13, "SECONDARY_5")
				AABBCCDD(14, "SECONDARY_6")
				AABBCCDD(15, "SECONDARY_7")
				AABBCCDD(16, "SECONDARY_8")
				AABBCCDD(17, "SECONDARY_9")
				AABBCCDD(18, "SECONDARY_10")
				AABBCCDD(19, "SECONDARY_11")
				AABBCCDD(20, "SECONDARY_12")
				AABBCCDD(21, "SECONDARY_13")
				AABBCCDD(22, "SECONDARY_14")
			}
		}

		int Hzaiboshu = 0;
		for(TiXmlElement* ACTHSDPATCARRIER = ACTHSDPATCARRIERRoot->FirstChildElement(); ACTHSDPATCARRIER; ACTHSDPATCARRIER = ACTHSDPATCARRIER->NextSiblingElement())
		{
			GetNodePointerByName(ACTHSDPATCARRIER, "CELLID", temp);
			if(strcmp(CELLID->GetText(), temp->GetText()) == 0)
			{
				GetNodePointerByName(ACTHSDPATCARRIER, "CARRIERINDEX", temp);
				if(strcmp(temp->GetText(), "PRIMARY") == 0)
				{
					int num = sheet->readNum(row, 8);
					sheet->writeNum(row, 8, num, FormatHIGH);
					Hzaiboshu++;
				}
				DDCCBBAA(9, "SECONDARY_1")
				DDCCBBAA(10, "SECONDARY_2")
				DDCCBBAA(11, "SECONDARY_3")
				DDCCBBAA(12, "SECONDARY_4")
				DDCCBBAA(13, "SECONDARY_5")
				DDCCBBAA(14, "SECONDARY_6")
				DDCCBBAA(15, "SECONDARY_7")
				DDCCBBAA(16, "SECONDARY_8")
				DDCCBBAA(17, "SECONDARY_9")
				DDCCBBAA(18, "SECONDARY_10")
				DDCCBBAA(19, "SECONDARY_11")
				DDCCBBAA(20, "SECONDARY_12")
				DDCCBBAA(21, "SECONDARY_13")
				DDCCBBAA(22, "SECONDARY_14")
			}
		}
		
		sheet->writeNum(row, 3, zaipingshu);
		sheet->writeNum(row, 4, zaipingshu - Hzaiboshu);
		sheet->writeNum(row, 5, Hzaiboshu);
		
		row++;
	}

	delete ADDTCELLRoot->GetDocument();
	delete ADDTCARRIERRoot->GetDocument();
	delete ACTHSDPATCARRIERRoot->GetDocument();

	if(book->save(_T(filename.GetBuffer(0)) )) 
	{
		return 1;
	}
	else
	{
		return 0;
	}

	book->release();
}
