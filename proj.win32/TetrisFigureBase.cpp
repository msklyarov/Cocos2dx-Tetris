#include "TetrisFigureBase.h"
#include "Settings.h"
#include "TetrisGlass.h"
#include "Log.h"


CTetrisFigureBase::CTetrisFigureBase(void)
{
	_iFigureDirection = FigureDirection::North;
}

CTetrisFigureBase::~CTetrisFigureBase(void)
{
	CLog::add( "~CTetrisFigureBase :: Number of blocks to delete: %d", this->getChildren()->count() );
	this->removeAllChildrenWithCleanup( true );
}

void CTetrisFigureBase::setFigureDirection(const int iDirection)
{
	CLog::add("%s", "Direction");
	CLog::add("%d", iDirection);
	_iFigureDirection = iDirection;

	for (int i = 0; i < CSettings::FigureBlocksCount; i++)
	{
		((CCSprite*) this->getChildren()->objectAtIndex(i))->setPosition(
			ccp( (*_pRotationMatrix)[_iFigureDirection][i].x * CSettings::GlassCellSize,
									(*_pRotationMatrix)[_iFigureDirection][i].y * CSettings::GlassCellSize)
			);
	}
};

void CTetrisFigureBase::rotateClockwise()
{
	CLog::add("%s", "CTetrisFigureBase::rotateClockwise() called");

	int iNextFigureDirection = _iFigureDirection + 1;
	iNextFigureDirection %= CSettings::FigureDirectionsCount;

	CTetrisGlass* pTGlass = CTetrisGlass::getInstance();

	for (int i = 0; i < CSettings::FigureBlocksCount; i++)
	{
		if ( !pTGlass->isValidEmptyCell(getBlockGlassPointX(i, iNextFigureDirection),
										getBlockGlassPointY(i, iNextFigureDirection) ) )
		{
			return;
		}
	}

	_iFigureDirection = iNextFigureDirection;

	// rotate figure matrix on scene
	for (int i = 0; i < CSettings::FigureBlocksCount; i++)
	{
		((CCSprite*) this->getChildren()->objectAtIndex(i))->setPosition(
			ccp( (*_pRotationMatrix)[_iFigureDirection][i].x * CSettings::GlassCellSize,
									(*_pRotationMatrix)[_iFigureDirection][i].y * CSettings::GlassCellSize)
			);
	}
}

void CTetrisFigureBase::setFigureGlassPoint(const int x, const int y)
{
	int actualX = CSettings::GlassMinPxX + CSettings::FigureSpriteSize / 2 + CSettings::GlassCellSize * x;
	int actualY = CSettings::GlassMinPxY - 1 + CSettings::FigureSpriteSize / 2 + CSettings::GlassCellSize * y;
	this->setPosition( ccp(actualX, actualY) );
}

void CTetrisFigureBase::setFigureGlassPointX(const int x)
{
	int actualX = CSettings::GlassMinPxX + CSettings::FigureSpriteSize / 2 + CSettings::GlassCellSize * x;
	this->setPositionX(actualX);
}

void CTetrisFigureBase::setFigureGlassPointY(const int y)
{
	int actualY = CSettings::GlassMinPxY - 1 + CSettings::FigureSpriteSize / 2 + CSettings::GlassCellSize * y;
	this->setPositionY(actualY);
}

int CTetrisFigureBase::getFigureGlassPointX()
{
	return (this->getPositionX() - CSettings::GlassMinPxX - CSettings::FigureSpriteSize / 2) / CSettings::GlassCellSize;
}

int CTetrisFigureBase::getFigureGlassPointY()
{
	// round == floor(0.5 + x)
	return floor(0.5 + this->getPositionY() - CSettings::GlassMinPxY + 1 - CSettings::FigureSpriteSize / 2) / CSettings::GlassCellSize;
}

void CTetrisFigureBase::moveLeft()
{
	move(-1, 0);
}

void CTetrisFigureBase::moveRight()
{
	move(1, 0);
}

bool CTetrisFigureBase::canMoveDown()
{
	return tryMove(0, -1);
}

bool CTetrisFigureBase::isFigureOverGlass()
{
	CTetrisGlass* pTGlass = CTetrisGlass::getInstance();

	for (int i = 0; i < CSettings::FigureBlocksCount; i++)
	{
		if ( getBlockGlassPointY(i) > CSettings::GlassBlocksHeight - 1 )
		{
			return true;
		}
	}
	return false;
}

void CTetrisFigureBase::move(const int dX, const int dY)
{
	if ( tryMove(dX, dY) )
	{
		if (dX != 0)
		{
			this->setFigureGlassPointX(this->getFigureGlassPointX() + dX);
		}

		if (dY != 0)
		{
			this->setFigureGlassPointY(this->getFigureGlassPointY() + dY);
		}
	}
}

bool CTetrisFigureBase::tryMove(const int dX, const int dY)
{
	CTetrisGlass* pTGlass = CTetrisGlass::getInstance();

	for (int i = 0; i < CSettings::FigureBlocksCount; i++)
	{
		if ( !pTGlass->isValidEmptyCell(getBlockGlassPointX(i) + dX,
										getBlockGlassPointY(i) + dY) )
		{
			return false;
		}
	}
	return true;
}

int CTetrisFigureBase::getLeftBlockCount()
{
	int iMin = 0;
	for (int i = 0; i < CSettings::FigureBlocksCount; i++)
	{
		iMin = min( iMin, (*_pRotationMatrix)[_iFigureDirection][i].x );
	}
	return abs( iMin );

	/*return abs( min( min( (*_pRotationMatrix)[_iFigureDirection][0].x,
							(*_pRotationMatrix)[_iFigureDirection][1].x),
					min( (*_pRotationMatrix)[_iFigureDirection][2].x,
							(*_pRotationMatrix)[_iFigureDirection][3].x )
					)
				);*/
}

int CTetrisFigureBase::getRightBlockCount()
{
	int iMax = 0;
	for (int i = 0; i < CSettings::FigureBlocksCount; i++)
	{
		iMax = max( iMax, (*_pRotationMatrix)[_iFigureDirection][i].x );
	}
	return iMax;

	/*return max( max( (*_pRotationMatrix)[_iFigureDirection][0].x,
						(*_pRotationMatrix)[_iFigureDirection][1].x),
				max( (*_pRotationMatrix)[_iFigureDirection][2].x,
						(*_pRotationMatrix)[_iFigureDirection][3].x )
				);*/
}

int CTetrisFigureBase::getTopBlockCount()
{
	int iMax = 0;
	for (int i = 0; i < CSettings::FigureBlocksCount; i++)
	{
		iMax = max( iMax, (*_pRotationMatrix)[_iFigureDirection][i].y );
	}
	return iMax;

	/*return max( max( (*_pRotationMatrix)[_iFigureDirection][0].y,
						(*_pRotationMatrix)[_iFigureDirection][1].y),
				max( (*_pRotationMatrix)[_iFigureDirection][2].y,
						(*_pRotationMatrix)[_iFigureDirection][3].y )
				);*/
}

int CTetrisFigureBase::getBottomBlockCount()
{
	int iMin = 0;
	for (int i = 0; i < CSettings::FigureBlocksCount; i++)
	{
		iMin = min( iMin, (*_pRotationMatrix)[_iFigureDirection][i].y );
	}
	return abs( iMin );

	/*return abs( min( min( (*_pRotationMatrix)[_iFigureDirection][0].y,
					(*_pRotationMatrix)[_iFigureDirection][1].y),
				min( (*_pRotationMatrix)[_iFigureDirection][2].y,
					(*_pRotationMatrix)[_iFigureDirection][3].y) )
				);*/
}

int CTetrisFigureBase::getBlockGlassPointX(const int iBlockNum)
{
	return getBlockGlassPointX(iBlockNum, _iFigureDirection);
}

int CTetrisFigureBase::getBlockGlassPointY(const int iBlockNum)
{
	return getBlockGlassPointY(iBlockNum, _iFigureDirection);
}

int CTetrisFigureBase::getBlockGlassPointX(const int iBlockNum, const int iDirection)
{
	assert(iBlockNum < CSettings::FigureBlocksCount && iBlockNum >= 0);
	assert(iDirection < CSettings::FigureDirectionsCount && iDirection >= 0);

	int actualPtX = getFigureGlassPointX() + (*_pRotationMatrix)[iDirection][iBlockNum].x;
	return actualPtX;
}

int CTetrisFigureBase::getBlockGlassPointY(const int iBlockNum, const int iDirection)
{
	assert(iBlockNum < CSettings::FigureBlocksCount && iBlockNum >= 0);
	assert(iDirection < CSettings::FigureDirectionsCount && iDirection >= 0);

	int actualPtY = getFigureGlassPointY() + (*_pRotationMatrix)[iDirection][iBlockNum].y;
	return actualPtY;
}

int CTetrisFigureBase::getBlockPointX(const int iBlockNum)
{
	assert(iBlockNum < CSettings::FigureBlocksCount && iBlockNum >= 0);

	int actualX = CSettings::GlassMinPxX + CSettings::FigureSpriteSize / 2
			+ CSettings::GlassCellSize * getBlockGlassPointX(iBlockNum, _iFigureDirection); 
	return actualX;
}

int CTetrisFigureBase::getBlockPointY(const int iBlockNum)
{
	assert(iBlockNum < CSettings::FigureBlocksCount && iBlockNum >= 0);

	int actualY = CSettings::GlassMinPxY - 1 + CSettings::FigureSpriteSize / 2
			+ CSettings::GlassCellSize * getBlockGlassPointY(iBlockNum, _iFigureDirection);
	return actualY;
}

