#include <stdlib.h>
#include <stdio.h>

#include "bmp_scaleFrame.h"

int main(int argc, char* argv[]) {
	if (argc < 2)
	{
		printf("ERROR: bmpreader <bmp_file>\n");
		return 0;
	}

	BMP_File* pBmpFile = LoadBmpFile(argv[1]);
	PrintBmpFile(pBmpFile);
	PrintMbpPalette(pBmpFile);

	printf("Do you want to see pixel map? (Y/N)");

	char input[1];
	char path[20];
	gets(input);
	if (input[0] == 'Y' || input[0] == 'y')
	{
		PrintMbpPixels(pBmpFile);
	}

    // Масштабирование с коэффициентом 2.0
    BMP_File* scaledBmp = ScaleBmpFile(pBmpFile, 2.0);
    if (scaledBmp == NULL)
        return 1;

    // Сохранение масштабированного BMP-файла
    SaveBmpFile("scaled.bmp", scaledBmp);

	printf("Do you want to save the changes? (Y/N)");
	gets(input);

	if (input[0] == 'Y' || input[0] == 'y')
	{
		printf("Write path (filename): ");
		gets(path);

		SaveBmpFile(path, pBmpFile);
	}
	
	FreeBmpFile(pBmpFile);
	FreeBmpFile(scaledBmp);
	return 0;
}