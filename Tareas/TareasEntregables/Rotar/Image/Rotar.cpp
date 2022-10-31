#include <opencv2/opencv.hpp>
#include <stdio.h>

using namespace std;
using namespace cv;

Mat Rotar90(Mat image);
Mat Rotar180(Mat image);
Mat Rotar270(Mat image);

void funcionUmbral(int umbral, void *userData);

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Pasar 1 imagen\n");
        return -1;
    }

    Mat image = imread(argv[1]);

    namedWindow("Rotar", WINDOW_AUTOSIZE);
    int umbral = 0;
    createTrackbar("Escala", "Rotar", &umbral, 3, funcionUmbral, &umbral);
    Mat result;

    while (true)
    {
        if (umbral == 0)
            imshow("Rotar", image);
        if (umbral == 1)
        {
            result = Rotar90(image);
            imshow("Rotar", result);
        }
        else if (umbral == 2)
        {
            result = Rotar180(image);
            imshow("Rotar", result);
        }
        else if (umbral == 3)
        {

            result = Rotar270(image);
            imshow("Rotar", result);
        }
        if (waitKey(10) == 27)
            break;
    }

    return 0;
}

Mat Rotar270(Mat image)
{
    Mat result(image.cols, image.rows, CV_8UC3, Scalar(0, 0, 0));

    int nf = image.rows, nc = image.cols, canales = image.channels();
    int iAux = (nc - 1) * 3;
    for (int j = 0; j < nc; j++)
    {
        uchar *res = result.ptr<uchar>(j);
        int jAux = 0;
        for (int i = 0; i < nc * canales; i += canales)
        {
            if (jAux == nf)
                break;
            uchar *A = image.ptr<uchar>(jAux);

            *(res + i) = *(A + iAux);
            *(res + i + 1) = *(A + iAux + 1);
            *(res + i + 2) = *(A + iAux + 2);

            jAux++;
        }
        iAux -= 3;
    }
    return result;
}

Mat Rotar90(Mat image)
{
    Mat result(image.cols, image.rows, CV_8UC3, Scalar(0, 0, 0));

    int nf = image.rows, nc = image.cols, canales = image.channels();
    int iAux = 0;
    for (int j = 0; j < nc; j++)
    {
        uchar *res = result.ptr<uchar>(j);
        int jAux = nf - 1;
        for (int i = 0; i < nc * canales; i += canales)
        {
            if (jAux <= 0)
                break;
            uchar *A = image.ptr<uchar>(jAux);
            *(res + i) = *(A + iAux);
            *(res + i + 1) = *(A + iAux + 1);
            *(res + i + 2) = *(A + iAux + 2);
            jAux--;
        }
        iAux += 3;
    }
    imwrite("pathName.png", result);
    return result;
}

Mat Rotar180(Mat image)
{
    Mat result(image.rows, image.cols, CV_8UC3, Scalar(0, 0, 0));

    int nf = image.rows, nc = image.cols, canales = image.channels();

    int jAux = nf - 1;

    for (int j = 0; j < nf; j++)
    {
        uchar *res = result.ptr<uchar>(j);
        uchar *A = image.ptr<uchar>(jAux);

        int iAux = (nc - 1) * 3;
        for (int i = 0; i < nc * canales; i += canales)
        {
            *(res + i) = *(A + iAux);
            *(res + i + 1) = *(A + iAux + 1);
            *(res + i + 2) = *(A + iAux + 2);
            iAux -= 3;
        }
        jAux--;
    }
    return result;
}

void funcionUmbral(int umbral, void *userData)
{
}
