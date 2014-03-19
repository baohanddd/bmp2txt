#include "stdafx.h"

static DOTMATRIX* dm;

int	
carve(DOTMATRIX* dots, DotMatrixRanges* ranges)
{
	dm = dots;
}

int
carve(DotMatrixRange* range, Font* fonts)
{

}

static DotMatrixRow carveRow(DOTMATRIX* dots)
{
	DotMatrixPot start;
	start.r = start.c = 0;
	while(start.r == dots->r) {
		
	}
}

static DotMatrixRange
range(FontSize* size)
{
	DotMatrixRange range;
	DotMatrixPot start, end;
	start = dmpScanLH(&start);
	start = dmpScanLV(&start, size);
	end   = dmpScanRV(&start, size);
	range.tl = start;
	range.br = end;
	return range;
}

static DotMatrixPot
dmpScanLH(DotMatrixPot* start)	// scan dot matrix to left by horizontal
{
	DotMatrixPot pot;
	size_t i = 0, j = 0;
	for (i = start->r; i < dm->r; ++i) {
		if (i == start->r) j = start->c;
		else j = 0;
		for (; j < dm->c; ++j)
			if (dm->map[i][j] == 1) goto found;
	}

	found:
		pot.r = i;
		pot.c = j;
	return pot;
}

static DotMatrixPot
dmpScanLV(DotMatrixPot* start, FontSize* size)
{
	DotMatrixPot pot;
	pot.c = pot.r = 0;
	size_t i, j = start->c, stop = size->h + start->r;
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

static DotMatrixPot
dmpScanRV(DotMatrixPot* start, FontSize* size)
{
	DotMatrixPot pot;
	size_t limit = 0;
	pot.c = pot.r = 0;
	size_t i, j = start->c, stop = size->h + start->r;
	if (dm->r < stop || dm->c == start->c) return pot;

	do {
		for (i = start->r; i < stop; ++i) {
			if (j == dm->c - 1) goto ENDMAT;
			if (dm->map[i][j] == 1) { ++j; i = start->r; }
		}
		++limit; ++j; i = start->r;
	} while (limit < 3);

ENDMAT:
	pot.r = start->r + size->h;
	pot.c = j - limit;
	return pot;
}