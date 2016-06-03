#ifndef MYSTRING_H
#define MYSTRING_H
#include "mess.h"
#include <string>
using namespace std;
#include <vector>


//ȥ��ȫ���ո�
void trimmidspace(char *src);

//ȥ����ո�
void LTrim(char *strSrc);
//ȥ���ҿո񼰻��з�
void RTrim(char *strSrc);
//ȥ�����˿ո�
void Trim(char *strSrc);

#define IS_SPACE(x) ((x)==' '||(x)=='\r'||(x)=='\n'||(x)=='\f'||(x)=='\b'||(x)=='\t')
//ȥȫ���ո�
char* trimspace(char *p_string);


//�ҵ�ð�� ����ֵָ��ð��  �������-1 ��ʾû���ҵ�ð��
char* findColon(char *str);

//���ع̶�ָ���ĵ�һ������  �� System RNCID: 288\n\0;   ����unsigned int ���� ��288��  ����-1��ʾû�ҵ�
unsigned int getFirstNum(char *str);

//��ȡð��ǰ����ַ��� out���ַ�������
int findColonPreStr(char *str, char *out);


void removeSpace(char *inout);

//ȥ��˫����
void removeQuot(char *inout);

//��ȡ=��ǰ��ͺ����ֵ  ���غ����ָ�� Ϊ�����ṩ���� ʧ�ܷ���-1
char* getEqualSine(char *str, char *preOut, char *behindOut);

//ʮ�������ַ���תʮ��������
int hex_to_dig10(char *);

//�ҵ�H'ת��ʮ�����ַ���
void findHex_to_dig10(char *inout);


//��ͨ�ַ���ƥ���㷨
int indexOf(string s,string t,int pos);//����ַ�ƥ���㷨����s����posλ�ÿ�ʼ,����t���ֵ���λ��

//KMP�ַ���ƥ���㷨
int KMP(string s,string t,int pos);//KMP�㷨��ģʽƥ��ĸĽ��㷨��
void getNext(string t,int* next);//�����ִ�t��next[]����֮������������
bool equals(string t,int i,int j);//�Ƚ��ַ���t[0]~t[j-1]ͬt[i-j]~t[j]�Ƿ����


//**********************************************************************/
//�ж�һ���ַ����Ƿ�ȫ����������� ����ʮλ�������ַ��� ��������
//����ֵ����0 ��ȫ�����������   ����0������ȫ�����������
//**********************************************************************/
int isString(char* str);

//  �ж�src.txt, �Ƿ���txt  �������Ϊ�� ��
int fileExternName(const char *src, const char *des);



void splitCellIDandName(const char *src, char *dest1, char *dest2);


//���ַ�����ָ��λ�ò���һ���ַ� pos >= 0
char* insertChar(char *p, char c, int pos);

//���ַ�����ָ��λ�ò���һ���ַ��� pos >= 0
char *insertStr(char *src, char *dst, int pos);


//�ӷָ����л������
int GetParamFromString(std::string str, std::vector<int>& IntVec, char Delim = ',');
int GetParamFromString(std::string str, std::vector<float>& FloatVec, char Delim = ',');
int GetParamFromString(std::string str, std::vector<unsigned int>& uiIntVec, char Delim = ',');
int GetParamFromString(std::string str, std::vector<std::string>& StringVec, char Delim = ',');

//�����ҷ��ŵõ������е�����ex:[3.1415;0.125][1000;9999]
template<typename T>
int GetParamFromArea(std::string str, std::vector<std::vector<T> >& IntVec, char left = '[', char right = ']', char Delim = ';');


#endif