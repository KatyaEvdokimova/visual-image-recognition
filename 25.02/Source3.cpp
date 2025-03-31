#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    Mat image = imread("C:/Users/���������/Documents/kot.jpg");
    if (image.empty()) {
        cerr << "������: �� ������� ��������� �����������!" << endl;
        return -1;
    }

    // �������� ������ ��� �������� ��������������� �����������
    Mat imageHSV, imageLab, imageYUV, imageXYZ, imageGray;

    // �������������� � ��������� �������� ������������
    cvtColor(image, imageHSV, COLOR_BGR2HSV);
    cvtColor(image, imageLab, COLOR_BGR2Lab);
    cvtColor(image, imageYUV, COLOR_BGR2YUV);
    cvtColor(image, imageXYZ, COLOR_BGR2XYZ);
    cvtColor(image, imageGray, COLOR_BGR2GRAY);

    // ����������� �����������
    imshow("Original Image", image);
    imshow("HSV Image", imageHSV);
    imshow("Lab Image", imageLab);
    imshow("YUV Image", imageYUV);
    imshow("XYZ Image", imageXYZ);
    imshow("Gray Image", imageGray);

    // �������� ������� �������
    waitKey(0);
    return 0;
}