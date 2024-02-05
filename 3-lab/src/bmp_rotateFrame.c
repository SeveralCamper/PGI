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
        }
    }

    pBmpFile->m_dibHeader.m_width = newWidth;
    pBmpFile->m_dibHeader.m_height = newHeight;

    free(pBmpFile->m_pData);
    pBmpFile->m_pData = newData;
}