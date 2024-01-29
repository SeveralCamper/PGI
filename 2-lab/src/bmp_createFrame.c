#include <stdio.h>
#include <stdlib.h>

#include "bmp_createFrame.h"

#include <stdlib.h>
#include <time.h>

void AddRandomBorder(BMP_File* pBmpFile)
{
	srand(time(NULL));

	int originalWidth = pBmpFile->m_dibHeader.m_width;
	int originalHeight = pBmpFile->m_dibHeader.m_height;

	int rowSize = (originalWidth * pBmpFile->m_dibHeader.m_bitsPerPixel + 7) / 8;
	int rowPadding = (4 - (rowSize % 4)) % 4;

	unsigned char* newData = (unsigned char*)malloc(rowSize * originalHeight);

	for (int i = 0; i < originalHeight; i++)
	{
		for (int j = 0; j < originalWidth; j++)
		{
		int originalOffset = i * rowSize + j * pBmpFile->m_dibHeader.m_bitsPerPixel / 8;
		int newOffset = i * rowSize + j * pBmpFile->m_dibHeader.m_bitsPerPixel / 8;

		if (j < 15 || j >= originalWidth - 15 || i < 15 || i >= originalHeight - 15)
		{
			for (int k = 0; k < pBmpFile->m_dibHeader.m_bitsPerPixel / 8; k++)
			{
				newData[newOffset + k] = rand() % 256;
			}
		}
		else
		{
			for (int k = 0; k < pBmpFile->m_dibHeader.m_bitsPerPixel / 8; k++)
			{
				newData[newOffset + k] = pBmpFile->m_pData[originalOffset + k];
			}
		}
		}
	}

	pBmpFile->m_dibHeader.m_width = originalWidth;
	pBmpFile->m_dibHeader.m_height = originalHeight;

	free(pBmpFile->m_pData);
	pBmpFile->m_pData = newData;
}

