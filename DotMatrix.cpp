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

char*
bin2hex(const Font* font)
{
	size_t i, j, size = font->c * font->r;
	char *bin, *hex;
	if ((bin = (char*)malloc(sizeof(char)*size)) == NULL) return ;
	if ((hex = (char*)malloc(sizeof(char)*size/4)) == NULL) return ;

	for (i = 0; i < font->r; ++i)
		for (j = 0; j < font->c; ++j)
			bin[i + j] = font->map[i][j];

	for (i = 0; i < size; i += 4);

	return 0;
}