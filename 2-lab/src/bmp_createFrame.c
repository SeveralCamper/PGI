#include <stdio.h>
#include <stdlib.h>

#include "bmp_createFrame.h"

#include <stdlib.h>
#include <time.h>

void AddRandomBorder(BMP_File* pBmpFile)
{
	srand(time(NULL));

	int rowSize = (pBmpFile->m_dibHeader.m_width * pBmpFile->m_dibHeader.m_bitsPerPixel + 7) / 8;
	int rowPadding = (4 - (rowSize % 4)) % 4; // Дополнительный байт для выравнивания

	unsigned char* newData = (unsigned char*)malloc(rowSize * pBmpFile->m_dibHeader.m_height);

	for (int i = 0; i < pBmpFile->m_dibHeader.m_height; i++)
	{
		for (int j = 0; j < pBmpFile->m_dibHeader.m_width; j++)
		{
			int offset = i * rowSize + j * pBmpFile->m_dibHeader.m_bitsPerPixel / 8;

			if (j < 15 || j >= pBmpFile->m_dibHeader.m_width - 15 || i < 15 || i >= pBmpFile->m_dibHeader.m_height - 15)
			{
				for (int k = 0; k < pBmpFile->m_dibHeader.m_bitsPerPixel / 8; k++)
				{
					newData[offset + k] = rand() % 256;
				}
			}
			else
			{
				for (int k = 0; k < pBmpFile->m_dibHeader.m_bitsPerPixel / 8; k++)
				{
					newData[offset + k] = pBmpFile->m_pData[offset + k];
				}
			}
		}
	}

	free(pBmpFile->m_pData);
	pBmpFile->m_pData = newData;
}

