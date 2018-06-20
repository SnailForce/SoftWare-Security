#include "stdafx.h"
#include <iostream>
#include <cstdlib>
using namespace std;
// ͳ���ڴ�����ڴ�����
int l = 0;
// ͳ��δ���ջ�����ʹ�õ��ڴ�����
int l1 = 0;

// ��������
struct buffer
{
	char t[256];
	int flag = 0;
	buffer* next = NULL;
};
// ͷָ��
buffer* node = new buffer;
// βָ��
buffer* last = NULL;

int initPool(size_t size = 1000)
{
	buffer* r = node;
	for (size_t i = 0; i < size; ++i)
	{
		buffer* t1 = NULL;
		t1 = new buffer;
		// ����ռ�ʧ��
		if (t1 == NULL)
		{
			return -1;
		}
		r->next = t1;
		r = r->next;
		// ͳ���ڴ�����ڴ�����
		++l;
	}
	// βָ��ָ�����һ��ռ�
	last = r;
	// cout << l << " " << l1 << endl;
	return 0;
}

char* allocBlock()
{
	int i;
	buffer* r = node->next;
	for (i = 0; i < l; ++i)
	{
		// �����־λΪ1��˵������ʹ��
		if (r->flag == 1)
		{
			r = r->next;
		}
		else
		{
			break;
		}
	}
	if (i < l)
	{
		r->flag = 1;
		memset(r->t, 0, 256 * sizeof(char));
		// ͳ��δ�����ڴ�����
		++l1;
		return r->t;
	}
	else
	{
		buffer* r1 = new buffer;
		if (r1 == NULL)
		{
			return NULL;
		}
		last->next = r1;
		last = last->next;
		memset(last->t, 0, 256 * sizeof(char));
		// ͳ��δ�����ڴ�����
		++l1;
		// �����ڴ�����ڴ�����
		++l;
		return last->t;
	}
	return 0;
}
int freeBlock(char* buf)
{
	// ��������
	if (buf == NULL)
	{
		return -1;
	}
	buffer* r = node;
	for (int i = 0; i < l; ++i)
	{
		// ��ַƥ��
		if (r->next->t == buf)
		{
			// �жϸ��ڴ���Ƿ񱻷��䣬��δ��������˵���ڷ�����ڴ����δ�ҵ����ڴ�飬����-2
			if (r->next->flag == 1)
			{
				r->next->flag = 0;
				memset(r->next->t, 0, 256 * sizeof(char));
				--l1;
				return 0;
			}
		}
		r = r->next;
	}
	return -2;
}
int freePool()
{
	buffer* t1 = node->next;
	buffer* t2;
	// �ж��Ƿ����δ���յ��ڴ��
	if (l1 > 0)
	{
		return -1;
	}
	while(t1!=NULL)
	{
		// ���
		memset(t1, 0, sizeof(buffer));
		// �ͷ�
		t2 = t1->next;
		delete(t1);
		t1 = t2;
	}
	l = 0;
	l1 = 0;
	node->next = NULL;
	return 0;
}
int freePoolForce()
{
	buffer* t1 = node->next;
	buffer* t2;
	while(t1!=NULL)
	{
		// ���
		if (memset(t1, 0, sizeof(buffer)) == NULL)
		{
			return -1;
		}
		// �ͷ�
		t2 = t1->next;
		delete(t1);
		t1 = t2;
	}
	node->next = NULL;
	l = 0;
	l1 = 0;
	return 0;
}
int getBlockCount()
{
	// lΪ�ڴ���������ڴ�����
	return l;
}
int getAvailableBlockCount()
{
	// l1Ϊ�ڴ���ڱ�������ڴ�������lΪ�ڴ���������ڴ�����������֮��Ϊ���пɷ�����ڴ�����
	return l - l1;
	/*
	int res = 0;
	buffer* t = node;
	for (int i = 0; i < l; ++i)
	{
		if (t->next != NULL && t->next->flag == 0)
		{
			++res;
		}
		t = t->next;
	}
	return res;
	*/
}