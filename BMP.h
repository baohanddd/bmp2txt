#ifndef _BMP_
#define _BMP_

typedef struct {
	BITMAPFILEHEADER header;
	BITMAPINFO* info;
	RGB* colors;
} PALLET;

int getPallet(PALLET* pal, FILE* fp);

int getHeader(BITMAPFILEHEADER *header, FILE* fp);

int isBMP(BITMAPFILEHEADER* header);

int getInfo(PALLET* pal, FILE* fp);

int getColors(PALLET* pal, FILE* fp);

int freePallet(PALLET* pal);

int										/* O - 0 = success, -1 = failure */
saveBMP2file(const _TCHAR *filename,	/* I - Filename to save */
		PALLET *pal);					/* I - Bitmap information */

#endif