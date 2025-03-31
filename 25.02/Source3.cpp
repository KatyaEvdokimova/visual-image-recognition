#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    Mat image = imread("C:/Users/Екатерина/Documents/kot.jpg");
    if (image.empty()) {
        cerr << "Ошибка: Не удалось загрузить изображение!" << endl;
        return -1;
    }

    // Создание матриц для хранения преобразованных изображений
    Mat imageHSV, imageLab, imageYUV, imageXYZ, imageGray;

    // Преобразование в различные цветовые пространства
    cvtColor(image, imageHSV, COLOR_BGR2HSV);
    cvtColor(image, imageLab, COLOR_BGR2Lab);
    cvtColor(image, imageYUV, COLOR_BGR2YUV);
    cvtColor(image, imageXYZ, COLOR_BGR2XYZ);
    cvtColor(image, imageGray, COLOR_BGR2GRAY);

    // Отображение изображений
    imshow("Original Image", image);
    imshow("HSV Image", imageHSV);
    imshow("Lab Image", imageLab);
    imshow("YUV Image", imageYUV);
    imshow("XYZ Image", imageXYZ);
    imshow("Gray Image", imageGray);

    // Ожидание нажатия клавиши
    waitKey(0);
    return 0;
}
