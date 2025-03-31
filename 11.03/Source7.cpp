#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // ��������� ���������
    VideoCapture cap("C:\\Users\\���������\\Downloads\\video.mp4");
    if (!cap.isOpened()) {
        cout << "������: �� ������� ������� ���������!" << endl;
        return -1;
    }

    Mat frame, gray, blurred, edges, contourImg;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    while (true) {
        cap >> frame; // ������ ����
        if (frame.empty()) break; // ���� ����� ����������� � �������

        // ����� ����� ��� ��������� ��������
        contourImg = frame.clone();

        // �������������� � ������� ������ � ��������� ��������
        cvtColor(frame, gray, COLOR_BGR2GRAY);
        GaussianBlur(gray, blurred, Size(5, 5), 0);  // ��������
        Canny(blurred, edges, 50, 150);  // ��������� ������

        // ����� ��������
        findContours(edges, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        // ������ ������� �� �������� ����� (contourImg)
        drawContours(contourImg, contours, -1, Scalar(0, 255, 0), 2); // ������� �������

        // ����������� ����� � ��������� � ���������� ���� � ����������
        imshow("Video Tracking", contourImg); // ���� � ����� � ������������� ���������
        imshow("Edges", edges); // ���� � ������������ ������������ (�������)

        // ����� ��� ������� 'q'
        if (waitKey(30) == 'q') break;
    }

    cap.release();
    destroyAllWindows();
    return 0;
}
