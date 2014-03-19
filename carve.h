#ifndef __CARVE__
#define __CARVE__

typedef struct {
	DotMatrixPot top;
	DotMatrixPot bottom;
} DotMatrixRow;

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