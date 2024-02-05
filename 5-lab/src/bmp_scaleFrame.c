#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "bmp_scaleFrame.h"

BMP_File* ScaleBmpFile(BMP_File* originalBmp, float scaleFactor)
{
    if (scaleFactor < 0.1 || scaleFactor > 10.0)
    {
        printf("ERROR: Invalid scale factor. It should be between 0.1 and 10.0\n");
        return NULL;
    }

    BMP_File* scaledBmp = (BMP_File*)malloc(sizeof(BMP_File));

    scaledBmp->m_bmpHeader = originalBmp->m_bmpHeader;
    scaledBmp->m_dibHeader = originalBmp->m_dibHeader;

    // Записываем оригинальную палитру
    if (originalBmp->m_dibHeader.m_bitsPerPixel <= 8)
    {
        int numColors = 1 << originalBmp->m_dibHeader.m_bitsPerPixel;
        for (int i = 0; i < numColors; i++)
        {
            scaledBmp->m_palette[i][0] = originalBmp->m_palette[i][0];
            scaledBmp->m_palette[i][1] = originalBmp->m_palette[i][1];
            scaledBmp->m_palette[i][2] = originalBmp->m_palette[i][2];
            scaledBmp->m_palette[i][3] = originalBmp->m_palette[i][3];
        }
    }

    scaledBmp->m_dibHeader.m_width = (unsigned int)(originalBmp->m_dibHeader.m_width * scaleFactor);
    scaledBmp->m_dibHeader.m_height = (unsigned int)(originalBmp->m_dibHeader.m_height * scaleFactor);

    int newDataSize = scaledBmp->m_dibHeader.m_width * scaledBmp->m_dibHeader.m_height * scaledBmp->m_dibHeader.m_bitsPerPixel / 8;
    scaledBmp->m_pData = (unsigned char*)malloc(newDataSize);

    for (int j = 0; j < scaledBmp->m_dibHeader.m_height; j++)
    {
        for (int i = 0; i < scaledBmp->m_dibHeader.m_width; i++)
        {
            int originalX = (int)(i / scaleFactor);
            int originalY = (int)(j / scaleFactor);

            if (originalX >= 0 && originalX < originalBmp->m_dibHeader.m_width &&
                originalY >= 0 && originalY < originalBmp->m_dibHeader.m_height)
            {
                int originalIndex = originalY * originalBmp->m_dibHeader.m_width + originalX;
                int newIndex = j * scaledBmp->m_dibHeader.m_width + i;

                memcpy(&scaledBmp->m_pData[newIndex * (originalBmp->m_dibHeader.m_bitsPerPixel / 8)],
                       &originalBmp->m_pData[originalIndex * (originalBmp->m_dibHeader.m_bitsPerPixel / 8)],
                       originalBmp->m_dibHeader.m_bitsPerPixel / 8);
            }
        }
    }

    return scaledBmp;
}
