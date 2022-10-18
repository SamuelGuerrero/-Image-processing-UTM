#include <opencv2/opencv.hpp>
#include <stdio.h>

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
    int i, j;
    if (argc != 4)
    {
        printf("Pasar 1 imagen y 2 offsets como parámetros\n");
        return -1;
    }

    cv::Mat image = cv::imread(argv[1]);
    cv::Mat result(image.rows, image.cols, CV_8UC3, cv::Scalar(0));

    int nf = image.rows, nc = image.cols, canales = image.channels();

    int offsetX = stoi(argv[2]), offsetY = stoi(argv[3]);
    int jTemp;

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

    if (offsetY > 0)
        jTemp = nf - offsetY;
    else
        jTemp = -1 * offsetY;

    for (j = 0; j < nf; j++)
    {

        if (jTemp == nf)
            jTemp = 0;

        uchar *res = result.ptr<uchar>(j);
        uchar *A = image.ptr<uchar>(jTemp);

        for (i = 0; i < nc * canales; i += canales)
        {
            if (offsetX > 0)
            {
                *(res + i + offsetX * 3) = *(A + i);
                *(res + i + 1 + offsetX * 3) = *(A + i + 1);
                *(res + i + 2 + offsetX * 3) = *(A + i + 2);
            }
            else
            {
                *(res + i) = *(A + i - offsetX * 3);
                *(res + i + 1) = *(A + i + 1 - offsetX * 3);
                *(res + i + 2) = *(A + i + 2 - offsetX * 3);
            }
        }
        jTemp++;
    }

    cv::imwrite("Offset.png", result);

    return 0;
}
