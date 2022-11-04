#include <stdio.h>
#include <cstdlib>
#include <cmath>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

float PI = 3.141592653589793;
float convertRadians(int angle);

int main(int argc, char **argv)
{
    int i, j;

    if (argc != 3)
    {
        printf("Pasar una imágen y un grado de rotación\n");
        return -1;
    }

    Mat image = imread(argv[1]);
    int grados = stoi(argv[2]);

    int filas = image.rows;
    int columnas = image.cols;
    int nCanales = image.channels();

    int imagenRotada[100][100];

    int nDF = (filas * abs(cos(convertRadians(grados))) + columnas * abs(sin(convertRadians(grados))));
    int nDC = (filas * abs(sin(convertRadians(grados))) + columnas * abs(cos(convertRadians(grados))));

    Mat result(nDF, nDC, CV_8UC3, Scalar(0, 0, 0));

    int refX = nDC / 2;
    int refY = nDF / 2;

    int yoffset = refY - filas / 2;
    int xoffset = refX - columnas / 2;

    for (j = 0; j < filas; j++)
    {
        for (i = 0; i < columnas; i++)
        {
            int nuevaX = i - refX + xoffset;
            int nuevaY = j - refY + yoffset;

            int yPrima = refY + (nuevaY * cos(convertRadians(grados)) - nuevaX * sin(convertRadians(grados)));
            int xPrima = refX + (nuevaY * sin(convertRadians(grados)) + nuevaX * cos(convertRadians(grados)));

            if (yPrima >= 0 && yPrima < nDF && xPrima >= 0 && xPrima < nDC)
            {
                uchar *res = result.ptr<uchar>(yPrima);
                uchar *A = image.ptr<uchar>(j);

                *(res + xPrima * nCanales) = *(A + i * nCanales);
                *(res + xPrima * nCanales + 1) = *(A + i * nCanales + 1);
                *(res + xPrima * nCanales + 2) = *(A + i * nCanales + 2);
            }
        }
    }

    imwrite("result.png", result);
    return 0;
}

float convertRadians(int angle)
{
    return angle * (PI / 180);
}
