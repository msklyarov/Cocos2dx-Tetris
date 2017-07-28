#include "TetrisFigure_I.h"
#include "Settings.h"

CTetrisFigure_I::CTetrisFigure_I(void)
{
	/*
	 *	####
	 *	....
	 */
	// COLOR_CYAN
	static RotationMatrixType matrix_I = 
	{
		{ CGlassPoint(0, 0), CGlassPoint(-1, 0), CGlassPoint(1, 0), CGlassPoint(2, 0) },
		{ CGlassPoint(0, 0), CGlassPoint(0, 1), CGlassPoint(0, -1), CGlassPoint(0, -2) },
		{ CGlassPoint(0, 0), CGlassPoint(-1, 0), CGlassPoint(1, 0), CGlassPoint(2, 0) },
		{ CGlassPoint(0, 0), CGlassPoint(0, 1), CGlassPoint(0, -1), CGlassPoint(0, -2) }
	};

	_pRotationMatrix = &matrix_I;

	CCSprite* pBlocks[CSettings::FigureBlocksCount];

	pBlocks[0] = CCSprite::create( CSettings::FigureSpritesImgFileName,
		CCRectMake(CSettings::GlassCellSize * CSettings::Color::Cyan, 0, CSettings::FigureSpriteSize, CSettings::FigureSpriteSize) );

	for (int i = 1; i < CSettings::FigureBlocksCount; i++)
	{
		pBlocks[i] = new CCSprite(*pBlocks[0]);
	}

	for (int i = 0; i < CSettings::FigureBlocksCount; i++)
	{
		pBlocks[i]->setPosition( ccp( (*_pRotationMatrix)[_iFigureDirection][i].x * CSettings::GlassCellSize,
									(*_pRotationMatrix)[_iFigureDirection][i].y * CSettings::GlassCellSize ) );
		this->addChild(pBlocks[i]);
	}
}

CTetrisFigure_I::~CTetrisFigure_I(void)
{
}

