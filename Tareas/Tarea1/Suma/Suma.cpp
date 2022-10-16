#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <tuple>
#include <algorithm>

using namespace std;
using namespace cv;

uchar Suma(uchar A, uchar B, uchar maxValue);
tuple<uchar, uchar, uchar> getMaxValues(Mat image1, Mat image2);
tuple<string, string> getImageProperties(string pathName);

int main(int argc, char **argv)
{
    int i, j;
    if (argc != 3)
    {
        printf("Pasar 2 imagen como parámetro\n");
        return -1;
    }

    cv::Mat image1 = cv::imread(argv[1]);
    cv::Mat image2 = cv::imread(argv[2]);

    if ((image1.rows != image2.rows) || (image1.cols != image2.cols) || (image1.channels() != image2.channels()))
    {
        printf("Las imágenes deben ser de las mismas dimensiones y canales");
    }

    cv::Mat suma(image1.rows, image1.cols, CV_8UC3);

    int nf = image1.rows, nc = image1.cols, canales = image1.channels();

    auto [maxB, maxG, maxR] = getMaxValues(image1, image2);

    for (j = 0; j < nf; j++)
    {
        uchar *res = suma.ptr<uchar>(j);
        uchar *A = image1.ptr<uchar>(j);
        uchar *B = image2.ptr<uchar>(j);

        for (i = 0; i < nc * canales; i += canales)
        {
            *(res + i) = Suma(*(A + i), *(B + i), maxB);
            *(res + i + 1) = Suma(*(A + i + 1), *(B + i + 1), maxG);
            *(res + i + 2) = Suma(*(A + i + 2), *(B + i + 2), maxR);
        }
    }

    string pathName1 = argv[1], pathName2 = argv[2];
    auto [newPathName1, format1] = getImageProperties(pathName1);
    auto [newPathName2, format2] = getImageProperties(pathName2);

    string sumaImage = newPathName1 + newPathName2 + format1;

    cv::imwrite(sumaImage, suma);

    return 0;
}

uchar Suma(uchar A, uchar B, uchar maxValue)
{
    int res;
    res = A + B;

    if (res >= 255)
    {
        // printf("%d\n", res);
        // res = (res * 255) / maxValue;
        return 255;
    }
    return res;
}

tuple<uchar, uchar, uchar> getMaxValues(Mat image1, Mat image2)
{
    int nf = image1.rows, nc = image1.cols, canales = image1.channels();

    uchar maxB = 0;
    uchar maxG = 0;
    uchar maxR = 0;

    for (int j = 0; j < nf; j++)
    {
        uchar *A = image1.ptr<uchar>(j);
        uchar *B = image1.ptr<uchar>(j);

        for (int i = 0; i < nc * canales; i += canales)
        {
            if (*(A + i) >= maxB)
                maxB = *(A + i);
            if (*(B + i) >= maxB)
                maxB = *(B + i);

            if (*(A + i + 1) >= maxG)
                maxG = *(A + i + 1);
            if (*(B + i + 1) >= maxG)
                maxG = *(B + i + 1);

            if (*(A + i + 2) >= maxR)
                maxR = *(A + i + 2);
            if (*(B + i + 2) >= maxR)
                maxR = *(B + i + 2);
        }
    }
    return {maxB, maxG, maxR};
}

tuple<string, string> getImageProperties(string pathName)
{
    string imageName = "", imageFormat = "";
    int i;
    for (i = 0; pathName[i] != '.'; i++)
    {
        imageName += pathName[i];
    }

    for (; pathName[i] != '\0'; i++)
    {
        imageFormat += pathName[i];
    }

    return {imageName, imageFormat};
}