#ifndef BMP_WRITER_H__
#define BMP_WRITER_H__

#include "bmp_reader.h"

void TurnIntoBlackWhite(BMP_File* pBmpFile);
void WriteBmpRowByRow(FILE* fp, BMP_File* pBmpFile);
void SaveBmpFile(char* pFileName, BMP_File* pBmpFile);

#endif // BMP_WRITER_H__