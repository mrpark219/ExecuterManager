#pragma once
#ifndef __EXECUTERMANAGER_H__
#define __EXECUTERMANAGER_H__

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#define defaultpath "D:\\exelist.txt"

struct Program {
	char exelistName[1000];
	char exelistPath[1000];
	int useAt;
} pro[20];

int checkpath(char* path, int count);
int collectingList(char* path, int count);
void showList(int total, int index);


#endif // !__EXECUTERMANAGER_H__
