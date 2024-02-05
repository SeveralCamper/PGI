#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bmp_rotateFrame.h"

void RotateImage90Degrees(BMP_File* pBmpFile)
{
    unsigned int newWidth = pBmpFile->m_dibHeader.m_height;
    unsigned int newHeight = pBmpFile->m_dibHeader.m_width;

    unsigned char* newData = (unsigned char*)malloc(newWidth * newHeight * (pBmpFile->m_dibHeader.m_bitsPerPixel / 8));

    for (unsigned int y = 0; y < pBmpFile->m_dibHeader.m_height; y++)
    {
        for (unsigned int x = 0; x < pBmpFile->m_dibHeader.m_width; x++)
        {
            unsigned int srcIndex = (y * pBmpFile->m_dibHeader.m_width + x) * (pBmpFile->m_dibHeader.m_bitsPerPixel / 8); // формируем изначальный индекс изображения
            unsigned int destIndex = ((pBmpFile->m_dibHeader.m_width - 1 - x) * newWidth + y) * (pBmpFile->m_dibHeader.m_bitsPerPixel / 8); // конечный

			if (pBmpFile->m_dibHeader.m_colorsCount != 0 && pBmpFile->m_dibHeader.m_impColorsCount != 0)
			{
				unsigned char tmp = pBmpFile->m_pData[srcIndex];
				pBmpFile->m_pData[srcIndex] = pBmpFile->m_pData[srcIndex + 2];
				pBmpFile->m_pData[srcIndex + 2] = tmp;
			}
			memcpy(&newData[destIndex], &pBmpFile->m_pData[srcIndex], (pBmpFile->m_dibHeader.m_bitsPerPixel / 8));
        }
    }

    pBmpFile->m_dibHeader.m_width = newWidth;
    pBmpFile->m_dibHeader.m_height = newHeight;

    free(pBmpFile->m_pData);
    pBmpFile->m_pData = newData;
}