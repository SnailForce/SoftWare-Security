#include "stdafx.h"
#include <iostream>
#include <cstdlib>
using namespace std;
// 统计内存池内内存块个数
int l = 0;
// 统计未回收或正在使用的内存块个数
int l1 = 0;

// 单向链表
struct buffer
{
	char t[256];
	int flag = 0;
	buffer* next = NULL;
};
// 头指针
buffer* node = new buffer;
// 尾指针
buffer* last = NULL;

int initPool(size_t size = 1000)
{
	buffer* r = node;
	for (size_t i = 0; i < size; ++i)
	{
		buffer* t1 = NULL;
		t1 = new buffer;
		// 申请空间失败
		if (t1 == NULL)
		{
			return -1;
		}
		r->next = t1;
		r = r->next;
		// 统计内存池内内存块个数
		++l;
	}
	// 尾指针指向最后一块空间
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
		// 如果标志位为1，说明正在使用
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
		// 统计未回收内存块个数
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
		// 统计未回收内存块个数
		++l1;
		// 更新内存池内内存块个数
		++l;
		return last->t;
	}
	return 0;
}
int freeBlock(char* buf)
{
	// 参数错误
	if (buf == NULL)
	{
		return -1;
	}
	buffer* r = node;
	for (int i = 0; i < l; ++i)
	{
		// 地址匹配
		if (r->next->t == buf)
		{
			// 判断该内存块是否被分配，若未被分配则说明在分配的内存块中未找到该内存块，返回-2
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
	// 判断是否存在未回收的内存块
	if (l1 > 0)
	{
		return -1;
	}
	while(t1!=NULL)
	{
		// 清空
		memset(t1, 0, sizeof(buffer));
		// 释放
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
		// 清空
		if (memset(t1, 0, sizeof(buffer)) == NULL)
		{
			return -1;
		}
		// 释放
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
	// l为内存池内所有内存块个数
	return l;
}
int getAvailableBlockCount()
{
	// l1为内存池内被分配的内存块个数，l为内存池内所有内存块个数，两者之差为空闲可分配的内存块个数
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