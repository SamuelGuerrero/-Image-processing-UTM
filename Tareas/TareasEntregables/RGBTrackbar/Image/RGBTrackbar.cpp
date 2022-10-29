#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <string.h>

using namespace std;
using namespace cv;

void funcionUmbral(int umbral, void *userData);
Mat makeGray(string pathName);
Mat BlueChannel(Mat A);

string pathName;

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Pasar 1 imagen\n");
        return -1;
    }

    Mat image = imread(argv[1]);
    pathName = argv[1];

    int umbral = 0;
    imshow("FocoCamera", image);

    createTrackbar("Escala", "FocoCamera", &umbral, 3, funcionUmbral, &umbral);

    Mat result;

    while (true)
    {

        if (umbral == 0)
        {
            result = image;
            imshow("FocoCamera", result);
        }
        if (umbral == 1)
        {
            result = makeGray(pathName);
            imshow("FocoCamera", result);
        }
        if (umbral == 2)
        {
            result = BlueChannel(image);
            imshow("FocoCamera", result);
        }

        if (waitKey(27) >= 0)
            break;
    }

    return 0;
}

Mat BlueChannel(Mat A)
{
    Mat B(A.rows, A.cols, CV_8UC3);

    int nf = A.rows, nc = A.cols, canales = A.channels();
    int i, j;
    for (j = 0; j < nf; j++)
    {
        uchar *rA = A.ptr<uchar>(j);
        uchar *BImage = B.ptr<uchar>(j);
        for (i = 0; i < nc * canales; i += canales)
        {
            *(BImage + i) = *(rA + i);
        }
    }

    return B;
}

void funcionUmbral(int umbral, void *userData)
{
    printf("%d\n", umbral);
}

Mat makeGray(string pathName)
{
    Mat colorImage = imread(pathName);
    Mat res(colorImage.rows, colorImage.cols, CV_8UC3);

    int i, j;
    int nf = colorImage.rows, nc = colorImage.cols, canales = colorImage.channels();

    for (j = 0; j < nf; j++)
    {
        uchar *rA = colorImage.ptr<uchar>(j);
        uchar *rR = res.ptr<uchar>(j);
        for (i = 0; i < nc * canales; i += canales)
        {
            uchar pR = *(rA + i);
            uchar pG = *(rA + i + 1);
            uchar pB = *(rA + i + 2);
            uchar pP = (pR + pG + pB) / 3;
            *(rR + i) = *(rR + i + 1) = *(rR + i + 2) = pP;
        }
    }

    return res;
}