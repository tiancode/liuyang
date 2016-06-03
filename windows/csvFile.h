#ifndef CSVFILE_H
#define CSVFILE_H

#include <map>
#include <vector>
#include <queue>
#include <set>
#include <string>
#include <list>

/********************************************************************************
*																				*
*						读写CSV文件 以1 ， 1 为开始					     	*
*																				*
********************************************************************************/
class CsvFile
{

public:
	CsvFile(){};
	~CsvFile(){};
	CsvFile(const char* path);


	bool LoadCSV(const char* path);
	bool SaveCSV(const char* path = NULL);

	bool GetInt(unsigned int uiLine, unsigned int uiCol, int& iValue);
	bool GetFloat(unsigned int uiLine, unsigned int uiCol, float& fValue);
	std::string* GetString(unsigned uiLine, unsigned int uiCol);
	bool SetNumber(unsigned int uiLine, unsigned int uiCol, int iValue);
	bool SetNumber(unsigned int uiLine, unsigned int uiCol, float fValue);
	bool SetString(unsigned uiLine, unsigned uiCol, const char* pStr);
	std::map<unsigned int, std::map<unsigned int, std::string> >& GetCSVMap(){return m_StringKeyMap;}
protected:
	std::string m_CSVName;
	std::map<unsigned int, std::map<unsigned int, std::string> > m_StringKeyMap;

};


#endif