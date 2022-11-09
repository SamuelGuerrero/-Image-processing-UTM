#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

static void mouseHandler(int event, int x, int y, int flags, void *param);
void FocoMove(Mat image, Mat result, Mat foco);

int X, Y;

int main(int argc, char **argv)
{
    VideoCapture cap;
    int deviceID = 0;
    int apiID = CAP_ANY;
    cap.open(deviceID, apiID);

    if (argc != 2)
    {
        printf("Pasar 1 imagen\n");
        return -1;
    }

    if (!cap.isOpened())
    {
        printf("Error al leer la cámara\n");
        return -1;
    }
    
    Mat foco = imread(argv[1]);
    Mat A;

    namedWindow("FocoCamera", WINDOW_AUTOSIZE);
    setMouseCallback("FocoCamera", mouseHandler, &A);
    cap.read(A);
    X = A.cols / 2;
    Y = A.rows / 2;

    int tecla;

    while (true)
    {
        cap.read(A);
        if (A.empty())
        {
            printf("Error al obtener imagen\n");
            break;
        }
        Mat result(A.rows, A.cols, CV_8UC3, Scalar(0, 0, 0));
        FocoMove(A, result, foco);

        imshow("FocoCamera", result);
        if (waitKey(27) >= 0)
            break;
    }
    return 0;
}

void FocoMove(Mat image, Mat result, Mat foco)
{
    int i, j;

    int nf = image.rows, nc = image.cols, canales = image.channels();
    int Fnf = foco.rows, Fnc = foco.cols, Fcanales = foco.channels();
    int Xaux = X - (Fnc / 2);
    int Yaux = Y - (Fnf / 2);

    if (((X + (Fnc / 2)) > nc))
        Xaux = nc - Fnc;
    if (((X - (Fnc / 2)) < 0))
        Xaux = 0;

    if (((Y + (Fnf / 2)) > nf))
        Yaux = nf - Fnf;

    if (((Y - (Fnf / 2)) < 0))
        Yaux = 0;

    for (j = 0; j < Fnf; j++)
    {
        uchar *res = result.ptr<uchar>(Yaux);
        uchar *A = image.ptr<uchar>(Yaux);
        uchar *Foco = foco.ptr<uchar>(j);

        int iAux = Xaux * 3;
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
        Yaux++;
    }
}

static void mouseHandler(int event, int x, int y, int flags, void *param)
{
    if (event == 4)
        X = x, Y = y;
}