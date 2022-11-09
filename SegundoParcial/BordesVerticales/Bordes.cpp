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
    int intensity = 1.2;
    int b, g, r;

    for (i = 0; i < nc * canales; i += canales)
    {
        for (j = 0; j < nf; j++)
        {
            uchar *A = image.ptr<uchar>(j);
            uchar *res = borde.ptr<uchar>(j);

            b = abs((*(A + i)) - (*(A + (i + canales))));
            g = abs((*(A + i + 1)) - (*(A + (i + canales) + 1)));
            r = abs((*(A + i + 2)) - (*(A + (i + canales) + 2)));

            *(res + i) = (b > 100) ? b * intensity : b;
            *(res + i + 1) = (g > 100) ? g * intensity : g;
            *(res + i + 2) = (r > 100) ? r * intensity : r;
        }
    }

    imwrite("BordesVerticales.png", borde);

    return 0;
}