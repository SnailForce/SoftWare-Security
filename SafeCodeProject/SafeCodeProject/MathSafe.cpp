#include "stdafx.h"
#include <iostream>
using namespace std;
char *strip(char *str)
{
	int l = strlen(str);
	char* p = new char[l];
	int j = 0;
	for (int i = 0; i < l; ++i)
	{
		if (str[i] == ' ')
		{
			;
		}
		else
		{
			p[j++] = str[i];
		}
	}
	p[j] = '\0';
	return p;
}
int panduan(char s)
{
	int t = int(s);
	// 1-9 
	if (t > 57 || t < 48)
	{
		if (t != 43 && t != 45)
		{
			return -1;
		}
		else
		{
			// + -
			return 2;
		}
	}
	// 1-9
	if (t > 48 && t <= 57)
	{
		return 0;
	}
	// 0
	if (t == 48)
	{
		return 1;
	}
	/*
	if (t == 32)
	{
		return 2;
	}
	*/
	return 0;
}
int conversion(char s)
{
	int t = int(s) - 48;
	return t;
}
// ������ֻ���[-128,127]��Χ�ڵ�����ִ��ת��
// Str �Ϲ���ת���ɹ���(*of) = 0��str ��ָ�����ֻ���Ϊ�գ�(*of) = -1��str ָ������ֲ��Ϸ���(*of) = -2
// ����ֵ������ת������������������str����ȷ����ָ�������Խ�磬�򷵻�0
int8_t my_atoi8(char* str, int* of)
{
	int res = 0;
	if (str == NULL)
	{
		*of = -1;
		return 0;
	}
	if (strlen(str) == 0)
	{
		*of = -1;
		return 0;
	}
	// ȥ�����еĿո�
	char *t = strip(str);
	if (str == NULL)
	{
		*of = -1;
		return 0;
	}
	int l = strlen(t);
	// ֻ��һ��0
	if ((l == 1) && (t[0] = '0'))
	{
		*of = 0;
		return 0;
	}
	// �жϳ���һλ������λ�Ƿ�ȫ������
	// �����ּ�����ĸҲ��0��ͷ���ַ�����Ϊ��-1��ָ�����ֵ����
	for (int i = 0; i < l; ++i)
	{
		if (panduan(t[i]) == -1)
		{
			*of = -1;
			return 0;
		}
	}
	// +/-
	if (panduan(t[0]) == 2)
	{
		// +/- 0
		if (panduan(t[1]) == 1)
		{
			*of = -2;
			return 0;
		}
		else
		{
			// +
			if (conversion(t[0]) == -5)
			{
				for (int i = 1; i < l; ++i)
				{
					res = res * 10 + conversion(t[i]);
					if (res > 127)
					{
						*of = -2;
						return 0;
					}
				}
				*of = 0;
				return res;
			}
			// -
			else if (conversion(t[0]) == -3)
			{
				for (int i = 1; i < l; ++i)
				{
					res = res * 10 + conversion(t[i]);
					if (res > 128)
					{
						*of = -2;
						return 0;
					}
				}
				*of = 0;
				return -res;
			}
		}
	}
	else
	{
		// 0
		if (panduan(t[0]) == 1)
		{
			*of = -2;
			return 0;
		}
		else
		{
			for (int i = 0; i < l; ++i)
			{
				res = res * 10 + conversion(t[i]);
				if (res > 127)
				{
					*of = -2;
					return 0;
				}
			}
			*of = 0;
			return res;
		}
	}
	return 0;
}
int iAdd_Safe(int8_t a, int8_t b, int* of)
{
	int res = a + b;
	/*
	if ((a > 0 && b > 0) || (a < 0 && b < 0))
	{
		if ((a > 127 - b) || (a < -128 - b))
		{
			*of = -2;
			return 0;
		}
		else
		{
			*of = 0;
			return res;
		}
	}
	else
	{
		*of = 0;
		return res;
	}
	*/
	if ((res > 127) || (res < -128))
	{
		*of = -2;
		return 0;
	}
	else
	{
		*of = 0;
		return res;
	}
}
int iSubtract_Safe(int8_t a, int8_t b, int* of)
{
	int res = a - b;
	/*
	if ((a > 0 && b > 0) || (a < 0 && b < 0))
	{
		*of = 0;
		return res;
	}
	else
	{
		if ((a > 127 + b) || (a < -128 + b))
		{
			*of = -2;
			return 0;
		}
		else
		{
			*of = 0;
			return res;
		}
	}
	*/
	if ((res > 127) || (res < -128))
	{
		*of = -2;
		return 0;
	}
	else
	{
		*of = 0;
		return res;
	}
}
int iMultiply_Safe(int8_t a, int8_t b, int* of)
{
	int res = a * b;
	if ((res > 127) || (res < -128))
	{
		*of = -2;
		return 0;
	}
	else
	{
		*of = 0;
		return res;
	}
}
int iDivide_Safe(int8_t a, int8_t b, int* of)
{
	if (!b)
	{
		*of = -1;
		return 0;
	}
	int res = a / b;
	if ((res > 127) || (res < -128))
	{
		*of = -2;
		return 0;
	}
	else
	{
		*of = 0;
		return res;
	}
}
unsigned int Add_Safe(uint8_t a, uint8_t b, int *of)
{
	unsigned int res = a + b;
	if (res > 255)
	{
		*of = -2;
		return 0;
	}
	else
	{
		*of = 0;
		return res;
	}
}
unsigned int Subtract_Safe(uint8_t a, uint8_t b, int* of)
{
	unsigned int res = a - b;
	if (res > a)
	{
		*of = -2;
		return 0;
	}
	else
	{
		*of = 0;
		return res;
	}
}
unsigned int Multiply_Safe(uint8_t a, uint8_t b, int* of)
{
	unsigned int res = a * b;
	if (res > 255)
	{
		*of = -2;
		return 0;
	}
	else
	{
		*of = 0;
		return res;
	}
}
unsigned int Divide_Safe(uint8_t a, uint8_t b, int* of)
{
	if (!b)
	{
		*of = -1;
		return 0;
	}
	unsigned int res = a / b;
	*of = 0;
	return res;
}
