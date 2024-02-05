#include <stdio.h>
#include <stdlib.h>

#include "bmp_writer.h"

void WriteBmpRowByRow(FILE* fp, BMP_File* pBmpFile)
{
	// Запись данных пикселей
	int rowSize = pBmpFile->m_dibHeader.m_width * pBmpFile->m_dibHeader.m_bitsPerPixel / 8;
	int rowPadding = (4 - (rowSize % 4)) % 4;
	unsigned char* row = (unsigned char*)malloc(rowSize + rowPadding);
	unsigned char* p = pBmpFile->m_pData + (pBmpFile->m_dibHeader.m_height - 1) * rowSize;

	for (int rowWritten = 0; rowWritten < pBmpFile->m_dibHeader.m_height; rowWritten++)
	{
		memcpy(row, p, rowSize);
		fwrite(row, rowSize + rowPadding, 1, fp);
		p -= rowSize;
	}

	free(row);
}

void SaveBmpFile(char* pFileName, BMP_File* pBmpFile)
{
	FILE* fp = fopen(pFileName, "wb");
	if(!fp)
	{
		printf("ERROR: Can't save the file: \'%s\'\n", pFileName);
		exit(0);
	}

	fwrite(&pBmpFile->m_bmpHeader, sizeof(BMP_Header), 1, fp);
	fwrite(&pBmpFile->m_dibHeader, sizeof(DIB_Header), 1, fp);

	if (pBmpFile->m_dibHeader.m_colorsCount != 0 && pBmpFile->m_dibHeader.m_impColorsCount != 0)
	{
		int dataSize = (pBmpFile->m_bmpHeader.m_pixelOffset - sizeof(pBmpFile->m_bmpHeader) - sizeof(pBmpFile->m_dibHeader)) / 4;
		for(int i = 0; i < dataSize; i++)
		{
			fwrite(pBmpFile->m_palette[i], 4, 1, fp);
		}
	}

	WriteBmpRowByRow(fp, pBmpFile);

	fclose(fp);
}

void TurnIntoBlackWhite(BMP_File* pBmpFile)
{
	if (pBmpFile->m_dibHeader.m_colorsCount != 0 && pBmpFile->m_dibHeader.m_impColorsCount != 0)
	{
		int avgValue = 0;
		int dataSize = (pBmpFile->m_bmpHeader.m_pixelOffset - sizeof(pBmpFile->m_bmpHeader) - sizeof(pBmpFile->m_dibHeader)) / 4;
		for(int i = 0; i < dataSize; i++)
		{
			avgValue = (pBmpFile->m_palette[i][0] + pBmpFile->m_palette[i][1] + pBmpFile->m_palette[i][2]) / 3;
			for (int j = 0; j < 3; j++)
			{
				pBmpFile->m_palette[i][j] = avgValue;
			}
		}
	}	
}