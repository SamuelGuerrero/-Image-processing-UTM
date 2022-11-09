#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <string.h>

using namespace std;
using namespace cv;

void funcionUmbral(int umbral, void *userData);
Mat Scala(int umbral, Mat image);
Mat image;

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
        printf("No pasar argumentos\n");
        return -1;
    }

    namedWindow("Scala", WINDOW_AUTOSIZE);

    int umbral = 0;
    cap.read(image);

    imshow("Scala", image);
    createTrackbar("Escala", "Scala", &umbral, 3, funcionUmbral, &umbral);

    Mat result;

    while (true)
    {
        cap.read(image);

        if (image.empty())
        {
            printf("Error al obtener imagen\n");
            break;
        }

        if (umbral == 0)
        {
            imshow("Scala", image);
        }
        else
        {
            Mat result = Scala(umbral, image);
            imshow("Scala", result);
        }

        if (waitKey(27) == 0)
            break;
    }

    return 0;
}

Mat Scala(int umbral, Mat image)
{
    int yAux = 0;
    int i, j;

    Mat result(image.rows / (umbral + 1), image.cols / (umbral + 1), CV_8UC3, Scalar(0, 0, 0));
    int nf = result.rows, nc = result.cols, canales = result.channels();

    for (j = 0; j < nf; j++)
    {
        uchar *res = result.ptr<uchar>(j);
        uchar *A = image.ptr<uchar>(yAux);

        for (i = 0; i < nc * canales; i += canales)
        {
            *(res + i) = *(A + (i * (umbral + 1)));
            *(res + i + 1) = *(A + (i * (umbral + 1)) + 1);
            *(res + i + 2) = *(A + (i * (umbral + 1)) + 2);
        }
        yAux += (umbral + 1);
    }
    return result;
}

void funcionUmbral(int umbral, void *userData)
{
    printf("%d\n", umbral);
}