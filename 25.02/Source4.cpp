#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // Загружаем изображение
    Mat image = imread("C:/Users/Екатерина/Documents/kot.jpg");
    if (image.empty()) {
        cerr << "Error: Could not open or find the image!" << endl;
        return -1;
    }

    // Преобразуем в оттенки серого
    Mat grayImage;
    cvtColor(image, grayImage, COLOR_BGR2GRAY);

    // Применяем фильтр Гаусса
    Mat blurredImage;
    GaussianBlur(grayImage, blurredImage, Size(5, 5), 0);

    // Показываем изображения
    imshow("Gray Image", grayImage);
    imshow("Gauss Image", blurredImage);
    waitKey(0);

    return 0;
}
