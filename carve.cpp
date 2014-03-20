#include "stdafx.h"

int
carve(const DOTMATRIX* dm, FontSize* size, Font* fonts, size_t* found)
{
	DotMatrixPot     pot = { 0, 0 };
	DotMatrixPot    *start = &pot, *prev = &pot;
	DotMatrixRange  *range;
	DotMatrixRange **ranges, **tmp_ranges;
	size_t n_range = 100, c_range = 0;

	if((ranges = (DotMatrixRange**)malloc(sizeof(DotMatrixRange*)*n_range)) == NULL) return 3;

	do {
		prev = start;
		carveRange(dm, start, size, range);
		if(c_range == n_range) {
			tmp_ranges = ranges;
			if((ranges = (DotMatrixRange**)malloc(sizeof(DotMatrixRange*)*n_range*2)) == NULL) return 3;
			

		}
		ranges[c_range++] = range;
	} while(dmpCmp(prev, start));
}

static
int geneRanges()
{

}

static 
int dmpCmp(DotMatrixPot* p1, DotMatrixPot* p2) {
	return (p1->r == p2->r) && (p2->c == p2->c);
}

static DotMatrixRow carveRow(DOTMATRIX* dots)
{
	DotMatrixPot start;
	start.r = start.c = 0;
	while(start.r == dots->r) {
		
	}
}

size_t width(DotMatrixRange* range)
{
	size_t w = range->cpr.c - range->cpl.c;
	if(w < 0) w = 0;
	return w;
}

size_t height(DotMatrixRange* range)
{
	// return range->size->h;
	return 0;
}

size_t count(DotMatrixRange* range)
{
	// size_t c = width(range) / range->size->w;
	// return c;
}

int 
carveRange(const DOTMATRIX* dm, 
	DotMatrixPot* start, 
	FontSize *size,
	DotMatrixRange* range)			/* O - A block of range */
{
	if((range = (DotMatrixRange*)malloc(sizeof(DotMatrixRange))) == NULL) return 3;

	dmpScanLH(start);
	range->cpl = dmpScanLV(start, size);
	range->cpr = dmpScanRV(start, size);
	return 0;
}

int 
carve(DotMatrixRange* range, Font* fonts, size_t* found)
{
	Font* font;
	DotMatrixPot pot;
	DOTMATRIX* dots;
	size_t n = count(range), c, i, j;	 
	if(n <= 0) return 2;
	if((fonts = (Font*)malloc(sizeof(Font)*n)) == NULL) return 3;
	pot.c = range->cpl.c;
	pot.r = range->cpr.r;
	*found = 0;
	for(c = 0; pot.c < range->cpr.c; ++c, pot.c += range->size->w) {
		font = &fonts[c];
		if(DotMatrix(&pot, &(range->cpr), dm, dots) != 0) return 4;
		font->map = dots;
		font->size = range->size;
		++(*found);
	}
	return 0;
}

int 
DotMatrix(DotMatrixPot* corner, DotMatrixPot* bottom, const DOTMATRIX* dm, DOTMATRIX* odm)
{
	odm->r = bottom->r - corner->r;
	odm->c = bottom->c - corner->c;
	size_t* rows;
	size_t i, j = 0, m = 0, n, stop = corner->r + odm->r;

	if ((odm->map = (size_t**)malloc(sizeof(size_t*)* odm->r)) == NULL) return 3;

	for (i = corner->r, n = 0; i < stop; ++i, n = 0) {
		if ((rows = (size_t*)malloc(sizeof(size_t)* odm->c)) == NULL) return 3;
		for (j = corner->c; j < bottom->c; ++j) rows[n++] = dm->map[i][j];
		odm->map[m++] = rows;
	}
	return 0;
}

static void
dmpScanLH(DotMatrixPot* start)	// scan dot matrix to left by horizontal
{
	for (; start->r < dm->r; ++start->r) {
		for (; start->c < dm->c; ++start->c) { if (dm->map[start->r][start->c] == 1)  return; }
		start->c = 0;
	}
}

static DotMatrixPot
dmpScanLV(DotMatrixPot* start, const FontSize* size)
{
	DotMatrixPot pot;
	size_t i, j = start->c, stop = size->h + start->r;
	if (dm->r < stop || dm->c == start->c) return ;

	for (i = start->r; start->r < stop; ++i) {
		if (j == 0) break;
		if (dm->map[i][j] == 1) { --j; i = start->r; }
	}
	start->c = ++j;
	pot.r = start->r;
	pot.c = start->c;
	return pot;
}

static DotMatrixPot
dmpScanRV(const DotMatrixPot* start, const FontSize* size)
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