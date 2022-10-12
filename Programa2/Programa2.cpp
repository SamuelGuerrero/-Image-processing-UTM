#include <opencv2/opencv.hpp>
#include <stdio.h>
using namespace cv;

// Programa que extra 3 imágenes en RGB separados

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

    cv::Mat R(A.rows, A.cols, CV_8UC3);
    cv::Mat G(A.rows, A.cols, CV_8UC3);
    cv::Mat B(A.rows, A.cols, CV_8UC3);

    int nf = A.rows, nc = A.cols, canales = A.channels();

    for (j = 0; j < nf; j++)
    {
        uchar *rA = A.ptr<uchar>(j);
        uchar *RImage = R.ptr<uchar>(j);
        uchar *GImage = G.ptr<uchar>(j);
        uchar *BImage = B.ptr<uchar>(j);
        for (i = 0; i < nc * canales; i += canales)
        {
            *(BImage + i) = *(rA + i);
            *(GImage + i + 1) = *(rA + i + 1);
            *(RImage + i + 2) = *(rA + i + 2);
        }
    }

    cv::imwrite("InnerspeakerRed.png", R);
    cv::imwrite("InnerspeakerGreen.png", G);
    cv::imwrite("InnerspeakerBlue.png", B);

    return 0;
}
