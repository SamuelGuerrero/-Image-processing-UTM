#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <string.h>

using namespace std;
using namespace cv;

int radio = 100;
Mat C;
Scalar gris(192, 192, 192);
Scalar amarillo(0, 255, 255);
Point P(radio, radio);

void funcionUmbral(int umbral, void *userData);

int main(int argc, char **argv)
{
    int tecla;
    C = Mat(radio * 2, radio * 2, CV_8UC3, gris);
    namedWindow("Foco", WINDOW_AUTOSIZE);
    circle(C, P, radio, amarillo, FILLED, LINE_8);
    imshow("Foco", C);

    int umbral = 0;
    // Nombre de la barra, ventana en la que aparece, su balor inicia,
    // el valor final o lìmite, funcion que va a llamar cuando se mueve la barra, para mandar parámetros
    createTrackbar("Escala", "Foco", &umbral, 6, funcionUmbral, &umbral);

    while (true)
    {
        tecla = waitKey(0);
        if (tecla == 27)
            break;
    }

    return 0;
}

void funcionUmbral(int umbral, void *userData)
{
    C = Mat(radio * 2 * (umbral + 1), radio * 2 * (umbral + 1), CV_8UC3, gris);
    Point Q(P.x * (umbral + 1), P.y * (umbral + 1));
    circle(C, Q, radio * (umbral + 1), amarillo, FILLED, LINE_8);

    imshow("Foco", C);
}