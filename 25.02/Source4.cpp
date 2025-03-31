#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // ��������� �����������
    Mat image = imread("C:/Users/���������/Documents/kot.jpg");
    if (image.empty()) {
        cerr << "Error: Could not open or find the image!" << endl;
        return -1;
    }

    // ����������� � ������� ������
    Mat grayImage;
    cvtColor(image, grayImage, COLOR_BGR2GRAY);

    // ��������� ������ ������
    Mat blurredImage;
    GaussianBlur(grayImage, blurredImage, Size(5, 5), 0);

    // ���������� �����������
    imshow("Gray Image", grayImage);
    imshow("Gauss Image", blurredImage);
    waitKey(0);

    return 0;
}
