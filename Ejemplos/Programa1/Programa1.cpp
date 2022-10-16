#include <opencv2/opencv.hpp>
#include <stdio.h>
using namespace cv;

int main(int argc, char **argv)
{
    int i, j;
    if (argc != 2)
    {
        printf("Pasar 1 imagen como parámetro\n");
        return -1;
    }

    cv::Mat A = cv::imread(argv[1]);
    cv::namedWindow("Imagen", cv::WINDOW_AUTOSIZE);

    cv::Mat res(A.rows, A.cols, CV_8UC3);
    printf("%d %d %d\n", res.rows, res.cols, res.channels());

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

    cv::imwrite("InnerspeakerGray.png", res);

    return 0;
}
