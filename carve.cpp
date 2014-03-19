#include "stdafx.h"

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
	range.cpl  = start;
	range.cpr = end;
	return range;
}

size_t width(DotMatrixRange* range)
{
	size_t w = range->cpr.c - range->cpl.c;
	if(w < 0) w = 0;
	return w;
}

size_t height(DotMatrixRange* range)
{
	return range->size->h;
}

size_t count(DotMatrixRange* range)
{
	size_t c = width(range) / range->size->w;
	return c;
}

int carve(DotMatrixRange* range, Font* fonts, size_t* found)
{
	Font* font;
	DotMatrixPot pot;
	DOTMATRIX* dots;
	size_t n = count(range), c, i, j;	 
	if(n <= 0) return 2;
	if((fonts = (Font*)malloc(sizeof(Font)*n)) == NULL) return 3;
	pot.c = range->cpl.c;
	pot.r = range->cpr.r;
	for(c = 0; pot.c < range->cpr.c; ++c, pot.c += range->size->w) {
		font = &fonts[c];
		if(DotMatrix(&pot, &(range->cpr), dm, dots, range->size) != 0) return 4;
		font->map = dots;
		font->size = range->size;
	}
	return 0;
}

int 
DotMatrix(DotMatrixPot* corner, DotMatrixPot* ep, const DOTMATRIX* dm, DOTMATRIX* odm, const FontSize* fs)
{
	odm->r = fs->h;
	odm->c = ep->c - corner->c;
	size_t* rows;
	size_t i, j = 0, m = 0, n, stop = corner->r + fs->h;

	if ((odm->map = (size_t**)malloc(sizeof(size_t*)* odm->r)) == NULL) return 3;

	for (i = corner->r, n = 0; i < stop; ++i, n = 0) {
		if ((rows = (size_t*)malloc(sizeof(size_t)* odm->c)) == NULL) return 3;
		for (j = corner->c; j < ep->c; ++j) rows[n++] = dm->map[i][j];
		odm->map[m++] = rows;
	}
	return 0;
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