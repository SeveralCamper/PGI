#ifndef BMP_READER_H__
#define BMP_READER_H__

#pragma pack(1)

typedef struct BMP_Header
{
	unsigned short m_id;
	unsigned int m_fileSize;
	unsigned int m_reserved;
	unsigned int m_pixelOffset;
} BMP_Header;

typedef struct DIB_Header
{
	unsigned int m_headerSize;
	unsigned int m_width;
	unsigned int m_height;
	unsigned short m_colorPlanes;
	unsigned short m_bitsPerPixel;
	unsigned int m_compressionMethod;
	unsigned int m_dataSize;
	unsigned int m_permissionWidth;
	unsigned int m_permissionHeight;
	unsigned int m_colorsCount;
	unsigned int m_impColorsCount;
} DIB_Header;

typedef struct BMP_File
{
	BMP_Header m_bmpHeader;
	DIB_Header m_dibHeader;
	unsigned char m_palette[256][4];
	unsigned char* m_pData;
} BMP_File;

BMP_File* LoadBmpFile(char* pFileName);
void ReadBmpRowByRow(FILE* fp, BMP_File* pBmpFile);
void PrintMbpPalette(BMP_File* pBmpFile);
void PrintMbpPixels(BMP_File* pBmpFile);
void PrintBmpFile(BMP_File* pBmpFile);
void FreeBmpFile(BMP_File* pBmpFile);

#endif // BMP_READER_H__