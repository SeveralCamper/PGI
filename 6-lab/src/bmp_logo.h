#ifndef BMP_SCALEFRAME_H__
#define BMP_SCALEFRAME_H__

#include "bmp_reader.h"
#include "bmp_writer.h"

void OverlayLogoToTruecolorBmp(BMP_File* originalBmp, BMP_File* logoBmp, float transparencyCoefficient);

#endif // BMP_SCALEFRAME_H__