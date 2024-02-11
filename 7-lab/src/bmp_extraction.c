#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

#include "bmp_extraction.h"

char generateRandomLetter() {
    return 'A' + rand() % 26;
}

void generateRandomTextFile(const char* fileName, size_t fileSize) {
    FILE* fp = fopen(fileName, "w");
    if (!fp) {
        printf("Error: Cannot create file %s\n", fileName);
        exit(EXIT_FAILURE);
    }

    srand((unsigned int)time(NULL));

    for (size_t i = 0; i < fileSize; ++i) {
        fputc(generateRandomLetter(), fp);
    }

    fclose(fp);
}

void generateRandomTextFileBasedOnBmp(const BMP_File* pBmpFile, double percentage) {
    size_t fileSize = (size_t)(pBmpFile->m_bmpHeader.m_fileSize * percentage);

    char fileName[100];
    sprintf(fileName, "random_text_%d_percent.txt", (int)(percentage));

    generateRandomTextFile(fileName, fileSize);
}

BMP_File* writeTextToImage(BMP_File* pBmpFile, const char* text, double percentage) {
    size_t imageSize = pBmpFile->m_dibHeader.m_width * pBmpFile->m_dibHeader.m_height * 3;

    if (percentage == 0.1)
	{
        for (size_t i = 0; i < imageSize; ++i)
		{
            pBmpFile->m_pData[i] = (pBmpFile->m_pData[i] & 0xFE) | ( (text[i / 3] & 0x01) << (i % 3));
        }
    }
	else if (percentage == 0.2)
	{
        for (size_t i = 0; i < imageSize; ++i)
		{
            pBmpFile->m_pData[i] = (pBmpFile->m_pData[i] & 0xFC) | ((text[i / 3] & 0x03) << (i % 3));
        }
    }
	else if (percentage == 0.5)
	{
        for (size_t i = 0; i < imageSize; ++i)
		{
            pBmpFile->m_pData[i] = (pBmpFile->m_pData[i] & 0xF0) | ((text[i / 3] & 0x0F) << (i % 3));
        }
    }

    return pBmpFile;
}

char* readTextFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char* buffer = (char*)malloc(file_size + 1);
    if (!buffer) {
        perror("Memory allocation error");
        fclose(file);
        return NULL;
    }

    size_t read_size = fread(buffer, 1, file_size, file);
    if (read_size != (size_t)file_size) {
        perror("Error reading file");
        free(buffer);
        fclose(file);
        return NULL;
    }

    buffer[file_size] = '\0';  // Null-terminate the string

    fclose(file);
    return buffer;
}

char* readTextFromImage(const BMP_File* pBmpFile, double percentage) {
    size_t imageSize = pBmpFile->m_dibHeader.m_width * pBmpFile->m_dibHeader.m_height * 3;
    size_t textLength = (size_t)(imageSize * percentage / 8);

    char* extractedText = (char*)malloc(textLength + 1);  // +1 для завершающего нулевого символа
    if (!extractedText) {
        perror("Memory allocation error");
        return NULL;
    }

    size_t textIndex = 0;
    size_t bitIndex = 0;

    for (size_t i = 0; i < imageSize; ++i) {
        if (bitIndex == 8) {
            ++textIndex;
            bitIndex = 0;
        }

        if (textIndex >= textLength) {
            break;
        }

        if (percentage == 0.1) {
            extractedText[textIndex] |= ((pBmpFile->m_pData[i] & 0x01) << (7 - bitIndex));
        } else if (percentage == 0.2) {
            extractedText[textIndex] |= ((pBmpFile->m_pData[i] & 0x03) << (6 - bitIndex * 2));
        } else if (percentage == 0.5) {
            extractedText[textIndex] |= ((pBmpFile->m_pData[i] & 0x0F) << (4 - bitIndex * 4));
        }

        ++bitIndex;
    }

    extractedText[textLength] = '\0';

    return extractedText;
}

BMP_File* duplicateBmpFile(const BMP_File* source) {
    BMP_File* duplicate = (BMP_File*)malloc(sizeof(BMP_File));

    // Копируем заголовки
    memcpy(&duplicate->m_bmpHeader, &source->m_bmpHeader, sizeof(BMP_Header));
    memcpy(&duplicate->m_dibHeader, &source->m_dibHeader, sizeof(DIB_Header));

    // Копируем палитру
    memcpy(duplicate->m_palette, source->m_palette, sizeof(unsigned char) * 256 * 4);

    // Копируем данные изображения
    size_t imageSize = source->m_dibHeader.m_width * source->m_dibHeader.m_height * 3;
	duplicate->m_pData = (unsigned char*)malloc(imageSize);
	memcpy(duplicate->m_pData, source->m_pData, imageSize);

    return duplicate;
}