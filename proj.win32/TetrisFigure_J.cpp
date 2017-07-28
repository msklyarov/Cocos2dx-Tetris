#include "TetrisFigure_J.h"


CTetrisFigure_J::CTetrisFigure_J(void)
{
	/*
	 *	#...
	 *	###.
	 */
	// COLOR_BLUE
	static RotationMatrixType matrix_J = 
	{
		{ CGlassPoint(0, 0), CGlassPoint(0, 1), CGlassPoint(1, 0), CGlassPoint(2, 0) },
		{ CGlassPoint(0, 0), CGlassPoint(1, 0), CGlassPoint(0, -1), CGlassPoint(0, -2) },
		{ CGlassPoint(0, 0), CGlassPoint(0, -1), CGlassPoint(-1, 0), CGlassPoint(-2, 0) },
		{ CGlassPoint(0, 0), CGlassPoint(-1, 0), CGlassPoint(0, 1), CGlassPoint(0, 2) },
	};

	_pRotationMatrix = &matrix_J;

	CCSprite* pBlocks[4];

	pBlocks[0] = CCSprite::create( CSettings::FigureSpritesImgFileName,
		CCRectMake(CSettings::GlassCellSize * CSettings::Color::Blue, 0, CSettings::FigureSpriteSize, CSettings::FigureSpriteSize) );

	for (int i = 1; i < 4; i++)
	{
		pBlocks[i] = new CCSprite(*pBlocks[0]);
	}

	for (int i = 0; i < 4; i++)
	{
		pBlocks[i]->setPosition( ccp( (*_pRotationMatrix)[_iFigureDirection][i].x * CSettings::GlassCellSize,
									(*_pRotationMatrix)[_iFigureDirection][i].y * CSettings::GlassCellSize) );
		this->addChild(pBlocks[i]);
	}
}

CTetrisFigure_J::~CTetrisFigure_J(void)
{
}
