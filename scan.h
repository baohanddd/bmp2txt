#ifndef _DMSCAN_
#define _DMSCAN_

typedef struct {
	size_t r;
	size_t c;
} DotMatrixPot;

typedef struct {
	DotMatrixRange* ranges;
	size_t length;
	int (*found)(DOTMATRIX*);	// Get some blocks of range from dots
} DotMatrixRanges;

typedef struct {
	DotMatrixPot tl;	// top left
	DotMatrixPot br;	// bottom right
	DotMatrixCarver* carver;	
	int (*width)();
	int (*height)();
	int (*count)(FontSize*);	// how many chars included?
	int (*carve)(Font* /* O - fonts carved */);		
} DotMatrixRange;

typedef struct {
	size_t w;	// width
	size_t h;	// height
} FontSize;

typedef struct {
	DOTMATRIX dots;
	FontSize* size;
	int (*toFile)(TCHAR*);
	wchar_t (*getc)(FontLib*);
} Font;

typedef struct {
	DOTMATRIX* dots;
	FontSize*  size;
	DotMatrixRanges ranges;
	int (*carve)(DotMatrixRanges*);
} DotMatrixCarver;

typedef struct {
	int (*open)(TCHAR* libname);
	wchar_t (*cmp)(const char*);
	int (*close)();
} FontLib;

static DotMatrixRange*
dmpRange(FontSize* size);

static DotMatrixPot
dmpScanLH(DotMatrixPot* start);	// scan dot matrix to left by horizontal

static DotMatrixPot
dmpScanLV(DotMatrixPot* start, FontSize* size);

static DotMatrixPot
dmpScanRV(DotMatrixPot* start, FontSize* size);

DotMatrixCarver*
	dmcInit();

DotMatrixRange*
	dmrInit();

static int
	dmrWidth();
static int
	dmrHeight();
static int 
	dmrCount(FontSize*);	// how many chars included?
static int 
	dmrCarve(Font*);		/* O - fonts carved */	

#endif