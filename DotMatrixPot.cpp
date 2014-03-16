#include "stdafx.h"

static DOTMATRIXPOT pot;
static DOTMATRIX* dm;

DOTMATRIXPOT*
dmpInit(DOTMATRIX* matrix)
{
	pot.c = 0; pot.r = 0;
	pot.range = dmpRange;
	dm = matrix;
	return &pot;
}

static DOTMATRIXRANGE* 
dmpRange(FONTSIZE* size)
{
	
}

DOTMATRIXPOT
static dmpScanLH(DOTMATRIXPOT* start)	// scan dot matrix to left by horizontal
{
	DOTMATRIXPOT pot;
	size_t i = 0, j = 0;
	for (i = start->r; i < dm->r; ++i)
		for (j = 0; j < dm->c; ++j)
			if (dm->map[i][j] == 1) goto found;

	found:
		pot.r = i;
		pot.c = j;
	return pot;
}

DOTMATRIXPOT
static dmpSanLV(DOTMATRIXPOT* start, FONTSIZE* fs)
{
	DOTMATRIXPOT pot;
	pot.c = pot.r = 0;
	size_t i, j = start->c, stop = fs->h + start->r;
	if (dm->r < stop || dm->c == start->c) return pot;

	for (i = start->r; i < stop; ++i) {
		if (j == 0) break;
		if (dm->map[i][j] == 1) {
			--j;
			i = start->r;
		}
	}
	pot.r = start->r;
	pot.c = ++j;
	return pot;
}

DOTMATRIXPOT
static dmpSanRV(DOTMATRIXPOT* start, FONTSIZE* fs)
{
	DOTMATRIXPOT pot;
	size_t limit = 0;
	pot.c = pot.r = 0;
	size_t i, j = start->c, stop = fs->h + start->r;
	if (dm->r < stop || dm->c == start->c) return pot;

	do {
		for (i = start->r; i < stop; ++i) {
			if (j == dm->c - 1) goto ENDMAT;
			if (dm->map[i][j] == 1) { ++j; i = start->r; }
		}
		++limit; ++j; i = start->r;
	} while (limit < 3);

ENDMAT:
	pot.r = start->r;
	pot.c = j - limit;
	return pot;
}