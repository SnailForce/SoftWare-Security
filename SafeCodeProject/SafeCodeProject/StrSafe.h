#pragma once
#include <string>
using namespace std;
int isUsernameOK(char* name);
int isPasswordOK(char* pwd);
int isUsernameOK1(string name);

int gets_safe(char* str, rsize_t n);
int strcpy_safe(char* dest, rsize_t destz, const char* src);