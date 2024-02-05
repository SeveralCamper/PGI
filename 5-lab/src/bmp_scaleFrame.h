#ifndef BMP_SCALEFRAME_H__
#define BMP_SCALEFRAME_H__

#include "bmp_reader.h"
#include "bmp_writer.h"

BMP_File* ScaleBmpFile(BMP_File* originalBmp, float scaleFactor);

#endif // BMP_SCALEFRAME_H__