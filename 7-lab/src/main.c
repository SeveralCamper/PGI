#include <stdlib.h>
#include <stdio.h>

#include "bmp_extraction.h"

int main(int argc, char* argv[]) {
	if (argc < 2)
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

	PrintBmpFile(pBmpFile);
	PrintMbpPalette(pBmpFile);

	// generateRandomTextFileBasedOnBmp(pBmpFile, 10);
	// generateRandomTextFileBasedOnBmp(pBmpFile, 20);
	// generateRandomTextFileBasedOnBmp(pBmpFile, 50);

	char* text_1 = readTextFile("random_text_10_percent.txt");
	char* text_2 = readTextFile("random_text_20_percent.txt");
	char* text_3 = readTextFile("random_text_50_percent.txt");

	BMP_File* resultBmpFile_1 = LoadBmpFile(argv[1]);
	BMP_File* resultBmpFile_2 = LoadBmpFile(argv[1]);
	BMP_File* resultBmpFile_3 = LoadBmpFile(argv[1]);
    if (text_1) 
	{
		SaveBmpFile("result_1bits.bmp", writeTextToImage(resultBmpFile_1, text_1, 0.1));
		char* extractedText_1 = readTextFromImage(resultBmpFile_1, 0.1);
		printf("Extracted Text 1: %s\n", extractedText_1);
		free(extractedText_1);
	}

	if (text_2)
	{
		SaveBmpFile("result_2bits.bmp", writeTextToImage(resultBmpFile_2, text_2, 0.2));
		/* char* extractedText_2 = readTextFromImage(resultBmpFile_2, 0.2);
		printf("Extracted Text 2: %s\n", extractedText_2);
		free(extractedText_2); */
	}

	if (text_3)
	{
		SaveBmpFile("result_4bits.bmp", writeTextToImage(resultBmpFile_3, text_3, 0.5));
		/* char* extractedText_3 = readTextFromImage(resultBmpFile_3, 0.5);
		printf("Extracted Text 3: %s\n", extractedText_3);
		free(extractedText_3); */
	}

	FreeBmpFile(pBmpFile);
	FreeBmpFile(resultBmpFile_1);
	FreeBmpFile(resultBmpFile_2);
	FreeBmpFile(resultBmpFile_3);
	return 0;
}