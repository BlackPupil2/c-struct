#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include"ReadBmp.h"

int main()
{
    unsigned char ImgData[3000][3];//将位图信息转为灰度 存储RGB图像的一行像素点
    unsigned char ImgData2[3000];//将灰度图的像素存到一个一维数组中
    int i, j, k;
    FILE * fpBMP, *fpGray;
    BITMAPFILEHEADER *fileHeader;
    BITMAPINFOHEADER *infoHeader;
    RGBQUAD * ipRGB;
    char filename1[20], filename2[20];

    printf("输入图像文件名：");
    scanf("%s", filename1);
    if ((fpBMP = fopen(filename1, "rb")) == NULL)
    {
        printf("打开图片失败");
        exit(0);
    }
    printf("输出图像文件名：");
    scanf("%s", filename2);
    if ((fpGray = fopen(filename2, "wb")) == NULL)
    {
        printf("创建图片失败");
        exit(0);
    }
    
    fileHeader = (BITMAPFILEHEADER *)malloc(sizeof(BITMAPFILEHEADER));
    infoHeader = (BITMAPINFOHEADER *)malloc(sizeof(BITMAPINFOHEADER));
   
    fread(fileHeader, sizeof(BITMAPFILEHEADER), 1, fpBMP);
    fread(infoHeader, sizeof(BITMAPINFOHEADER), 1, fpBMP);
    。
    printf("原始图片每个像素的位数:%d\n" ,infoHeader->biBitCount);
    printf("原始图片每个像素像素数据偏移:%d\n" ,fileHeader->bfOffBits);

    //修改信息头                
    //信息头共有11部分，灰度化时需要修改两部分
    infoHeader->biBitCount = 8;//将24位真彩图转换成8位灰度图
    infoHeader->biSizeImage = ((infoHeader->biWidth * 3 + 3) / 4) * 4 * infoHeader->biHeight;//24Bit真彩图每一行占的实际字节数
    //修改文件头
    //文件头共有5部分，灰度化时需要修改两部分
    fileHeader->bfOffBits = sizeof( BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD);
    fileHeader->bfSize = fileHeader->bfOffBits + infoHeader->biSizeImage;
    printf("修改后的图片每个像素的位数:%d\n" ,infoHeader->biBitCount);
    printf("修改后的图片每个像素数据偏移:%d\n" ,fileHeader->bfOffBits);

    //创建调色版 应为灰度图像的调色板是 R=G=B.而真彩图的三值不相等
    ipRGB = (RGBQUAD *)malloc(256 * sizeof(RGBQUAD));
    for (i = 0; i < 256; i++)
    {
        ipRGB[i].rgbBlue = ipRGB[i].rgbGreen = ipRGB[i].rgbRed = i;
    }
    //读取BMP图像的信息头、文件头、BMP调色板到新建的图片
    fwrite(fileHeader, sizeof(BITMAPFILEHEADER), 1,   fpGray);
    fwrite(infoHeader, sizeof(BITMAPINFOHEADER), 1,   fpGray);
    fwrite(ipRGB     , sizeof(RGBQUAD)         , 256, fpGray);
    //读取RGB图像素并转换为灰度值
    for (i = 0; i < infoHeader->biHeight; i++)//一行一行的扫描
    {
        //24Bit真彩图每一行占的实际字节数：[(biWidth*3+3)/4*4]  故biHeight行每行扫描[(biWidth*3+3)/4*4]次
        for (j = 0; j < (infoHeader->biWidth + 3) / 4 * 4; j++)//写BMP图像的位图数据部分
        {
            for (k = 0; k < 3; k++)
                fread(&ImgData[j][k], 1, 1, fpBMP);////每次只读取一个字节，存入数组
        }
        //修改位图数据部分这部分主要是由原真彩图的rgbRed、rgbGreen、rgbBlue分量值得到灰度图像的灰度值Y，可以用下面公式得到：
        for (j = 0; j < (infoHeader->biWidth + 3) / 4 * 4; j++)  
        {
            ImgData2[j] = (int)((float)ImgData[j][0] * 0.114 +
                                (float)ImgData[j][1] * 0.587 +
                                (float)ImgData[j][2] * 0.299  );
        }
        //将灰度图信息写入
        fwrite(ImgData2, j, 1, fpGray);//按顺序写入BMP图像的各个部分
    }
    free(fileHeader);
    free(infoHeader);
    free(ipRGB);
    fclose(fpBMP);
    fclose(fpGray);
    printf("bmp图片背景去除完成\n");
    return 0;
}