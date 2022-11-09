#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

static void mouseHandler(int event, int x, int y, int flags, void *param);
void FocoMove(Mat image, Mat result, Mat foco);
Mat makeGray( Mat colorImage);

int X, Y;

int radio = 100, width, heigth;
Mat C;
Scalar gris(0, 0, 0);
Scalar amarillo(255, 255, 255);
Point P(radio, radio);

void funcionUmbral(int umbral, void *userData);

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

    Mat A;

    C = Mat(radio * 2, radio * 2, CV_8UC3, gris);
    namedWindow("FocoCamera", WINDOW_AUTOSIZE);
    circle(C, P, radio, amarillo, FILLED, LINE_8);
    imshow("FocoCamera", C);
    int umbral = 0;

    createTrackbar("Escala", "FocoCamera", &umbral, 6, funcionUmbral, &umbral);

    namedWindow("FocoCamera", WINDOW_AUTOSIZE);
    setMouseCallback("FocoCamera", mouseHandler, &A);
    cap.read(A);
    X = A.cols / 2;
    Y = A.rows / 2;

    width = A.cols, heigth = A.rows;

    int tecla;

    while (true)
    {
        cap.read(A);
        if (A.empty())
        {
            printf("Error al obtener imagen\n");
            break;
        }

        Mat result = makeGray(A);
        FocoMove(A, result, C);

        imshow("FocoCamera", result);
        if (waitKey(10) == 27)
            break;
    }
    return 0;
}

Mat makeGray( Mat colorImage)
{
    Mat res(colorImage.rows, colorImage.cols, CV_8UC3);

    int i, j;
    int nf = colorImage.rows, nc = colorImage.cols, canales = colorImage.channels();

    for (j = 0; j < nf; j++)
    {
        uchar *rA = colorImage.ptr<uchar>(j);
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

    return res;
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
    X = x, Y = y;
}

void funcionUmbral(int umbral, void *userData)
{
    if ((radio * 2 * (umbral + 1) <= width) && (radio * 2 * (umbral + 1) <= heigth))
    {
        C = Mat(radio * 2 * (umbral + 1), radio * 2 * (umbral + 1), CV_8UC3, gris);
        Point Q(P.x * (umbral + 1), P.y * (umbral + 1));
        circle(C, Q, radio * (umbral + 1), amarillo, FILLED, LINE_8);
    }
}