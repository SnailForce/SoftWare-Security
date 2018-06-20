#pragma once
#include <iostream>
tm getTime();
streampos getFileSize(const char* path = NULL);
int initLog(char* path);
int logStr(char* level, char* str);
