#include "mystring.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

void trimmidspace(char *src)
{
	char *pTmp = src;  

	while (*src != '\0')   
	{  
		if (*src != ' ')  
		{  
			*pTmp++ = *src;  
		}  
		++src;  
	}  
	*pTmp = '\0'; 
}


void LTrim(char * strSrc)
{
	char       * p_buf;
	long          i;

	if( strSrc == NULL )
		return;

	i = 0;
	while( strSrc[ i ] == 0x20 )
		i++;

	if( strSrc[ i ] == 0x00 ) {
		strSrc[ 0 ] = 0x00;
		return;
	}

	p_buf = ( char * )malloc( strlen( &strSrc[ i ] ) + 1 );
	strcpy( p_buf, &strSrc[ i ] );
	strcpy( strSrc, p_buf );

	free( p_buf ); 
	return;
}
void RTrim(char * strSrc)
{
	char * p;

	if( strSrc == NULL )
		return;

	if( strSrc[ 0 ] == 0x00 )
		return;

	p = strSrc + strlen( strSrc );
	while( ( *( p - 1 ) ) == 0x20 || ( *( p - 1 ) ) == '\n')
		p--;

	*p = '\0';

	return;
}

void Trim(char * strSrc)
{
	LTrim( strSrc );
	RTrim( strSrc );
	return;
}

char* trimspace(char *p_string)
{
	char *v_tail=NULL, *v_head=NULL; 

	for( v_tail = p_string + strlen(p_string)-1; v_tail >= p_string; v_tail--) 
		if( ! IS_SPACE(*v_tail) ) 
			break;
	v_tail[1] = 0; 

	for( v_head = p_string; v_head <= v_tail; v_head++) 
		if( ! IS_SPACE(*v_head) )
			break;

	if( v_head != p_string ) 
		memcpy( p_string, v_head, (v_tail-v_head+2 )*sizeof(char) );

	return p_string;
}


char* findColon(char *str)
{
	char *p = str;
	while(*p != '\0')
	{
		if(*p == ':')
			return p;
		p++;
	}
	return (char*)-1;
}

unsigned int getFirstNum(char *str)
{
	char *p = str;
	int num = 0;
	while(*p != '\0')
	{
		if(*p >= '0' && *p <= '9')
		{
			num = num * 10 + (*p - '0');
			if(*(p + 1) < '0' || *(p + 1) > '9')
			{
				return num;
			}
		}
		p++;
	}
	return -1;
}

int findColonPreStr(char *str, char *out)
{
	char *p = str;
	char *colon = findColon(p);
	if((int)colon == -1)
		return -1;
	int n = colon - p;
	while(n != 0)
	{
		out[n - 1] = p[n - 1];
		n--;
	}
}
void removeSpace(char *inout)
{
	char *p = inout;
	while(*p != ' ')
	{
		p++;
	}
	while(*p != NULL)
	{
		*p = *(p + 1);
		p++;
	}
}

void removeQuot(char *inout)
{
	char *p = inout;
	if(*p != '\"')
		return;
	else
	{
		while(*p != '\0')
		{
			*p = *(p+1);
			p++;
		}
		p = p -2;
		*p = '\0';
	}
}

char* getEqualSine(char *str, char *preOut, char *behindOut)
{
	char *p = str;
	while(*p != '\0')
	{
		if(*p == '=')
		{
			char *q = p;
			p--;
			while( (*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z') || (*p >= '0' && *p <= '9') )
			{
				p--;
			}
			int n = q - p -1;

			for(int i = 0; i < n; i++)
			{
				preOut[i] = *(p + 1);
				p++;
			}

			char *p = q;
			p++;
			while(*p != ',' && *p != ';')
			{
				p++;
			}
			n = p - q -1;
			for(int i = 0; i < n; i++)
			{
				behindOut[i] = *(q + 1);
				q++;
			}
			return q;
		}
		p++;
	}

	return (char*)-1;
}

static int trans_char_dig(char c)
{
	if(c >= 48 && c <= 57)
		return c - 48;
	else if(c >= 65 && c <= 70)
		return c - 55;
	else if(c >= 97 && c <= 102)
		return c - 87;
}

int hex_to_dig10(char *he)
{
	int i = 0, n,x;
	int sum = 0;
	while(he[i] != 0)
	{
		i++;
	}
	n = i;
	while(i > 0)
	{
		x = trans_char_dig(he[n - i]);
		sum = x * pow(16.0, i -1) + sum;
		i--;
	}
	return sum;
}

void findHex_to_dig10(char *inout)
{
	char *p = inout;
	if(*p == 'H' && *(p +1) == '\'')
	{
		int num = hex_to_dig10(p + 2);
		char buff[8];
		sprintf(buff, "%d", num);
		strcpy(inout, buff);
	}
	else
	{
		return;
	}
}


bool equals(string t,int i,int j)  //�Ƚ��ַ���t[0]~t[j-1]ͬt[i-j]~t[j]�Ƿ����
{
	int temp = i-j;

	for(int k = 0; k < j; k++,temp++)//if((j-1)==(2*j-i)){//���������ͬ
	{
		if(t[k]!=t[temp])//����в���ͬ�ģ�����false
		{
			return false;
		}
	}
	return true;//���е����˵���ַ���t[0]~t[j-1]ͬt[i-j]~t[j]���
}

void getNext(string t,int* next) //�����ִ�t��next[]����֮������������
{
	int temp = 0;
	int zm = 0;
	for(int i = 0; i < t.size();i++)//��0��ʼѭ��
	{
		temp = i-1;
		if(i == 0)//��һ����ʱ��Ϊ-1
		{
			next[i] = -1;
		}
		else if(temp > 0)
		{
			for(int j = temp;j>0;j--)
			{
				if(equals(t,i,j))
				{
					next[i] = j;
					break;
				}else{
					next[i] = 0;//��Ϊ�������Ϊ0
					continue;
				}

			}
		}
		else
		{
			next[i] = 0;//�������Ϊ0
		}
	}
}

int KMP(string s,string t,int pos)//KMP�㷨��ģʽƥ��ĸĽ��㷨��
{
	if(t.empty())//t�ִ���ҪΪ��
	{
		return -1;
	}
	int* next = new int[t.size()];
	int pause = 0;//�����Ƿ���ͣ��
	getNext(t,next);
	int i = 0,j = 0;
	while(i!=s.size())
	{
		if(s[i]==t[j])
		{
			i++;
			j++;
		}
		else
		{
			if(pause==1)//�������Ҫ��ͣ
			{
				pause=0;
				i++;
			}
			else//�����Ҫ��ͣ
			{
				pause=1;
			}
			j = next[j];
			if(j==-1)
			{
				j=0;
			}
		}
		if(j==t.size())
		{
			return i-t.size();
		}
	}
	return -1;
}

int indexOf(string s,string t,int pos)//����ַ�ƥ���㷨����s����posλ�ÿ�ʼ,����t���ֵ���λ��
{
	if(t.empty())//�ִ���ҪΪ��
	{
		return -1;
	}
	int i = pos;
	int temp = 0;
	for(;i<s.size();i++)
	{
		temp = i;
		for(int j = 0;j<t.size();j++)
		{
			if(s[temp] == t[j])//������,�ͼ���ѭ����ȥ
			{
				temp++;
				if(j == (t.size()-1))
				{
					return i;//���س��ֵ���λ��
				}
			}
			else//�����
			{
				break;
			}
		}
	}
}


int isString(char* str)
{

	int n = 0;
	while(*str != '\0')
	{
		if(*str >= '0' && *str <= '9')
		{
			n++;
		}
		else
			return 0;

		str++;
	}
	if(n > 10)
		return 0;

	return 1;
}

int fileExternName(const char *src, const char *des)
{
	char *p = (char*)src;
	while(*p != NULL)
		p++;
	while(*p != '.')
		p--;

	p++;

	int res = strcmp(p, des);
	if(res == 0)
		return 1;
	else
		return 0;
}

//С������=��ֱ��14��RNC290����վ, С����ʶ=64021
void splitCellIDandName(const char *src, char *dest1, char *dest2)
{
	char *p = (char*)src;
	while(*p != '=')
	{
		p++;
	}
	while( *p != ',' )
	{
		p++;
	}
	*p = NULL;
	strcpy(dest1, src + 9);
	p++;
	while(*p != '=')
	{
		p++;
	}
	strcpy(dest2, ++p);
}

char* insertChar(char *src, char c, int pos)
{
	int len = strlen(src);
	if(pos > len)
		return src;
	int i;
	for (i = len - 1; i >= pos; i--)
	{
		src[i + 1] = src[i];
	}
	src[pos] = c;
	src[len + 1] = '\0';

	return src;
}

char *insertStr(char *src, char *dst, int pos)
{
	int len_src = strlen(src);
	if(pos > len_src)
		return src;
	int len_dst = strlen(dst);

	int i, j;
	for(i = len_src - 1; i >= pos; i--)
	{
		src[i + len_dst] = src[i];
	}
	for(j = 0; j < len_dst; j++)
	{
		src[++i] = dst[j];
	}
	src[len_src + len_dst] = '\0';

	return src;
}


// csv ֧��
//�ӷָ����л������
int GetParamFromString(std::string str, std::vector<int>& IntVec, char Delim)
{
	char* p = strtok((char*)str.c_str(), &Delim); 
	while (p)
	{
		IntVec.push_back(atoi(p));
		p = strtok(NULL, &Delim); 
	}
	return IntVec.size();
}

int GetParamFromString(std::string str, std::vector<float>& FloatVec, char Delim)
{
	char* p = strtok((char*)str.c_str(), &Delim); 
	while (p)
	{
		FloatVec.push_back(atof(p));
		p = strtok(NULL, &Delim); 
	}
	return FloatVec.size();
}

int GetParamFromString(std::string str, std::vector<unsigned int>& uiIntVec, char Delim)
{
	char* p = strtok((char*)str.c_str(), &Delim); 
	while (p)
	{
		uiIntVec.push_back(strtoul(p, NULL, 10));
		p = strtok(NULL, &Delim); 
	}
	return uiIntVec.size();
}

int GetParamFromString(std::string str, std::vector<std::string>& StringVec, char Delim)
{
	char* p = strtok((char*)str.c_str(), &Delim); 
	while (p)
	{
		std::string buffer = p;
		StringVec.push_back(buffer);
		p = strtok(NULL, &Delim); 
	}
	return StringVec.size();
}

template<typename T>
int GetParamFromArea(std::string str, std::vector<std::vector<T> >& IntVec, char left, char right, char Delim)
{
	char* pTarget = (char*)str.c_str();
	for (;;)
	{
		char* pLeft = strchr(pTarget, left);
		char* pRight = strchr(pTarget, right);
		if (pLeft && pRight)
		{
			std::string strbuff;
			strbuff.insert(0, ++pLeft, pRight-pLeft);

			std::vector<T> Intbuff;
			if (GetParamFromString(strbuff, Intbuff, Delim))
			{
				IntVec.push_back(Intbuff);
			}
			pTarget = ++pRight;
		}
		else
		{
			break;
		}
	}
	return IntVec.size();
}