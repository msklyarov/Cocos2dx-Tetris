#pragma once

#define ENABLE_LOGGING

#ifdef ENABLE_LOGGING
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC // enable generation of debug heap alloc map
#define new new( _NORMAL_BLOCK, __FILE__, __LINE__) // redefine "new" to get file names in output
#endif

class CSettings
{
public:

	// figure colors
	enum Color { Cyan = 1, Red = 2, Blue = 3, Orange = 4, Green = 5, Yellow = 6, Purple = 7 };

	static const char* BackgroundImgFileName;
	static const int BackgroundWidth = 320;
	static const int BackgroundHeight = 480;

	static const char* FigureSpritesImgFileName;

	static const char* ArrowUpImgFileName;
	static const int ArrowUpImgRadius = 25;

	static const char* ReplayImgFileName;
	static const int ReplayImgRadius = 45;

	static const int FigureSpriteSize = 18;
	static const int GlassCellSize = FigureSpriteSize - 1;

	static const int GlassBlocksWidth = 10;
	static const int GlassBlocksHeight = 20;

	static const int FigureDirectionsCount = 4;
	static const int FigureBlocksCount = 4;

	static const int GlassMinPxX = 30;
	static const int GlassMinPxY = 30;

	static const float InitialFallDuration;
	static const float FallDurationDecrementPerLevel;

	static const char* LogFilePath;
	static const char* MemLeaksLogFilePath;
};

