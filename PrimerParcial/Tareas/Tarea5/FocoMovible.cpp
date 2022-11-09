#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <string.h>

using namespace std;
using namespace cv;

void FocoMove(Mat image, Mat result, Mat foco, int X, int Y);

int main(int argc, char **argv)
{
    int i, j, tecla;
    if (argc != 3)
    {
        printf("Pasar 2 imágenes\n");
        return -1;
    }

    Mat image = imread(argv[1]);
    Mat foco = imread(argv[2]);

    Mat result(image.rows, image.cols, CV_8UC3, Scalar(0, 0, 0));

    int X = (image.cols / 2) - (foco.cols / 2), Y = image.rows / 2 - (foco.rows / 2);

    FocoMove(image, result, foco, X, Y);

    while (true)
    {

        tecla = waitKey(0);
        if (tecla == 27)
            break;
        if (tecla == 'a')
        {
            X -= 10;
            if (X > 0)
            {
                Mat result(image.rows, image.cols, CV_8UC3, Scalar(0, 0, 0));
                FocoMove(image, result, foco, X, Y);
            }
            else
                X += 10;
        }
        if (tecla == 'w')
        {
            Y -= 10;
            if (Y >= 0)
            {
                Mat result(image.rows, image.cols, CV_8UC3, Scalar(0, 0, 0));
                FocoMove(image, result, foco, X, Y);
            }
            else
                Y += 10;
        }
        if (tecla == 'd')
        {
            X += 10;
            if (X + foco.cols <= image.cols)
            {
                Mat result(image.rows, image.cols, CV_8UC3, Scalar(0, 0, 0));
                FocoMove(image, result, foco, X, Y);
            }
            else
                X -= 10;
        }
        if (tecla == 's')
        {
            Y += 10;
            if (Y + foco.rows <= image.rows)
            {
                Mat result(image.rows, image.cols, CV_8UC3, Scalar(0, 0, 0));
                FocoMove(image, result, foco, X, Y);
            }
            else
                Y -= 10;
        }
    }

    return 0;
}

void FocoMove(Mat image, Mat result, Mat foco, int X, int Y)
{
    int i, j;

    int nf = image.rows, nc = image.cols, canales = image.channels();
    int Fnf = foco.rows, Fnc = foco.cols, Fcanales = foco.channels();

    for (j = 0; j < Fnf; j++)
    {
        uchar *res = result.ptr<uchar>(Y);
        uchar *A = image.ptr<uchar>(Y);
        uchar *Foco = foco.ptr<uchar>(j);

        int iAux = X * 3;
        for (i = 0; i < Fnc * Fcanales; i += Fcanales)
        {
            int pixel = *(Foco + i);
            if (!(pixel == 0))
            {
                *(res + iAux) = *(A + iAux);
                *(res + iAux + 1) = *(A + iAux + 1);
                *(res + iAux + 2) = *(A + iAux + 2);
            }
            iAux += 3;
        }
        Y++;
    }
    namedWindow("Salida", cv::WINDOW_AUTOSIZE);
    imshow("Salida", result);
}