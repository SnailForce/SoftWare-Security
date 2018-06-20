#include "stdafx.h"
#include <iostream>
#include "StrSafe.h"
#include <cctype>
#include <string>
using namespace std;
int isUsernameOK(char* name)
{
	if(name == NULL)
	{
		return -1;
	}
	int t = strlen(name), i;
	char s;
	if (t >= 8 && t <= 16 && isalpha(name[0]))
	{
		for (i = 0; i < t; ++i)
		{
			s = name[i];
			if (isalnum(s))
			{
				;
			}
			else
			{
				return -1;
			}
		}
		return 0;
	}
	else
	{
		return -1;
	}
}
int isUsernameOK1(string name)
{
	int t = name.length(), i;
	char s;
	if (t >= 8 && t <= 16 && isalpha(name[0]))
	{
		for (i = 0; i < t; ++i)
		{
			s = name[i];
			if (isalnum(s))
			{
				;
			}
			else
			{
				return -1;
			}
		}
		return 0;
	}
	else
	{
		return -1;
	}
}

int isPasswordOK(char* pwd)
{
	if(pwd == NULL)
	{
		return -1;
	}
	int t = strlen(pwd), i;
	char s;
	int res1 = 0, res2 = 0;
	if (t >= 8 && t <= 16)
	{
		for (i = 0; i < t; ++i)
		{
			s = pwd[i];
			if (isdigit(s))
			{
				++res1;
			}
			else if (isupper(s))
			{
				++res2;
			}
		}
		if (res1 > 0 && res2 > 0)
		{
			return 0;
		}
		else
		{
			return -1;
		}
	}
	else
	{
		return -1;
	}
}

int gets_safe(char* str, rsize_t n)
{
	//int t = sizeof(str) - 1;
	unsigned int k = 0;
	char s;
	if (n <= 0)
	{
		if (str != NULL)
		{
			str[0] = '\0';
		}
		return -1;
	}

	s = getchar();
	if (ferror(stdin))
	{
		str[0] = '\0';
		return -2;
	}
	while (s != '\n')
	{
		if (ferror(stdin))
		{
			str[0] = '\0';
			return -2;
		}
		str[++k] = s;
		if (k >= n - 1)
		{
			str[k] = '\0';
			break;
		}
		s = getchar();
	}
	if (k < n - 1)
	{
		str[k] = '\0';
	}
	rewind(stdin);
	//while ((s = getchar()) != '\n'&&s != EOF);
	return k;
}

int strcpy_safe(char* dest, rsize_t destz, const char* src)
{
	if (destz == 0)
	{
		dest[0] = '\0';
		return -1;
	}
	if (dest == NULL || src == NULL)
	{
		return -1;
	}
	unsigned int t1 = strlen(src);
	unsigned int t2 = sizeof(dest);
	if (t1 >= destz)
	{
		for (unsigned int i = 0; i < destz - 1; ++i)
		{
			dest[i] = src[i];
		}
		dest[destz - 1] = '\0';
		return destz;
	}
	else
	{
		for (unsigned int i = 0; i < t1; ++i)
		{
			dest[i] = src[i];
		}
		dest[t1] = '\0';
		return t1;
	}
}
