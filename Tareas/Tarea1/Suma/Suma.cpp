#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <tuple>
#include <algorithm>

using namespace std;
using namespace cv;

uchar Suma(uchar A, uchar B, int maxValue);
tuple<int, int, int> getMaxValues(Mat image1, Mat image2);
tuple<string, string> getImageProperties(string pathName);
int SumaNormal(int A, int B);

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

    printf("%d %d %d \n", maxB, maxG, maxR);

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

uchar Suma(uchar A, uchar B, int maxValue)
{
    int res;
    res = A + B;
    /*
        if (res > 255)
        {
            res = res * 255;
            res = res / maxValue;
            //return 255;
        }*/
    res = res * 255;
    res = res / maxValue;
    return res;
}

int SumaNormal(int A, int B)
{
    int res;
    res = A + B;
    return res;
}

tuple<int, int, int> getMaxValues(Mat image1, Mat image2)
{
    int nf = image1.rows, nc = image1.cols, canales = image1.channels();

    int maxB = 0, maxG = 0, maxR = 0;
    int res1, res2, res3;

    for (int j = 0; j < nf; j++)
    {
        uchar *A = image1.ptr<uchar>(j);
        uchar *B = image2.ptr<uchar>(j);

        for (int i = 0; i < nc * canales; i += canales)
        {
            res1 = SumaNormal(*(A + i), *(B + i));
            if (res1 > maxB)
                maxB = res1;

            res2 = SumaNormal(*(A + i + 1), *(B + i + 1));
            if (res2 > maxG)
                maxG = res2;

            res3 = SumaNormal(*(A + i + 2), *(B + i + 2));
            if (res3 > maxR)
                maxR = res3;
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