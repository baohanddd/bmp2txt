#ifndef __CARVE__
#define __CARVE__

static DOTMATRIX* dm;
static FontSize size;

static inline FontSize fsInit(int size) { 
	FontSize fs;
	fs.h = fs.w = size;
	return fs;
}

typedef struct {
	size_t r;	// row
	size_t c;	// col
} DotMatrixPot;

typedef struct {
	DotMatrixPot top;
	DotMatrixPot bottom;
} DotMatrixRow;

typedef struct {
	DotMatrixPot cpl;	// top left
	DotMatrixPot cpr;	// bottom right
	FontSize* size;
} DotMatrixRange;

typedef struct {
	DOTMATRIX* map;
	FontSize* size;
	//int (*toFile)(TCHAR*);
	//wchar_t (*getc)(FontLib*);
	char* (*bin2hex)(DotMatrixPot*);
} Font;

int								/* O - How many ranges be found */
carve(DOTMATRIX* dm,			/* I - dots */
	DotMatrixRanges* ranges);	/* O - ranges */

int								/* O - How many fonts be found */
carve(DotMatrixRange* range,    /* I - a block of text range */
	Font* fonts);				/* O - fonts */

static DotMatrixRange			/* O - return range */
range(DOTMATRIX* dm,			/* I - dots */
	FontSize* size);			/* I - font size */

#endif