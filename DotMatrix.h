#ifndef _DOTMATRIX_
#define _DOTMATRIX_

typedef struct {
	size_t** map;
	size_t r;	// number of row
	size_t c;	// number of column
} DOTMATRIX;

typedef struct {
	size_t w;	// width
	size_t h;	// height
} FONTSIZE;

void dmInit(const PALLET* pallet);
int getMatrix();
void freeMatrix();
void dotmat2File(FILE* fp);


#endif