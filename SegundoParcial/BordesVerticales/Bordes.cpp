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

    for (i = 0; i < nc * canales; i += canales)
    {
        for (j = 0; j < nf; j++)
        {
            uchar *A = image.ptr<uchar>(j);
            uchar *res = borde.ptr<uchar>(j);

            *(res + i) = abs((*(A + i)) - (*(A + (i + canales))));
            *(res + i + 1) = abs((*(A + i + 1)) - (*(A + (i + canales) + 1)));
            *(res + i + 2) = abs((*(A + i + 2)) - (*(A + (i + canales) + 2)));
        }
    }

    imwrite("BordesVerticales.png", borde);

    return 0;
}