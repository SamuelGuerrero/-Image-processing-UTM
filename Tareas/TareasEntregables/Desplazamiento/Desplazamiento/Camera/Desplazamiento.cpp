#include <opencv2/opencv.hpp>
#include <stdio.h>

using namespace std;
using namespace cv;

Mat Desplazar(Mat image, int umbralX, int umbralY);
void funcionUmbral(int umbral, void *userData);

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

    namedWindow("Desplazamiento", WINDOW_AUTOSIZE);

    cap.read(image);
    imshow("Desplazamiento", image);

    int nf = image.rows, nc = image.cols, canales = image.channels();

    int spaceX = nc * 2, spaceY = nf * 2;

    int umbralX = spaceX / 2, umbralY = spaceY / 2;

    createTrackbar("EscalaX", "Desplazamiento", &umbralX, spaceX, funcionUmbral, &umbralX);
    createTrackbar("EscalaY", "Desplazamiento", &umbralY, spaceY, funcionUmbral, &umbralY);

    while (true)
    {
        cap.read(image);

        if (image.empty())
        {
            printf("Error al obtener imagen\n");
            break;
        }

        Mat result = Desplazar(image, umbralX, umbralY);
        imshow("Desplazamiento", result);

        if (waitKey(10) == 27)
            break;
    }

    return 0;
}

Mat Desplazar(Mat image, int umbralX, int umbralY)
{
    umbralX = umbralX - image.cols;
    umbralY = umbralY - image.rows;

    int nf = image.rows, nc = image.cols, canales = image.channels();
    Mat result(image.rows, image.cols, CV_8UC3, Scalar(0, 0, 0));

    int i, j;

    for (j = 0; j < nf; j++)
    {
        int moveOrigin = j + umbralY, moveDestiny = j;

        if (umbralY < 0)
        {
            moveOrigin = j;
            moveDestiny = j - umbralY;
            if ((j - umbralY) >= nf)
                break;
        }

        if (moveOrigin >= nf)
            break;

        uchar *res = result.ptr<uchar>(moveOrigin);
        uchar *A = image.ptr<uchar>(moveDestiny);

        for (i = 0; i < nc * canales; i += canales)
        {
            if (umbralX > 0)
            {
                if ((i + 1 + umbralX * 3) > nc * canales)
                    break;
                *(res + i + umbralX * 3) = *(A + i);
                *(res + i + 1 + umbralX * 3) = *(A + i + 1);
                *(res + i + 2 + umbralX * 3) = *(A + i + 2);
            }
            else
            {
                int auxOffset = -1 * umbralX;
                if ((i + 1 + auxOffset * 3) > nc * canales)
                    break;
                *(res + i) = *(A + i + auxOffset * 3);
                *(res + i + 1) = *(A + i + 1 + auxOffset * 3);
                *(res + i + 2) = *(A + i + 2 + auxOffset * 3);
            }
        }
    }

    return result;
}

void funcionUmbral(int umbral, void *userData)
{
}