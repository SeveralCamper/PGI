#ifndef BMP_LOGO_H__
#define BMP_LOGO_H__

#include "bmp_reader.h"
#include "bmp_writer.h"

void OverlayLogoToBmp(BMP_File* originalBmp, BMP_File* logoBmp, float transparencyCoefficient);

#endif // BMP_LOGO_H__