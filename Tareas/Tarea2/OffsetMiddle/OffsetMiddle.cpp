#include <opencv2/opencv.hpp>
#include <stdio.h>

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
    int i, j;
    if (argc != 5)
    {
        printf("Pasar 1 imagen y 2 offsets y el nombre destino como parámetros\n");
        return -1;
    }

    cv::Mat image = cv::imread(argv[1]);
    cv::Mat result(image.rows, image.cols, CV_8UC3, cv::Scalar(0, 0, 0));

    int nf = image.rows, nc = image.cols, canales = image.channels();

    int offsetX = stoi(argv[2]), offsetY = stoi(argv[3]);

    if (abs(offsetX) > nc)
    {
        printf("Pasar un offsetX entre %d %d\n", -nc, nc);
        return -1;
    }
    if (abs(offsetY) > nf)
    {
        printf("Pasar un offsetY entre %d %d\n", -nf, nf);
        return -1;
    }

    for (j = 0; j < nf; j++)
    {
        int moveOrigin = j + offsetY, moveDestiny = j;

        if (offsetY < 0)
        {
            moveOrigin = j;
            moveDestiny = j - offsetY;
            if ((j - offsetY) >= nf)
                break;
        }

        uchar *res = result.ptr<uchar>(moveOrigin);
        uchar *A = image.ptr<uchar>(moveDestiny);

        for (i = 0; i < nc * canales; i += canales)
        {
            if (offsetX > 0)
            {
                if ((i + 1 + offsetX * 3) > nc * canales)
                    break;
                *(res + i + offsetX * 3) = *(A + i);
                *(res + i + 1 + offsetX * 3) = *(A + i + 1);
                *(res + i + 2 + offsetX * 3) = *(A + i + 2);
            }
            else
            {
                int auxOffset = -1 * offsetX;
                if ((i + 1 + auxOffset * 3) > nc * canales)
                    break;
                *(res + i) = *(A + i + auxOffset * 3);
                *(res + i + 1) = *(A + i + 1 + auxOffset * 3);
                *(res + i + 2) = *(A + i + 2 + auxOffset * 3);
            }
        }
    }

    string name = argv[4];
    string pathName = name + ".png";

    cv::imwrite(pathName, result);

    return 0;
}
