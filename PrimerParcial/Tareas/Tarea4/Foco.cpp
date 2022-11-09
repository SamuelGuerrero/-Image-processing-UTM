#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <string.h>

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
    int i, j;

    if (argc != 5)
    {
        printf("Pasar 2 imágenes y 2 coordenadas X Y\n");
        return -1;
    }

    Mat image = imread(argv[1]);
    Mat foco = imread(argv[2]);
    int X = stoi(argv[3]), Y = stoi(argv[4]);

    Mat result(image.rows, image.cols, CV_8UC3, Scalar(0, 0, 0));

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

    imwrite("Foco.png", result);

    return 0;
}

tuple<string, string> getImageProperties(string pathName)
{
    string imageName = "", imageFormat = "";
    int i;
    for (i = 0; pathName[i] != '.'; i++)
    {
        imageName += pathName[i];
    }
    imageName.pop_back();

    for (; pathName[i] != '\0'; i++)
    {
        imageFormat += pathName[i];
    }

    return {imageName, imageFormat};
}
