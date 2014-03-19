#include "stdafx.h"

static DotMatrixCarver dmc;

DotMatrixCarver*
	dmcInit(DOTMATRIX* dm, FontSize* size)
{
	dmc.dots = dm;
	dmc.size = size;
}