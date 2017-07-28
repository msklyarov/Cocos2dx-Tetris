#include "TetrisFigure_T.h"


CTetrisFigure_T::CTetrisFigure_T(void)
{
	/*
	 *	.#..
	 *	###.
	 */
	// COLOR_PURPLE
	static RotationMatrixType matrix_T = 
	{
		{ CGlassPoint(0, 0), CGlassPoint(-1, 0), CGlassPoint(1, 0), CGlassPoint(0, 1) },
		{ CGlassPoint(0, 0), CGlassPoint(1, 0), CGlassPoint(0, 1), CGlassPoint(0, -1) },
		{ CGlassPoint(0, 0), CGlassPoint(-1, 0), CGlassPoint(1, 0), CGlassPoint(0, -1) },
		{ CGlassPoint(0, 0), CGlassPoint(-1, 0), CGlassPoint(0, 1), CGlassPoint(0, -1) }
	};

	_pRotationMatrix = &matrix_T;

	CCSprite* pBlocks[CSettings::FigureBlocksCount];

	pBlocks[0] = CCSprite::create( CSettings::FigureSpritesImgFileName,
		CCRectMake(CSettings::GlassCellSize * (int) CSettings::Color::Purple, 0, CSettings::FigureSpriteSize, CSettings::FigureSpriteSize) );

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


CTetrisFigure_T::~CTetrisFigure_T(void)
{
}
