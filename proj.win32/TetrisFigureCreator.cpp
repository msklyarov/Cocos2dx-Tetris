#include "TetrisFigureCreator.h"
#include "TetrisFigure_I.h"
#include "TetrisFigure_O.h"
#include "TetrisFigure_T.h"
#include "TetrisFigure_S.h"
#include "TetrisFigure_Z.h"
#include "TetrisFigure_J.h"
#include "TetrisFigure_L.h"
#include "Settings.h"



CTetrisFigureBase* CTetrisFigureCreator::CreateById(int id)
{
	CTetrisFigureBase *pFigure;
	switch (id)
	{
		case 0:
			pFigure = new CTetrisFigure_I();
			break;
		case 1:
			pFigure = new CTetrisFigure_O();
			break;
		case 2:
			pFigure = new CTetrisFigure_T();
			break;
		case 3:
			pFigure = new CTetrisFigure_S();
			break;
		case 4:
			pFigure = new CTetrisFigure_Z();
			break;
		case 5:
			pFigure = new CTetrisFigure_J();
			break;
		case 6:
			pFigure = new CTetrisFigure_L();
			break;
		default:
			return NULL;
	}

	return pFigure;
}

CTetrisFigureBase* CTetrisFigureCreator::CreateRandom()
{
	return CTetrisFigureCreator::CreateById( rand() % 7 );
}