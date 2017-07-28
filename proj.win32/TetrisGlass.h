#pragma once
#include "TetrisFigureBase.h"

using namespace std;

typedef vector<CCSprite*> GlassRow;

class CTetrisGlass
{
public:
	static CTetrisGlass* getInstance();
	static void deleteInstance();

	bool isValidEmptyCell(const int x, const int y);

	void addFigure(CTetrisFigureBase* pFigure);

	int getRowsCount() const;
	bool isRowFull(const int iRowNum);
	void removeRow(const int iRowNum);
	void clearGlass();


private:
	static CTetrisGlass* _pSingletonInstance;
	vector<GlassRow*> _glass;

	CTetrisGlass(void);
	~CTetrisGlass(void);  // TODO ???

	void addRow();
};
