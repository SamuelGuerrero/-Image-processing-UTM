#include <opencv2/opencv.hpp>
#include <stdio.h>

using namespace std;
using namespace cv;

void Rotar90(Mat image, Mat result);
void Rotar180(Mat image, Mat result);
void Rotar270(Mat image, Mat result);

int main(int argc, char **argv)
{
    int rotation;
    if (argc != 3)
    {
        printf("Pasar 1 imagen y un grado de rotación\n");
        return -1;
    }

    Mat image = imread(argv[1]);
    rotation = stoi(argv[2]);

    if (rotation == 90)
    {
        Mat result(image.cols, image.rows, CV_8UC3, Scalar(0, 0, 0));
        Rotar90(image, result);
    }
    else if (rotation == 180)
    {
        Mat result(image.rows, image.cols, CV_8UC3, Scalar(0, 0, 0));
        Rotar180(image, result);
    }
    else if (rotation == 270)
    {
        Mat result(image.cols, image.rows, CV_8UC3, Scalar(0, 0, 0));
        Rotar270(image, result);
    }
    else
    {
        printf("Escoger una opción válida: 90, 180, 270\n");
        return -1;
    }

    return 0;
}

void Rotar270(Mat image, Mat result)
{
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
    imwrite("pathName.png", result);
}

void Rotar90(Mat image, Mat result)
{
    int nf = image.rows, nc = image.cols, canales = image.channels();
    int iAux = 0;
    for (int j = 0; j < nc; j++)
    {
        uchar *res = result.ptr<uchar>(j);
        int jAux = nf - 1;
        for (int i = 0; i < nc * canales; i += canales)
        {
            uchar *A = image.ptr<uchar>(jAux);
            *(res + i) = *(A + iAux);
            *(res + i + 1) = *(A + iAux + 1);
            *(res + i + 2) = *(A + iAux + 2);
            jAux--;
        }
        iAux += 3;
    }
    imwrite("pathName.png", result);
}

void Rotar180(Mat image, Mat result)
{
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
    imwrite("pathName.png", result);
}
