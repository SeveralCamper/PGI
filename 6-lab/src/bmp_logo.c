#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "bmp_logo.h"


void OverlayLogoToBmp(BMP_File* originalBmp, BMP_File* logoBmp, float transparencyCoefficient)
{
    // Проверка наличия данных исходного и логотипа BMP файлов
    if (originalBmp == NULL || logoBmp == NULL)
    {
        printf("ERROR: Invalid BMP file pointers.\n");
        return;
    }

    // Обработка случая, когда originalBmp - не truecolor BMP
    if (originalBmp->m_dibHeader.m_bitsPerPixel != 24 && logoBmp->m_dibHeader.m_bitsPerPixel)
    {
        printf("ERROR: Original BMP file must be a truecolor BMP (24 bits per pixel).\n");
        return;
    }

    // Проверка, что размеры логотипа не превышают размеры исходного файла
    if (logoBmp->m_dibHeader.m_width > originalBmp->m_dibHeader.m_width ||
        logoBmp->m_dibHeader.m_height > originalBmp->m_dibHeader.m_height)
    {
        printf("ERROR: Logo dimensions exceed original BMP dimensions.\n");
        return;
    }

    // Обходим область вставки и обновляем пиксели в оригинальном файле
    for (int y = 0; y < logoBmp->m_dibHeader.m_height; y++)
    {
        for (int x = 0; x < logoBmp->m_dibHeader.m_width; x++)
        {
            int resultX = x;
            int resultY = y;

            int resultIndex = (resultY * originalBmp->m_dibHeader.m_width + resultX) * 3;
            int logoIndex = (y * logoBmp->m_dibHeader.m_width + x) * 3;

			if (logoBmp->m_pData[logoIndex] != 0 && logoBmp->m_pData[logoIndex + 1] != 255 && logoBmp->m_pData[logoIndex + 2] != 0) {
				// Копируем цвета с учетом полупрозрачности
				originalBmp->m_pData[resultIndex] = (unsigned char)(logoBmp->m_pData[logoIndex] * transparencyCoefficient +
																	originalBmp->m_pData[resultIndex]  * (1 - transparencyCoefficient));

				originalBmp->m_pData[resultIndex + 1] = (unsigned char)(logoBmp->m_pData[logoIndex + 1] * transparencyCoefficient +
																		originalBmp->m_pData[resultIndex + 1] * (1 - transparencyCoefficient));

				originalBmp->m_pData[resultIndex + 2] = (unsigned char)(logoBmp->m_pData[logoIndex + 2] * transparencyCoefficient +
																		originalBmp->m_pData[resultIndex + 2] * (1 - transparencyCoefficient));
			}
        }
    }
}

