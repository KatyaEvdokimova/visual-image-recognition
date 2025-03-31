#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

// ������� ��� ��������� ����� �����������
void processPart(Mat& part, int operationType) {
    switch (operationType) {
    case 0:  // �������� ������
        bitwise_not(part, part);
        break;
    case 1:  // ������� ������
        cvtColor(part, part, COLOR_BGR2GRAY);
        cvtColor(part, part, COLOR_GRAY2BGR);  // ���������� � BGR ��� ����������� �����������
        break;
    case 2:  // �������� (Gaussian blur)
        GaussianBlur(part, part, Size(15, 15), 5);
        break;
    case 3:  // ��������� ���� (Canny edge detection)
        Mat edges;
        cvtColor(part, edges, COLOR_BGR2GRAY);
        Canny(edges, edges, 100, 200);
        cvtColor(edges, part, COLOR_GRAY2BGR);
        break;
    }
}

int main() {
    // �������� �����������
    Mat image = imread("C:/Users/���������/Documents/kot.jpg");
    if (image.empty()) {
        cout << "������: ����������� �� ���������!" << endl;
        return -1;
    }

    // ��������, ����� �� ��������� �� 4 ��������
    if (image.rows != image.cols || image.rows % 2 != 0) {
        cout << "����������� ������ ���� ���������� � � ������� ���������!" << endl;
        return -1;
    }

    // ���������� �� 4 ��������
    int halfSize = image.rows / 2;
    vector<Mat> parts = {
        image(Rect(0, 0, halfSize, halfSize)),                     // ������� �����
        image(Rect(halfSize, 0, halfSize, halfSize)),              // ������� ������
        image(Rect(0, halfSize, halfSize, halfSize)),               // ������ �����
        image(Rect(halfSize, halfSize, halfSize, halfSize))         // ������ ������
    };

    // ��������� ������ ����� (����� ������ ��������)
    processPart(parts[0], 0);  // ��������
    processPart(parts[1], 1);  // ������� ������
    processPart(parts[2], 2);  // ��������
    processPart(parts[3], 3);  // ��������� ����

    // ����������� ������� � ���� �����������
    Mat topRow, bottomRow, result;
    hconcat(parts[0], parts[1], topRow);
    hconcat(parts[2], parts[3], bottomRow);
    vconcat(topRow, bottomRow, result);

    // ����������� ������������� � ������������� �����������
    imshow("Original Image", image);
    imshow("Processed Image", result);
    waitKey(0);

    return 0;
}