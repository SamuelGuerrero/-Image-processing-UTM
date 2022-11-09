#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <tuple>
#include <algorithm>

using namespace std;
using namespace cv;

uchar Resta(uchar A, uchar B);

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

    cv::Mat resta(image1.rows, image1.cols, CV_8UC3);

    int nf = image1.rows, nc = image1.cols, canales = image1.channels();

    for (j = 0; j < nf; j++)
    {
        uchar *res = resta.ptr<uchar>(j);
        uchar *A = image1.ptr<uchar>(j);
        uchar *B = image2.ptr<uchar>(j);

        for (i = 0; i < nc * canales; i += canales)
        {
            *(res + i) = Resta(*(A + i), *(B + i));
            *(res + i + 1) = Resta(*(A + i + 1), *(B + i + 1));
            *(res + i + 2) = Resta(*(A + i + 2), *(B + i + 2));
        }
    }

    cv::imwrite("Resta.png", resta);
    return 0;
}

uchar Resta(uchar A, uchar B)
{
    int res;
    res = A - B;
    if (res < 0)
        return abs(res);

    return abs(res);
}