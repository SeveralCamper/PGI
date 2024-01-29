#pragma pack (1)
#include <stdio.h>
struct  head {
        unsigned short id;
        unsigned long  f_size;
        unsigned short rez1, rez2;
        unsigned long  bm_offset;
        unsigned long  h_size;
        long  width;
        long  height;
        unsigned short planes;
        unsigned short bitperpixel;
        unsigned long  compression;
        unsigned long  sizeimage;
        unsigned long  hres;
        unsigned long  vres;
        unsigned long  clrused;
        unsigned long  clrimp;
} head_file;

main() {
  int i,n,s=0;
  unsigned char buffer[1024];
  unsigned char palitra[256][4];
  FILE *f1;
  f1=fopen("cat256.bmp","rb");
  fread(&head_file,sizeof(head_file),1,f1);
  
  printf("sizeof(head_file)=%d id = %c%c fsize=%d\n",sizeof(head_file),       head_file.id&255, head_file.id>>8,head_file.f_size);
  printf("width = %d height = %d bitperpixel = %d clrused = %d \n",head_file.width, head_file.height,  head_file.bitperpixel, head_file.clrused);
  s=sizeof(head_file);
  for(i=0; i<(head_file.bm_offset-sizeof(head_file))/4; i++) {
    s+=4;
    fread(palitra[i],4,1,f1);
  }
  do {
    n=fread(buffer,1,1024,f1);
    s+=n;
  } while(n==1024);
  printf("fsize=%d",s);
  fclose(f1);
}
