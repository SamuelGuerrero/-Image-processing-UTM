#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <string.h>

using namespace std;
using namespace cv;

// Programa que junta los 3 canales en una imagen a color
tuple<string, string> getImageProperties(string pathName);

int main(int argc, char **argv)
{
    int i, j;
    if (argc != 4)
    {
        printf("Pasar 3 imágenes en 3 canales B G R\n");
        return -1;
    }

    cv::Mat B = cv::imread(argv[1]);
    cv::Mat G = cv::imread(argv[2]);
    cv::Mat R = cv::imread(argv[3]);

    cv::Mat OriginalImage(B.rows, B.cols, CV_8UC3);

    int nf = B.rows, nc = B.cols, canales = B.channels();

    for (j = 0; j < nf; j++)
    {
        uchar *BGR = OriginalImage.ptr<uchar>(j);
        uchar *BChannel = B.ptr<uchar>(j);
        uchar *GChannel = G.ptr<uchar>(j);
        uchar *RChannel = R.ptr<uchar>(j);
        for (i = 0; i < nc * canales; i += canales)
        {
            *(BGR + i) = *(BChannel + i);
            *(BGR + i + 1) = *(GChannel + i + 1);
            *(BGR + i + 2) = *(RChannel + i + 2);
        }
    }

    string pathName = argv[1];
    auto [newPathName, format] = getImageProperties(pathName);

    string RGBImage = newPathName + "BGR" + format;

    cv::imwrite(RGBImage, OriginalImage);

    return 0;
}

tuple<string, string> getImageProperties(string pathName)
{
    string imageName = "", imageFormat = "";
    int i;
    for (i = 0; pathName[i] != '.'; i++)
    {
        imageName += pathName[i];
    }
    imageName.pop_back();

    for (; pathName[i] != '\0'; i++)
    {
        imageFormat += pathName[i];
    }

    return {imageName, imageFormat};
}
