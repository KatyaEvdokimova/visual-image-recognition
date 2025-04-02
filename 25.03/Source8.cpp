#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/stitching.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    Mat img1 = imread("C:\\Users\\Екатерина\\Downloads\\image1.png");
    Mat img2 = imread("C:\\Users\\Екатерина\\Downloads\\image2.png");
    if (img1.empty() || img2.empty()) {
        cerr << "Ошибка загрузки изображений" << endl;
        return -1;
    }

    // Обнаружение ключевых точек и вычисление дескрипторов с помощью ORB
    Ptr<ORB> orb = ORB::create();
    vector<KeyPoint> keypoints1, keypoints2;
    Mat descriptors1, descriptors2;
    orb->detectAndCompute(img1, noArray(), keypoints1, descriptors1);
    orb->detectAndCompute(img2, noArray(), keypoints2, descriptors2);

  
    BFMatcher matcher(NORM_HAMMING);
    vector<DMatch> matches;
    matcher.match(descriptors1, descriptors2, matches);

  
    sort(matches.begin(), matches.end(), [](const DMatch& a, const DMatch& b) {
        return a.distance < b.distance;
        });
    matches.resize(50); 

    vector<Point2f> points1, points2;
    for (const auto& match : matches) {
        points1.push_back(keypoints1[match.queryIdx].pt);
        points2.push_back(keypoints2[match.trainIdx].pt);
    }

 
    Mat H = findHomography(points2, points1, RANSAC);

    // Применение перспективного преобразования
    Mat result;
    warpPerspective(img2, result, H, Size(img1.cols + img2.cols, img1.rows));
    Mat roi(result, Rect(0, 0, img1.cols, img1.rows));
    img1.copyTo(roi);

    // Отображение и сохранение результата
    imshow("Panorama", result);
    imwrite("panorama.jpg", result);

    // Отображение соответствий ключевых точек
    Mat img_matches;
    drawMatches(img1, keypoints1, img2, keypoints2, matches, img_matches);
    imshow("Matches", img_matches);

    waitKey(0);

    return 0;
}
