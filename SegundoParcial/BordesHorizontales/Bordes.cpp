#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <string.h>

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Pasar 1 imagen\n");
        return -1;
    }

    Mat image = imread(argv[1]);
    Mat borde(image.rows, image.cols, CV_8UC3, Scalar(0, 0, 0));

    int nf = image.rows, nc = image.cols, canales = image.channels();
    int i, j;

    for (j = 0; j < nf; j++)
    {
        for (i = 0; i < nc * canales; i += canales)
        {
            uchar *A = image.ptr<uchar>(j);
            uchar *B = image.ptr<uchar>(j + 1);

            uchar *res = borde.ptr<uchar>(j);

            *(res + i) = abs((*(A + i)) - (*(B + i)));
            *(res + i + 1) = abs((*(A + i + 1)) - (*(B + i + 1)));
            *(res + i + 2) = abs((*(A + i + 2)) - (*(B + i + 2)));
        }
    }

    imwrite("BordesHorizontales.png", borde);

    return 0;
}