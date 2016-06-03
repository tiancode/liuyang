#ifndef MYSTRING_H
#define MYSTRING_H
#include "mess.h"
#include <string>
using namespace std;
#include <vector>


//去掉全部空格
void trimmidspace(char *src);

//去掉左空格
void LTrim(char *strSrc);
//去掉右空格及换行符
void RTrim(char *strSrc);
//去掉两端空格
void Trim(char *strSrc);

#define IS_SPACE(x) ((x)==' '||(x)=='\r'||(x)=='\n'||(x)=='\f'||(x)=='\b'||(x)=='\t')
//去全部空格
char* trimspace(char *p_string);


//找到冒号 返回值指向冒号  如果返回-1 表示没有找到冒号
char* findColon(char *str);

//返回固定指针后的第一个数字  如 System RNCID: 288\n\0;   返回unsigned int 类型 （288）  返回-1表示没找到
unsigned int getFirstNum(char *str);

//获取冒号前面的字符串 out把字符串带走
int findColonPreStr(char *str, char *out);


void removeSpace(char *inout);

//去掉双引号
void removeQuot(char *inout);

//获取=号前面和后面的值  返回后面的指针 为后面提供方便 失败返回-1
char* getEqualSine(char *str, char *preOut, char *behindOut);

//十六进制字符串转十进制数字
int hex_to_dig10(char *);

//找到H'转成十进制字符串
void findHex_to_dig10(char *inout);


//普通字符串匹配算法
int indexOf(string s,string t,int pos);//逐个字符匹配算法，从s串的pos位置开始,返回t出现的首位置

//KMP字符串匹配算法
int KMP(string s,string t,int pos);//KMP算法；模式匹配的改进算法；
void getNext(string t,int* next);//求子字串t的next[]函数之并存入数组中
bool equals(string t,int i,int j);//比较字符串t[0]~t[j-1]同t[i-j]~t[j]是否相等


//**********************************************************************/
//判断一个字符串是否全部用数字组成 大于十位的数字字符串 不是数字
//返回值大于0 是全部用数字组成   返回0，不是全部由数字组成
//**********************************************************************/
int isString(char* str);

//  判读src.txt, 是否是txt  如果返回为真 是
int fileExternName(const char *src, const char *des);



void splitCellIDandName(const char *src, char *dest1, char *dest2);


//在字符串中指定位置插入一个字符 pos >= 0
char* insertChar(char *p, char c, int pos);

//在字符串中指定位置插入一个字符串 pos >= 0
char *insertStr(char *src, char *dst, int pos);


//从分隔符中获得数据
int GetParamFromString(std::string str, std::vector<int>& IntVec, char Delim = ',');
int GetParamFromString(std::string str, std::vector<float>& FloatVec, char Delim = ',');
int GetParamFromString(std::string str, std::vector<unsigned int>& uiIntVec, char Delim = ',');
int GetParamFromString(std::string str, std::vector<std::string>& StringVec, char Delim = ',');

//以左右符号得到括号中的数据ex:[3.1415;0.125][1000;9999]
template<typename T>
int GetParamFromArea(std::string str, std::vector<std::vector<T> >& IntVec, char left = '[', char right = ']', char Delim = ';');


#endif