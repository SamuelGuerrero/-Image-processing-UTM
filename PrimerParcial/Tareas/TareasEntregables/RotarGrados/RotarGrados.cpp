#include <stdio.h>
#include <cstdlib>
#include <cmath>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

float PI = 3.141592653589793;
float convertRadians(int angle);
void funcionUmbral(int umbral, void *userData);

int main(int argc, char **argv)
{
    int i, j;

    if (argc != 2)
    {
        printf("Pasar una imágen\n");
        return -1;
    }

    Mat image = imread(argv[1]);

    int filas = image.rows;
    int columnas = image.cols;
    int nCanales = image.channels();

    int umbral = 0;
    imshow("Rotar", image);

    createTrackbar("Escala", "Rotar", &umbral, 360, funcionUmbral, &umbral);

    while (true)
    {

        int nDF = (filas * abs(cos(convertRadians(umbral))) + columnas * abs(sin(convertRadians(umbral))));
        int nDC = (filas * abs(sin(convertRadians(umbral))) + columnas * abs(cos(convertRadians(umbral))));

        Mat result(nDF, nDC, CV_8UC3, Scalar(0, 0, 0));

        int refX = nDC / 2;
        int refY = nDF / 2;

        int yoffset = refY - filas / 2;
        int xoffset = refX - columnas / 2;

        for (j = 0; j < filas; j++)
        {
            for (i = 0; i < columnas; i++)
            {
                int nuevaY = j - refY + yoffset;
                int nuevaX = i - refX + xoffset;

                int yPrima = refY + (nuevaY * cos(convertRadians(umbral)) - nuevaX * sin(convertRadians(umbral)));
                int xPrima = refX + (nuevaY * sin(convertRadians(umbral)) + nuevaX * cos(convertRadians(umbral)));

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

        imshow("Rotar", result);

        if (waitKey(10) == 27)
            break;
    }

    return 0;
}

float convertRadians(int angle)
{
    return angle * (PI / 180);
}

void funcionUmbral(int umbral, void *userData)
{
}