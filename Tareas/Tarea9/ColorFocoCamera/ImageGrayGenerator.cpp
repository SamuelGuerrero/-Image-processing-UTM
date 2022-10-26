#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <tuple>

using namespace cv;
using namespace std;

tuple<string, string> getImageProperties(string pathName);

int main(int argc, char **argv)
{
    int i, j;
    if (argc != 2)
    {
        printf("Pasar 1 imagen como parámetro\n");
        return -1;
    }

    Mat A = imread(argv[1]);
    namedWindow("Imagen", WINDOW_AUTOSIZE);

    Mat res(A.rows, A.cols, CV_8UC3);

    int nf = A.rows, nc = A.cols, canales = A.channels();

    for (j = 0; j < nf; j++)
    {
        uchar *rA = A.ptr<uchar>(j);
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

    string pathName = argv[1];
    auto [newPathName, format] = getImageProperties(pathName);
    string finalPath = newPathName + "Gray" + format;

    imwrite(finalPath, res);

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

    for (; pathName[i] != '\0'; i++)
    {
        imageFormat += pathName[i];
    }

    return {imageName, imageFormat};
}