#include "stdafx.h"

static const PALLET* pal;
static DOTMATRIX dm;

void
dmInit(const PALLET* pallet)
{
	pal = pallet;
}

int
getMatrix() {
	RGB *color;
	size_t points = pal->info->bmiHeader.biSizeImage / sizeof(RGB);
	size_t rows = points / pal->info->bmiHeader.biWidth;
	size_t i;
	size_t r = 0;
	size_t* row;
	if ((dm.map = (size_t**)malloc(sizeof(size_t*)* rows)) == NULL) return 3;
	dm.r = rows;
	dm.c = pal->info->bmiHeader.biWidth;

	for (size_t m = rows; m != 0; --m) {
		// init row...
		if ((row = (size_t*)malloc(sizeof(size_t)*pal->info->bmiHeader.biWidth)) == NULL) return 3;
		memset(row, 0, sizeof(size_t)* pal->info->bmiHeader.biWidth);

		for (size_t n = 0; n < pal->info->bmiHeader.biWidth; ++n) {
			i = (m - 1) * pal->info->bmiHeader.biWidth + n;
			color = &pal->colors[i];
			if (color->blue == 0) row[n] = 1;
		}
		dm.map[r++] = row;
	}
	return 0;
}

void 
freeMatrix() 
{
	for (size_t r = 0; r < dm.r; ++r) free(dm.map[r]);
	free(dm.map);
}

void 
dotmat2File(FILE* fp) 
{
	for (size_t i = 0; i < dm.r; ++i) {
		for (size_t j = 0; j < dm.c; ++j) fprintf(fp, "%d", dm.map[i][j]);
		fprintf(fp, "\n");
	}
}

DOTMATRIXPOT
cornerTL()	/* Top & Left */
{

}

int
matCarve(DOTMATRIXPOT* corner, DOTMATRIXPOT* ep/* end point */, const DOTMATRIX* dm, DOTMATRIX* odm, const FONTSIZE* fs)
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

int
matCarveByChar(DOTMATRIX* dm, FONTSIZE* size)
{
	DOTMATRIX** fonts;
	DOTMATRIX font;
	size_t num = dm->c / size->w;
	size_t* row;
	size_t i, j, n, ww, p, m = 0; // ww: word width

	if ((fonts = (DOTMATRIX**)malloc(sizeof(DOTMATRIX*)*num)) == NULL) return 3;

	if (num == 0) return 1;
	for (n = 0; n < num; ++n) {
		font.r = size->h;
		font.c = size->w;
		if ((font.map = (size_t**)malloc(sizeof(size_t*)*font.r)) == NULL) return 3;
		for (i = 0, p = 0; i < font.r; ++i, p = 0) {
			if ((row = (size_t*)malloc(sizeof(size_t)*font.c)) == NULL) return 3;
			ww = n * font.c + font.c;
			for (j = n * font.c; j < ww; ++j) row[p++] = dm->map[i][j];
			font.map[m++] = row;
		}
		fonts[n] = &font;
	}
	return 0;
}

int
bin2hex(DOTMATRIX* font)
{
	return 0;
}