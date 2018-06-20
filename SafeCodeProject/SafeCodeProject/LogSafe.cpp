#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <string>
#include <ctime>
#include <mutex>
#include <Windows.h>
using namespace std;
// ������
mutex m;
// ������־�ļ���ַ
char* pp = NULL;
// char bup[] = "D://LogSafe_1.txt";
// ������־�ļ���ַΪ������־�ļ�����Ŀ¼��
char bup1[1024];
// ��־λ��ʾ�Ƿ�Ϊ��һ�α���
int flag = 0;
// ��־�ļ�������
fstream OutFile;
// �����ļ�������
fstream backup;
// get system time Ӣ�ı�ʾ�ߴ���һ��233
tm getTime()
{
	time_t t = time(0);
	struct tm now_time;
	localtime_s(&now_time, &t);
	return now_time;
}
// get file size ��ȡ�ļ���С
// Ĭ��Ϊ��
streampos getFileSize(const char* path = NULL)
{
	// ��Ϊ�� �ļ�Ϊ��ʼ���ж�Ӧ�ĵ�ַ
	if (path == NULL)
	{
		path = pp;
	}
	ifstream in(path);
	in.seekg(0, std::ios_base::end);
	streampos sp = in.tellg();
	return sp;
	/*
	// ���ַ���Ҳ���Ի�ȡ�ļ���С
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
	// ����� Ȼ��Ͽ�����
	// ����Ϊʲô��ôд ��Ҳ��֪�� ����Ҳû˵ ���Լ���������� ��������ļ�=.=
	// ����˵�Ľ�������Ϊ0�ķ�������û�� �ƺ�
	OutFile.open(path, ios::out);
	// ȫ�ֱ���������־�ļ���ַ
	pp = path;
	// ��ȡ��־�ļ�����Ŀ¼ ���������ļ���D://a.txt��ΪD://a�ټ���_copy.txt�õ�D://a_copy.txt
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
	// ��һ�䳢��
	// OutFile << "This is a try123!" << endl;
	// �Ͽ�����
	OutFile.close();
	return 0;
}
// �̺߳���
int logStr(char* level, char* str)
{
	// RAII��
	lock_guard<mutex> lck(m);
	// ��ͨ����Ҳ���� ���������ַ���
	// m.lock();
	if (!OutFile || !level || !str)
	{
		return -1;
	}
	// ��ȡid
	thread::id tid = this_thread::get_id();
	// ��ȡʱ��
	tm t = getTime();
	// ׷����ʽд��
	OutFile.open(pp, ios::app);
	OutFile << level << "||" << tid << "||" << t.tm_hour << ":" << t.tm_min << ":" << t.tm_sec << "||" << str << endl;
	// �Ͽ�����
	OutFile.close();
	// �жϴ�С
	if (getFileSize() > 1024 * 1024)
	{
		// �ж��Ƿ��ǵ�һ�� ��һ��Ϊ�������� �Ժ�Ϊ��������
		if (!flag)
		{
			// ����Ϊʲô��ôд ��Ҳ��֪�� ����Ҳû˵ ���Լ���������� ��������ļ�==
			// ����˵�Ľ�������Ϊ0�ķ�������û�� �ƺ�
			// �����ļ���ղ�������־�ļ�1M������
			backup.open(bup1, ios::out);
			backup.close();
			CopyFileA(pp, bup1, false);
			flag = 1;
		}
		else
		{
			// �����ļ�׷����ʽͬ����־�ļ�
			backup.open(bup1, ios::app);
			backup << level << "||" << tid << "||" << t.tm_hour << ":" << t.tm_min << ":" << t.tm_sec << "||" << str << endl;
			backup.close();
		}
	}
	// ����ͺ�����ͷ��m.lock()��� ������ �����RAII��ͬ
	// m.unlock();
	return 0;
}