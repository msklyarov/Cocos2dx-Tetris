#include "Log.h"
#include "Settings.h"

#include <iostream>
#include <fstream>
#include <conio.h>

using namespace std;

void CLog::add(char* format, char* str)
{
#ifdef ENABLE_LOGGING
	const int strLength = 100;
	char strText[strLength];

	sprintf(strText, format, str);

	ofstream logfile;
	logfile.open (CSettings::LogFilePath, std::ios_base::app);
	logfile << strText;
	logfile << "\n";
	logfile.close();
#endif
}

void CLog::add(char* format, int num)
{
#ifdef ENABLE_LOGGING
	const int strLength = 100;
	char strText[strLength];

	sprintf(strText, format, num);

	ofstream logfile;
	logfile.open (CSettings::LogFilePath, std::ios_base::app);
	logfile << num;
	logfile << "\n";
	logfile.close();
#endif
}


void CLog::printGlass(CTetrisGlass* pGlass)
{
#ifdef ENABLE_LOGGING
	ofstream logfile;
	logfile.open (CSettings::LogFilePath, std::ios_base::app);
	logfile << "\n";

	for (int y = 0; y < CSettings::GlassBlocksHeight; y++)
	{
		for (int x = 0; x < CSettings::GlassBlocksWidth; x++)
		{
			if ( pGlass->isValidEmptyCell(x, y) )
			{
				logfile << " ";
			}
			else
			{
				logfile << "X";
			}
		}
		logfile << "\n";
	}

	logfile << "\n---------------------------\n";

	logfile << "\n";
	logfile.close();

#endif
}
