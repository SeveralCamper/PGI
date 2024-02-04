#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graphics.h"
#pragma comment(lib, "graphics.lib")

#include "bmp_displayFile.h"

void displayBMP(BMP_File* pBmpFile, int colorMode)
{
    for (int y = 0; y < pBmpFile->m_dibHeader.m_height; y++) {
        for (int x = 0; x < pBmpFile->m_dibHeader.m_width; x++) {
            int index = y * pBmpFile->m_dibHeader.m_width + x;
            unsigned char pixelValue = pBmpFile->m_pData[index];

            // В зависимости от режима цветности, преобразуем значение пикселя
			if (colorMode == 1)
			{
                // True Color режим
                int r = pBmpFile->m_palette[pixelValue][0];
                int g = pBmpFile->m_palette[pixelValue][1];
                int b = pBmpFile->m_palette[pixelValue][2];

                // Пример: выводим True Color цвет в консоль
                printf("\x1b[48;2;%d;%d;%dm  \x1b[0m", r, g, b);
            }
            else if (colorMode == 2)
			{
                int color = pixelValue % 16;
                putpixel(x, y, color);
            }
			else if (colorMode == 3)
			{
                int color = pixelValue % 256;
                putpixel(x, y, color);
            }
        }
        printf("\n");
    }
}
