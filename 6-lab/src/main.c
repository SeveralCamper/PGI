#include <stdlib.h>
#include <stdio.h>

#include "bmp_logo.h"

int main(int argc, char* argv[]) {
	if (argc < 3)
	{
		printf("ERROR: bmpreader <bmp_file>\n");
		return 0;
	}

	BMP_File* pBmpFile = LoadBmpFile(argv[1]);
    if (pBmpFile == NULL)
    {
        FreeBmpFile(pBmpFile);
        return 0;
    }

    BMP_File* overlayBmp = LoadBmpFile(argv[2]);
    if (overlayBmp == NULL)
    {
        FreeBmpFile(overlayBmp);
        return 0;
    }

	PrintBmpFile(pBmpFile);
	printf("\n");
	PrintBmpFile(overlayBmp);
	PrintMbpPalette(pBmpFile);

	float transparencyCoefficient = 0.5;
    OverlayLogoToBmp(pBmpFile, overlayBmp, transparencyCoefficient);

    // Сохранение результата
    SaveBmpFile("result.bmp", pBmpFile);

	FreeBmpFile(pBmpFile);
	FreeBmpFile(overlayBmp);
	return 0;
}