#pragma once

#include "TetrisGlass.h"

class CLog
{
public:

	//memory tests

	static void add(char* format, char* str);
	static void add(char* format, int num);
	static void printGlass(CTetrisGlass* pGlass);
};

