#pragma once
#include "tetrisfigurebase.h"

class CTetrisFigureCreator
{
public:

	static CTetrisFigureBase* CreateById(int id);
	static CTetrisFigureBase* CreateRandom();
};
