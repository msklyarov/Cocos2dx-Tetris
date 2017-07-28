#pragma once
#include "cocos2d.h"
#include "Settings.h"

using namespace cocos2d;
using namespace std;

class CGlassPoint
{
public:
	CGlassPoint(const int x, const int y)
	{
		this->x = x;
		this->y = y;
	};

	int x, y;
};

typedef CGlassPoint
	RotationMatrixType[CSettings::FigureDirectionsCount][CSettings::FigureBlocksCount];

class CTetrisFigureBase:
	public CCScene
{
public:

	static enum FigureDirection { North = 0, East = 1, South = 2, West = 3 };

	void setFigureDirection(const int iDirection);

	void rotateClockwise();

	void moveLeft();
	void moveRight();
	bool canMoveDown();
	bool isFigureOverGlass();

	int getLeftBlockCount();
	int getRightBlockCount();
	int getTopBlockCount();
	int getBottomBlockCount();

	// set Figure center point in Glass Axis
	void setFigureGlassPoint(const int x, const int y);
	void setFigureGlassPointX(const int x);
	void setFigureGlassPointY(const int y);

	// get Figure center point in Glass Axis
	int getFigureGlassPointX();
	int getFigureGlassPointY();

	// get Figure Block point in Glass Axis
	int getBlockGlassPointX(const int iBlockNum);
	int getBlockGlassPointY(const int iBlockNum);

	int getBlockPointX(const int iBlockNum);
	int getBlockPointY(const int iBlockNum);

	CTetrisFigureBase(void);
	virtual ~CTetrisFigureBase(void);

protected:
	RotationMatrixType* _pRotationMatrix;
	int _iFigureDirection;

	void move(const int dX, const int dY);
	bool tryMove(const int dX, const int dY);

	// get Figure Block point in Glass Axis with user-defined rotation direction
	int getBlockGlassPointX(const int iBlockNum, const int iDirection);
	int getBlockGlassPointY(const int iBlockNum, const int iDirection);
};
