#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

static void mouseHandler(int event, int x, int y, int flags, void *param);
void FocoMove(Mat image, Mat result, Mat foco);
Mat makeGray(string pathName);

int X, Y;

int radio = 100, width, heigth;
Mat C;
Scalar gris(0, 0, 0);
Scalar blanco(255, 255, 255);
Point P(radio, radio);
Mat Respaldo;
Mat grayImage, grayImageAux;
string pathName;

void funcionUmbral(int umbral, void *userData);

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Pasar 1 imagen a color\n");
        return -1;
    }

    Mat colorImage = imread(argv[1]);
    pathName = argv[1];
    grayImageAux = makeGray(pathName);
    grayImage = grayImageAux.clone();

    C = Mat(radio * 2, radio * 2, CV_8UC3, gris);
    namedWindow("FocoCamera", WINDOW_AUTOSIZE);
    circle(C, P, radio, blanco, FILLED, LINE_8);
    imshow("FocoCamera", C);
    int umbral = 0;

    createTrackbar("Escala", "FocoCamera", &umbral, 6, funcionUmbral, &umbral);

    namedWindow("FocoCamera", WINDOW_AUTOSIZE);
    setMouseCallback("FocoCamera", mouseHandler, &grayImage);
    X = colorImage.cols / 2;
    Y = colorImage.rows / 2;

    width = colorImage.cols, heigth = colorImage.rows;

    int tecla;

    while (true)
    {
        FocoMove(colorImage, grayImage, C);
        imshow("FocoCamera", grayImage);
        if (waitKey(10) == 27)
            break;
    }

    imwrite("Resultado.png", Respaldo);

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
    grayImage = makeGray(pathName);
    X = x, Y = y;
}

void funcionUmbral(int umbral, void *userData)
{
    if ((radio * 2 * (umbral + 1) <= width) && (radio * 2 * (umbral + 1) <= heigth))
    {
        C = Mat(radio * 2 * (umbral + 1), radio * 2 * (umbral + 1), CV_8UC3, gris);
        Point Q(P.x * (umbral + 1), P.y * (umbral + 1));
        circle(C, Q, radio * (umbral + 1), blanco, FILLED, LINE_8);
    }
}

Mat makeGray(string pathName)
{
    Mat colorImage = imread(pathName);
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