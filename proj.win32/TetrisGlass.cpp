#include "TetrisGlass.h"
#include "Settings.h"
#include "TetrisLayer.h"
#include "Log.h"
#include "cocos2d.h"


CTetrisGlass* CTetrisGlass::_pSingletonInstance = NULL;

CTetrisGlass::CTetrisGlass(void)
{
}

CTetrisGlass::~CTetrisGlass(void)
{
	clearGlass();
	/*vector<GlassRow*>::iterator it;
	for (it = _glass.begin(); it != _glass.end(); it++)
	{
		(*it)->clear(); // elements of the vector are dropped: their destructors are called
	}*/
	_glass.clear();
}


CTetrisGlass* CTetrisGlass::getInstance()
{
	if (_pSingletonInstance == NULL)
	{
		_pSingletonInstance = new CTetrisGlass();
	}
	return _pSingletonInstance;
}

void CTetrisGlass::deleteInstance()
{
	if (_pSingletonInstance != NULL)
	{
		delete _pSingletonInstance;
		_pSingletonInstance = NULL;
	}
}


void CTetrisGlass::addRow()
{
	_glass.push_back(new GlassRow(CSettings::GlassBlocksWidth));
}

bool CTetrisGlass::isValidEmptyCell(const int x, const int y)
{
	if ( x < 0 || x > CSettings::GlassBlocksWidth - 1 ||
		y < 0 || y > CSettings::GlassBlocksHeight + CSettings::FigureBlocksCount - 1 )
	{
		return false;
	}

	if (y >= (int) _glass.size())
	{
		return true;
	}

	return (_glass[y]->at(x) == NULL);
}

void CTetrisGlass::addFigure(CTetrisFigureBase* pFigure)
{
	TetrisLayer* pTetrisLayer = (TetrisLayer*) pFigure->getParent();

	for (int i = 0; i < CSettings::FigureBlocksCount; i++)
	{
		int blockPosX = pFigure->getBlockGlassPointX(i);
		int blockPosY = pFigure->getBlockGlassPointY(i);

		assert( blockPosX >= 0 && blockPosX < CSettings::GlassBlocksWidth &&
				blockPosY >= 0 && blockPosY < CSettings::GlassBlocksHeight );

		// move from TetrisFigure CScene to CLayer
		CCSprite* pSprite = (CCSprite*) pFigure->getChildren()->objectAtIndex(i);
		pSprite->setParent(NULL);

		pSprite->setPosition( ccp(pFigure->getBlockPointX(i),
									pFigure->getBlockPointY(i)) );

		pTetrisLayer->addChild( pSprite );

		// add to _glass array
		while (blockPosY >= (int) _glass.size())
		{
			addRow();
		}
		_glass[blockPosY]->at(blockPosX) = pSprite;
	}

	// Remove TetrisFigure CScene, but not CSprite's.
	pTetrisLayer->removeChild(pFigure, false);

	CLog::printGlass(this);
}

int CTetrisGlass::getRowsCount() const
{
	return _glass.size();
}

bool CTetrisGlass::isRowFull(const int iRowNum)
{
	assert( iRowNum >= 0 && iRowNum < (int) _glass.size() );

	GlassRow::iterator it;

	for (it = _glass[iRowNum]->begin(); it != _glass[iRowNum]->end(); it++)
	{
		if (*it == NULL)
		{
			return false;
		}
	}
	return true;

}

void CTetrisGlass::removeRow(const int iRowNum)
{
	assert( iRowNum >= 0 && iRowNum < _glass.size() );

	vector<CCSprite*>::iterator it;
	for (it = _glass[iRowNum]->begin(); it != _glass[iRowNum]->end(); it++)
	{
		if ( (*it) != NULL )
		{
			// remove block from screen glass
			(*it)->getParent()->removeChild((*it), true);
		}
	}

	_glass[iRowNum]->clear(); // call destructor again ? :-)
	_glass.erase(_glass.begin() + iRowNum);


	// set Y-- for all upper blocks
	for (int i = iRowNum; i < _glass.size(); i++)
	{
		for (it = _glass[i]->begin(); it != _glass[i]->end(); it++)
		{
			if ( (*it) != NULL )
			{
				// remove block from screen glass
				(*it)->setPositionY( (*it)->getPositionY() - CSettings::GlassCellSize );
			}
		}
	}
}

void CTetrisGlass::clearGlass()
{
	for (int i = _glass.size() - 1; i >= 0 ; i--)
	{
		removeRow(i);
	}
}
