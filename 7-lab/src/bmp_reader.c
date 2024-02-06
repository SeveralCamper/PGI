#include <stdio.h>
#include <stdlib.h>

#include "bmp_reader.h"

void ReadBmpRowByRow(FILE* fp, BMP_File* pBmpFile)
{
	int bytesPerPixel = pBmpFile->m_dibHeader.m_bitsPerPixel / 8;
	int rowSize = bytesPerPixel * pBmpFile->m_dibHeader.m_width;
	int rowPadding = (4 - (rowSize % 4)) % 4; // высчитываем кол-во пикселей для выравнивания
	int rowWritten = 0;
	unsigned char* row = (unsigned char*)malloc(rowSize + rowPadding);
	unsigned char* p = &pBmpFile->m_pData[(pBmpFile->m_dibHeader.m_height - 1) * rowSize]; // адрес места в памяти, которое соответствует последней строке

	fseek(fp, pBmpFile->m_bmpHeader.m_pixelOffset, SEEK_SET);

	while(rowWritten < pBmpFile->m_dibHeader.m_height)
	{
		fread(row, rowSize + rowPadding, 1, fp);
		if (bytesPerPixel == 1)
		{
			for (int i = 0; i < rowSize; i+= bytesPerPixel)
			{
				*p = row[i]; p++;
			}		
		}
		else if (bytesPerPixel == 2)
		{
			for (int i = 0; i < rowSize; i+= bytesPerPixel)
			{
				*p = row[i + 1]; p++;
				*p = row[i]; p++;
			}
		}
		else if (bytesPerPixel == 3)
		{
			for (int i = 0; i < rowSize; i+= bytesPerPixel)
			{
				*p = row[i + 2]; p++;
				*p = row[i + 1]; p++;
				*p = row[i]; p++;
			}
		}
		else if (bytesPerPixel == 4)
		{
			for (int i = 0; i < rowSize; i+= bytesPerPixel)
			{
				*p = row[i + 3]; p++;
				*p = row[i + 2]; p++;
				*p = row[i + 1]; p++;
				*p = row[i]; p++;
			}			
		}
		else
		{
			printf("ERROR: can't work with bytesPerPixel = %d\n", bytesPerPixel);
			exit(0);
		}
		rowWritten++;
		p = p - 2 * rowSize;
	}
	free(row);
}

BMP_File* LoadBmpFile(char* pFileName)
{
	FILE* fp = fopen(pFileName, "rb");
	if(!fp)
	{
		printf("ERROR: Can't load the file: \'%s\'\n", pFileName);
		exit(0);
	}

	BMP_File* pBmpFile = (BMP_File*)malloc(sizeof(BMP_File));
	fread(&pBmpFile->m_bmpHeader, sizeof(BMP_Header), 1, fp);
	fread(&pBmpFile->m_dibHeader, sizeof(DIB_Header), 1, fp);

	if (pBmpFile->m_dibHeader.m_colorsCount != 0 && pBmpFile->m_dibHeader.m_impColorsCount != 0)
	{
		int dataSize = (pBmpFile->m_bmpHeader.m_pixelOffset - sizeof(pBmpFile->m_bmpHeader) - sizeof(pBmpFile->m_dibHeader)) / 4;
		for(int i = 0; i < dataSize; i++)
		{
			fread(pBmpFile->m_palette[i], 4, 1, fp);
		}
	}

	int dataSize = (pBmpFile->m_dibHeader.m_width * pBmpFile->m_dibHeader.m_height * pBmpFile->m_dibHeader.m_bitsPerPixel / 8);
			
	pBmpFile->m_pData = (unsigned char*)malloc(dataSize);
	ReadBmpRowByRow(fp, pBmpFile);

	fclose(fp);

	return pBmpFile;
}

void FreeBmpFile(BMP_File* pBmpFile)
{
	if (pBmpFile)
	{
		printf("File has been freed\n");
		free(pBmpFile);
	}
	else
	{
		printf("ERROR: File has already been freed");
	}
}

void PrintBmpFile(BMP_File* pBmpFile)
{
	printf("BMP Header:\n");
	printf("ID: %d%d   Size: %d   Pixel Offset: %d\n", pBmpFile->m_bmpHeader.m_id,
			pBmpFile->m_bmpHeader.m_id, pBmpFile->m_bmpHeader.m_fileSize, pBmpFile->m_bmpHeader.m_pixelOffset);
	printf("DMI Header:\n\n");
	printf("Header Size: %d   Picture Width: %d   Picture Height: %d\n"
	        "Color Planes: %d   Bits Per Pixel: %d   Compression Method: %d\n"
			"Data Size: %d   Permission Width: %d   Permission Height: %d\n"
			"Colors Count: %d   Imp Colors Count: %d\n", pBmpFile->m_dibHeader.m_headerSize, pBmpFile->m_dibHeader.m_width, pBmpFile->m_dibHeader.m_height,
			pBmpFile->m_dibHeader.m_colorPlanes, pBmpFile->m_dibHeader.m_bitsPerPixel, pBmpFile->m_dibHeader.m_compressionMethod,
			pBmpFile->m_dibHeader.m_dataSize, pBmpFile->m_dibHeader.m_permissionWidth, pBmpFile->m_dibHeader.m_permissionHeight,
			pBmpFile->m_dibHeader.m_colorsCount, pBmpFile->m_dibHeader.m_impColorsCount);
	printf("\n");
}

void PrintMbpPalette(BMP_File* pBmpFile)
{
	printf("BMP Palette:\n");
	if (pBmpFile->m_dibHeader.m_colorsCount != 0 && pBmpFile->m_dibHeader.m_impColorsCount != 0)
	{
		int dataSize = (pBmpFile->m_bmpHeader.m_pixelOffset - sizeof(pBmpFile->m_bmpHeader) - sizeof(pBmpFile->m_dibHeader)) / 4;
		for(int i = 0; i < dataSize; i++)
		{
			printf("%d: ", i);
			for (int j = 0; j < 4; j++)
			{
				printf("%d ", pBmpFile->m_palette[i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}
	else
	{
		printf("ERROR: BMP doesn't have a color palette\n\n");
	}
}

void PrintMbpPixels(BMP_File* pBmpFile)
{
	printf("BMP Pixel Map:\n");
	int dataSize = pBmpFile->m_dibHeader.m_width * pBmpFile->m_dibHeader.m_height * pBmpFile->m_dibHeader.m_bitsPerPixel / 8;
	for (int i = 0; i < dataSize; i++)
	{
		if (i % 16 == 0)
		{
			printf("\n%04x: ", i);
		}
		printf("%02x ", pBmpFile->m_pData[i]);
	}
	printf("\n\n");
}