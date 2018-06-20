#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <string>
#include <ctime>
#include <mutex>
#include <Windows.h>
using namespace std;
// 互斥锁
mutex m;
// 保存日志文件地址
char* pp = NULL;
// char bup[] = "D://LogSafe_1.txt";
// 备份日志文件地址为传入日志文件所在目录下
char bup1[1024];
// 标志位表示是否为第一次备份
int flag = 0;
// 日志文件输入流
fstream OutFile;
// 备份文件输入流
fstream backup;
// get system time 英文表示高大上一点233
tm getTime()
{
	time_t t = time(0);
	struct tm now_time;
	localtime_s(&now_time, &t);
	return now_time;
}
// get file size 获取文件大小
// 默认为空
streampos getFileSize(const char* path = NULL)
{
	// 若为空 文件为初始化中对应的地址
	if (path == NULL)
	{
		path = pp;
	}
	ifstream in(path);
	in.seekg(0, std::ios_base::end);
	streampos sp = in.tellg();
	return sp;
	/*
	// 这种方法也可以获取文件大小
	struct _stat info;
	_stat(path, &info);
	int size = info.st_size;
	return size;
	*/
}
// init log file
int initLog(char* path)
{
	// init
	// 先清空 然后断开连接
	// 至于为什么这么写 我也不知道 网上也没说 我自己试验出来的 可以清空文件=.=
	// 网上说的将长度置为0的方法试了没用 似乎
	OutFile.open(path, ios::out);
	// 全局变量保存日志文件地址
	pp = path;
	// 获取日志文件所在目录 并将传入文件如D://a.txt变为D://a再加上_copy.txt得到D://a_copy.txt
	strcpy_s(bup1, path);
	for (unsigned int i = 0; i < strlen(bup1); ++i)
	{
		if (bup1[i] == '.'&&bup1[i + 1] == 't'&&bup1[i + 2] == 'x'&&bup1[i + 3] == 't')
		{
			bup1[i] = '\0';
			break;
		}
	}
	strcat_s(bup1, "_copy.txt");
	if (!OutFile)
	{
		return -1;
	}
	// 简单一句尝试
	// OutFile << "This is a try123!" << endl;
	// 断开连接
	OutFile.close();
	return 0;
}
// 线程函数
int logStr(char* level, char* str)
{
	// RAII锁
	lock_guard<mutex> lck(m);
	// 普通的锁也可以 尝试了两种方法
	// m.lock();
	if (!OutFile || !level || !str)
	{
		return -1;
	}
	// 获取id
	thread::id tid = this_thread::get_id();
	// 获取时间
	tm t = getTime();
	// 追加形式写入
	OutFile.open(pp, ios::app);
	OutFile << level << "||" << tid << "||" << t.tm_hour << ":" << t.tm_min << ":" << t.tm_sec << "||" << str << endl;
	// 断开连接
	OutFile.close();
	// 判断大小
	if (getFileSize() > 1024 * 1024)
	{
		// 判断是否是第一次 第一次为海量备份 以后为增量备份
		if (!flag)
		{
			// 至于为什么这么写 我也不知道 网上也没说 我自己试验出来的 可以清空文件==
			// 网上说的将长度置为0的方法试了没用 似乎
			// 备份文件清空并复制日志文件1M的内容
			backup.open(bup1, ios::out);
			backup.close();
			CopyFileA(pp, bup1, false);
			flag = 1;
		}
		else
		{
			// 备份文件追加形式同步日志文件
			backup.open(bup1, ios::app);
			backup << level << "||" << tid << "||" << t.tm_hour << ":" << t.tm_min << ":" << t.tm_sec << "||" << str << endl;
			backup.close();
		}
	}
	// 这个和函数开头的m.lock()配合 互斥锁 结果与RAII相同
	// m.unlock();
	return 0;
}