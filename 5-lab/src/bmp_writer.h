#ifndef BMP_WRITER_H__
#define BMP_WRITER_H__

#include "bmp_reader.h"

void SwapRGB(unsigned char* data, int size, int bytesPerPixel);
void TurnIntoBlackWhite(BMP_File* pBmpFile);
void WriteBmpRowByRow(FILE* fp, BMP_File* pBmpFile);
void SaveBmpFile(char* pFileName, BMP_File* pBmpFile);

#endif // BMP_WRITER_H__