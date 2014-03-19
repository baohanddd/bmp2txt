#include "stdafx.h"

typedef struct {
	DotMatrixPot tl;	// top left
	DotMatrixPot br;	// bottom right
	DotMatrixCarver* carver;	
	int (*width)();
	int (*height)();
	int (*count)(FontSize*);	// how many chars included?
	int (*carve)(Font* /* O - fonts carved */);		
} DotMatrixRange;

DotMatrixRange 
	dmrInit()
{
	DotMatrixRange range;
	range.carver = dmcInit();
}

static int
	dmrWidth();
static int
	dmrHeight();
static int 
	dmrCount(FontSize*);	// how many chars included?
static int 
	dmrCarve(Font*);		/* O - fonts carved */	