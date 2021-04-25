
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
 
int main(int argc, char** argv)
{
	FILE* fp = fopen("C:\\VS-Code-C\\c_2\\1.bmp", "rb");
	if (fp == 0)
		return 0;
	BITMAPFILEHEADER fileHead;
	fread(&fileHead, sizeof(BITMAPFILEHEADER), 1, fp);
	
	BITMAPINFOHEADER infoHead;
	fread(&infoHead, sizeof(BITMAPINFOHEADER), 1, fp);
	int width = infoHead.biWidth;
	int height = infoHead.biHeight;
	int biCount = infoHead.biBitCount;
 
	int lineByte = (biCount*width / 8 + 3) / 4 * 4;
	RGBQUAD* pColorTable;
	pColorTable = new RGBQUAD[256];
	fread(pColorTable, sizeof(RGBQUAD), 256, fp);
 
	unsigned char* pBmpBuf;
	pBmpBuf = new unsigned char[lineByte*height];
	fread(pBmpBuf, lineByte*height, 1, fp);
	fclose(fp);
	
	// 统计概率
	double st[256] = { 0 };
	int st1[256] = { 0 };
	int t;
	for (int i = 0; i < height; ++i){
		for (int j = 0; j < width; ++j){
			t = *(pBmpBuf + i*lineByte + j);
			st[t]++;
		}
	}
	// 计算累加直方图并完成映射
	st[0] = st[0] / (width*height);
	st1[0] = round(double((256 - 1)*st[0]));
	for (int i = 1; i < 256; ++i){
		st[i] = st[i] / (width*height);
		 st[i] = st[i] + st[i - 1];
		st1[i] = int(round(double((256 - 1)*st[i])));
		printf("st[i] = %d, st1[t] = %d\n", st[i], st1[i]);
	}
	
	// 新图像的像素填充
	unsigned char* pBmpBuf1;
	pBmpBuf1 = new unsigned char[lineByte*height];
	for (int i = 0; i < height; ++i){
		for (int j = 0; j < width; ++j){
			t = *(pBmpBuf + i*lineByte + j);
			*(pBmpBuf1 + i*lineByte + j) = st1[t];
		}
	}
 
	FILE* fop = fopen("C:\\VS-Code-C\\c_2\\imhist.bmp", "wb");
	if (fop == 0)
		return 0;
	fwrite(&fileHead, sizeof(BITMAPFILEHEADER), 1, fop);
	fwrite(&infoHead, sizeof(BITMAPINFOHEADER), 1, fop);
	fwrite(pColorTable, sizeof(RGBQUAD), 256, fop);
	fwrite(pBmpBuf1, lineByte*height, 1, fop);
	fclose(fop);
 
	system("pause");
	return 0;
}
