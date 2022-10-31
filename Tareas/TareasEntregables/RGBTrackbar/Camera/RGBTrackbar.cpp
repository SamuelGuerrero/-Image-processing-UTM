#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <string.h>

using namespace std;
using namespace cv;

void funcionUmbral(int umbral, void *userData);

Mat Gray(Mat A);

Mat BlueChannel(Mat A);
Mat GreenChannel(Mat A);
Mat RedChannel(Mat A);

Mat A;
int main(int argc, char **argv)
{
    VideoCapture cap;
    int deviceID = 0;
    int apiID = CAP_ANY;
    cap.open(deviceID, apiID);

    if (!cap.isOpened())
    {
        printf("Error al leer la cámara\n");
        return -1;
    }

    if (argc != 1)
    {
        printf("Pasar 1 imagen\n");
        return -1;
    }
    namedWindow("RGBTrackbar", WINDOW_AUTOSIZE);


    int umbral = 0;
    cap.read(A);

    createTrackbar("Escala", "RGBTrackbar", &umbral, 4, funcionUmbral, &umbral);

    Mat result;

    while (true)
    {
        cap.read(A);

        if (A.empty())
        {
            printf("Error al obtener imagen\n");
            break;
        }

        if (umbral == 0)
            result = A;
        if (umbral == 1)
            result = Gray(A);
        if (umbral == 2)
            result = BlueChannel(A);
        if (umbral == 3)
            result = GreenChannel(A);
        if (umbral == 4)
            result = RedChannel(A);
        imshow("RGBTrackbar", result);

        if (waitKey(10) == 27)
            break;
    }

    return 0;
}

Mat BlueChannel(Mat A)
{
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

Mat GreenChannel(Mat A)
{
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

Mat RedChannel(Mat A)
{
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

Mat Gray(Mat colorImage)
{
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