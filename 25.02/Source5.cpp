#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // Загружаем изображение
    cv::Mat image = cv::imread("C:/Users/Екатерина/Documents/kot.jpg", cv::IMREAD_COLOR);
    if (image.empty()) {
        std::cerr << "Ошибка: не удалось загрузить изображение!" << std::endl;
        return -1;
    }

    // Преобразуем в градации серого
    cv::Mat gray;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

    // Размытие для уменьшения шумов
    cv::GaussianBlur(gray, gray, cv::Size(5, 5), 1.5);

    // Обнаружение границ с помощью Canny
    cv::Mat edges;
    cv::Canny(gray, edges, 50, 150);

    // Обнаружение линий методом Хафа
    std::vector<cv::Vec2f> lines;
    cv::HoughLines(edges, lines, 1, CV_PI / 180, 100);

    // Рисуем линии на изображении
    for (size_t i = 0; i < lines.size(); i++) {
        float rho = lines[i][0], theta = lines[i][1];
        cv::Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a * rho, y0 = b * rho;
        pt1.x = cvRound(x0 + 1000 * (-b));
        pt1.y = cvRound(y0 + 1000 * (a));
        pt2.x = cvRound(x0 - 1000 * (-b));
        pt2.y = cvRound(y0 - 1000 * (a));
        cv::line(image, pt1, pt2, cv::Scalar(0, 0, 255), 2);
    }

    // Обнаружение кругов методом Хафа
    std::vector<cv::Vec3f> circles;
    cv::HoughCircles(gray, circles, cv::HOUGH_GRADIENT, 1, gray.rows / 16, 100, 30, 10, 100);

    // Рисуем круги на изображении
    for (size_t i = 0; i < circles.size(); i++) {
        cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        cv::circle(image, center, radius, cv::Scalar(0, 255, 0), 2);
    }

    // Отображаем результат
    cv::imshow("Detected Lines and Circles", image);
    cv::waitKey(0);
    return 0;
}