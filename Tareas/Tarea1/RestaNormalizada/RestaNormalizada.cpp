#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <tuple>
#include <algorithm>

using namespace std;
using namespace cv;

uchar RestaNormalizada(uchar A, uchar B, int a, int b);
tuple<int, int, int, int, int, int> getMinMaxValues(Mat image1, Mat image2);

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

    cv::Mat restaNormalizada(image1.rows, image1.cols, CV_8UC3);

    int nf = image1.rows, nc = image1.cols, canales = image1.channels();

    auto [minB, maxB, minG, maxG, minR, maxR] = getMinMaxValues(image1, image2);

    printf("%d, %d, %d, %d, %d, %d, \n", minB, maxB, minG, maxG, minR, maxR);

    for (j = 0; j < nf; j++)
    {
        uchar *res = restaNormalizada.ptr<uchar>(j);
        uchar *A = image1.ptr<uchar>(j);
        uchar *B = image2.ptr<uchar>(j);

        for (i = 0; i < nc * canales; i += canales)
        {
            *(res + i) = RestaNormalizada(*(A + i), *(B + i), minB, maxB);
            *(res + i + 1) = RestaNormalizada(*(A + i + 1), *(B + i + 1), minG, maxG);
            *(res + i + 2) = RestaNormalizada(*(A + i + 2), *(B + i + 2), minR, maxR);
        }
    }

    cv::imwrite("RestaNormalizada.png", restaNormalizada);
    return 0;
}

uchar RestaNormalizada(uchar A, uchar B, int a, int b)
{
    float res;
    res = A - B;
    if (res < 0)
    {
        res = ((res)-a) * 255 / (b - a);
    }
    return res;
}

tuple<int, int, int, int, int, int> getMinMaxValues(Mat image1, Mat image2)
{
    int nf = image1.rows, nc = image1.cols, canales = image1.channels();

    int maxB = 0;
    int minB = 0;

    int maxG = 0;
    int minG = 0;

    int maxR = 0;
    int minR = 0;

    int res;

    for (int j = 0; j < nf; j++)
    {
        uchar *A = image1.ptr<uchar>(j);
        uchar *B = image1.ptr<uchar>(j);

        for (int i = 0; i < nc * canales; i += canales)
        {
            res = *(A + i) - *(B + i);
            if ((res) < minB)
                minB = res;
            if ((res) > maxB)
                maxB = res;

            res = *(A + i + 1) - *(B + i + 1);
            if ((res) < minG)
                minG = res;
            if ((res) > maxG)
                maxG = res;

            res = *(A + i + 2) - *(B + i + 2);
            if ((res) < minR)
                minR = res;
            if ((res) > maxR)
                maxR = res;
        }
    }
    return {minB, maxB, minG, maxG, minR, maxR};
}