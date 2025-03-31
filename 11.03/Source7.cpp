#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // Открываем видеофайл
    VideoCapture cap("C:\\Users\\Екатерина\\Downloads\\video.mp4");
    if (!cap.isOpened()) {
        cout << "Ошибка: не удалось открыть видеофайл!" << endl;
        return -1;
    }

    Mat frame, gray, blurred, edges, contourImg;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    while (true) {
        cap >> frame; // Читаем кадр
        if (frame.empty()) break; // Если видео закончилось — выходим

        // Копия кадра для рисования контуров
        contourImg = frame.clone();

        // Преобразование в оттенки серого и обработка контуров
        cvtColor(frame, gray, COLOR_BGR2GRAY);
        GaussianBlur(gray, blurred, Size(5, 5), 0);  // Размытие
        Canny(blurred, edges, 50, 150);  // Выделение границ

        // Поиск контуров
        findContours(edges, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        // Рисуем контуры на исходном видео (contourImg)
        drawContours(contourImg, contours, -1, Scalar(0, 255, 0), 2); // Зеленые контуры

        // Отображение видео с контурами и отдельного окна с обработкой
        imshow("Video Tracking", contourImg); // Окно с видео и нарисованными контурами
        imshow("Edges", edges); // Окно с обработанным изображением (границы)

        // Выход при нажатии 'q'
        if (waitKey(30) == 'q') break;
    }

    cap.release();
    destroyAllWindows();
    return 0;
}
