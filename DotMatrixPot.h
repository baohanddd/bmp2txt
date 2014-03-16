#ifndef _DOTMATRIXPOT_
#define _DOTMATRIXPOT_

typedef struct {
	size_t r;
	size_t c;
	DOTMATRIXPOT* (*range)(FONTSIZE*);
} DOTMATRIXPOT;

typedef struct {
	DOTMATRIXPOT tl;	// top left
	DOTMATRIXPOT br;	// bottom right
} DOTMATRIXRANGE;

DOTMATRIXPOT
matSanH(DOTMATRIX* dm, DOTMATRIXPOT* start);

DOTMATRIXPOT
matSanV(DOTMATRIX* dm, DOTMATRIXPOT* start, FONTSIZE* fs);

DOTMATRIXPOT
reMatSanV(DOTMATRIX* dm, DOTMATRIXPOT* start, FONTSIZE* fs);

DOTMATRIXPOT*
corner(FONTSIZE* size);

static DOTMATRIXRANGE* dmpRange(FONTSIZE* size);

#endif