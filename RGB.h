#ifndef _RGB_
#define _RGB_

typedef struct {
	BYTE blue;
	BYTE green;
	BYTE red;
} RGB;

RGB _tchar2RGB(_TCHAR*);

int _hex2int(const TCHAR *value);

int						/* O - 0 = Out of fault tolerant, 1 = Inside of fault tolerant */
color_cmp(RGB *one,		/* I - One color */
	RGB	*other,			/* I - Other color */
	double variation);  /* I - fault tolerant */

#endif