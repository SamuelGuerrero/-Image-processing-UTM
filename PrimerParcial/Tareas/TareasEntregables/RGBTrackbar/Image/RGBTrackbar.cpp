#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <string.h>

using namespace std;
using namespace cv;

void funcionUmbral(int umbral, void *userData);
Mat MakeGray(string pathName);

Mat BlueChannel(string pathName);
Mat GreenChannel(string pathName);
Mat RedChannel(string pathName);

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
    imshow("RGBTrackbar", image);

    createTrackbar("Escala", "RGBTrackbar", &umbral, 4, funcionUmbral, &umbral);

    Mat result;

    while (true)
    {

        if (umbral == 0)
            result = image;
        if (umbral == 1)
            result = MakeGray(pathName);
        if (umbral == 2)
            result = BlueChannel(pathName);
        if (umbral == 3)
            result = GreenChannel(pathName);
        if (umbral == 4)
            result = RedChannel(pathName);
        imshow("RGBTrackbar", result);

        if (waitKey(10) == 27)
            break;
    }

    return 0;
}

Mat BlueChannel(string pathName)
{
    Mat A = imread(pathName);
    Mat B(A.rows, A.cols, CV_8UC3, Scalar(0, 0, 0));

    int nf = A.rows, nc = A.cols, canales = A.channels();
    int i, j;
    for (j = 0; j < nf; j++)
    {
        uchar *rA = A.ptr<uchar>(j);
        uchar *BImage = B.ptr<uchar>(j);
        for (i = 0; i < nc * canales; i += canales)
            *(BImage + i) = *(rA + i);
    }

    return B;
}

Mat GreenChannel(string pathName)
{
    Mat A = imread(pathName);
    Mat G(A.rows, A.cols, CV_8UC3, Scalar(0, 0, 0));

    int nf = A.rows, nc = A.cols, canales = A.channels();
    int i, j;
    for (j = 0; j < nf; j++)
    {
        uchar *rA = A.ptr<uchar>(j);
        uchar *GImage = G.ptr<uchar>(j);
        for (i = 0; i < nc * canales; i += canales)
            *(GImage + i + 1) = *(rA + i + 1);
    }

    return G;
}

Mat RedChannel(string pathName)
{
    Mat A = imread(pathName);
    Mat R(A.rows, A.cols, CV_8UC3, Scalar(0, 0, 0));

    int nf = A.rows, nc = A.cols, canales = A.channels();
    int i, j;
    for (j = 0; j < nf; j++)
    {
        uchar *rA = A.ptr<uchar>(j);
        uchar *RImage = R.ptr<uchar>(j);
        for (i = 0; i < nc * canales; i += canales)
            *(RImage + i + 2) = *(rA + i + 2);
    }

    return R;
}

void funcionUmbral(int umbral, void *userData)
{
    printf("%d\n", umbral);
}

Mat MakeGray(string pathName)
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