#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

// Функция для обработки части изображения
void processPart(Mat& part, int operationType) {
    switch (operationType) {
    case 0:  // Инверсия цветов
        bitwise_not(part, part);
        break;
    case 1:  // Оттенки серого
        cvtColor(part, part, COLOR_BGR2GRAY);
        cvtColor(part, part, COLOR_GRAY2BGR);  // Возвращаем в BGR для корректного отображения
        break;
    case 2:  // Размытие (Gaussian blur)
        GaussianBlur(part, part, Size(15, 15), 5);
        break;
    case 3:  // Выделение краёв (Canny edge detection)
        Mat edges;
        cvtColor(part, edges, COLOR_BGR2GRAY);
        Canny(edges, edges, 100, 200);
        cvtColor(edges, part, COLOR_GRAY2BGR);
        break;
    }
}

int main() {
    // Загрузка изображения
    Mat image = imread("C:/Users/Екатерина/Documents/kot.jpg");
    if (image.empty()) {
        cout << "Ошибка: изображение не загружено!" << endl;
        return -1;
    }

    // Проверка, можно ли разделить на 4 квадрата
    if (image.rows != image.cols || image.rows % 2 != 0) {
        cout << "Изображение должно быть квадратным и с чётными размерами!" << endl;
        return -1;
    }

    // Разделение на 4 квадрата
    int halfSize = image.rows / 2;
    vector<Mat> parts = {
        image(Rect(0, 0, halfSize, halfSize)),                     // Верхний левый
        image(Rect(halfSize, 0, halfSize, halfSize)),              // Верхний правый
        image(Rect(0, halfSize, halfSize, halfSize)),               // Нижний левый
        image(Rect(halfSize, halfSize, halfSize, halfSize))         // Нижний правый
    };

    // Обработка каждой части (можно менять операции)
    processPart(parts[0], 0);  // Инверсия
    processPart(parts[1], 1);  // Оттенки серого
    processPart(parts[2], 2);  // Размытие
    processPart(parts[3], 3);  // Выделение краёв

    // Объединение обратно в одно изображение
    Mat topRow, bottomRow, result;
    hconcat(parts[0], parts[1], topRow);
    hconcat(parts[2], parts[3], bottomRow);
    vconcat(topRow, bottomRow, result);

    // Отображение оригинального и обработанного изображений
    imshow("Original Image", image);
    imshow("Processed Image", result);
    waitKey(0);

    return 0;
}
