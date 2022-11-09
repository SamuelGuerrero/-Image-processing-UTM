#include <opencv2/opencv.hpp>

int main(int argc, char **argv)
{
    cv::VideoCapture cap;
    int deviceID = 0;
    int apiID = cv::CAP_ANY;
    cap.open(deviceID, apiID);
    if (!cap.isOpened())
    {
        printf("Error al leer la cámara\n");
        return -1;
    }

    cv::Mat A;
    cv::namedWindow("RES", cv::WINDOW_AUTOSIZE);

    int tecla;

    while (true)
    {
        cap.read(A);
        if (A.empty())
        {
            printf("Error al obtener imagen\n");
            break;
        }
        cv::imshow("RES", A);
        if (cv::waitKey(27) >= 0)
            break;
    }
    return 0;
}