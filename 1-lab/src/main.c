#include <stdlib.h>
#include <stdio.h>

#include "bmp_reader.h"
#include "bmp_writer.h"

// потерять цветность - усреднить пармметры RGB
// оставить яркость - сумма RGB - такаяже

int main(int argc, char* argv[])
{
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

	printf("Do you want to change pixel map into bw format? (Y/N)");
	gets(input);

	if (input[0] == 'Y' || input[0] == 'y')
	{
		TurnIntoBlackWhite(pBmpFile);
		PrintMbpPalette(pBmpFile);
	}

	printf("Do you want to save the changes? (Y/N)");
	gets(input);

	if (input[0] == 'Y' || input[0] == 'y')
	{
		printf("Write path (filename): ");
		gets(path);

		SaveBmpFile(path, pBmpFile);
	}
	
	FreeBmpFile(pBmpFile);
	return 0;
}