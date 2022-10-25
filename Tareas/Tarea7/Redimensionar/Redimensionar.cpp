#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <string.h>

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
    int i, j;

    if (argc != 2)
    {
        printf("Pasar 1 imagen\n");
        return -1;
    }

    Mat image = imread(argv[1]);

    Mat result(image.rows / 2, image.cols / 2, CV_8UC3, Scalar(0, 0, 0));

    int nf = result.rows, nc = result.cols, canales = result.channels();

    int yAux = 0;

    for (j = 0; j < nf; j++)
    {
        uchar *res = result.ptr<uchar>(j);
        uchar *A = image.ptr<uchar>(yAux);

        for (i = 0; i < nc * canales; i += canales)
        {
            *(res + i) = *(A + (i * 2));
            *(res + i + 1) = *(A + (i * 2) + 1);
            *(res + i + 2) = *(A + (i * 2) + 2);
        }
        yAux += 2;
    }

    imwrite("Redim.png", result);

    return 0;
}
