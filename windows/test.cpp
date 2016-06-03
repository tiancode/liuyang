#include "test.h"
#include "mess.h"
#include "csvFile.h"


void TEST()
{
	CsvFile CSVOperator;
	CSVOperator.LoadCSV("C:\\Users\\WSW\\Desktop\\vc++csvfile\\codefans.net\\c++读写csv文件的类\\config.csv");
	CSVOperator.SetString(1,1, "dfdfdd");
	std::string* pString = CSVOperator.GetString(1,1);
	if (pString)
	{
		std::cout<< pString->c_str() << '\n';
	}
	pString = CSVOperator.GetString(2,4);
	if (pString)
	{
		std::cout<< pString->c_str() << '\n';
	}
	int _int = 0;
	if (CSVOperator.GetInt(3,1,_int))
	{
		std::cout<< _int <<'\n';
	}
	float _float = 0.0f;
	if (CSVOperator.GetFloat(4,1, _float))
	{
		std::cout<< _float<<'\n';
	}

	CSVOperator.SaveCSV();
}