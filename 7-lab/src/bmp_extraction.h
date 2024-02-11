#ifndef BMP_EXTRACTION_H__
#define BMP_EXTRACTION_H__

#include "bmp_reader.h"
#include "bmp_writer.h"


char generateRandomLetter();
char* readTextFile(const char* filename);
BMP_File* duplicateBmpFile(const BMP_File* source);
void generateRandomTextFile(const char* fileName, size_t fileSize);
char* readTextFromImage(const BMP_File* pBmpFile, double percentage);
void generateRandomTextFileBasedOnBmp(const BMP_File* pBmpFile, double percentage);
BMP_File* writeTextToImage(BMP_File* pBmpFile, const char* text, double percentage);

#endif // BMP_EXTRACTION_H__