#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//�������� �����������
int main() {
    setlocale(LC_ALL, "Ru");
    Mat image = imread("C:/Users/���������/Documents/kot.jpg");
    if (image.empty()) {
        cout << "������ �������� �����������" << endl;
        return -1;
    }
    // �����
    line(image, Point(45, 300), Point(200, 3), Scalar(0, 255, 0), 2);

    // �������������
    rectangle(image, Point(200, 200), Point(400, 300), Scalar(255, 0, 0), 2);

    // ����
    circle(image, Point(250, 300), 50, Scalar(0, 0, 255), 2);

    // ������
    ellipse(image, Point(250, 400), Size(100, 50), 30, 0, 360, Scalar(0, 255, 255), 2);

    // �������������
    vector<Point> points;
    points.push_back(Point(150, 350));
    points.push_back(Point(200, 250));
    points.push_back(Point(300, 250));
    points.push_back(Point(350, 350));
    const Point* pts[] = { points.data() };
    int npts[] = { static_cast<int>(points.size()) };
    polylines(image, pts, npts, 1, true, Scalar(255, 255, 255), 2);

    // �����
    putText(image, "chill girl", Point(180, 470), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 0), 2);

    // ���������� �����������
    imshow("Drawing", image);
    waitKey(0);

    return 0;
}
